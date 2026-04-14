#ifndef TETRIS_CLASS_HPP
# define TETRIS_CLASS_HPP

#include <iostream>
#include "engine/Window.class.hpp"
#include "engine/Actor.class.hpp"
#include <cmath>

class Tetris: public Actor {
	public:
		Tetris(Window &window) : Actor(window) {};
		~Tetris() {};

	protected:
		int side = 1;
		float time = 0.0f;
		size_t messageIndex = 0;
		int cnt = 0;
		std::string message = std::to_string(cnt) + " - Hello, Tetris!";
		void update() override {
			x += side;
			if (x + 100 >= 800 || x < 0) side = -side;

			time += 0.05f;
			messageIndex++;
			if (messageIndex % 60 == 0)
				message = std::to_string(cnt++) + " - Hello, Tetris!";
		};

		void draw() override {
			this->drawText(message, 50, 50, {255, 255, 255, 255});
			this->drawRect(50, 100, 100 + x, 100, {255, 0, 0, 255});
			
			int centerY = 300;
			int amplitude = 80;
			float frequency = 0.02f;

			int prevX = 0;
			int prevY = centerY;

			for (int x = 0; x < 800; x++) {
				int y = centerY + static_cast<int>(
					std::sin((frequency * x) + time) * amplitude
				);

				if (x > 0) {
					this->drawLine(prevX, prevY, x, y, {0, 255, 0, 255});
				}
				prevX = x;
				prevY = y;

			}
		};
};

#endif
