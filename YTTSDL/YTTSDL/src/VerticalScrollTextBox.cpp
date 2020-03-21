#include "VerticalScrollTextBox.h"

void VerticalScrollTextBox::addText(const std::string& text)
{
	m_text.push_back(text);
	m_number_of_lines += (text.size() - 1) / m_horizontal_char_limit + 1;
}

void VerticalScrollTextBox::clearText()
{
	m_text.clear();
	m_number_of_lines = 0;
	offsetScrollbarY(-1000000000);
}

void VerticalScrollTextBox::offsetScrollbarY(int scrollbar_yoffset)
{
	m_scrollbar_yoffset += scrollbar_yoffset;
	if (m_scrollbar_yoffset < 0)
	{
		m_scrollbar_yoffset = 0;
	}
	else if (m_scrollbar_yoffset > m_scrollarea.h - m_scrollbar.h)
	{
		m_scrollbar_yoffset = m_scrollarea.h - m_scrollbar.h;
	}
	m_text_yoffset = static_cast<int>(static_cast<double>(m_scrollbar_yoffset) / m_scrollarea.h * (m_number_of_lines * m_text_handler->getVerticalSpace()));
}

bool VerticalScrollTextBox::isWithinScrollbar(int x, int y)
{
	if (x >= m_scrollbar.x && x < (m_scrollbar.x + m_scrollbar.w) && y >= m_scrollbar.y && y < (m_scrollbar.y + m_scrollbar.h))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool VerticalScrollTextBox::isWithinWhole(int x, int y)
{
	if (x >= m_x && x < m_x1 && y >= m_y && y < m_y1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void VerticalScrollTextBox::render()
{
	//The 2 here is a horizontal buffer between the border and the letters
	int x = m_x + 2; 
	//m_yoffset offsets the text due to scrolling
	int y = m_y - m_text_yoffset;

	int chars_to_render;
	for (size_t i{ 0 }; i < m_text.size(); ++i)
	{
		size_t char_number{ 0 };
		chars_to_render = m_text[i].size();
		do
		{
			if (y < m_y || y > (m_y + m_scrollarea.h - m_text_handler->getVerticalSpace()))
			{
			}
			else
			{
				m_text_handler->render(m_text[i].substr(char_number, m_horizontal_char_limit), x, y, 0);
			}
			char_number += m_horizontal_char_limit;
			y += m_text_handler->getVerticalSpace();
			chars_to_render -= m_horizontal_char_limit;
		} while (chars_to_render > 0);
	}
	if (m_number_of_lines <= m_vertical_char_limit)
	{
	}
	else
	{
		SDL_SetRenderDrawColor(m_renderer, m_scrollarea_color.r, m_scrollarea_color.g, m_scrollarea_color.b, m_scrollarea_color.a);
		SDL_RenderFillRect(m_renderer, &m_scrollarea);

		m_scrollbar.y = m_scrollarea.y + m_scrollbar_yoffset;
		m_scrollbar.h = static_cast<int>(static_cast<double>(m_vertical_char_limit) / m_number_of_lines * m_scrollarea.h);
		SDL_SetRenderDrawColor(m_renderer, m_scrollbar_color.r, m_scrollbar_color.g, m_scrollbar_color.b, m_scrollbar_color.a);
		SDL_RenderFillRect(m_renderer, &m_scrollbar);
	}
}
