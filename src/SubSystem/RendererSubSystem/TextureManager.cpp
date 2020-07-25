#include "TextureManager.h"
#include "TextureLoader.h"

TextureManager::TextureManager()
    : textureMap() {
    SDEBUG("Constructing TextureManager");
}

TextureManager::~TextureManager() {
    SDEBUG("Destructing TextureManager");
}

void TextureManager::initializeResource(char* path) {
    TextureMap newMap = TextureLoader::generateTextureMapFromFile(path);
    textureMap.insert(newMap.begin(), newMap.end());
}

Texture* TextureManager::getTexture(std::string resourceId) {
    Texture* t = nullptr;
    if (textureMap.find(resourceId) != textureMap.end()) {
        t = textureMap.at(resourceId);
    } 
    return t;
}