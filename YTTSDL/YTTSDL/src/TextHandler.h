#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <string>

//Loads and handles a monospaced font for rendering text to a renderer passed in to TextHandler
class TextHandler
{
private:
	static bool m_initialized;

	TTF_Font* m_font;
	SDL_Renderer* m_renderer;
	std::vector<SDL_Texture*> m_character_textures;

	int m_width, m_height; //Of each character in the font

	SDL_Texture* createTextTexture(SDL_Renderer* renderer, const char* text);
public:
	TextHandler(SDL_Renderer* renderer, const char* font_filename, int ptsize);
	~TextHandler();

	void render(const std::string& text, int x, int y, int newlines = 0);
	void renderAll();

	int getVerticalSpace() const { return m_height; }
	int getHorizontalSpace() const { return m_width; }
	int convertToTextureIndex(int character) const { return character - 33; } //Converts '!' (33) to its corresponding texture index (0)
};