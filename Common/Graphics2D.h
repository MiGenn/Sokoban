#pragma once
#include <vector>
#include "RenderLayer.h"
#include "SpriteRenderInfo.h"
#include "Window.h"

class Graphics2D final
{
public:
	static inline const Vector2i referenceResolution{ 1280, 720 };
	static constexpr float referencePixelsAmountPerWorldUnit{ 70.f };
	static constexpr COLORREF chroma{ RGB(102, 0, 51) };

	Graphics2D(Window* renderWindow) NOEXCEPT_WHEN_NDEBUG;
	Graphics2D(const Graphics2D&) = delete;

	Graphics2D& operator=(const Graphics2D&) = delete;

	void Present();
	void RenderSprite(const SpriteRenderInfo& renderInfo);
	void RenderRect(int layerIndex, 
		const RECT& rectInScreenCoords, COLORREF color) NOEXCEPT_WHEN_NDEBUG;
	void RenderLine(int layerIndex, Vector2i startPositionScreenCoords, 
		Vector2i endPositionInScreenCoords, COLORREF color) NOEXCEPT_WHEN_NDEBUG;
	void RenderGrid(int layerIndex, COLORREF color) NOEXCEPT_WHEN_NDEBUG;
	void Fill(int layerIndex, COLORREF color) NOEXCEPT_WHEN_NDEBUG;
	void Clear(COLORREF color = RGB(0, 0, 0)) NOEXCEPT_WHEN_NDEBUG;

	void ResizeLayers(Vector2i newSize) NOEXCEPT_WHEN_NDEBUG;

	void SetZoom(float zoom) noexcept;
	void SetCameraPosition(Vector2f newDrawingOrigin) noexcept;
	float GetZoom() const noexcept;
	Vector2f GetCameraPosition() const noexcept;

	Vector2i ConvertWorldToScreenCoords(Vector2f worldCoords) const noexcept;
	Vector2f ConvertScreenToWorldCoords(Vector2i screenCoords) const noexcept;

	Vector2i ConvertWorldToScreenUnits(Vector2f worldUnits) const noexcept;
	Vector2f ConvertScreenToWorldUnits(Vector2i screenUnits) const noexcept;

private:
	static constexpr int m_mainLayerIndex{ 0 };
	float m_pixelsAmountPerWorldUnit;
	float m_zoom{ 1.f };
	Vector2f m_cameraPosition;
	Vector2i m_layersSize;
	Window* m_renderWindow;

	std::vector<std::unique_ptr<RenderLayer>> m_layers;

	float CalculatePixelsAmountPerWorldUnit(Vector2i layerSize) const noexcept;
	bool IsInDrawingRect(const Vector2f positionInWorldCoords, const Vector2f sizeInWorldUnits) const noexcept;
	bool IsInDrawingRect(const RECT& rectInScreenCoords) const noexcept;

	void AddOrNotNewLayer(int layerIndex) noexcept;
	std::unique_ptr<RenderLayer> CreateCompatibleLayer();
	void MergeTwoLayers(HDC destinationLayerContext, HDC sourceLayerContext);
	void MergeLayers();
	void ClearLayer(RenderLayer& layer) NOEXCEPT_WHEN_NDEBUG;
	
	void RenderSprite(HDC layerContext, HDC spriteContext, const SpriteRenderInfo& renderInfo);
	void RenderRect(RenderLayer& layer, const RECT& rectInScreenCoords, COLORREF color) NOEXCEPT_WHEN_NDEBUG;
	void Fill(RenderLayer& layer, COLORREF color) NOEXCEPT_WHEN_NDEBUG;
};
