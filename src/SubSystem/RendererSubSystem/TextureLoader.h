#pragma once

#include "../../Utils/SDLUtils.h"
#include "../../Utils/Debug.h"
#include "TextureManager.h"

#include <map>

class TextureLoader
{
public:
    static TextureManager::TextureMap generateTextureMapFromFile(std::string assetFile);

private:
    TextureLoader();
};


