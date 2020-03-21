#include "main.h"
#include <utility>
#include <iostream>

enum class LeftClickActive
{
	NONE = 0,
	VERTSCROLL_TEXT1,
	HORISCROLL_TEXT1,
	SCROLL_TEXT1_VERT,
	SCROLL_TEXT1_HORI
};

enum class MiddleClickActive
{
	NONE = 0,
	VERTSCROLL_TEXT1,
	HORISCROLL_TEXT1,
	SCROLL_TEXT1
};

enum class MouseOverActive
{
	NONE = 0,
	VERTSCROLL_TEXT1,
	HORISCROLL_TEXT1,
	SCROLL_TEXT1_HORI,
	SCROLL_TEXT1_WHOLE
};

int main(int argc, char* args[])
{
	try
	{
		GraphicsHandler main_window(800, 640);
		TextHandler text_handler(main_window.getRenderer(), "UbuntuMono-R.ttf", 12);
		LeftClickActive left_click_active = LeftClickActive::NONE;
		MiddleClickActive middle_click_active = MiddleClickActive::NONE;
		SDL_Point middle_click_pos;
		SDL_Point current_mouse_pos;
		double scroll_amount_x{ 0 };
		double scroll_amount_y{ 0 };
		MouseOverActive mouse_over_active = MouseOverActive::NONE;

		GTexture texture{ 1, 2, 3, 4, 1,2 ,3, 4, nullptr };
		if (texture.getSrcrect())
		{
			std::cout << "not nullptr";
		}
		main_window.addRenderTexture(std::move(texture));
		if (!texture.getSrcrect())
		{
			std::cout << "\nnullptr";
		}

		TextBox text1(&text_handler, 5, 0, 20);
		text1.addText("Welcome to the main menu");
		text1.addText("Program is currently a work in progress");
		text1.addText("Version: 0.1.2 INDEV");
		text1.addText(__DATE__);
		text1.addText(__TIME__);

		BorderedTextBox bordered_text1(&text_handler, main_window.getRenderer(), 200, 0, 20, 5);
		bordered_text1.addText("Welcome to the main menu");
		bordered_text1.addText("Program is currently a work in progress");
		bordered_text1.addText("Version: 0.1.2 INDEV");


		ColoredBorderedTextBox colored_text1(&text_handler, main_window.getRenderer(), 5, 200, 20, 5, SDL_Color{ 0xff,0,0,0xff });
		colored_text1.addText("Welcome to the main menu");
		colored_text1.addText("Program is currently a work in progress");
		colored_text1.addText("Version: 0.1.2 INDEV");

		VerticalScrollTextBox vertscroll_text1(&text_handler, main_window.getRenderer(), 200, 200, 25, 5, SDL_Color{ 0xaa, 0,0, 0xff }, SDL_Color{ 0, 0xaa, 0xff, 0xff });
		vertscroll_text1.addText("Welcome to the main menu");
		vertscroll_text1.addText("Program is currently a work in progressfsfsafsfafsafdsadsadsa");
		vertscroll_text1.addText("Version: 0.1.2 INDEV");
		vertscroll_text1.addText("Version: 0.1.2 INDEV2");
		vertscroll_text1.addText("Version: 0.1.2 INDEV3");
		vertscroll_text1.addText("Version: 0.1.2 INDEV4");
		vertscroll_text1.addText("Version: 0.1.2 INDEV5");
		vertscroll_text1.addText("Version: 0.1.2 INDEV6");
		vertscroll_text1.addText("Version: 0.1.2 INDEV7");
		vertscroll_text1.addText("Version: 0.1.2 INDEV8");
		vertscroll_text1.addText("Version: 0.1.2 INDEV9");

		HorizontalScrollTextBox horiscroll_text1(&text_handler, main_window.getRenderer(), 5, 400, 25, 5, SDL_Color{ 0xaa, 0,0, 0xff }, SDL_Color{ 0, 0xaa, 0xff, 0xff });
		horiscroll_text1.addText("Welcome to the main menu");
		horiscroll_text1.addText("Program is currently a work in progress");
		horiscroll_text1.addText("Version: 0.1.2 INDEV");
		horiscroll_text1.addText("Version: 0.1.2 INDEV222222222222222222222222222e");

		ScrollTextBox scroll_text1(&text_handler, main_window.getRenderer(), 200, 400, 35, 7, SDL_Color{ 0xaa, 0,0, 0xff }, SDL_Color{ 0, 0xaa, 0xff, 0xff }, SDL_Color{ 0xaa, 0,0, 0xff }, SDL_Color{ 0, 0xaa, 0xff, 0xff });
		scroll_text1.addText("Welcome to the main menu");
		scroll_text1.addText("Program is currently a work in progress");
		scroll_text1.addText("Version: 0.1.2 INDEV");
		scroll_text1.addText("Version: 0.1.2 INDEV222222222222222222222222222e");
		scroll_text1.addText("Welcome to the main menu");
		scroll_text1.addText("Program is currently a work in progressfsfsafsfafsafdsadsadsa");
		scroll_text1.addText("Version: 0.1.2 INDEV");
		scroll_text1.addText("Version: 0.1.2 INDEV2");
		scroll_text1.addText("Version: 0.1.2 INDEV3");
		scroll_text1.addText("Version: 0.1.2 INDEV4");
		scroll_text1.addText("Version: 0.1.2 INDEV5");
		scroll_text1.addText("Version: 0.1.2 INDEV6");
		scroll_text1.addText("Version: 0.1.2 INDEV7");
		scroll_text1.addText("Version: 0.1.2 INDEV8");
		scroll_text1.addText("Version: 0.1.2 INDEV9");

		SDL_Event evnt;
		bool quit = false;
		while (!quit)
		{

			//Handle events
			while (SDL_PollEvent(&evnt) != 0)
			{
				switch (evnt.type)
				{
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_WINDOWEVENT:
					main_window.handleWindowEvent(evnt);
					break;
				case SDL_KEYDOWN:
					if (evnt.key.keysym.sym == SDLK_UP)
					{
						
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					if (evnt.button.button == SDL_BUTTON_LEFT)
					{
						if (vertscroll_text1.isWithinScrollbar(evnt.button.x, evnt.button.y))
						{
							left_click_active = LeftClickActive::VERTSCROLL_TEXT1;
						}
						else if (horiscroll_text1.isWithinScrollbar(evnt.button.x, evnt.button.y))
						{
							left_click_active = LeftClickActive::HORISCROLL_TEXT1;
						}
						else if (scroll_text1.isWithinVerticalScrollbar(evnt.button.x, evnt.button.y))
						{
							left_click_active = LeftClickActive::SCROLL_TEXT1_VERT;
						}
						else if (scroll_text1.isWithinHorizontalScrollbar(evnt.button.x, evnt.button.y))
						{
							left_click_active = LeftClickActive::SCROLL_TEXT1_HORI;
						}
					}
					else if (evnt.button.button == SDL_BUTTON_MIDDLE)
					{
						middle_click_pos = { evnt.button.x, evnt.button.y };
						if (vertscroll_text1.isWithinWhole(evnt.button.x, evnt.button.y))
						{
							middle_click_active = MiddleClickActive::VERTSCROLL_TEXT1;
						}
						else if (horiscroll_text1.isWithinWhole(evnt.button.x, evnt.button.y))
						{
							middle_click_active = MiddleClickActive::HORISCROLL_TEXT1;
						}
						else if (scroll_text1.isWithinWhole(evnt.button.x, evnt.button.y))
						{
							middle_click_active = MiddleClickActive::SCROLL_TEXT1;
						}
					}
					break;
				case SDL_MOUSEBUTTONUP:
					if (evnt.button.button == SDL_BUTTON_LEFT)
					{
						left_click_active = LeftClickActive::NONE;
					}
					else if (evnt.button.button == SDL_BUTTON_MIDDLE)
					{
						middle_click_active = MiddleClickActive::NONE;
						scroll_amount_x = 0;
						scroll_amount_y = 0;
					}
					break;
				case SDL_MOUSEMOTION:

					switch (left_click_active)
					{
					case LeftClickActive::VERTSCROLL_TEXT1:
						vertscroll_text1.offsetScrollbarY(evnt.motion.yrel);
						break;
					case LeftClickActive::HORISCROLL_TEXT1:
						horiscroll_text1.offsetScrollbarX(evnt.motion.xrel);
						break;
					case LeftClickActive::SCROLL_TEXT1_VERT:
						scroll_text1.offsetScrollbarY(evnt.motion.yrel);
						break;
					case LeftClickActive::SCROLL_TEXT1_HORI:
						scroll_text1.offsetScrollbarX(evnt.motion.xrel);
						break;
					case LeftClickActive::NONE:
						break;
					}

					if (vertscroll_text1.isWithinWhole(evnt.motion.x, evnt.motion.y))
					{
						mouse_over_active = MouseOverActive::VERTSCROLL_TEXT1;
					}
					else if (horiscroll_text1.isWithinWhole(evnt.motion.x, evnt.motion.y))
					{
						mouse_over_active = MouseOverActive::HORISCROLL_TEXT1;
					}
					else if (scroll_text1.isWithinHorizontalScrollarea(evnt.motion.x, evnt.motion.y))
					{
						mouse_over_active = MouseOverActive::SCROLL_TEXT1_HORI;
					}
					else if (scroll_text1.isWithinWhole(evnt.motion.x, evnt.motion.y))
					{
						mouse_over_active = MouseOverActive::SCROLL_TEXT1_WHOLE;
					}
					else
					{
						mouse_over_active = MouseOverActive::NONE;
					}

					current_mouse_pos = { evnt.motion.x, evnt.motion.y };
					break;
				case SDL_MOUSEWHEEL:
					switch (mouse_over_active)
					{
					case MouseOverActive::VERTSCROLL_TEXT1:
						vertscroll_text1.offsetScrollbarY(-evnt.wheel.y * 10);
						break;
					case MouseOverActive::HORISCROLL_TEXT1:
						horiscroll_text1.offsetScrollbarX(-evnt.wheel.y * 10);
						break;
					case MouseOverActive::SCROLL_TEXT1_HORI:
						scroll_text1.offsetScrollbarX(-evnt.wheel.y * 10);
						break;
					case MouseOverActive::SCROLL_TEXT1_WHOLE:
						scroll_text1.offsetScrollbarY(-evnt.wheel.y * 10);
						scroll_text1.offsetScrollbarX(-evnt.wheel.x * 10);
						break;
					}
					break;
				}

			}

			switch (middle_click_active)
			{
			case MiddleClickActive::VERTSCROLL_TEXT1:
				scroll_amount_y += static_cast<double>(current_mouse_pos.y - middle_click_pos.y) / 10;
				vertscroll_text1.offsetScrollbarY(static_cast<int>(scroll_amount_y));
				scroll_amount_y -= static_cast<int>(scroll_amount_y);
				break;
			case MiddleClickActive::HORISCROLL_TEXT1:
				scroll_amount_x += static_cast<double>(current_mouse_pos.x - middle_click_pos.x) / 10;
				horiscroll_text1.offsetScrollbarX(static_cast<int>(scroll_amount_x));
				scroll_amount_x -= static_cast<int>(scroll_amount_x);
				break;
			case MiddleClickActive::SCROLL_TEXT1:
				scroll_amount_x += static_cast<double>(current_mouse_pos.x - middle_click_pos.x) / 10;
				scroll_amount_y += static_cast<double>(current_mouse_pos.y - middle_click_pos.y) / 10;
				scroll_text1.offsetScrollbarX(static_cast<int>(scroll_amount_x));
				scroll_text1.offsetScrollbarY(static_cast<int>(scroll_amount_y));
				scroll_amount_x -= static_cast<int>(scroll_amount_x);
				scroll_amount_y -= static_cast<int>(scroll_amount_y);
				break;
			}

			//Handle text rendering
			//text_handler.render("Welcome to the main menu", 5, 0, 0);
			//text_handler.render("Program is currently a work in progress", 5, 0, 1);
			//text_handler.render("Version: 0.1.0 INDEV", 5, 0, 2);

			bordered_text1.render();
			text1.render();
			colored_text1.render();
			vertscroll_text1.render();
			horiscroll_text1.render();
			scroll_text1.render();


			//Handle graphics rendering
			main_window.render();
		}

	}
	catch (std::exception& e)
	{
		ypu::logError(e.what());
		return -1;
	}
	return 0;
}