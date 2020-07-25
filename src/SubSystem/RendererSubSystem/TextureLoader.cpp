#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "TextureLoader.h"

std::vector<std::string> split(std::string str, char delim)
{
    std::stringstream ss(str);
    std::string segment;
    std::vector<std::string> output;

    while(std::getline(ss, segment, delim))
    {
        output.push_back(segment);
    }

    return output;
}

TextureManager::TextureMap TextureLoader::generateTextureMapFromFile(std::string assetFile)
{
    TextureManager::TextureMap textureMap;
    std::ifstream file;
    std::string line;
   
    file.open(assetFile.c_str());
    if (file.is_open())
    {
        std::string path;

        getline(file, line);

        path = split(line, '=').at(1);

        SDL_Texture* texture = loadPng(path.c_str());

        if (texture)
        {         
            bool error = false;
            int lineNum = 1;

            while (getline(file, line) && !error)
            {
                ++lineNum;

                if (line == "[tile]")
                {
                    SDL_Rect sourceRect;
                    std::string id;
                    bool hasId, hasX, hasY, hasW, hasH = false;

                    while (getline(file, line) && line != "[endtile]" && !error)
                    {
                        ++lineNum;

                        auto list = split(line, '=');
                        if (list.size() == 2)
                        {
                            std::string tag = list.at(0);
                            std::string value = list.at(1);

                            if (tag == "id")
                            {
                                id = value;
                                hasId = true;
                            }
                            else if (tag == "startX")
                            {
                                sourceRect.x = std::stoi(value);
                                hasX = true;
                            }
                            else if (tag == "startY")
                            {
                                sourceRect.y = std::stoi(value);
                                hasY = true;
                            }
                            else if (tag == "width")
                            {
                                sourceRect.w = std::stoi(value);
                                hasW = true;
                            }
                            else if (tag == "height")
                            {
                                sourceRect.h = std::stoi(value);
                                hasH = true;
                            }
                            else
                            {
                                error = true;
                            }
                        }
                        else
                        {
                            error = true;
                        }
                    }

                    if (hasId && hasX && hasY && hasW && hasH)
                    {
                        Texture* newTexture = new Texture(texture, sourceRect);
                        textureMap.insert({id, newTexture});
                    }
                    else
                    {
                        error = true;
                    }
                }
                else
                {
                    error = true;
                }
            }

            if(error)
            {
                SERROR("Failed to parse asset file. Error at line %d.", lineNum);
            }
        }
        else
        {
            SERROR("Failed to load specified texture.");
        }

        file.close();
    }
    else
    {
        SERROR("Failed to open file.");
    }

    return textureMap;
}