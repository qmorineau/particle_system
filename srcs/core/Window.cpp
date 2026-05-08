#include "Window.hpp"
#include "Application.hpp"
#include "InputManager.hpp"

Window::Window(Application* app)
{
	// glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

    // glfw window creation
    // --------------------
    _window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Scop", NULL, NULL);
    if (_window == NULL)
		throw GLWF_WindowError();

	glfwMakeContextCurrent(_window);
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetWindowUserPointer(_window, app);

    glfwMakeContextCurrent(_window);
    glfwSetFramebufferSizeCallback(_window, Window::framebufferSizeCallback);
	glfwSetCursorPosCallback(_window, InputManager::mouseCallback);
    glfwSetScrollCallback(_window, InputManager::scrollCallback);
	glfwSetMouseButtonCallback(_window, InputManager::mouseButtonCallback);
	glfwSetKeyCallback(_window, InputManager::keyCallback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw GLAD_Error();

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_PROGRAM_POINT_SIZE);
}

Window::~Window()
{
	if (_window)
	{
		glfwDestroyWindow(_window);
		_window = nullptr;
	}
	glfwTerminate();
}

void Window::manageTitle(Application& app)
{
	_title = "Particles System ";
	float fps = 1.f / std::max(app.getDelta(), 0.0001f);
	std::string strFps = std::to_string(static_cast<int>(fps));
	_title.append("[" + strFps + " fps]");
	std::string speed = std::to_string(static_cast<int>(app.scene()->getTimeSpeed() * 100));
	_title.append("	- Speed: " + speed + "%");
	std::string gravityState(app.scene()->getGravity() ? "On" : "Off");
	_title.append(" - Gravity: " + gravityState);
	std::string emitterState(app.scene()->getEmitter() ? "On" : "Off");
	_title.append(" - Emitter: " + emitterState);
	if (_isMouse && app.scene()->getTracking() != Scene::PosTracked::None && app.scene()->getTracking() != Scene::PosTracked::Mouse)
	{
		std::string str;
		Scene::PosTracked tmp = app.scene()->getTracking();
		if (tmp == Scene::PosTracked::Gravity)
			str = "Gravity";
		else
			str = "Emitter";
		_title.append(" - [Moving: " + str + " position]");
	}
	glfwSetWindowTitle(_window, _title.c_str());
}

void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	(void) window;
    glViewport(0, 0, width, height);
}

void Window::closeWindow()
{
	glfwSetWindowShouldClose(_window, true);
};

void Window::enableMouse()
{
	if (!_isMouse)
	{
		_isMouse = true;
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

void Window::disableMouse()
{
	if (_isMouse)
	{
		_isMouse = false;
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}