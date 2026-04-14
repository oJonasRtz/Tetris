
#ifndef ACTOR_CLASS_HPP
# define ACTOR_CLASS_HPP

#include <iostream>
#include <cstddef>
#include <climits>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Window;

class Actor {
	private:
		Window &render;

		void tick() {
			update();
			draw();
		};
		friend class Window;

	public:
		Actor(Window &window);
		virtual ~Actor();

	protected:
		// == Events(Runs every frame) ==
		virtual void update() = 0;
		virtual void draw() = 0;

		// == Utility methods ==
		void drawText(const std::string &text, int x, int y, SDL_Color color = {0, 0, 0, 255});
		void drawRect(int x, int y, int width, int height, SDL_Color color = {0, 0, 0, 255});
		void drawLine(int x1, int y1, int x2, int y2, SDL_Color color = {0, 0, 0, 255});
		void drawTexture(SDL_Texture* texture, int x, int y, size_t width, size_t height);
};

#endif
