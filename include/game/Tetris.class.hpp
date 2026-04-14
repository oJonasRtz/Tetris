#ifndef TETRIS_CLASS_HPP
# define TETRIS_CLASS_HPP

#include <iostream>
#include "engine/Window.class.hpp"
#include "engine/Actor.class.hpp"

class Tetris: public Actor {
	public:
		Tetris(Window &window) : Actor(window) {};
		~Tetris() {};

	protected:
		void update() override {};

		void draw() override {
			this->drawText("Hello, Tetris!", 50, 50, {255, 255, 255, 255});
			this->drawRect(50, 100, 100, 100, {255, 0, 0, 255});
			this->drawLine(50, 250, 150, 350, {0, 255, 0, 255});
			// Example texture drawing (assuming you have a valid SDL_Texture* named 'texture')
			// this->drawTexture(texture, 200, 100, 64, 64);
		};
};

#endif
