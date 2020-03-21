#pragma once
#include "TextHandler.h"

//A textbox with an invisible border, where text that is too long to be displayed on one line in the box, it will automatically be moved to the next line
class TextBox
{
protected:
	TextHandler* m_text_handler;
	std::vector<std::string> m_text;

	int m_horizontal_char_limit;

	int m_x;
	int m_y;

public:
	TextBox(TextHandler* text_handler, int x, int y, int horizontal_char_limit) : m_text_handler{ text_handler }, m_x{ x }, m_y{ y }, 
		m_horizontal_char_limit{ horizontal_char_limit }
	{}
	~TextBox()
	{}

	void addText(const std::string& text) { m_text.push_back(text); }
	void clearText() { m_text.clear(); }

	void render();
};

