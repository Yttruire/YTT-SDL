#include <string>
#include "TextHandler.h"



bool TextHandler::m_initialized = false;

TextHandler::TextHandler(SDL_Renderer* renderer, const char* font_filename, int ptsize) : m_renderer{ renderer }
{
	//If one of this is already initialized, prevent it
	if (m_initialized)
	{
		throw std::runtime_error("GraphicsHandler already initialized, do not define two instances of GraphicsHandler.");
	}

	//Initialize SDL_TTF
	if (TTF_Init() < 0)
	{
		throw std::runtime_error("SDL_TTF could not be initialized! TTF Error: " + std::string(TTF_GetError()));
	}

	//Load font
	m_font = TTF_OpenFont(font_filename, ptsize);
	if (m_font == nullptr)
	{
		throw std::runtime_error("Font could not be loaded! TTF Error: " + std::string(TTF_GetError()));
	}

	//Get width and height of a character in the font
	TTF_SizeText(m_font, "!", &m_width, &m_height);

	//Render all visible ASCII characters into textures to store
	char character[2] = "!";
	for (; character[0] < 127; ++character[0])
	{
		m_character_textures.reserve(94);
		SDL_Texture* temp_holder = createTextTexture(renderer, character);
		m_character_textures.push_back(temp_holder);
	}
}

TextHandler::~TextHandler()
{
	//Destroy all textures
	for (auto& i : m_character_textures)
	{
		SDL_DestroyTexture(i);
	}
	TTF_CloseFont(m_font);
	TTF_Quit();
}

//Creates and returns a texture of a C-style string (Note: TextHandler will not own it)
SDL_Texture* TextHandler::createTextTexture(SDL_Renderer* renderer, const char* text)
{
	//Render black solid text to a surface
	SDL_Surface* text_surface = TTF_RenderText_Blended(m_font, text, SDL_Color{ 0, 0, 0 });
	if (text_surface == nullptr)
	{
		throw std::runtime_error("Text surface could not be rendered! TTF Error: " + std::string(TTF_GetError()));
	}

	//Create texture from surface
	SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	if (text_texture == nullptr)
	{
		throw std::runtime_error("Text texture could not be created from surface! TTF Error: " + std::string(TTF_GetError()));
	}

	//Free surface and return rendered texture for the text
	SDL_FreeSurface(text_surface);

	return text_texture;
}

//Render a string onto position (x, y). Newlines represent how many vertical spaces down to start the string rendering on (Negative no. accepted)
void TextHandler::render(const std::string& text, int x, int y, int newlines)
{
	SDL_Rect dstrect{ x, (y + newlines * m_height), m_width, m_height };
	for (const auto& character : text)
	{
		if (character != ' ')
		{
			SDL_RenderCopy(m_renderer, m_character_textures[convertToTextureIndex(character)], nullptr, &dstrect);
		}
		dstrect.x += m_width;
	}
}

//Render all of the characters loaded from the font (For testing purposes)
void TextHandler::renderAll()
{
	SDL_Rect dstrect{ 0, 0, m_width, m_height };
	for (const auto& character_textures : m_character_textures)
	{
		SDL_RenderCopy(m_renderer, character_textures, nullptr, &dstrect);
		dstrect.x += m_width;
	}
}