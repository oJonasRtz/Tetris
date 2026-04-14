#ifndef TETRIS_CLASS_HPP
# define TETRIS_CLASS_HPP

#include <iostream>
#include "engine/Window.class.hpp"
#include "engine/Actor.class.hpp"
#include <cmath>

class Tetris: public Actor {
	public:
		Tetris(Window &window) : Actor(window) {
			x = 50;
			y = 50;
		};
		~Tetris() {};

	protected:
		void update(float _delta) override {
			(void)_delta;
		};
		void draw() override {
			drawRect(x, y, 32, 32, {0, 0, 255, 255});
		};

		void draw_GUI() override {
			drawText("Tetris", 10, 10, {255, 255, 255, 255});
		};

		void onKeyboardEvent() override {
			auto left = keyboardCheckPressed(KEY_LEFT);
			auto right = keyboardCheckPressed(KEY_RIGHT);
			auto down = keyboardCheckPressed(KEY_DOWN);
			auto up = keyboardCheckPressed(KEY_UP);

			auto esc = keyboardCheckDown(KEY_ESCAPE);
			auto any = keyboardCheckPressed(KEY_ANY);

			int speed = 10;

			x += (right - left) * speed;
			y += (down - up) * speed;

			if (any)
				drawText("Any key pressed!", 10, 30, {255, 255, 255, 255});

			if (esc)
				gameExit();
		};
};

#endif
