#pragma once
#include <memory>

class Encounter;

class EncounterFactory {
public:
    virtual ~EncounterFactory() = default;

    virtual std::unique_ptr<Encounter> create(int encounterId) const = 0;
};