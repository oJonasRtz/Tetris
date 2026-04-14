#ifndef WINDOW_CLASS_HPP
# define WINDOW_CLASS_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Actor.class.hpp"
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <functional>

class Window {
	private:
		SDL_Window* window;
		SDL_Renderer* renderer;
		TTF_Font* defaultFont;
		SDL_Color defaultColor;

		bool running;
		bool paused;
		std::string name;
		size_t fps;
		size_t width;
		size_t height;

		// Keys
		std::unordered_map<uint32_t, std::function<void(SDL_Event&)>> keyEvent;
		std::unordered_map<t_keyboard, t_input> keyboard;
		std::unordered_map<t_mouse, t_input> mouseButtons;

		//	== Instances Running ==
		std::vector<Actor*> actors;

		void addActor(Actor* actor);
		void removeActor(Actor* actor);
		SDL_Texture* loadTexture(const std::string &path);

		friend class Actor;
	public:
		Window(const std::string &name, size_t width = 800, size_t height = 600);
		~Window();

		void mainLoop();
		void updateFPS(size_t fps = 60);

		// == Drawing methods ==
		void drawText(const std::string &text, int x, int y, const TTF_Font* font, SDL_Color color);
		void drawText(const std::string &text, int x, int y, SDL_Color color);
		void drawText(const std::string &text, int x, int y);

		void drawRect(int x, int y, int width, int height, SDL_Color color);
		void drawLine(int x1, int y1, int x2, int y2, SDL_Color color);
		// void drawTexture(const std::string &texture, int x, int y, size_t width, size_t height);

		// ==  Running events ==
		void stop() { paused = true; };
		void resume() { paused = false; };
		void exit() { running = false; };

		// == input ==
		void resetInput();
};

#endif
