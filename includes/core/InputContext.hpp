#ifndef INPUTCONTEXTHPP
#define INPUTCONTEXTHPP

struct InputContext
{
	bool	keys[1024] = {false};
	double	mouseX = 0;
	double	mouseY = 0;
	bool	mouseMoved = false;
	double	mouseOffsetX = 0;
	double	mouseOffsetY = 0;
	bool	mouseScrolled = false;
};

#endif