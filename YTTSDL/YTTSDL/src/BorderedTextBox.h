#pragma once
#include "TextBox.h"


//A textbox with a visible border, where text that is too long to be displayed on one line in the box, it will automatically be moved to the next line
//Also warns if text exceeds bottom border (If YPU_DEBUG_MODE is defined)
class BorderedTextBox
{
protected:
	TextHandler* m_text_handler;
	SDL_Renderer* m_renderer;
	std::vector<std::string> m_text;

	int m_horizontal_char_limit;

	SDL_Rect m_rect;

public:
	BorderedTextBox(TextHandler* text_handler, SDL_Renderer* renderer, int x, int y, int horizontal_char_limit, int number_of_lines)
		: m_text_handler{ text_handler }, m_renderer{ renderer }, m_horizontal_char_limit{ horizontal_char_limit },
		m_rect{ x, y, m_text_handler->getHorizontalSpace() * horizontal_char_limit + 4, m_text_handler->getVerticalSpace() * number_of_lines } //4 for horizontal buffer
	{}
	~BorderedTextBox()
	{}
	void addText(const std::string& text) { m_text.push_back(text); }
	void clearText() { m_text.clear(); }

	void render();
};

