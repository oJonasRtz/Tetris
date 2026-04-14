
#ifndef ACTOR_CLASS_HPP
# define ACTOR_CLASS_HPP

#include <iostream>
#include <cstddef>
#include <climits>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Actor.structs.hpp"
#include <unordered_map>
#include <typeindex>

class Window;

class Actor {
	private:
		t_sprite	*sprite;
		Window	&render;

		void tick(float _delta) {
			preUpdate(_delta);
			update(_delta);
			postUpdate(_delta);

			preDraw();
			draw();
			draw_GUI();
			postDraw();
		};

		void events() {
			onKeyboardEvent();
			onMouseEvent();
		}

		// == Input handling helpers ==
		enum e_input_state {
			PRESSED,
			DOWN,
			UP
		};
		bool checkState(const t_input &i, e_input_state state) const;
		bool inputKeyHelper(t_keyboard key, e_input_state state) const;
		bool inputMouseHelper(t_mouse button, e_input_state state) const;

		friend class Window;
	public:
		Actor(Window &window, int x, int y, int width, int height);
		virtual ~Actor();

		// == getters ==
		int getX() const { return x; };
		int getY() const { return y; };
		int getWidth() const { return width; };
		int getHeight() const { return height; };
		virtual std::type_index getType() const { return typeid(*this); };

	protected:
		int x, y, width, height;

		// == Events(Runs every frame) ==
		virtual void preUpdate(float _delta) { (void)_delta; };
		virtual void update(float _delta) { (void)_delta; };
		virtual void postUpdate(float _delta) { (void)_delta; };

		virtual void preDraw() {};
		virtual void draw() {};
		virtual void postDraw() {};

		virtual void draw_GUI() {};

		// == Input handling ==
		virtual void	onKeyboardEvent() {}
		virtual void	onMouseEvent() {};

		// == Utility methods ==
		size_t getFPS() const;
		size_t getWindowWidth() const;
		size_t getWindowHeight() const;

		// == Physics methods ==
		void	setPosition(int newX, int newY);
		bool	placeMeeting(int x, int y, std::type_index type) const;

		// == Draw methods ==
		void drawText(const std::string &text, int x, int y, SDL_Color color = {0, 0, 0, 255});
		void drawRect(int x, int y, int width, int height, SDL_Color color = {0, 0, 0, 255});
		void drawLine(int x1, int y1, int x2, int y2, SDL_Color color = {0, 0, 0, 255});
		// void drawTexture(SDL_Texture* texture, int x, int y, size_t width, size_t height);

		// == Running events ==
		void	gameStop();
		void	gameResume();
		void	gameExit();

		// == Input checks ==
		bool keyboardCheckPressed(t_keyboard key) const;
		bool keyboardCheckDown(t_keyboard key) const;	
		bool keyboardCheckUp(t_keyboard key) const;

		bool mouseCheckPressed(t_mouse button) const;
		bool mouseCheckDown(t_mouse button) const;
		bool mouseCheckUp(t_mouse button) const;
};

#endif
