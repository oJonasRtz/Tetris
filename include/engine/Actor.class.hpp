
#ifndef ACTOR_CLASS_HPP
# define ACTOR_CLASS_HPP

#include <iostream>
#include <cstddef>
#include <climits>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Actor.structs.hpp"
#include <unordered_map>

class Window;

class Actor {
	private:
		t_sprite	*sprite;
		Window	&render;

		void tick(float _delta) {
			update(_delta);
			draw();
		};

		void events(
			const std::unordered_map<t_keyboard, t_input> &keyboard,
			const std::unordered_map<t_mouse, t_input> &mouse
		) {
			onKeyboardEvent(keyboard);
			onMouseEvent(mouse);
		};

		friend class Window;
	public:
		Actor(Window &window);
		virtual ~Actor();

	protected:
		int x, y;

		// == Events(Runs every frame) ==
		virtual void update(float _delta) {
			(void)_delta;
		};
		virtual void draw() {};

		// == Utility methods ==
		size_t getFPS() const;
		size_t getWindowWidth() const;
		size_t getWindowHeight() const;

		// == Physics methods ==
		void	setPosition(int newX, int newY);
		//void	checkCollision(const Actor &other);

		// == Draw methods ==
		void drawText(const std::string &text, int x, int y, SDL_Color color = {0, 0, 0, 255});
		void drawRect(int x, int y, int width, int height, SDL_Color color = {0, 0, 0, 255});
		void drawLine(int x1, int y1, int x2, int y2, SDL_Color color = {0, 0, 0, 255});
		// void drawTexture(SDL_Texture* texture, int x, int y, size_t width, size_t height);

		// == Running events ==
		void	gameStop();
		void	gameResume();
		void	gameExit();

		// == Input handling ==
		virtual void	onKeyboardEvent(const std::unordered_map<t_keyboard, t_input> &key) {
			(void)key;
		};
		virtual void	onMouseEvent(const std::unordered_map<t_mouse, t_input> &button) {
			(void)button;
		};
};

#endif
