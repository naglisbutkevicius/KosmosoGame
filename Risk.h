#pragma once
#include "RiskResult.h"

class Player;
class EncounterFactory;

class Risk {
public:
    Risk(int riskLevel, const EncounterFactory& factory);

    RiskResult roll(Player& player) const;

    int getLevel() const { return riskLevel; }

private:
    int riskLevel;
    const EncounterFactory& factory;
};
