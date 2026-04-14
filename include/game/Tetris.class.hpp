#ifndef TETRIS_CLASS_HPP
# define TETRIS_CLASS_HPP

#include <iostream>
#include "engine/Window.class.hpp"
#include "engine/Actor.class.hpp"
#include <cmath>
#include "game/Block.class.hpp"

class Tetris: public Actor {
	public:
		Tetris(Window &window, int x, int y, int width, int height) : Actor(window, x, y, width, height) {
			this->width = 32;
			this->height = 32;

			this->x = getWindowWidth() / 2 - this->width / 2;
			this->y = getWindowHeight() / 2 - this->height / 2;
		};
		~Tetris() {};

	protected:
		bool any = false;
		bool none = true;
		int side = 1;
		int renderSide = 1;

		bool left = false;
		bool right = false;
		bool up = false;
		bool down = false;

		int speed = 10;

		void update(float _delta) override {
			(void)_delta;

			float dx = (right - left) * speed;
			float dy = (down - up) * speed;

			if (!placeMeeting(x + dx, y, typeid(Block)))
				x += dx;
			if (!placeMeeting(x, y + dy, typeid(Block)))
				y += dy;
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

			// light zone
			drawRect(50, 100, 200, 200, {255, 255, 0, 128});
			drawRect(250, 100, 200, 200, {255, 0, 255, 128});
			drawRect(150, 300, 200, 200, {255, 255, 255, 128});
		};

		void draw_GUI() override {
			drawText("Tetris", 10, 10, {255, 255, 255, 255});

			if (none)
				drawText("NO KEY PRESSED", 10, 40, {255, 0, 0, 255});
			if (any)
				drawText("ANY KEY PRESSED", 10, 40, {255, 0, 0, 255});
		};

		void onKeyboardEvent() override {
			left = keyboardCheckPressed(KEY_LEFT);
			right = keyboardCheckPressed(KEY_RIGHT);
			down = keyboardCheckPressed(KEY_DOWN);
			up = keyboardCheckPressed(KEY_UP);

			auto esc = keyboardCheckDown(KEY_ESCAPE);
			any = keyboardCheckPressed(KEY_ANY);
			none = keyboardCheckPressed(KEY_NONE);

			if (esc)
				gameExit();
		};
};

#endif
