#include "engine/Actor.class.hpp"
#include "engine/Window.class.hpp"


// == Constructor and Destructor ==
Actor::Actor(Window &window, int x, int y, int width, int height) : render(window) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
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

// === Utility methods ===
size_t Actor::getFPS() const {
	return render.fps;
}
size_t Actor::getWindowWidth() const {
	return render.width;
}
size_t Actor::getWindowHeight() const {
	return render.height;
}

// == Physics methods ==
void Actor::setPosition(int newX, int newY) {
	x = newX;
	y = newY;
}

bool Actor::placeMeeting(int x, int y, std::type_index type) const {
	for (auto actor: render.actors) {
		if (actor == this || actor->getType() != type)
			continue;

		if (
			x < actor->getX() + actor->getWidth() &&
			x + getWidth() > actor->getX() &&
			y < actor->getY() + actor->getHeight() &&
			y + getHeight() > actor->getY()
		)
			return true;
	}

	return false;
}

// == Running events ==
void Actor::gameStop() {
	render.stop();
}
void Actor::gameResume() {
	render.resume();
}
void Actor::gameExit() {
	render.exit();
}

// === Input ===
bool Actor::checkState(const t_input &i, e_input_state state) const {
	switch (state) {
		case PRESSED: return i.pressed;
		case DOWN: return i.down;
		case UP: return i.up;
	}
	return false;
}

bool Actor::inputKeyHelper(t_keyboard key, e_input_state state) const {
	// ANY handling
	if (key == KEY_ANY) {
		for (auto &k: render.keyboard)
			if (checkState(k.second, state))
				return (true);

		return (false);
	}
	// NONE handling
	if (key == KEY_NONE) {
		for (auto &k: render.keyboard)
			if (checkState(k.second, state))
				return (false);

		return (true);
	}

	// Normal key handling
	auto it = render.keyboard.find(key);
	if (it == render.keyboard.end())
		return false;

	return checkState(it->second, state);
}
bool Actor::inputMouseHelper(t_mouse button, e_input_state state) const {
	// ANY handling
	if (button == MOUSE_ANY) {
		for (auto &b: render.mouseButtons)
			if (checkState(b.second, state))
				return (true);

		return (false);
	}
	// NONE handling
	if (button == MOUSE_NONE) {
		for (auto &b: render.mouseButtons)
			if (checkState(b.second, state))
				return (false);

		return (true);
	}

	// Normal button handling
	auto it = render.mouseButtons.find(button);
	if (it == render.mouseButtons.end())
		return false;

	return checkState(it->second, state);
}


bool Actor::keyboardCheckPressed(t_keyboard key) const {
	return inputKeyHelper(key, PRESSED);
}
bool Actor::keyboardCheckDown(t_keyboard key) const {
	return inputKeyHelper(key, DOWN);
}
bool Actor::keyboardCheckUp(t_keyboard key) const {
	return inputKeyHelper(key, UP);
}


bool Actor::mouseCheckPressed(t_mouse button) const {
	return inputMouseHelper(button, PRESSED);
}
bool Actor::mouseCheckDown(t_mouse button) const {
	return inputMouseHelper(button, DOWN);
}
bool Actor::mouseCheckUp(t_mouse button) const {
	return inputMouseHelper(button, UP);
}
