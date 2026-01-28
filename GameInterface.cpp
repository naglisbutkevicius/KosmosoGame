#include "GameInterface.h"
#include "RandomEncounterFactory.h"

GameInterface::GameInterface(int mapWidth, int mapHeight, char wallChar, char floorChar,
                             int playerX, int playerY, int playerFuel, int playerHealth,
                             int destX_, int destY_)
    : map(mapWidth, mapHeight, wallChar, floorChar),
      player(playerX, playerY, playerFuel, playerHealth),
      destX(destX_),
      destY(destY_)
{
    map.setPlayer(playerX, playerY);
    map.setDestination(destX, destY);
}

void GameInterface::addPlanet(int x, int y, const std::string& name) {
    planets.emplace_back(x, y, name);
    map.placePlanet(x, y);
}

void GameInterface::addPath(int x1, int y1, int x2, int y2,
                            int fuelRequired, int riskLevel) {
    paths.emplace_back(x1, y1, x2, y2, fuelRequired, riskLevel);
}

void GameInterface::printMap() const {
    map.print();
}

int GameInterface::getPlayerX() const {
    return player.getX();
}

int GameInterface::getPlayerY() const {
    return player.getY();
}

int GameInterface::getPlayerFuel() const {
    return player.getFuel();
}

int GameInterface::getPlayerHealth() const {
    return player.getHealth();
}

bool GameInterface::isPlayerDead() const {
    return player.isDead();
}

bool GameInterface::isPlayerOutOfFuel() const {
    return player.isOutOfFuel();
}

bool GameInterface::isPlayerStuck() const {
    return getAvailablePaths().empty();
}

const Planet* GameInterface::findPlanetAt(int x, int y) const {
    for (const auto& p : planets) {
        if (p.getX() == x && p.getY() == y)
            return &p;
    }
    return nullptr;
}

std::vector<GameInterface::AvailablePath>
GameInterface::getAvailablePaths() const {
    std::vector<AvailablePath> result;
    int index = 0;

    for (const auto& p : paths) {
        auto start = p.getStart();
        if (start.first == player.getX() &&
            start.second == player.getY() &&
            p.getFuelRequired() <= player.getFuel()) {

            auto end = p.getEnd();
            const Planet* planet = findPlanetAt(end.first, end.second);

            result.push_back({
                index,
                end.first,
                end.second,
                p.getFuelRequired(),
                p.getRiskLevel(),
                planet ? planet->getName() : "Unknown"
            });
        }
        index++;
    }
    return result;
}

GameInterface::MoveResult GameInterface::attemptMove(int availablePathIndex) {
    MoveResult result{};
    const auto available = getAvailablePaths();

    if (!isValidChoiceIndex(availablePathIndex, (int)available.size())) {
        result.message = "Invalid path selection.";
        return result;
    }

    const AvailablePath& choice = available[availablePathIndex];
    const Path& path = paths[choice.index];

    if (!hasEnoughFuel(path)) {
        result.message = "Not enough fuel.";
        updateEndState(result);
        return result;
    }

    payFuel(path);
    movePlayerTo(choice.toX, choice.toY);
    result.moved = true;

    RandomEncounterFactory factory;
    Risk risk(path.getRiskLevel(), factory);
    result.encounter = risk.roll(player);

    updateEndState(result);
    applyEncounterMessage(result);

    return result;
}

bool GameInterface::isValidChoiceIndex(int idx, int size) const {
    return idx >= 0 && idx < size;
}

bool GameInterface::hasEnoughFuel(const Path& path) const {
    return player.getFuel() >= path.getFuelRequired();
}

void GameInterface::payFuel(const Path& path) {
    player.changeFuel(-path.getFuelRequired());
}

void GameInterface::movePlayerTo(int x, int y) {
    player.moveTo(x, y);
    map.movePlayerTo(x, y);
}

void GameInterface::updateEndState(MoveResult& result) const {
    result.dead = player.isDead();
    result.outOfFuel = player.isOutOfFuel();
    result.win = hasWon();
}

void GameInterface::applyEncounterMessage(MoveResult& result) const {
    if (!result.encounter.description.empty()) {
        result.message = result.encounter.description;
    }
}

bool GameInterface::hasWon() const {
    return (player.getX() == destX && player.getY() == destY);
}

