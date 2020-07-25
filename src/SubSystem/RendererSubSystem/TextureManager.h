#pragma once

#include "../../Utils/SDLUtils.h"
#include "../../Utils/Debug.h"

#include <map>

struct Texture {
    Texture(SDL_Texture* t, SDL_Rect r)
        : spriteSheet(t)
        , sourceRect(r) {}
    SDL_Texture* spriteSheet;
    SDL_Rect sourceRect;
};

class TextureManager {
public:
    TextureManager();
    virtual ~TextureManager();

    Texture* getTexture(std::string resourceId);

    typedef std::map<std::string, Texture*> TextureMap;

    void initializeResource(char* path);

private:
    TextureMap textureMap;
};