#include "HorizontalScrollTextBox.h"

void HorizontalScrollTextBox::addText(const std::string& text)
{
	m_text.push_back(text);
	if (m_longest_string_size < text.size())
	{
		m_longest_string_size = text.size();
	}
}
void HorizontalScrollTextBox::clearText()
{
	m_text.clear();
	offsetScrollbarX(-1000000000);
}

void HorizontalScrollTextBox::offsetScrollbarX(int scrollbar_xoffset)
{
	m_scrollbar_xoffset += scrollbar_xoffset;
	if (m_scrollbar_xoffset < 0)
	{
		m_scrollbar_xoffset = 0;
	}
	else if (m_scrollbar_xoffset > m_scrollarea.w - m_scrollbar.w)
	{
		m_scrollbar_xoffset = m_scrollarea.w - m_scrollbar.w;
	}
	m_text_xoffset = static_cast<int>(static_cast<double>(m_scrollbar_xoffset) / m_scrollarea.w * (m_longest_string_size * m_text_handler->getHorizontalSpace()));
}

bool HorizontalScrollTextBox::isWithinScrollbar(int x, int y)
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

bool HorizontalScrollTextBox::isWithinWhole(int x, int y)
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

void HorizontalScrollTextBox::render()
{
	//The 2 here is a horizontal buffer between the border and the letters
	int x = m_x + 2 + (m_text_handler->getHorizontalSpace() - m_text_xoffset % m_text_handler->getHorizontalSpace()) % m_text_handler->getHorizontalSpace();
	int y = m_y;

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
			m_text_handler->render(m_text[i].substr(char_number, m_horizontal_char_limit), x, y, 0);
		}
		else //Can display m_horizontal_char_limit - 1 number of chars
		{
			char_number = m_text_xoffset / m_text_handler->getHorizontalSpace() + 1;
			if (char_number > m_text[i].size())
			{
				y += m_text_handler->getVerticalSpace();
				continue; //Continue to the next string to render
			}
			m_text_handler->render(m_text[i].substr(char_number, m_horizontal_char_limit - 1), x, y, 0);
		}

		y += m_text_handler->getVerticalSpace();
	}

	if (m_longest_string_size <= m_horizontal_char_limit)
	{
	}
	else
	{
		SDL_SetRenderDrawColor(m_renderer, m_scrollarea_color.r, m_scrollarea_color.g, m_scrollarea_color.b, m_scrollarea_color.a);
		SDL_RenderFillRect(m_renderer, &m_scrollarea);

		m_scrollbar.x = m_scrollarea.x + m_scrollbar_xoffset;
		m_scrollbar.w = static_cast<int>(static_cast<double>(m_horizontal_char_limit) / m_longest_string_size * m_scrollarea.w);
		SDL_SetRenderDrawColor(m_renderer, m_scrollbar_color.r, m_scrollbar_color.g, m_scrollbar_color.b, m_scrollbar_color.a);
		SDL_RenderFillRect(m_renderer, &m_scrollbar);
	}
}
