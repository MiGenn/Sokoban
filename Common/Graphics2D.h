#pragma once
#include <vector>
#include "RenderLayer.h"
#include "SpriteRenderInfo.h"
#include "Window.h"

class Graphics2D
{
public:
	static inline const Vector2i defaultSizeInUnits{ 32, 18 };
	static constexpr COLORREF chroma{ RGB(102, 0, 51) };
	
	Graphics2D(Window* renderWindow, Vector2f units = defaultSizeInUnits) NOEXCEPT_WHEN_NDEBUG;
	Graphics2D(const Graphics2D&) = delete;

	Graphics2D& operator=(const Graphics2D&) = delete;

	void Present();
	void RenderSprite(const SpriteRenderInfo& renderInfo);
	void RenderRect(int layerIndex, const RECT& rect, COLORREF color) NOEXCEPT_WHEN_NDEBUG;
	void RenderLine(int layerIndex, Vector2i startPositionInPixels, Vector2i endPositionInPixels,
		COLORREF color) NOEXCEPT_WHEN_NDEBUG;
	void RenderGrid(int layerIndex, COLORREF color) NOEXCEPT_WHEN_NDEBUG;
	void Fill(int layerIndex, COLORREF color) NOEXCEPT_WHEN_NDEBUG;
	void Clear(COLORREF color = RGB(0, 0, 0)) NOEXCEPT_WHEN_NDEBUG;

	void ResizeLayers(Vector2i newSize) NOEXCEPT_WHEN_NDEBUG;
	Vector2f ConvertUnitsToPixels(Vector2f positionInUnits);
	Vector2f ConvertPixelsToUnits(Vector2i positonInPixels);

private:
	static constexpr int m_mainLayerIndex{ 0 };
	float m_unitSize;
	Vector2i m_layersSize;
	Window* m_renderWindow;

	std::vector<std::unique_ptr<RenderLayer>> m_layers;

	float CalculateUnitSize(Vector2i windowSize, Vector2f units) noexcept;

	void AddOrNotNewLayer(int layerIndex) noexcept;
	std::unique_ptr<RenderLayer> CreateCompatibleLayer() noexcept;
	void MergeTwoLayers(HDC destinationLayerContext, HDC sourceLayerContext);
	void MergeLayers();
	void ClearLayer(int layerIndex) NOEXCEPT_WHEN_NDEBUG;
	void ClearLayer(RenderLayer& layer) NOEXCEPT_WHEN_NDEBUG;
	
	void RenderSprite(HDC layerContext, Vector2f positionInPixels, 
		HDC spriteContext, Box2i boundingBox, float sizeInUnits);
	void RenderRect(RenderLayer& layer, const RECT& rect, COLORREF color) NOEXCEPT_WHEN_NDEBUG;
	void Fill(RenderLayer& layer, COLORREF color) NOEXCEPT_WHEN_NDEBUG;
};
