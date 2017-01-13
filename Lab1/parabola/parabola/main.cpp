#include "stdafx.h"
#include "AbstractWindow.h"
#include "Window.h"
#include <glm/vec2.hpp>

#ifdef _WIN32
#undef main
#endif

int main()
{
	CWindow window;
	window.Show({ 600, 600 });
	window.DoGameLoop();

	return 0;
}
