#pragma once
#include <cstdint>
#include <Engine/Config.h>
namespace Engine
{
class ENGINE_API Texture
{
public:
	static Texture* LoadTexture(char* filename);
	uint32_t GetHandle()const { return m_handle; }
	uint32_t GetWidth()const { return m_width; }
	uint32_t GetHeight()const { return m_height; }
protected:
	uint32_t m_handle;
	uint32_t m_width;
	uint32_t m_height;
};
}