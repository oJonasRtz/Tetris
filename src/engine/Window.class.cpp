#include "engine/Window.class.hpp"

// == Private methods ==

SDL_Texture*	Window::loadTexture(const std::string &path) {
	SDL_Surface* surface = SDL_LoadBMP(path.c_str());
	if (!surface)
		return nullptr;

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	return texture;
}

// ## Actors management ##
void Window::addActor(Actor* actor) {
	actors.push_back(actor);
};
void Window::removeActor(Actor* actor) {
	actors.erase(
		std::remove(actors.begin(), actors.end(), actor),
		actors.end()
	);
};

// == Public methods ==
// ## Constructor and Destructor ##
Window::Window(const std::string &name, size_t width, size_t height): name(name), width(width), height(height) {
	// == Variables initialization ==
	fps = 60;
	running = true;
	paused = false;

	// == SDL Initialization ==
	if (SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init() < 0) {
		std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		running = false;
		return;
	}

	window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	defaultColor = {0, 0, 0, 255}; // Black as default color
	defaultFont = TTF_OpenFont(
		"/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf",
		24
	); // Example font loading

	if (!window || !renderer) {
		std::cerr << "Window or Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		running = false;
	}

	keyEvent[SDL_KEYDOWN] = [this](SDL_Event &e){
		auto key = (t_keyboard)e.key.keysym.scancode;
		auto &k = keyboard[key];

		if (!k.pressed)
			k.down = true;

		k.pressed = true;
	};
	keyEvent[SDL_KEYUP] = [this](SDL_Event &e){
		auto key = (t_keyboard)e.key.keysym.scancode;
		auto &k = keyboard[key];

		k.up = true;
		k.pressed = false;
	};
	keyEvent[SDL_MOUSEBUTTONDOWN] = [this](SDL_Event &e){
		auto button = (t_mouse)e.button.button;
		auto &b = mouseButtons[button];

		if (!b.pressed)
			b.down = true;

		b.pressed = true;
	};
	keyEvent[SDL_MOUSEBUTTONUP] = [this](SDL_Event &e){
		auto button = (t_mouse)e.button.button;
		auto &b = mouseButtons[button];

		b.up = true;
		b.pressed = false;
	};
};
Window::~Window() {
	if (renderer) SDL_DestroyRenderer(renderer);
	if (window) SDL_DestroyWindow(window);
	if (defaultFont) TTF_CloseFont(defaultFont);

	TTF_Quit();
	SDL_Quit();
};

// ## Main loop and rendering ##
void Window::mainLoop() {
	SDL_Event event;
	size_t frameDelay = 1000 / fps;
	size_t frameStart;
	size_t frameEnd;
	uint32_t lastTime = SDL_GetTicks();

	while (running) {
		uint32_t currentTime = SDL_GetTicks();
		float deltaTime = (currentTime - lastTime) / 1000.0f; // delta time in seconds
		lastTime = currentTime;
		frameStart = SDL_GetTicks();

		resetInput();
		// == Event handling ==
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT)
				running = false;

			auto it = keyEvent.find(event.type);
			if (it != keyEvent.end())
				it->second(event);
		}
		auto copy = actors;
		for (auto &actor: copy)
			actor->events(keyboard, mouseButtons);

		// == Game running ==
		if (!paused) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set background color to black as default
			SDL_RenderClear(renderer);
		
			for (auto &actor: copy)
				actor->tick(deltaTime);
			
			SDL_RenderPresent(renderer);
		}
		//	== FPS cap ==
		frameEnd = SDL_GetTicks();
		size_t frameTime = frameEnd - frameStart;
		if (frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);

		std::cout << "\rFPS: " << (1000.0f / (SDL_GetTicks() - frameStart)) << std::flush;
	}
}
void Window::updateFPS(size_t fps) {
	this->fps = fps;
}

// ## Drawing methods ##
void Window::drawText(const std::string &text, int x, int y, const TTF_Font* font, SDL_Color color) {
	if (!font) {
		std::cerr << "Font not set!" << std::endl;
		return;
	}

	SDL_Surface* surface = TTF_RenderText_Solid(const_cast<TTF_Font*>(font), text.c_str(), color);
	if (!surface) {
		std::cerr << "Failed to create text surface! TTF_Error: " << TTF_GetError() << std::endl;
		return;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture) {
		std::cerr << "Failed to create text texture! SDL_Error: " << SDL_GetError() << std::endl;
		SDL_FreeSurface(surface);
		return;
	}

	SDL_Rect dstRect = {x, y, surface->w, surface->h};
	SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}
void Window::drawText(const std::string &text, int x, int y, SDL_Color color) {
	if (!defaultFont) {
		std::cerr << "Default font not set!" << std::endl;
		return;
	}
	drawText(text, x, y, defaultFont, color);
}
void Window::drawText(const std::string &text, int x, int y) {
	if (!defaultFont) {
		std::cerr << "Default font not set!" << std::endl;
		return;
	}
	drawText(text, x, y, defaultFont, defaultColor);
}

void Window::drawRect(int x, int y, int width, int height, SDL_Color color) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_Rect rect = {x, y, width, height};
	SDL_RenderFillRect(renderer, &rect);
}
void Window::drawLine(int x1, int y1, int x2, int y2, SDL_Color color) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}
// void Window::drawTexture(SDL_Texture* texture, int x, int y, size_t width, size_t height) {
// 	if (!texture) {
// 		std::cerr << "Invalid texture!" << std::endl;
// 		return;
// 	}

// 	SDL_Rect dstRect = {x, y, static_cast<int>(width), static_cast<int>(height)};
// 	SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
// }


// == input ==
void Window::resetInput() {
	for (auto &key: keyboard) {
		key.second.down = false;
		key.second.up = false;
	}

	for (auto &button: mouseButtons) {
		button.second.down = false;
		button.second.up = false;
	}
}
