#include "Graphics2D.h"

#include <cmath>
#include "DeviceContextWrapper.h"

Graphics2D::Graphics2D(Window* renderWindow) :
	m_renderWindow(renderWindow), m_layersSize(renderWindow->GetSize())
{
	AddNewLayer(m_mainLayerIndex);
	Fill(m_mainLayerIndex, RGB(0, 0, 0));

	AddNewLayer(1);
}

Graphics2D::~Graphics2D()
{
	for (auto layer : m_layers)
		delete layer;
}

void Graphics2D::Fill(int layerIndex, COLORREF color)
{
	RenderRect(layerIndex, { 0, 0, m_layersSize.x, m_layersSize.y }, color);
}

void Graphics2D::Present()
{
	MergeLayers();

	const Vector2i windowSize{ m_renderWindow->GetSize() };
	if (!StretchBlt(m_renderWindow->GetDeviceContext().Get(), 0, 0, windowSize.x, windowSize.y,
		m_layers[m_mainLayerIndex]->GetMemoryContext(), 0, 0, m_layersSize.x, m_layersSize.y, SRCCOPY))
		throw LAST_EXCEPTION();
}

void Graphics2D::RenderSprite(const SpriteRenderInfo& renderInfo)
{
	int layerIndex{ renderInfo.GetLayerIndex() };
	if (DoesNotLayerExist(layerIndex))
		AddNewLayer(layerIndex);

	HDC destinationContext{ m_layers[layerIndex]->GetMemoryContext() };
	HDC sourceContext{ CreateCompatibleDC(destinationContext) };
	HGDIOBJ initialBitmap{ SelectObject(sourceContext, renderInfo.GetBitmap()) };

	MergeContexes(destinationContext, renderInfo.GetPosition(),
		sourceContext, renderInfo.GetBoundingBox(), 10.f);

	SelectObject(sourceContext, initialBitmap);
	DeleteDC(sourceContext);
}

void Graphics2D::RenderRect(int layerIndex, const RECT& rect, COLORREF color)
{
	if (DoesNotLayerExist(layerIndex))
		AddNewLayer(layerIndex);

	if (!FillRect(m_layers[layerIndex]->GetMemoryContext(), &rect, CreateSolidBrush(color)))
		throw LAST_EXCEPTION();
}

void Graphics2D::ResizeLayers(Vector2i newSize)
{
	m_layersSize = newSize;
	HDC context{ m_renderWindow->GetDeviceContext().Get() };

	for (auto layer : m_layers)
		if (layer != nullptr)
			layer->Resize(context, newSize);
}

bool Graphics2D::DoesNotLayerExist(int layerIndex)
{
	return layerIndex >= m_layers.size() || m_layers[layerIndex] == nullptr;
}

void Graphics2D::AddNewLayer(int layerIndex)
{
	int layersCount = static_cast<int>(m_layers.size());

	while (layerIndex > layersCount)
	{
		m_layers.push_back(nullptr);
		++layersCount;
	}

	if (layerIndex == layersCount)
		m_layers.push_back(CreateCompatibleLayer());
	else if (m_layers[layerIndex] == nullptr)
		m_layers[layerIndex] = CreateCompatibleLayer();

	ClearLayer(layerIndex);
}

Graphics2D::RenderLayer* Graphics2D::CreateCompatibleLayer()
{
	return new RenderLayer(m_renderWindow->GetDeviceContext().Get(), m_layersSize);
}

void Graphics2D::MergeContexes(HDC destinationContext, Vector2i destinationPosition, 
	 HDC sourceContext, Box2i boundingBox, float scale)
{
	if (!TransparentBlt(destinationContext, destinationPosition.x, destinationPosition.y, 
		round(boundingBox.size.x * scale), round(boundingBox.size.y * scale),
		sourceContext, boundingBox.position.x, boundingBox.position.y,
		boundingBox.size.x, boundingBox.size.y, (UINT)(chroma)))
		throw LAST_EXCEPTION();
}

void Graphics2D::MergeLayers()
{
	int layersCount{ static_cast<int>(m_layers.size()) };
	if (layersCount == 1)
		return;

	RenderLayer* const destinationLayer{ m_layers[m_mainLayerIndex] };
	for (int i{ m_mainLayerIndex + 1 }; i < layersCount; ++i)
	{
		if (m_layers[i] != nullptr && m_layers[i]->IsUsed())
		{
			RenderLayer* const sourceLayer{ m_layers[i] };
			MergeContexes(destinationLayer->GetMemoryContext(), { 0, 0 }, sourceLayer->GetMemoryContext(), 
				{ { 0, 0 }, { m_layersSize.x, m_layersSize.y } }, 1.f);
		}
	}
}

void Graphics2D::ClearLayer(int layerIndex)
{
	Fill(layerIndex, chroma);
	m_layers[layerIndex]->SetUsed(false);
}

Graphics2D::RenderLayer::RenderLayer(HDC referenceContext, Vector2i size) :
	m_isUsed(false)
{
	m_context = CreateCompatibleDC(referenceContext);
	m_bitmap = CreateCompatibleBitmap(referenceContext, size.x, size.y);
	m_initialBitmap = SelectObject(m_context, m_bitmap);
}

Graphics2D::RenderLayer::~RenderLayer()
{
	SelectObject(m_context, m_initialBitmap);
	DeleteObject(m_bitmap);
	DeleteDC(m_context);
}

HDC Graphics2D::RenderLayer::GetMemoryContext()
{
	m_isUsed = true;

	return m_context;
}

bool Graphics2D::RenderLayer::IsUsed() const
{
	return m_isUsed;
}

void Graphics2D::RenderLayer::SetUsed(bool isUsed)
{
	m_isUsed = isUsed;
}

void Graphics2D::RenderLayer::Resize(HDC referenceContext, Vector2i newSize)
{
	m_bitmap = CreateCompatibleBitmap(referenceContext, newSize.x, newSize.y);
	HGDIOBJ oldBitmap{ SelectObject(m_context, m_bitmap) };

	DeleteObject(oldBitmap);
}
