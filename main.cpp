#include <iostream>
#include "Game.h"

using namespace std;

int main()
{
    srand(time(NULL));
    Game g;
    g.run();
    return 0;
}