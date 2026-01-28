#include "Path.h"

Path::Path(int x1, int y1, int x2, int y2, int fuelRequired, int riskLevel)
    : x1(x1),
      y1(y1),
      x2(x2),
      y2(y2),
      fuelRequired(fuelRequired),
      riskLevel(riskLevel) {}

std::pair<int, int> Path::getStart() const {
    return {x1, y1};
}

std::pair<int, int> Path::getEnd() const {
    return {x2, y2};
}

int Path::getFuelRequired() const {
    return fuelRequired;
}

int Path::getRiskLevel() const {
    return riskLevel;
}
