#include "ScrollTextBox.h"

void ScrollTextBox::addText(const std::string& text)
{
	m_text.push_back(text);
	++m_number_of_lines;
	if (m_longest_string_size < text.size())
	{
		m_longest_string_size = text.size();
	}
}

void ScrollTextBox::clearText()
{
	m_text.clear();
	m_number_of_lines = 0;
	offsetScrollbarX(-1000000000);
	offsetScrollbarY(-1000000000);
}

void ScrollTextBox::offsetScrollbarX(int horizontal_scrollbar_xoffset)
{
	m_horizontal_scrollbar_xoffset += horizontal_scrollbar_xoffset;
	if (m_horizontal_scrollbar_xoffset < 0)
	{
		m_horizontal_scrollbar_xoffset = 0;
	}
	else if (m_horizontal_scrollbar_xoffset > m_horizontal_scrollarea.w - m_horizontal_scrollbar.w)
	{
		m_horizontal_scrollbar_xoffset = m_horizontal_scrollarea.w - m_horizontal_scrollbar.w;
	}
	m_text_xoffset = static_cast<int>(static_cast<double>(m_horizontal_scrollbar_xoffset) / m_horizontal_scrollarea.w * (m_longest_string_size * m_text_handler->getHorizontalSpace()));
}

void ScrollTextBox::offsetScrollbarY(int vertical_scrollbar_yoffset)
{
	m_vertical_scrollbar_yoffset += vertical_scrollbar_yoffset;
	if (m_vertical_scrollbar_yoffset < 0)
	{
		m_vertical_scrollbar_yoffset = 0;
	}
	else if (m_vertical_scrollbar_yoffset > m_vertical_scrollarea.h - m_vertical_scrollbar.h)
	{
		m_vertical_scrollbar_yoffset = m_vertical_scrollarea.h - m_vertical_scrollbar.h;
	}
	m_text_yoffset = static_cast<int>(static_cast<double>(m_vertical_scrollbar_yoffset) / m_vertical_scrollarea.h * (m_number_of_lines * m_text_handler->getVerticalSpace()));
}

bool ScrollTextBox::isWithinVerticalScrollbar(int x, int y)
{
	if (x >= m_vertical_scrollbar.x && x < (m_vertical_scrollbar.x + m_vertical_scrollbar.w) && y >= m_vertical_scrollbar.y && y < (m_vertical_scrollbar.y + m_vertical_scrollbar.h))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ScrollTextBox::isWithinHorizontalScrollbar(int x, int y)
{
	if (x >= m_horizontal_scrollbar.x && x < (m_horizontal_scrollbar.x + m_horizontal_scrollbar.w) && y >= m_horizontal_scrollbar.y && y < (m_horizontal_scrollbar.y + m_horizontal_scrollbar.h))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ScrollTextBox::isWithinHorizontalScrollarea(int x, int y)
{
	if (x >= m_horizontal_scrollarea.x && x < (m_horizontal_scrollarea.x + m_horizontal_scrollarea.w) && y >= m_horizontal_scrollarea.y && y < (m_horizontal_scrollarea.y + m_horizontal_scrollarea.h))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ScrollTextBox::isWithinWhole(int x, int y)
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

void ScrollTextBox::render()
{
	//The 2 here is a horizontal buffer between the border and the letters
	int x = m_x + 2 + (m_text_handler->getHorizontalSpace() - m_text_xoffset % m_text_handler->getHorizontalSpace()) % m_text_handler->getHorizontalSpace();
	//m_yoffset offsets the text due to scrolling
	int y = m_y - m_text_yoffset;

	for (size_t i{ 0 }; i < m_text.size(); ++i)
	{
		size_t char_number{ 0 };
		if (m_text_xoffset % m_text_handler->getHorizontalSpace() == 0) //Can display m_horizontal_char_limit number of chars
		{
			char_number = m_text_xoffset / m_text_handler->getHorizontalSpace();
			if (char_number > m_text[i].size())
			{
				y += m_text_handler->getVerticalSpace();
				continue; //Continue to the next string to render
			}
			if (y < m_y || y >(m_y + m_vertical_scrollarea.h - m_text_handler->getVerticalSpace()))
			{
			}
			else
			{
				m_text_handler->render(m_text[i].substr(char_number, m_horizontal_char_limit), x, y, 0);
			}
		}
		else //Can display m_horizontal_char_limit - 1 number of chars
		{
			char_number = m_text_xoffset / m_text_handler->getHorizontalSpace() + 1;
			if (char_number > m_text[i].size())
			{
				y += m_text_handler->getVerticalSpace();
				continue; //Continue to the next string to render
			}
			if (y < m_y || y >(m_y + m_vertical_scrollarea.h - m_text_handler->getVerticalSpace()))
			{
			}
			else
			{
				m_text_handler->render(m_text[i].substr(char_number, m_horizontal_char_limit - 1), x, y, 0);
			}
		}

		y += m_text_handler->getVerticalSpace();
	}

	if (m_longest_string_size <= m_horizontal_char_limit)
	{
	}
	else
	{
		SDL_SetRenderDrawColor(m_renderer, m_horizontal_scrollarea_color.r, m_horizontal_scrollarea_color.g, m_horizontal_scrollarea_color.b, m_horizontal_scrollarea_color.a);
		SDL_RenderFillRect(m_renderer, &m_horizontal_scrollarea);

		m_horizontal_scrollbar.x = m_horizontal_scrollarea.x + m_horizontal_scrollbar_xoffset;
		m_horizontal_scrollbar.w = static_cast<int>(static_cast<double>(m_horizontal_char_limit) / m_longest_string_size * m_horizontal_scrollarea.w);
		SDL_SetRenderDrawColor(m_renderer, m_horizontal_scrollbar_color.r, m_horizontal_scrollbar_color.g, m_horizontal_scrollbar_color.b, m_horizontal_scrollbar_color.a);
		SDL_RenderFillRect(m_renderer, &m_horizontal_scrollbar);
	}
	if (m_number_of_lines <= m_vertical_char_limit)
	{
	}
	else
	{
		SDL_SetRenderDrawColor(m_renderer, m_vertical_scrollarea_color.r, m_vertical_scrollarea_color.g, m_vertical_scrollarea_color.b, m_vertical_scrollarea_color.a);
		SDL_RenderFillRect(m_renderer, &m_vertical_scrollarea);

		m_vertical_scrollbar.y = m_vertical_scrollarea.y + m_vertical_scrollbar_yoffset;
		m_vertical_scrollbar.h = static_cast<int>(static_cast<double>(m_vertical_char_limit) / m_number_of_lines * m_vertical_scrollarea.h);
		SDL_SetRenderDrawColor(m_renderer, m_vertical_scrollbar_color.r, m_vertical_scrollbar_color.g, m_vertical_scrollbar_color.b, m_vertical_scrollbar_color.a);
		SDL_RenderFillRect(m_renderer, &m_vertical_scrollbar);
	}
}
