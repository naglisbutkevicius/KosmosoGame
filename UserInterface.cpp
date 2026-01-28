#include "UserInterface.h"

#include <iostream>
#include <limits>
#include <cstdlib>

#include "Risk.h"

using namespace std;

UserInterface::UserInterface(GameInterface& game)
    : game(game) {}

void UserInterface::run() {
    bool running = true;

    while (running) {
        clearConsole();
        drawScreen();

        if (game.hasWon()) {
            cout << "Congratulations! You have reached your destination and won the game!\n";
            waitForEnter();
            break;
        }
        if (game.isPlayerDead()) {
            cout << "Game Over! You have died.\n";
            waitForEnter();
            break;
        }
        if (game.isPlayerOutOfFuel()) {
            cout << "Game Over! You have run out of fuel.\n";
            waitForEnter();
            break;
        }
        if (game.isPlayerStuck()) {
            cout << "Game Over! You are stuck with no available paths.\n";
            waitForEnter();
            break;
        }

        printMenu();
        int choice = readInt("");

        if (choice == 3) {
            running = false;
        } else {
            handleChoice(choice);
        }
    }
}

void UserInterface::clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void UserInterface::drawScreen() {
    game.printMap();
    std::cout << "Player at ("
          << game.getPlayerX() << ", "
          << game.getPlayerY() << ") | Fuel: "
          << game.getPlayerFuel() << " | Health: "
          << game.getPlayerHealth() << "\n";
}

void UserInterface::printMenu() {
    cout << "\nMenu:\n";
    cout << "1. Move Player\n";
    cout << "2. Show Available Paths\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
}

void UserInterface::waitForEnter() {
    std::cout << "\nPress Enter to continue...";
    std::cin.get();
}

int UserInterface::readInt(const string& prompt) {
    int choice;
    while (true) {
        cout << prompt;
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        }
    }
}

void UserInterface::handleChoice(int choice) {
    switch (choice) {
        case 1: handleMove(); break;
        case 2: handleShowPaths(); break;
        case 3: cout << "Exiting game. Goodbye!\n"; break;
        default: cout << "Invalid choice.\n"; break;
    }
}

void UserInterface::handleMove() {
    int choice = readInt("Enter the path number to move: ");

    auto res = game.attemptMove(choice - 1);

    clearConsole();
    drawScreen();

    if (!res.moved) {
        std::cout << res.message << "\n";
    } else {
        if (!res.message.empty()) std::cout << res.message << "\n";
    }

    /*
    if (res.win) {
        std::cout << "\nYou reached the destination. You win!\n";
    } else if (res.dead) {
        std::cout << "\nGame Over! You died.\n";
    } else if (res.outOfFuel) {
        std::cout << "\nGame Over! You ran out of fuel.\n";
    }*/

    waitForEnter();
}


void UserInterface::handleShowPaths() {
    auto paths = game.getAvailablePaths();

    if (paths.empty()) {
        std::cout << "No available paths from your current location.\n";
    } else {
        std::cout << "Available paths:\n";
        for (int i = 0; i < paths.size(); ++i) {
            const auto& p = paths[i];
            std::cout << i + 1 << ". To " << p.destinationName
                      << " (" << p.toX << ", " << p.toY << ")"
                      << " | Fuel: " << p.fuelRequired
                      << " | Risk: " << p.riskLevel << "\n";
        }
    }

    waitForEnter();
}

