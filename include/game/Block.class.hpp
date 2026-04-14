#ifndef BLOCK_CLASS_HPP
# define BLOCK_CLASS_HPP

#include <iostream>
#include "engine/Window.class.hpp"
#include "engine/Actor.class.hpp"

class Block: public Actor {
	public:
		Block(Window &window, int x, int y, int width, int height) : Actor(window, x, y, width, height) {};
		~Block() {};

	protected:
		void draw() override {
			auto white = SDL_Color{255, 255, 255, 255};
			
			drawRect(x, y, width, height, white);
		};
};

#endif
