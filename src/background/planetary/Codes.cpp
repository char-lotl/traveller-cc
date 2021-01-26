#include <vector>
#include <string>
#include "Codes.h"

const trade_code Codes::TCS[Codes::TOTAL_TRADE_CODES] = {
    [AGRICULTURAL] = AGRICULTURAL,
    [ASTEROID] = ASTEROID,
    [BARREN] = BARREN,
    [DESERT] = DESERT,
    [FLUID_OCEANS] = FLUID_OCEANS,
    [GARDEN] = GARDEN,
    [HIGH_POPULATION] = HIGH_POPULATION,
    [HIGH_TECHNOLOGY] = HIGH_TECHNOLOGY,
    [ICE_CAPPED] = ICE_CAPPED,
    [INDUSTRIAL] = INDUSTRIAL,
    [LOW_POPULATION] = LOW_POPULATION,
    [LOW_TECHNOLOGY] = LOW_TECHNOLOGY,
    [NON_AGRICULTURAL] = NON_AGRICULTURAL,
    [NON_INDUSTRIAL] = NON_INDUSTRIAL,
    [POOR] = POOR,
    [RICH] = RICH,
    [VACUUM] = VACUUM,
    [WATER_WORLD] = WATER_WORLD
};

const std::string Codes::TC_STRINGS[Codes::TOTAL_TRADE_CODES] = {
    "Agricultural",
    "Asteroid",
    "Barren",
    "Desert",
    "Fluid Oceans",
    "Garden",
    "High Population",
    "High Technology",
    "Ice-capped",
    "Industrial",
    "Low Population",
    "Low Technology",
    "Non-Agricultural",
    "Non-Industrial",
    "Poor",
    "Rich",
    "Vacuum",
    "Water World"
};

Codes::Codes(const bool& an) :
trade_codes_long(0777777 * an) {
    
}

bool Codes::include_code(const trade_code& tc) const {
    return FLAGS[tc] & trade_codes_long;
}

bool Codes::overlaps(const Codes& c) const {
    return trade_codes_long & c.trade_codes_long;
}

std::vector<trade_code> Codes::get_codes_as_vector() const {
    std::vector<trade_code> tcv;
    for (int i = 0; i < TOTAL_TRADE_CODES; i++) {
        if (include_code(TCS[i])) tcv.push_back(TCS[i]);
    }
	return tcv;
}

bool Codes::empty() const {
    return (trade_codes_long == 0);
}

Codes Codes::add_code(const trade_code& tc) const {
    return Codes(trade_codes_long | FLAGS[tc]);
}

Codes Codes::intersect(const Codes& c) const {
    return Codes(trade_codes_long & c.trade_codes_long);
}
