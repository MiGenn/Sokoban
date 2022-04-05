#include "Graphics2D.h"

#include <cmath>
#include <cassert>
#include "DeviceContextWrapper.h"

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

void Graphics2D::Fill(int layerIndex, COLORREF color) NOEXCEPT_WHEN_NDEBUG
{
	RenderRect(layerIndex, { 0, 0, m_layersSize.x, m_layersSize.y }, color);
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

	MergeTwoBitmaps(destinationContext, renderInfo.GetPosition(),
		sourceContext, renderInfo.GetBoundingBox(), 10.f);

	SelectObject(sourceContext, initialBitmap);
	DeleteDC(sourceContext);
}

void Graphics2D::RenderRect(int layerIndex, const RECT& rect, COLORREF color) NOEXCEPT_WHEN_NDEBUG
{
	assert(layerIndex >= 0);
	if (DoesNotLayerExist(layerIndex))
		AddNewLayer(layerIndex);

	FillRect(m_layers[layerIndex]->GetMemoryContext(), &rect, CreateSolidBrush(color));
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
		throw WINAPI_LAST_EXCEPTION();
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
