#include "Risk.h"
#include "EncounterFactory.h"
#include "Encounter.h"
#include "Player.h"
#include <cstdlib>

Risk::Risk(int riskLevel, const EncounterFactory& factory)
    : riskLevel(riskLevel), factory(factory) {}

RiskResult Risk::roll(Player& player) const {
    RiskResult result{};

    int roll = (std::rand() % 100) + 1;
    if (roll > riskLevel) {
        result.type = RiskResultType::NONE;
        result.description = "No risk encountered.";
        return result;
    }

    int encounterId = std::rand() % 4;
    auto encounter = factory.create(encounterId);
    return encounter->resolve(player);
}
