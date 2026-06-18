#include"Game.h"
#include <SFML/Graphics.hpp>
#include <optional>
#include <ctime>

int main()
{
    srand(time(0));
    game G;
    G.Run();
    return 0;
}
