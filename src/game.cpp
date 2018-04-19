#include "game.h"

SDL_Renderer* Game::renderer = nullptr;

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

	player = std::make_shared<GameObject>("res/sprites/character/engineer-idle.png", 0, 0);
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
	player->update();
}

void Game::render()
{
	SDL_RenderClear(renderer);
	player->render();
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