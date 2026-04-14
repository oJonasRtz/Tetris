#include "tetris.hpp"

int main() {
	auto window = new Window("Tetris");
	auto tetris = new Tetris(*window, 0, 0, 0, 0);
	
	
	auto b1 = new Block(*window, 100, 100, 32, 32);
	auto b2 = new Block(*window, 132, 100, 32, 32);
	auto b3 = new Block(*window, 164, 100, 32, 32);
	auto b4 = new Block(*window, 196, 100, 32, 32);

	window->updateFPS(120);
	window->mainLoop();

	delete tetris;
	delete b1;
	delete b2;
	delete b3;
	delete b4;
	delete window;
	return 0;
}
