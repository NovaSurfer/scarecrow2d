#include "game.h"

SDL_Renderer* Game::renderer = nullptr;

Manager manager;
auto& player(manager.add_entity());

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	const unsigned short int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;

	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << ":: SUBSYSTEMS INITIALIZED ::" << std::endl;
		
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if(window)
		{
			std::cout << ":: WINDOW CREATED ::" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0); 
		if(renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			std::cout << ":: RENDERER CREATED ::" << std::endl;
		}

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	levelMap = std::make_shared<LevelMap>();
	player.add_component<Transform>(400, 300);
	player.add_component<Sprite>("res/sprites/character/engineer-idle.png");
}

void Game::handle_events()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
		case SDL_QUIT:
			isRunning = false;
		default: break;
	}
}

void Game::update()
{
	manager.refresh();
	manager.update();
}

void Game::render()
{
	SDL_RenderClear(renderer);

	levelMap->draw_map();
	manager.draw();

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	IMG_Quit();
	SDL_Quit();
	std::cout << ":: GAME CLEANED ::" << std::endl;
}