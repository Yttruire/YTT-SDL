#pragma once
#include "TextHandler.h"

class ScrollTextBox
{
protected:
	TextHandler * m_text_handler;
	SDL_Renderer* m_renderer;
	std::vector<std::string> m_text;

	size_t m_longest_string_size{ 0 };
	int m_number_of_lines{ 0 };

	int m_x, m_y;

	int m_horizontal_char_limit;
	int m_vertical_char_limit;

	int m_text_xoffset{ 0 };
	int m_horizontal_scrollbar_xoffset{ 0 };

	int m_text_yoffset{ 0 };
	int m_vertical_scrollbar_yoffset{ 0 };

	SDL_Rect m_horizontal_scrollarea;
	SDL_Rect m_horizontal_scrollbar;
	SDL_Color m_horizontal_scrollarea_color;
	SDL_Color m_horizontal_scrollbar_color;


	SDL_Rect m_vertical_scrollarea;
	SDL_Rect m_vertical_scrollbar;
	SDL_Color m_vertical_scrollarea_color;
	SDL_Color m_vertical_scrollbar_color;

	int m_x1, m_y1;

public:
	ScrollTextBox(TextHandler* text_handler, SDL_Renderer* renderer,
		int x, int y, int horizontal_char_limit, int vertical_char_limit,
		const SDL_Color& horizontal_scrollarea_color, const SDL_Color& horizontal_scrollbar_color,
		const SDL_Color& vertical_scrollarea_color, const SDL_Color& vertical_scrollbar_color)
		: m_text_handler{ text_handler }, m_renderer{ renderer }, m_x{ x }, m_y{ y },
		m_horizontal_char_limit{ horizontal_char_limit }, m_vertical_char_limit{ vertical_char_limit },
		m_horizontal_scrollarea{ x, y + m_text_handler->getVerticalSpace() * vertical_char_limit, m_text_handler->getHorizontalSpace() * horizontal_char_limit + 4, m_text_handler->getVerticalSpace() / 2 },
		m_horizontal_scrollbar{ m_horizontal_scrollarea.x, m_horizontal_scrollarea.y, 0, m_text_handler->getVerticalSpace() / 2 },
		m_horizontal_scrollarea_color{ horizontal_scrollarea_color }, m_horizontal_scrollbar_color{ horizontal_scrollbar_color },
		m_vertical_scrollarea{ x + m_text_handler->getHorizontalSpace() * horizontal_char_limit + 4, y, m_text_handler->getHorizontalSpace(), m_text_handler->getVerticalSpace() * vertical_char_limit },
		m_vertical_scrollbar{ m_vertical_scrollarea.x, m_vertical_scrollarea.y, m_text_handler->getHorizontalSpace(), 0 },
		m_vertical_scrollarea_color{ vertical_scrollarea_color }, m_vertical_scrollbar_color{ vertical_scrollbar_color }, 
		m_x1{ m_vertical_scrollarea.x +  m_vertical_scrollarea.w }, m_y1{ m_horizontal_scrollarea.y + m_horizontal_scrollarea.h}
	{}
	~ScrollTextBox() {}

	void addText(const std::string& text);
	void clearText();

	void offsetScrollbarX(int horizontal_scrollbar_xoffset);
	void offsetScrollbarY(int vertical_scrollbar_yoffset);

	bool isWithinVerticalScrollbar(int x, int y);
	bool isWithinHorizontalScrollbar(int x, int y);
	bool isWithinHorizontalScrollarea(int x, int y);
	bool isWithinWhole(int x, int y);

	void render();
};
