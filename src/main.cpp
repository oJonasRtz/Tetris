#include "tetris.hpp"

int main() {
	auto window = new Window("Tetris");
	auto tetris = new Tetris(*window);

	window->updateFPS(120);
	window->mainLoop();

	delete tetris;
	delete window;
	return 0;
}
