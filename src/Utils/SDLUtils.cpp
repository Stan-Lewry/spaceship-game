#include "SDLUtils.h"
#include "Debug.h"

SDL_Window* window;
SDL_Renderer* rend;

bool initSDL()
{
    bool ret = false;

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	IMG_Init(IMG_INIT_PNG);

    SDL_DisplayMode dm;

    SDL_GetDisplayMode(0, 0, &dm);


	//window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
    //                            dm.w, dm.h, SDL_WINDOW_FULLSCREEN_DESKTOP);

    window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                640, 480, 0);

	if (window)
    {
		SDEBUG("Window Initialized");
		
        rend = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
		if (rend)
        {
            SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_BLEND);

			SDEBUG("Renderer Initialized");

			SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);

			//SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
			ret = true;
		}
    }

    return ret;
}

void quitSDL()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(rend); 
    TTF_Quit();
    SDL_Quit(); 
}

SDL_Texture* loadPng(const char* path)
{
    SDL_Surface* tempSurface = IMG_Load(path);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(rend, tempSurface);
    SDL_FreeSurface(tempSurface);
    SDEBUG("Loading asset: %s... %s", path, (texture ? "Done!" : "Failed!"));
    return texture;
}

/*
SDL_Rect boundingBoxToRect(vect<vect<float>> bb) {
    SDL_Rect res;
    res.x = bb.x.x;
    res.y = bb.x.y;

    res.w = bb.y.x - bb.x.x;
    res.h = bb.y.y - bb.x.y;

    return res;
}
*/