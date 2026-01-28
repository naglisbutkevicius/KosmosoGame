#pragma once

#include <utility>

class Path {
public:
    Path(int x1, int y1, int x2, int y2, int fuelRequired, int riskLevel);

    std::pair<int, int> getStart() const;
    std::pair<int, int> getEnd() const;

    int getFuelRequired() const;
    int getRiskLevel() const;

private:
    int x1;
    int y1;
    int x2;
    int y2;
    int fuelRequired;
    int riskLevel;
};
