#pragma once
#include <Engine/Rendering/Sprite.h>
#include <Engine/System/System.h>
namespace Engine
{
class Renderer
{
public:
	void Init();
	void BeginFrame();
	void EndFrame();
	void OnResize(uint32_t width, uint32_t height);
	void RenderSprite(Sprite& sprite, uint32_t posX, uint32_t posY);
protected:
	uint32_t m_width;
	uint32_t m_height;
};

inline void Renderer::OnResize(uint32_t width, uint32_t height)
{
	m_width = width;
	m_height = height;
}
}
