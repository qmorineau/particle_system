#include "ScancodeResolver.hpp"

#include <GLFW/glfw3.h>

ScancodeResolver::ScancodeResolver()
{
	_table[static_cast<int>(Scancode::KEY_ESC)] = resolve(GLFW_KEY_ESCAPE, "KEY_ESC");
	_table[static_cast<int>(Scancode::KEY_TAB)] = resolve(GLFW_KEY_TAB, "KEY_TAB");
	_table[static_cast<int>(Scancode::KEY_G)] = resolve(GLFW_KEY_G, "KEY_G");
	_table[static_cast<int>(Scancode::KEY_E)] = resolve(GLFW_KEY_E, "KEY_E");
	_table[static_cast<int>(Scancode::KEY_1)] = resolve(GLFW_KEY_1, "KEY_1");
	_table[static_cast<int>(Scancode::KEY_2)] = resolve(GLFW_KEY_2, "KEY_2");
	_table[static_cast<int>(Scancode::KEY_R)] = resolve(GLFW_KEY_R, "KEY_R");
	_table[static_cast<int>(Scancode::KEY_C)] = resolve(GLFW_KEY_C, "KEY_C");
	_table[static_cast<int>(Scancode::KEY_F1)] = resolve(GLFW_KEY_F1, "KEY_F1");
	_table[static_cast<int>(Scancode::KEY_F2)] = resolve(GLFW_KEY_F2, "KEY_F2");
	_table[static_cast<int>(Scancode::KEY_W)] = resolve(GLFW_KEY_W, "KEY_W");
	_table[static_cast<int>(Scancode::KEY_A)] = resolve(GLFW_KEY_A, "KEY_A");
	_table[static_cast<int>(Scancode::KEY_S)] = resolve(GLFW_KEY_S, "KEY_S");
	_table[static_cast<int>(Scancode::KEY_D)] = resolve(GLFW_KEY_D, "KEY_D");
	_table[static_cast<int>(Scancode::KEY_LEFT)] = resolve(GLFW_KEY_LEFT, "KEY_LEFT");
	_table[static_cast<int>(Scancode::KEY_RIGHT)] = resolve(GLFW_KEY_RIGHT, "KEY_RIGHT");
	_table[static_cast<int>(Scancode::KEY_UP)] = resolve(GLFW_KEY_UP, "KEY_UP");
	_table[static_cast<int>(Scancode::KEY_DOWN)] = resolve(GLFW_KEY_DOWN, "KEY_DOWN");
}

ScancodeResolver::~ScancodeResolver() = default;

int ScancodeResolver::get(Scancode sc) const
{
	return _table.at(static_cast<int>(sc));
};

int ScancodeResolver::resolve(int glfwkey, std::string name)
{
	int sc = glfwGetKeyScancode(glfwkey);
	if (sc == -1)
	{
		throw std::runtime_error(std::string("ScancodeResolver: failed to resolve scancode for " + name));
	}
	return sc;
}