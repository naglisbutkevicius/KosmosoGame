#include "catch_amalgamated.hpp"

#include "Player.h"
#include "GameInterface.h"
#include "Encounters.h"

// ---------- Player state-change tests ----------

TEST_CASE("Player fuel decreases and clamps to zero") {
    Player p(0, 0, 10, 100);

    p.changeFuel(-3);
    REQUIRE(p.getFuel() == 7);
    REQUIRE_FALSE(p.isOutOfFuel());

    p.changeFuel(-999);
    REQUIRE(p.getFuel() == 0);
    REQUIRE(p.isOutOfFuel());
}

TEST_CASE("Player health decreases and clamps to zero") {
    Player p(0, 0, 100, 10);

    p.changeHealth(-4);
    REQUIRE(p.getHealth() == 6);
    REQUIRE_FALSE(p.isDead());

    p.changeHealth(-999);
    REQUIRE(p.getHealth() == 0);
    REQUIRE(p.isDead());
}

// ---------- Encounter interaction tests (deterministic) ----------

TEST_CASE("MeteorShower encounter reduces player health") {
    Player p(0, 0, 100, 100);
    MeteorShowerEncounter e;

    RiskResult r = e.resolve(p);

    REQUIRE(r.type == RiskResultType::METEOR_SHOWER);
    REQUIRE(r.healthImpact < 0);
    REQUIRE(r.fuelImpact == 0);
    REQUIRE(p.getHealth() == 100 + r.healthImpact);
}

TEST_CASE("PirateAttack encounter reduces player health") {
    Player p(0, 0, 100, 100);
    PirateAttackEncounter e;

    RiskResult r = e.resolve(p);

    REQUIRE(r.type == RiskResultType::PIRATE_ATTACK);
    REQUIRE(r.healthImpact < 0);
    REQUIRE(r.fuelImpact == 0);
    REQUIRE(p.getHealth() == 100 + r.healthImpact);
}

TEST_CASE("FuelLeak encounter reduces player fuel") {
    Player p(0, 0, 50, 100);
    FuelLeakEncounter e;

    RiskResult r = e.resolve(p);

    REQUIRE(r.type == RiskResultType::FUEL_LEAK);
    REQUIRE(r.fuelImpact < 0);
    REQUIRE(r.healthImpact == 0);
    REQUIRE(p.getFuel() == 50 + r.fuelImpact);
}

TEST_CASE("NavigationFailure encounter reduces player fuel") {
    Player p(0, 0, 50, 100);
    NavigationFailureEncounter e;

    RiskResult r = e.resolve(p);

    REQUIRE(r.type == RiskResultType::NAVIGATION_FAILURE);
    REQUIRE(r.fuelImpact < 0);
    REQUIRE(r.healthImpact == 0);
    REQUIRE(p.getFuel() == 50 + r.fuelImpact);
}

// ---------- GameInterface calculation + interaction tests ----------

TEST_CASE("getAvailablePaths returns only paths from current position and affordable by fuel") {
    GameInterface game(10, 6, '#', ' ', 1, 1, 10, 100, 8, 4);

    game.addPlanet(1, 1, "Start");
    game.addPlanet(3, 1, "A");
    game.addPlanet(4, 1, "B");

    game.addPath(1, 1, 3, 1, 5, 0);
    game.addPath(1, 1, 4, 1, 50, 0);

    auto paths = game.getAvailablePaths();
    REQUIRE(paths.size() == 1);
    REQUIRE(paths[0].toX == 3);
    REQUIRE(paths[0].toY == 1);
    REQUIRE(paths[0].fuelRequired == 5);
}

TEST_CASE("attemptMove invalid index does not move the player") {
    GameInterface game(10, 6, '#', ' ', 1, 1, 10, 100, 8, 4);
    game.addPlanet(1, 1, "Start");

    auto res = game.attemptMove(0);

    REQUIRE_FALSE(res.moved);
    REQUIRE(game.getPlayerX() == 1);
    REQUIRE(game.getPlayerY() == 1);
    REQUIRE(res.message.find("Invalid") != std::string::npos);
}
