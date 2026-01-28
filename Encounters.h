#pragma once
#include "Encounter.h"
#include <string>

class MeteorShowerEncounter : public Encounter {
private:
    static constexpr int DAMAGE = 20;
public:
    RiskResult resolve(Player& player) const override {
        RiskResult result;
        result.type = RiskResultType::METEOR_SHOWER;
        result.description = "A meteor shower damages your ship!";
        result.healthImpact = -DAMAGE;
        player.changeHealth(result.healthImpact);
        return result;
    }
};

class PirateAttackEncounter : public Encounter {
private:
    static constexpr int DAMAGE = 15;
public:
    RiskResult resolve(Player& player) const override {
        RiskResult result;
        result.type = RiskResultType::PIRATE_ATTACK;
        result.description = "Pirates attack and damage your ship!";
        result.healthImpact = -DAMAGE;
        player.changeHealth(result.healthImpact);
        return result;
    }
};

class FuelLeakEncounter : public Encounter {
private:
    static constexpr int FUEL_LOSS = 15;
public:
    RiskResult resolve(Player& player) const override {
        RiskResult result;
        result.type = RiskResultType::FUEL_LEAK;
        result.description = "A fuel leak reduces your fuel reserves!";
        result.fuelImpact = -FUEL_LOSS;
        player.changeFuel(result.fuelImpact);
        return result;
    }
};

class NavigationFailureEncounter : public Encounter {
private:
    static constexpr int FUEL_LOSS = 10;
public:
    RiskResult resolve(Player& player) const override {
        RiskResult result;
        result.type = RiskResultType::NAVIGATION_FAILURE;
        result.description = "Navigation failure makes you waste fuel!";
        result.fuelImpact = -FUEL_LOSS;
        player.changeFuel(result.fuelImpact);
        return result;
    }
};