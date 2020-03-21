#pragma once
#include "TextHandler.h"

class VerticalScrollTextBox
{
protected:
	TextHandler* m_text_handler;
	SDL_Renderer* m_renderer;
	std::vector<std::string> m_text;

	int m_number_of_lines;

	int m_x, m_y;

	int m_horizontal_char_limit;
	int m_vertical_char_limit;

	int m_text_yoffset{ 0 };
	int m_scrollbar_yoffset{ 0 };

	SDL_Rect m_scrollarea;
	SDL_Rect m_scrollbar;
	SDL_Color m_scrollarea_color;
	SDL_Color m_scrollbar_color;

	int m_x1, m_y1;

public:
	VerticalScrollTextBox(TextHandler* text_handler, SDL_Renderer* renderer,
		int x, int y, int horizontal_char_limit, int vertical_char_limit, const SDL_Color& scrollarea_color, const SDL_Color& scrollbar_color)
		: m_text_handler{ text_handler }, m_renderer{ renderer }, m_horizontal_char_limit{ horizontal_char_limit }, m_vertical_char_limit{ vertical_char_limit },
		m_x{ x }, m_y{ y },
		m_scrollarea{ x + m_text_handler->getHorizontalSpace() * horizontal_char_limit + 4, y, m_text_handler->getHorizontalSpace(), m_text_handler->getVerticalSpace() * vertical_char_limit },
		m_scrollbar{ m_scrollarea.x, m_scrollarea.y, m_text_handler->getHorizontalSpace(), 0 },
		m_scrollarea_color{ scrollarea_color }, m_scrollbar_color{ scrollbar_color }, m_x1{ m_scrollarea.x + m_scrollarea.w }, m_y1{ m_scrollarea.y + m_scrollarea.h }
	{}
	~VerticalScrollTextBox()
	{}

	void addText(const std::string& text);
	void clearText();

	void offsetScrollbarY(int scrollbar_yoffset);

	bool isWithinScrollbar(int x, int y);
	bool isWithinWhole(int x, int y);

	void render();
};

