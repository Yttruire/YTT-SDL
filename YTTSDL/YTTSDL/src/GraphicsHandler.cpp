#include <string>
#include <stdexcept>
#include "GraphicsHandler.h"



bool GraphicsHandler::m_initialized = false;

GraphicsHandler::GraphicsHandler(int initial_width, int initial_height) :m_width{ initial_width }, m_height{ initial_height }
{
	//If one of this is already initialized, prevent it
	if (m_initialized)
	{
		throw std::runtime_error("GraphicsHandler already initialized, do not define two instances of GraphicsHandler.");
	}

	//Initialize SDL's video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		throw std::runtime_error("SDL could not be initialized! SDL Error:" + std::string(SDL_GetError()));
	}

	//Create a window
	m_window = SDL_CreateWindow("SDL Quest!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (m_window == nullptr)
	{
		throw std::runtime_error("Window could not be initialized! SDL Error:" + std::string(SDL_GetError()));
	}

	//Create the renderer for the window
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_renderer == nullptr)
	{
		throw std::runtime_error("Renderer could not be initialized! SDL Error:" + std::string(SDL_GetError()));
	}

	SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(m_renderer);
}

GraphicsHandler::~GraphicsHandler()
{
	//All textures will go out of scope and be cleaned up by GTexture class destructor
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);

	SDL_Quit();
}

//Render all textures needed to be rendered to the window
void GraphicsHandler::render()
{
	//Render only if window is being shown
	if (m_is_shown)
	{
		for (auto& texture : m_textures)
		{
			SDL_RenderCopy(m_renderer, texture.getTexture(), texture.getSrcrect(), texture.getDstrect());
		}

		SDL_RenderPresent(m_renderer);
		SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(m_renderer);
	}
}

//Handle SDL_Event.window events, should be called if such an event was polled
void GraphicsHandler::handleWindowEvent(SDL_Event& evnt)
{
	switch (evnt.window.event)
	{
	//Window should be rendered
	case SDL_WINDOWEVENT_SHOWN:
	case SDL_WINDOWEVENT_MAXIMIZED:
	case SDL_WINDOWEVENT_RESTORED:
	case SDL_WINDOWEVENT_EXPOSED:
		m_is_shown = true;
		break;

	//Window need not be rendered
	case SDL_WINDOWEVENT_HIDDEN:
	case SDL_WINDOWEVENT_MINIMIZED:
		m_is_shown = false;
		break;

	//Window size changed, update member variables accordingly
	case SDL_WINDOWEVENT_RESIZED:
	case SDL_WINDOWEVENT_SIZE_CHANGED:
		m_width = evnt.window.data1;
		m_height = evnt.window.data2;
		break;

	//Cases that have no defined instructions to carry out for now
	case SDL_WINDOWEVENT_ENTER:
	case SDL_WINDOWEVENT_LEAVE:
	case SDL_WINDOWEVENT_FOCUS_GAINED:
	case SDL_WINDOWEVENT_FOCUS_LOST:
	case SDL_WINDOWEVENT_MOVED:
	case SDL_WINDOWEVENT_CLOSE:
		break;

	//TAKE_FOCUS and HIT_TEST events ignored
	}
}