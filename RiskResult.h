#pragma once
#include <string>

enum class RiskResultType {
    NONE,
    METEOR_SHOWER,
    PIRATE_ATTACK,
    FUEL_LEAK,
    NAVIGATION_FAILURE
};

struct RiskResult {
    RiskResultType type = RiskResultType::NONE;
    std::string description;
    int healthImpact = 0;
    int fuelImpact = 0;
};