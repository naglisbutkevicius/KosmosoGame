#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "MapCreator.h"
#include "Player.h"
#include "Planet.h"
#include "GameInterface.h"
#include "UserInterface.h"

using namespace std;
int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    GameInterface game(50, 8, '#', ' ', 1, 6, 100, 100, 47, 1);
    game.addPlanet(1, 6, "ERath");

    game.addPlanet(10, 4, "Mon");
    game.addPlanet(25, 5, "Mar");
    game.addPlanet(25, 2, "Venis");
    game.addPlanet(38, 2, "Montreal");
    game.addPlanet(47, 1, "Earth");
    game.addPath(1, 6, 10, 4, 15, 0);
    game.addPath(10, 4, 25, 5, 20, 30);
    game.addPath(10, 4, 25, 2, 25, 40);
    game.addPath(25, 5, 38, 2, 30, 50);
    game.addPath(25, 2, 38, 2, 10, 10);
    game.addPath(38, 2, 47, 1, 15, 50);

    UserInterface ui(game);
    ui.run();

    return 0;
}