#ifndef INC_2D_ENGINE_GAME_H
#define INC_2D_ENGINE_GAME_H

#include "SDL.h"
#include "SDL_image.h"
#include "levelmap.h"
#include "components/components.h"

#include <iostream>
#include <memory>

// TODO: Is there is a way to avoid **Cyclic Dependency**
class GameObject;
class LevelMap;

class Game
{
public:
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	void handle_events();
	void update();
	void render();
	void clean();

	bool running() const { return isRunning; }

	static SDL_Renderer *renderer;

private:
	bool isRunning;
	SDL_Window *window;
	std::shared_ptr<LevelMap> levelMap;
};

#endif //INC_2D_ENGINE_GAME_H