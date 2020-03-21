#pragma once
#include "TextBox.h"

class ColoredBorderedTextBox
{
protected:
	TextHandler* m_text_handler;
	SDL_Renderer* m_renderer;
	std::vector<std::string> m_text;

	int m_horizontal_char_limit;

	SDL_Rect m_rect;

	SDL_Color m_color;

public:
	ColoredBorderedTextBox(TextHandler* text_handler, SDL_Renderer* renderer, int x, int y, int horizontal_char_limit, int vertical_char_limit, const SDL_Color& border_color)
		: m_text_handler{ text_handler }, m_renderer{ renderer }, m_horizontal_char_limit{ horizontal_char_limit },
		m_rect{ x, y, m_text_handler->getHorizontalSpace() * horizontal_char_limit + 4, m_text_handler->getVerticalSpace() * vertical_char_limit }, //4 for horizontal buffer
		m_color{ border_color }
	{}
	~ColoredBorderedTextBox()
	{}
	void addText(const std::string& text) { m_text.push_back(text); }
	void clearText() { m_text.clear(); }

	void changeBorderColor(const SDL_Color& border_color) { m_color = border_color; }

	void render();
};

