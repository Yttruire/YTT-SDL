#pragma once
#include <utility>
#include <SDL.h>
#include "GTexture.h"

class Button
{
	SDL_Renderer* m_renderer;
	GTexture m_texture;

public:
	Button(SDL_Renderer* renderer, GTexture&& texture)
		:m_renderer{ renderer }, m_texture{ std::move(texture) }
	{};
	~Button() {};

	bool isWithinWhole(int x, int y)
	{
		if (x >= m_texture.getDstrectx() && x < (m_texture.getDstrectx() + m_texture.getDstrectw()) && 
			y >= m_texture.getDstrecty() && y < (m_texture.getDstrecty() + m_texture.getDstrecth()))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void render() { SDL_RenderCopy(m_renderer, m_texture.getTexture(), m_texture.getSrcrect(), m_texture.getDstrect()); }
};

