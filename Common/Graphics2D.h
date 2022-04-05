#pragma once
#include <vector>
#include "RenderLayer.h"
#include "Window.h"
#include "SpriteRenderInfo.h"

class Graphics2D
{
public:
	static constexpr COLORREF chroma{ RGB(102, 0, 51) };
	static constexpr int tileSize{ 24 };

	Graphics2D(Window* renderWindow) NOEXCEPT_WHEN_NDEBUG;
	Graphics2D(const Graphics2D&) = delete;

	Graphics2D& operator=(const Graphics2D&) = delete;

	void Present();
	void RenderSprite(const SpriteRenderInfo& renderInfo);
	void RenderRect(int layerIndex, const RECT& rect, COLORREF color) NOEXCEPT_WHEN_NDEBUG;
	void Fill(int layerIndex, COLORREF color) NOEXCEPT_WHEN_NDEBUG;

	void ResizeLayers(Vector2i newSize) NOEXCEPT_WHEN_NDEBUG;

private:
	static constexpr int m_mainLayerIndex{ 0 };
	Vector2i m_layersSize;
	Window* m_renderWindow;

	std::vector<std::unique_ptr<RenderLayer>> m_layers;

	bool DoesNotLayerExist(int layerIndex) const noexcept;
	void AddNewLayer(int layerIndex) noexcept;
	std::unique_ptr<RenderLayer> CreateCompatibleLayer() const noexcept;
	void MergeTwoBitmaps(HDC destinationLayerContext, Vector2i destinationPosition,
		HDC sourceLayerContext, Box2i boundingBox, float scale);
	void MergeLayers();

	void ClearLayer(int layerIndex) NOEXCEPT_WHEN_NDEBUG;
};
