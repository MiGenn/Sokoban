#pragma once
#include <vector>
#include "Window.h"
#include "SpriteRenderInfo.h"

#pragma comment(lib, "MSIMG32.LIB")

class Graphics2D
{
public:
	static constexpr COLORREF chroma{ RGB(102, 0, 51) };
	static constexpr int tileSize{ 24 };

	Graphics2D(Window* renderWindow);
	Graphics2D(const Graphics2D&) = delete;
	~Graphics2D();

	Graphics2D& operator=(const Graphics2D&) = delete;

	void Test();

	void Present();
	void RenderSprite(const SpriteRenderInfo& renderInfo);
	void RenderRect(int layerIndex, const RECT& rect, COLORREF color);
	void Fill(int layerIndex, COLORREF color);

	void ResizeLayers(Vector2i newSize);

private:
	static constexpr int m_mainLayerIndex{ 0 };
	Vector2i m_layersSize;
	Window* m_renderWindow;

	class RenderLayer
	{
	public:
		RenderLayer(HDC referenceContext, Vector2i size);
		RenderLayer(const RenderLayer&) = delete;
		RenderLayer& operator=(const RenderLayer&) = delete;
		~RenderLayer();

		void SetUsed(bool isUsed);
		void Resize(HDC referenceContext, Vector2i newSize);
		HDC GetMemoryContext();
		bool IsUsed() const;

	private:
		bool m_isUsed;
		HDC m_context;
		HBITMAP m_bitmap;
		HGDIOBJ m_initialBitmap;
	};

	std::vector<RenderLayer*> m_layers;

	bool DoesNotLayerExist(int layerIndex);
	void AddNewLayer(int layerIndex);
	RenderLayer* CreateCompatibleLayer();
	void MergeLayers();

	void ClearLayer(int layerIndex);
};
