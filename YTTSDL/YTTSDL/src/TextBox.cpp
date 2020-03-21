#include "TextBox.h"

void TextBox::render()
{
	int x = m_x + 2; //The 2 here is a horizontal buffer between the border and the letters
	
	int line_number{ 0 };
	int chars_to_render;
	for (size_t i{ 0 }; i < m_text.size(); ++i)
	{
		chars_to_render = m_text[i].size();
		int char_number{ 0 };
		do
		{
			chars_to_render -= m_horizontal_char_limit;
			m_text_handler->render(m_text[i].substr(char_number, char_number + m_horizontal_char_limit), x, m_y, line_number);
			char_number += m_horizontal_char_limit;
			++line_number;
		} while (chars_to_render > 0);
	}
}