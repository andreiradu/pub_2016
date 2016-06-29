#pragma once
#include <cstdint>
#include <Engine/Rendering/Texture.h>
namespace Engine
{
class Sprite
{
public:
	Sprite(Texture* tex, int32_t lowerLeftX, uint32_t lowerLeftY, uint32_t upperRightX, uint32_t upperRightY)
		: m_tex(tex)
		, m_lowerLeftX(lowerLeftX)
		, m_lowerLeftY(lowerLeftY)
		, m_upperRightX(upperRightX)
		, m_upperRightY(upperRightY) {}

	Texture* m_tex;
	uint32_t m_lowerLeftX;
	uint32_t m_lowerLeftY;
	uint32_t m_upperRightX;
	uint32_t m_upperRightY;
};
}