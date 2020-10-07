#pragma once
#include<SDL.h>
#include "SDL_image.h"

//class GameObject;
enum GameState
{
	Menu=1,
	Play,
	Pause,
	GameOver
};;

class Game {
private:
	bool isRunning;
	int PLayerScore=0;
	
	SDL_Window *pWindow;
	
public:

	static SDL_Renderer* pRenderer;
	
	Game();
	~Game();

	void Init(const char *WindowTitle, int xpos, int ypos, int width, int height, bool isFullScreen);

	void Prepare();
	void HandleEvents();
	void Input();
	void Update();
	void Render();
	void Clean();
	void Quit();
	void Destroy();

	bool running()
	{
		return isRunning;
	}
};
