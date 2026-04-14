#include "engine/Actor.class.hpp"
#include "engine/Window.class.hpp"


// == Constructor and Destructor ==
Actor::Actor(Window &window) : render(window) {
	x = 0;
	y = 0;
	render.addActor(this);
};
Actor::~Actor() {
	render.removeActor(this);
};

// == Utility methods ==
void Actor::drawText(const std::string &text, int x, int y, SDL_Color color) {
	render.drawText(text, x, y, color);
}
void Actor::drawRect(int x, int y, int width, int height, SDL_Color color) {
	render.drawRect(x, y, width, height, color);
}
void Actor::drawLine(int x1, int y1, int x2, int y2, SDL_Color color) {
	render.drawLine(x1, y1, x2, y2, color);
}
// void Actor::drawTexture(SDL_Texture* texture, int x, int y, size_t width, size_t height) {
// 	render.drawTexture(texture, x, y, width, height);
// }
