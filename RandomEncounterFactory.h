#pragma once
#include "EncounterFactory.h"
#include "Encounters.h"
#include <memory>

class RandomEncounterFactory : public EncounterFactory {
public:
    std::unique_ptr<Encounter> create(int encounterId) const override {
        switch (encounterId) {
            case 0:
                return std::make_unique<MeteorShowerEncounter>();
            case 1:
                return std::make_unique<PirateAttackEncounter>();
            case 2:
                return std::make_unique<FuelLeakEncounter>();
            default:
                return std::make_unique<NavigationFailureEncounter>();
        }
    }
};