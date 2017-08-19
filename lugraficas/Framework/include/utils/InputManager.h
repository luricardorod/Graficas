#ifndef PATO_INPUT_MANAGER_H
#define PATO_INPUT_MANAGER_H

#include "../Config.h"

#ifdef USING_SDL
#include <SDL/SDL_keysym.h>
#elif defined(USING_FREEGLUT)
#include <GL/freeglut.h>
#endif

#define MAXKEYS 512
#define MAXMOUSEBUTTONS 5


class InputManager {
public:
	InputManager();
	bool	PressedOnceKey(int key);
	bool	PressedOnceMouseButton(int mb);

	bool	PressedKey(int key);
	bool	PressedMouseButton(int mb);

	bool	KeyStates[2][MAXKEYS];
	bool	MouseButtonStates[2][MAXMOUSEBUTTONS];

	int		xDelta;
	int 	yDelta;
};

#endif
