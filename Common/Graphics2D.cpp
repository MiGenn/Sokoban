#include "Graphics2D.h"

#include <cmath>
#include <cassert>
#include <ranges>
#include "WindowDCWrapper.h"

#pragma comment(lib, "Msimg32")
#undef min

Graphics2D::Graphics2D(Window* renderWindow, Vector2f units) NOEXCEPT_WHEN_NDEBUG :
	m_renderWindow(renderWindow)
{
	assert(renderWindow != nullptr);

	m_layersSize = renderWindow->GetSize();
	m_unitSize = CalculateUnitSize(m_layersSize, units);
	AddOrNotNewLayer(m_mainLayerIndex);
	Fill(m_mainLayerIndex, RGB(0, 0, 0));

	AddOrNotNewLayer(1);
}

void Graphics2D::Present()
{
	MergeLayers();

	const Vector2i windowSize{ m_renderWindow->GetSize() };
	if (!StretchBlt(m_renderWindow->GetDeviceContext().Get(), 0, 0, windowSize.x, windowSize.y,
		m_layers[m_mainLayerIndex]->GetMemoryContext(), 0, 0, m_layersSize.x, m_layersSize.y, SRCCOPY))
		throw WINAPI_LAST_EXCEPTION();
}

void Graphics2D::RenderSprite(const SpriteRenderInfo& renderInfo)
{
	int layerIndex{ renderInfo.GetLayerIndex() };
	AddOrNotNewLayer(layerIndex);

	auto layerContext{ m_layers[layerIndex]->GetMemoryContext() };
	MemoryDCWrapper spriteContext(CreateCompatibleDC(layerContext));
	SelectWrapper selectWrapper(spriteContext.Get(), renderInfo.GetBitmap());

	RenderSprite(layerContext, ConvertUnitsToPixels(renderInfo.GetPosition()),
		spriteContext.Get(), renderInfo.GetBoundingBox(), renderInfo.GetSizeInUnits());
}
 
void Graphics2D::RenderRect(int layerIndex, const RECT& rect,
	COLORREF color) NOEXCEPT_WHEN_NDEBUG
{
	assert(layerIndex >= 0);
	AddOrNotNewLayer(layerIndex);

	RenderRect(*m_layers[layerIndex], rect, color);
}

void Graphics2D::RenderLine(int layerIndex, 
	Vector2i startPositionInPixels, Vector2i endPositionInPixels, COLORREF color) NOEXCEPT_WHEN_NDEBUG
{
	static constexpr int penWidth{ 1 };
	static constexpr int penStyle{ PS_SOLID };

	assert(layerIndex >= 0);
	AddOrNotNewLayer(layerIndex);

	auto layerContext{ m_layers[layerIndex]->GetMemoryContext() };
	UniqueGDIOBJ<HPEN> pen(CreatePen(penStyle, penWidth, color));
	SelectWrapper selectWrapper(layerContext, pen.get());

	MoveToEx(layerContext, startPositionInPixels.x, startPositionInPixels.y, NULL);
	LineTo(layerContext, endPositionInPixels.x, endPositionInPixels.y);
}

void Graphics2D::RenderGrid(int layerIndex, COLORREF color) NOEXCEPT_WHEN_NDEBUG
{
	const Vector2i startPositionInPixels{ 0, 0 };
	const Vector2i endPositionInPixels{ m_layersSize };
	const int unitSize{ (int)round(m_unitSize) };

	for (int x{ startPositionInPixels.x }; x < endPositionInPixels.x - 1; x += unitSize)
	{
		RenderLine(layerIndex, { x, startPositionInPixels.y }, { x, endPositionInPixels.y - 1 }, color);
		int secondLineX{ x + unitSize - 1 };
		RenderLine(layerIndex, { secondLineX, startPositionInPixels.y }, { secondLineX, endPositionInPixels.y - 1 }, color);
	}

	for (int y{ startPositionInPixels.y }; y < endPositionInPixels.y - 1; y += unitSize)
	{
		RenderLine(layerIndex, { startPositionInPixels.x, y }, { endPositionInPixels.x - 1, y }, color);
		int secondLineY{ y + unitSize - 1 };
		RenderLine(layerIndex, { startPositionInPixels.x, secondLineY }, { endPositionInPixels.x - 1, secondLineY }, color);
	}
}

void Graphics2D::Fill(int layerIndex, COLORREF color) NOEXCEPT_WHEN_NDEBUG
{
	assert(layerIndex >= 0);
	AddOrNotNewLayer(layerIndex);

	RenderRect(*m_layers[layerIndex], { 0, 0, m_layersSize.x, m_layersSize.y }, color);
}

void Graphics2D::Clear(COLORREF color) NOEXCEPT_WHEN_NDEBUG
{
	Fill(m_mainLayerIndex, color);

	for (auto& layer : m_layers | std::views::drop(1))
		if (layer.get() != nullptr)
			ClearLayer(*layer);
}

void Graphics2D::ResizeLayers(Vector2i newSize) NOEXCEPT_WHEN_NDEBUG
{
	m_layersSize = newSize;
	m_unitSize = CalculateUnitSize(m_layersSize, { m_unitSize, m_unitSize });

	HDC context{ m_renderWindow->GetDeviceContext().Get() };
	for (auto& layer : m_layers)
		if (layer.get() != nullptr)
			layer->Resize(context, newSize);
}

Vector2f Graphics2D::ConvertUnitsToPixels(Vector2f positionInUnits)
{
	return { positionInUnits.x * m_unitSize, positionInUnits.y * m_unitSize };
}

Vector2f Graphics2D::ConvertPixelsToUnits(Vector2i positonInPixels)
{
	return { positonInPixels.x / m_unitSize, positonInPixels.y / m_unitSize };
}

float Graphics2D::CalculateUnitSize(Vector2i windowSize, Vector2f units) noexcept
{
	return std::min(windowSize.x / units.x, windowSize.y / units.y);;
}

void Graphics2D::AddOrNotNewLayer(int layerIndex) noexcept
{
	int layersCount = (int)m_layers.size();
	for (; layerIndex > layersCount; ++layersCount)
		m_layers.emplace_back(nullptr);

	if (layerIndex == layersCount)
		m_layers.emplace_back(CreateCompatibleLayer());
	else if (m_layers[layerIndex] == nullptr)
		m_layers[layerIndex] = CreateCompatibleLayer();
}

std::unique_ptr<RenderLayer> Graphics2D::CreateCompatibleLayer() noexcept
{
	auto layer{ std::make_unique<RenderLayer>(m_renderWindow->GetDeviceContext().Get(), m_layersSize) };
	ClearLayer(*layer);

	return layer;
}

void Graphics2D::MergeTwoLayers(HDC destinationLayerContext, HDC sourceLayerContext)
{
	if (!TransparentBlt(destinationLayerContext, 0, 0, m_layersSize.x, m_layersSize.y,
		sourceLayerContext, 0, 0, m_layersSize.x, m_layersSize.y, (UINT)chroma))
		throw std::runtime_error("An error occurred while merging two layers");
}

void Graphics2D::MergeLayers()
{
	RenderLayer& destinationLayer{ *m_layers[m_mainLayerIndex] };
	for (auto& layer : m_layers | std::views::drop(1))
		if (layer.get() != nullptr && layer->IsUsed())
			MergeTwoLayers(destinationLayer.GetMemoryContext(), layer->GetMemoryContext());
}

void Graphics2D::RenderSprite(HDC layerContext, Vector2f positionInPixels, 
	HDC spriteContext, Box2i boundingBox, float sizeInUnits)
{
	auto boundingBoxPosition{ boundingBox.GetPosition() };
	auto actualSpriteSize{ (Vector2f)boundingBox.GetSize() };

	auto sizeInPixels{ sizeInUnits * m_unitSize };
	auto minScale{ std::min(sizeInPixels / actualSpriteSize.x, sizeInPixels / actualSpriteSize.y) };
	Vector2f finalSpriteSize(actualSpriteSize.x * minScale, actualSpriteSize.y * minScale);
	Vector2f shift((sizeInPixels - finalSpriteSize.x) / (sizeInPixels / finalSpriteSize.x),
		(sizeInPixels - finalSpriteSize.y) / (sizeInPixels / finalSpriteSize.y) );

	auto finalSpritePosition{ positionInPixels + shift };
	if (!TransparentBlt(layerContext, (int)round(finalSpritePosition.x), (int)round(finalSpritePosition.y),
		(int)round(finalSpriteSize.x), (int)round(finalSpriteSize.y),
		spriteContext, boundingBoxPosition.x, boundingBoxPosition.y, 
		(int)actualSpriteSize.x, (int)actualSpriteSize.y, (UINT)chroma))
		throw std::runtime_error("An error occurred while rendering a sprite");
}

void Graphics2D::ClearLayer(RenderLayer& layer) NOEXCEPT_WHEN_NDEBUG
{
	Fill(layer, chroma);
	layer.SetUsed(false);
}

void Graphics2D::ClearLayer(int layerIndex) NOEXCEPT_WHEN_NDEBUG
{
	ClearLayer(*m_layers[layerIndex]);
}

void Graphics2D::Fill(RenderLayer& layer, COLORREF color)
{
	RenderRect(layer, { 0, 0, m_layersSize.x, m_layersSize.y }, color);
}

void Graphics2D::RenderRect(RenderLayer& layer, const RECT& rect, COLORREF color) NOEXCEPT_WHEN_NDEBUG
{
	UniqueGDIOBJ<HBRUSH> brush(CreateSolidBrush(color));
	FillRect(layer.GetMemoryContext(), &rect, brush.get());
}
