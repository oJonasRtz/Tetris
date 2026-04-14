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

		void onKeyboardEvent(const std::unordered_map<t_keyboard, t_input> &key) override {
			auto left = key.find(KEY_LEFT) != key.end() ? key.at(KEY_LEFT) : t_input{};
			auto right = key.find(KEY_RIGHT) != key.end() ? key.at(KEY_RIGHT) : t_input{};
			auto down = key.find(KEY_DOWN) != key.end() ? key.at(KEY_DOWN) : t_input{};
			auto up = key.find(KEY_UP) != key.end() ? key.at(KEY_UP) : t_input{};

			int speed = 10;


			x += (right.pressed ? speed : 0) - (left.pressed ? speed : 0);
			y += (down.pressed ? speed : 0) - (up.pressed ? speed : 0);
		};
};

#endif
