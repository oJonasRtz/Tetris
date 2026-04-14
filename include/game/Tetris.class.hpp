#ifndef TETRIS_CLASS_HPP
# define TETRIS_CLASS_HPP

#include <iostream>
#include "engine/Window.class.hpp"
#include "engine/Actor.class.hpp"
#include <cmath>

class Tetris: public Actor {
	public:
		Tetris(Window &window) : Actor(window) {
			width = 32;
			height = 32;

			x = getWindowWidth() / 2 - width / 2;
			y = getWindowHeight() / 2 - height / 2;
		};
		~Tetris() {};

	protected:
		bool any = false;
		bool none = true;
		int side = 1;
		int renderSide = 1;

		void update(float _delta) override {
			(void)_delta;
		};
		void preDraw() override {
			if (side != 0)
				renderSide = side;
		}
		void draw() override {
			drawRect(x, y, width, height, {0, 0, 255, 255});
			//Eye
			int eyeW = width / 4;
			int eyeH = height / 2;

			int eyeX = x + width / 2 + (renderSide * (width / 4)) - (eyeW / 2);
			int eyeY = y + height / 4;

			drawRect(eyeX, eyeY, eyeW, eyeH, {255, 255, 255, 255});
		 };

		void draw_GUI() override {
			drawText("Tetris", 10, 10, {255, 255, 255, 255});

			if (none)
				drawText("NO KEY PRESSED", 10, 40, {255, 0, 0, 255});
			if (any)
				drawText("ANY KEY PRESSED", 10, 40, {255, 0, 0, 255});
		};

		void onKeyboardEvent() override {
			auto left = keyboardCheckPressed(KEY_LEFT);
			auto right = keyboardCheckPressed(KEY_RIGHT);
			auto down = keyboardCheckPressed(KEY_DOWN);
			auto up = keyboardCheckPressed(KEY_UP);

			auto esc = keyboardCheckDown(KEY_ESCAPE);
			any = keyboardCheckPressed(KEY_ANY);
			none = keyboardCheckPressed(KEY_NONE);

			int speed = 10;

			side = right - left;

			x += (right - left) * speed;
			y += (down - up) * speed;

			if (esc)
				gameExit();
		};
};

#endif
