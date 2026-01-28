#pragma once
#include "RiskResult.h"
#include "Player.h"

class Encounter {
public:
    virtual ~Encounter() = default;

    virtual RiskResult resolve(Player& player) const = 0;
};