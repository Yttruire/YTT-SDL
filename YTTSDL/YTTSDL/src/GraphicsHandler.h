#pragma once
#include <utility>
#include <vector>
#include <SDL.h>
#include "GTexture.h"

//Initializes SDL and a window (and its renderer) and is responsible for them, and rendering related to graphics
class GraphicsHandler
{
private:
	static bool m_initialized;
	bool m_is_shown;

	int m_width, m_height;

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	std::vector<GTexture> m_textures; //Hold all textures to be rendered (Or other user defined class in the future to wrap textures)

public:
	GraphicsHandler(int initial_xsize, int initial_ysize);
	~GraphicsHandler();

	SDL_Renderer* getRenderer() const { return m_renderer; }

	void render();
	void addRenderTexture(GTexture&& texture) { m_textures.push_back(std::move(texture)); }
	void handleWindowEvent(SDL_Event& evnt);
};