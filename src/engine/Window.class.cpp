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
Window::Window(const std::string &name): name(name) {
	// == Variables initialization ==
	fps = 60;
	running = true;

	// == SDL Initialization ==
	if (SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init() < 0) {
		std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		running = false;
		return;
	}

	window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
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

	while (running) {
		frameStart = SDL_GetTicks();
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT)
				running = false;
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set background color to black as default
		SDL_RenderClear(renderer);

		// copy to avoid issues with actors being added/removed during iteration
		auto copy = actors;
		for (auto &actor: copy)
			actor->tick();
		
		SDL_RenderPresent(renderer);
		
		//	== Frame rate control ==
		frameEnd = SDL_GetTicks();
		size_t frameTime = frameEnd - frameStart;
		
		if (frameTime < frameDelay)
			SDL_Delay(frameDelay - frameTime);

		frameEnd = SDL_GetTicks();
		frameTime = frameEnd - frameStart;
		if (frameTime > 0)
			std::cout << "\rFPS: " << 1000 / frameTime << std::flush;
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
void Window::drawTexture(SDL_Texture* texture, int x, int y, size_t width, size_t height) {
	if (!texture) {
		std::cerr << "Invalid texture!" << std::endl;
		return;
	}

	SDL_Rect dstRect = {x, y, static_cast<int>(width), static_cast<int>(height)};
	SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
}
