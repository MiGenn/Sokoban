#include "Graphics2D.h"

#include <cmath>
#include <cassert>
#include "WindowDCWrapper.h"
#include "UniqueAny.h"

#pragma comment(lib, "Msimg32")

Graphics2D::Graphics2D(Window* renderWindow) NOEXCEPT_WHEN_NDEBUG :
	m_renderWindow(renderWindow)
{
	assert(renderWindow != nullptr);

	m_layersSize = renderWindow->GetSize();
	AddNewLayer(m_mainLayerIndex);
	Fill(m_mainLayerIndex, RGB(0, 0, 0));

	AddNewLayer(1);
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
	if (DoesNotLayerExist(layerIndex))
		AddNewLayer(layerIndex);

	HDC destinationContext{ m_layers[layerIndex]->GetMemoryContext() };
	HDC sourceContext{ CreateCompatibleDC(destinationContext) };
	HGDIOBJ initialBitmap{ SelectObject(sourceContext, renderInfo.GetBitmap()) };

	MergeTwoBitmaps(destinationContext, renderInfo.GetScreenPosition(),
		sourceContext, renderInfo.GetBoundingBox(), 4.f);

	SelectObject(sourceContext, initialBitmap);
	DeleteDC(sourceContext);
}

void Graphics2D::Clear(COLORREF color) NOEXCEPT_WHEN_NDEBUG
{
	Fill(m_mainLayerIndex, color);

	int layersCount{ (int)m_layers.size() };
	for (int i{ m_mainLayerIndex + 1 }; i < layersCount; ++i)
		if (m_layers[i].get() != nullptr)
			ClearLayer(i);
}

void Graphics2D::RenderRect(int layerIndex, const RECT& rect,
	COLORREF color) NOEXCEPT_WHEN_NDEBUG
{
	assert(layerIndex >= 0);
	if (DoesNotLayerExist(layerIndex))
		AddNewLayer(layerIndex);

	UniqueGDIOBJ<HBRUSH> brush(CreateSolidBrush(color));
	FillRect(m_layers[layerIndex]->GetMemoryContext(), &rect, brush.get());
}

void Graphics2D::RenderLine(int layerIndex, Vector2i startPosition, Vector2i endPosition, COLORREF color) NOEXCEPT_WHEN_NDEBUG
{
	static constexpr int penWidth{ 1 };

	assert(layerIndex >= 0);
	if (DoesNotLayerExist(layerIndex))
		AddNewLayer(layerIndex);

	auto memoryContext{ m_layers[layerIndex]->GetMemoryContext() };
	UniqueGDIOBJ<HPEN> pen(CreatePen(PS_SOLID, penWidth, color));
	auto previousObject{ SelectObject(memoryContext, pen.get()) };

	MoveToEx(memoryContext, startPosition.x, startPosition.y, NULL);
	LineTo(memoryContext, endPosition.x, endPosition.y);

	SelectObject(memoryContext, previousObject);
}

void Graphics2D::RenderGrid(int layerIndex, Vector2i startPosition, Vector2i endPosition, 
	Vector2i sellSize, COLORREF color) NOEXCEPT_WHEN_NDEBUG
{
	assert(sellSize.x >= 0 && sellSize.y >= 0);

	for (int x{ startPosition.x }; x < endPosition.x - 1; x += sellSize.x)
	{
		RenderLine(layerIndex, { x, startPosition.y }, { x, endPosition.y - 1 }, color);
		int SecondLineX{ x + sellSize.x - 1 };
		RenderLine(layerIndex, { SecondLineX, startPosition.y }, { SecondLineX, endPosition.y - 1 }, color);
	}

	for (int y{ startPosition.y }; y < endPosition.y - 1; y += sellSize.y)
	{
		RenderLine(layerIndex, { startPosition.x, y }, { endPosition.x - 1, y }, color);
		int SecondLineY{ y + sellSize.y - 1 };
		RenderLine(layerIndex, { startPosition.x, SecondLineY }, { endPosition.x - 1, SecondLineY }, color);
	}
}

void Graphics2D::Fill(int layerIndex, COLORREF color) NOEXCEPT_WHEN_NDEBUG
{
	RenderRect(layerIndex, { 0, 0, m_layersSize.x, m_layersSize.y }, color);
}

void Graphics2D::ResizeLayers(Vector2i newSize) NOEXCEPT_WHEN_NDEBUG
{
	m_layersSize = newSize;
	HDC context{ m_renderWindow->GetDeviceContext().Get() };
	int layersCount{ (int)m_layers.size() };
	for (int i{ 0 }; i < layersCount; ++i)
		if (m_layers[i].get() != nullptr)
			m_layers[i]->Resize(context, newSize);
}

bool Graphics2D::DoesNotLayerExist(int layerIndex) const noexcept
{
	return layerIndex >= (int)m_layers.size() || m_layers[layerIndex] == nullptr;
}

void Graphics2D::AddNewLayer(int layerIndex) noexcept
{
	int layersCount = (int)m_layers.size();

	for (; layerIndex > layersCount; ++layersCount)
		m_layers.emplace_back(nullptr);

	if (layerIndex == layersCount)
		m_layers.emplace_back(CreateCompatibleLayer());
	else if (m_layers[layerIndex] == nullptr)
		m_layers[layerIndex] = CreateCompatibleLayer();

	ClearLayer(layerIndex);
}

std::unique_ptr<RenderLayer> Graphics2D::CreateCompatibleLayer() const noexcept
{
	return std::make_unique<RenderLayer>(m_renderWindow->GetDeviceContext().Get(), m_layersSize);
}

void Graphics2D::MergeTwoBitmaps(HDC destinationLayerContext, Vector2i destinationPosition,
	HDC sourceLayerContext, Box2i boundingBox, float scale)
{
	auto boxPosition{ boundingBox.GetPosition() };
	auto boxSize{ boundingBox.GetSize() };

	if (!TransparentBlt(destinationLayerContext, destinationPosition.x, destinationPosition.y,
		(int)round(boxSize.x * scale), (int)round(boxSize.y * scale),
		sourceLayerContext, boxPosition.x, boxPosition.y,
		boxSize.x, boxSize.y, (UINT)(chroma)))
		throw std::runtime_error("Error when merging");
}

void Graphics2D::MergeLayers()
{
	int layersCount{ (int)m_layers.size() };
	if (layersCount == 1)
		return;

	RenderLayer& destinationLayer{ *m_layers[m_mainLayerIndex] };
	for (int i{ m_mainLayerIndex + 1 }; i < layersCount; ++i)
	{
		if (m_layers[i].get() != nullptr && m_layers[i]->IsUsed())
		{ 
			RenderLayer& sourceLayer{ *m_layers[i] };
			MergeTwoBitmaps(destinationLayer.GetMemoryContext(), {0, 0}, sourceLayer.GetMemoryContext(),
				{ { 0, 0 }, { m_layersSize.x, m_layersSize.y } }, 1.f);
		}
	}
}

void Graphics2D::ClearLayer(int layerIndex) NOEXCEPT_WHEN_NDEBUG
{
	Fill(layerIndex, chroma);
	m_layers[layerIndex]->SetUsed(false);
}
