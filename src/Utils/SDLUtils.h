#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Types.h"

#define screenW 1920
#define screenH 1080

typedef SDL_Color color;
static const color red = {255, 0, 0, 255};
static const color green = {0, 255, 0, 255};
static const color blue = {0, 0, 255, 255};
static const color white = {255, 255, 255, 255};

extern SDL_Window* window;
extern SDL_Renderer* rend;

bool initSDL();
void quitSDL();
SDL_Texture* loadPng(const char* path);
