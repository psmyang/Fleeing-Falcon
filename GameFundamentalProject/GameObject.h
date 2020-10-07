#pragma once
#include <SDL.h>
#include "AniManager.h"

class GameObject
{
public:
	GameObject(const char* TextureSheet,int x,int y);
	~GameObject();

	GameObject(GameObject const&) {};
	GameObject& operator=(GameObject const&) {};
	
	void Update();
	void Render();
	void Move(int x,int y);
	void Destroy();
	void setActive(bool NewStatus);
	bool getActive() { return isActive; }

	bool isCollidingWith(const GameObject& other);

	SDL_Rect getSrcRect() const
	{
		return SrcRect;
	}

	SDL_Rect getDestRect() const
	{
   		return DestRect;
	}

	SDL_Texture* getObjTex() { return ObjTexture; }
	
protected:
	int xpos;
	int ypos;
	bool isActive;

	SDL_Texture* ObjTexture;
	SDL_Rect SrcRect, DestRect;
};
