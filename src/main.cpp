#include "Utils/SDLUtils.h"
#include "Utils/Debug.h"
#include "GameEngine.h"
#include "Entity/SpaceshipGame.h"

int main (int argv, char* argc[])
{
    SDEBUG("Starting...");

    if (argv > 1)
    {
        SDEBUG("Argument %s", argc[0]);
    }

    if (initSDL())
    {
        GameEngine* ge = GameEngine::getInstance();

        SpaceshipGame* sg = new SpaceshipGame();

        ge->run();

        delete sg;
    }
    else
    {
        SDEBUG("Failed to initialize SDL");
    }

    SDEBUG("Stopping");
    return 0;
}