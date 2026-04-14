#ifndef BLOCK_CLASS_HPP
# define BLOCK_CLASS_HPP

#include <iostream>
#include "engine/Window.class.hpp"
#include "engine/Actor.class.hpp"

class Block: public Actor {
	public:
		Block(Window &window) : Actor(window) {};
		~Block() {};
};

#endif
