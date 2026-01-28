#pragma once

#include <string>
#include "GameInterface.h"

class UserInterface {
public:
    explicit UserInterface(GameInterface& game);
    void run();

private:
    GameInterface& game;

    void clearConsole();
    void drawScreen();
    void printMenu();
    void waitForEnter();
    int readInt(const std::string& prompt);

    void handleChoice(int choice);
    void handleMove();
    void handleShowPaths();
};
