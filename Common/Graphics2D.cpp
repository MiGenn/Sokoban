#include "Graphics2D.h"

#include <cmath>
#include <cassert>
#include <ranges>
#include "WindowDC.h"
#include "MemoryDC.h"
#include "UniqueGDIOBJ.h"

#pragma comment(lib, "Msimg32")
#undef min

Graphics2D::Graphics2D(Window* renderWindow) NOEXCEPT_WHEN_NDEBUG :
	m_renderWindow(renderWindow)
{
	assert(renderWindow);

	m_layersSize = renderWindow->GetSize();
	m_pixelsAmountPerWorldUnit = CalculatePixelsAmountPerWorldUnit(m_layersSize);
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
	Utilities::Winapi::SmartPointer::MemoryDC spriteContext(CreateCompatibleDC(layerContext));
	Utilities::Winapi::Wrapper::SelectWrapper selectWrapper(spriteContext.Get(), renderInfo.GetBitmap());

	RenderSprite(layerContext, spriteContext.Get(), renderInfo);
}
 
void Graphics2D::RenderRect(int layerIndex, 
	const RECT& rectInScreenCoords, COLORREF color) NOEXCEPT_WHEN_NDEBUG
{
	assert(layerIndex >= 0);
	AddOrNotNewLayer(layerIndex);

	RenderRect(*m_layers[layerIndex], rectInScreenCoords, color);
}

void Graphics2D::RenderLine(int layerIndex, 
	Vector2i startPositionInScreenCoords, Vector2i endPositionInScreenCoords, COLORREF color) NOEXCEPT_WHEN_NDEBUG
{
	static constexpr int penWidth{ 1 };
	static constexpr int penStyle{ PS_SOLID };

	assert(layerIndex >= 0);
	AddOrNotNewLayer(layerIndex);

	auto layerContext{ m_layers[layerIndex]->GetMemoryContext() };
	Utilities::Winapi::SmartPointer::UniqueGDIOBJ<HPEN> pen(CreatePen(penStyle, penWidth, color));
	Utilities::Winapi::Wrapper::SelectWrapper selectWrapper(layerContext, pen.get());

	MoveToEx(layerContext, startPositionInScreenCoords.x, startPositionInScreenCoords.y, NULL);
	LineTo(layerContext, endPositionInScreenCoords.x, endPositionInScreenCoords.y);
}

void Graphics2D::RenderGrid(int layerIndex, COLORREF color) NOEXCEPT_WHEN_NDEBUG
{
	const auto halfScreenSizeInWorldUnits{ ConvertScreenToWorldUnits({ m_layersSize.x / 2, m_layersSize.y / 2 }) };
	const auto pixelsAmountPerWorldUnit{ m_pixelsAmountPerWorldUnit * m_zoom };

	const Vector2f startPositionInWorldCoords{ std::ceil(m_cameraPosition.x - halfScreenSizeInWorldUnits.x),
		std::floor(m_cameraPosition.y + halfScreenSizeInWorldUnits.y) };
	const Vector2f endPositionInWorldCoords{ std::floor(m_cameraPosition.x + halfScreenSizeInWorldUnits.x),
		std::ceil(m_cameraPosition.y - halfScreenSizeInWorldUnits.y) };
	const auto startPositionInScreenCoords{ (Vector2f)ConvertWorldToScreenCoords(startPositionInWorldCoords) };
	const auto endPositionInScreenCoords{ (Vector2f)ConvertWorldToScreenCoords(endPositionInWorldCoords) };

	//Малює горизотальні лінії
	RenderLine(layerIndex, { (int)startPositionInScreenCoords.x - 1, 0 }, 
		{ (int)startPositionInScreenCoords.x - 1, m_layersSize.y - 1 }, color);
	for (auto x{ startPositionInScreenCoords.x }; x <= endPositionInScreenCoords.x; x += pixelsAmountPerWorldUnit)
	{
		RenderLine(layerIndex, { (int)std::round(x), 0 }, { (int)std::round(x), m_layersSize.y - 1 }, color);
		const auto secondLineX{ (int)std::round(x + pixelsAmountPerWorldUnit - 1.f) };
		RenderLine(layerIndex, { secondLineX, 0 }, { secondLineX,  m_layersSize.y - 1 }, color);
	}

	//Малює вертикальні лінії
	RenderLine(layerIndex, { 0, (int)startPositionInScreenCoords.y - 1 }, 
		{ m_layersSize.x - 1, (int)startPositionInScreenCoords.y - 1 }, color);
	for (auto y{ startPositionInScreenCoords.y }; y <= endPositionInScreenCoords.y; y += pixelsAmountPerWorldUnit)
	{
		RenderLine(layerIndex, { 0, (int)std::round(y) }, { m_layersSize.x - 1, (int)std::round(y) }, color);
		const auto secondLineY{ (int)std::round(y + pixelsAmountPerWorldUnit - 1.f) };
		RenderLine(layerIndex, { 0, secondLineY }, { m_layersSize.x - 1, secondLineY }, color);
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
		if (layer.get())
			ClearLayer(*layer);
}

void Graphics2D::ResizeLayers(Vector2i newSize) NOEXCEPT_WHEN_NDEBUG
{
	m_layersSize = newSize;
	m_pixelsAmountPerWorldUnit = CalculatePixelsAmountPerWorldUnit(m_layersSize);

	HDC context{ m_renderWindow->GetDeviceContext().Get() };
	for (auto& layer : m_layers)
		if (!layer.get())
			layer->Resize(context, newSize);
}

void Graphics2D::SetZoom(float zoom) noexcept
{
	assert(zoom > 0.f);
	m_zoom = zoom;
}

void Graphics2D::SetCameraPosition(Vector2f newDrawingOrigin) noexcept
{
	m_cameraPosition = newDrawingOrigin;
}

float Graphics2D::GetZoom() const noexcept
{
	return m_zoom;
}

Vector2f Graphics2D::GetCameraPosition() const noexcept
{
	return m_cameraPosition;
}

Vector2i Graphics2D::ConvertWorldToScreenCoords(Vector2f worldCoords) const noexcept
{
	auto screenCoords{ ConvertWorldToScreenUnits(worldCoords - m_cameraPosition) };

	screenCoords.y *= -1;
	screenCoords.x += m_layersSize.x / 2;
	screenCoords.y += m_layersSize.y / 2;

	return screenCoords;
}

Vector2f Graphics2D::ConvertScreenToWorldCoords(Vector2i screenCoords) const noexcept
{
	screenCoords.x -= m_layersSize.x / 2;
	screenCoords.y -= m_layersSize.y / 2;
	screenCoords.y *= -1;

	return ConvertScreenToWorldUnits(screenCoords) + m_cameraPosition;
}

Vector2i Graphics2D::ConvertWorldToScreenUnits(Vector2f worldUnits) const noexcept
{
	return { (int)std::round(worldUnits.x * m_pixelsAmountPerWorldUnit * m_zoom),
		(int)std::round(worldUnits.y * m_pixelsAmountPerWorldUnit * m_zoom) };
}

Vector2f Graphics2D::ConvertScreenToWorldUnits(Vector2i screenUnits) const noexcept
{ 
	return { screenUnits.x / (m_pixelsAmountPerWorldUnit * m_zoom),
		screenUnits.y / (m_pixelsAmountPerWorldUnit * m_zoom) };
}

float Graphics2D::CalculatePixelsAmountPerWorldUnit(Vector2i layerSize) const noexcept
{
	return referencePixelsAmountPerWorldUnit *
		std::min(layerSize.x / (float)referenceResolution.x, layerSize.y / (float)referenceResolution.y);
}

bool Graphics2D::IsInDrawingRect(const Vector2f positionInWorldCoords, const Vector2f sizeInWorldUnits) const noexcept
{
	const auto topLeftInScreenCoords{ ConvertWorldToScreenCoords(positionInWorldCoords) };
	const auto bottomRightInScreenCoords{ topLeftInScreenCoords + ConvertWorldToScreenUnits(sizeInWorldUnits) };
	const RECT rectInScreenCoords{ topLeftInScreenCoords.x, topLeftInScreenCoords.y,
		bottomRightInScreenCoords.x, bottomRightInScreenCoords.y };

	return IsInDrawingRect(rectInScreenCoords);
}

bool Graphics2D::IsInDrawingRect(const RECT& rectInScreenCoords) const noexcept
{
	RECT intersection{};
	RECT drawingRectInScreenCoords{ 0, 0, m_layersSize.x, m_layersSize.y };

	return IntersectRect(&intersection, &drawingRectInScreenCoords, &rectInScreenCoords);
}

void Graphics2D::AddOrNotNewLayer(int layerIndex) noexcept
{
	auto layersCount{ (int)m_layers.size() };
	for (; layerIndex > layersCount; ++layersCount)
		m_layers.emplace_back(nullptr);

	if (layerIndex == layersCount)
		m_layers.emplace_back(CreateCompatibleLayer());
	else if (!m_layers[layerIndex])
		m_layers[layerIndex] = CreateCompatibleLayer();
}

std::unique_ptr<RenderLayer> Graphics2D::CreateCompatibleLayer()
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
		if (layer.get() && layer->IsUsed())
			MergeTwoLayers(destinationLayer.GetMemoryContext(), layer->GetMemoryContext());
}

void Graphics2D::RenderSprite(HDC layerContext, HDC spriteContext, const SpriteRenderInfo& renderInfo)
{
	auto positionInScreenCoords{ (Vector2f)ConvertWorldToScreenCoords(renderInfo.GetPosition()) };
	auto sizeInPixelsOnScreen{ (Vector2f)ConvertWorldToScreenUnits(renderInfo.GetSize()) };
	RECT spriteRectInScreenCoords{ (int)positionInScreenCoords.x, (int)positionInScreenCoords.y,
		(int)positionInScreenCoords.x + (int)sizeInPixelsOnScreen.x, (int)positionInScreenCoords.y + (int)sizeInPixelsOnScreen.y };
	if (!IsInDrawingRect(spriteRectInScreenCoords))
		return;

	const auto boundingBox{ renderInfo.GetBoundingBox() };
	const auto boundingBoxPosition{ boundingBox.GetPosition() };
	const auto actuaSizeInPixels{ (Vector2f)boundingBox.GetSize() };
	if (renderInfo.IsPreservingAspectRatio())
	{
		const auto minScale{ std::min(sizeInPixelsOnScreen.x / actuaSizeInPixels.x,
			sizeInPixelsOnScreen.y / actuaSizeInPixels.y) };
		const auto oldSizeInPixelsOnScreen{ sizeInPixelsOnScreen };
		sizeInPixelsOnScreen = { actuaSizeInPixels.x * minScale, actuaSizeInPixels.y * minScale };
		Vector2f shift{ (oldSizeInPixelsOnScreen - sizeInPixelsOnScreen) / 2.f };
		positionInScreenCoords = positionInScreenCoords + shift;
	}

	if (!TransparentBlt(layerContext, (int)round(positionInScreenCoords.x), 
		(int)round(positionInScreenCoords.y),
		(int)round(sizeInPixelsOnScreen.x), (int)round(sizeInPixelsOnScreen.y),
		spriteContext, boundingBoxPosition.x, boundingBoxPosition.y, 
		(int)actuaSizeInPixels.x, (int)actuaSizeInPixels.y, (UINT)chroma))
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

void Graphics2D::Fill(RenderLayer& layer, COLORREF color) NOEXCEPT_WHEN_NDEBUG
{
	RenderRect(layer, { 0, 0, m_layersSize.x, m_layersSize.y }, color);
}

void Graphics2D::RenderRect(RenderLayer& layer, const RECT& rectInScreenCoords, COLORREF color) NOEXCEPT_WHEN_NDEBUG
{
	Utilities::Winapi::SmartPointer::UniqueGDIOBJ<HBRUSH> brush(CreateSolidBrush(color));
	FillRect(layer.GetMemoryContext(), &rectInScreenCoords, brush.get());
}
