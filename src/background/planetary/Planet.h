#ifndef PLANET_H
#define PLANET_H

#include <array>
#include "Codes.h"

enum planetary_attribute {
    PLANET_SIZE,
    ATMOSPHERE,
    TEMPERATURE,
    HYDROLOGY,
    POPULATION,
    GOVERNMENT,
    LAW_LEVEL,
    TECHNOLOGY_LEVEL,
    STARPORT_RATING
};

const int NUM_PLANETARY_ATTRIBUTES = 9;

enum base_type {
    NAVAL,
    SCOUT,
    RESEARCH,
    TAS,
    IMPERIAL,
    PIRATE
};

class Planet {
private:
    //int planet_size;
    //int atmosphere;
    //int temperature;
    //int hydrology;
    //int population;
    //int government;
    //int law_level;
    //int tech_level;
    //int starport_rating;
    std::array<int,NUM_PLANETARY_ATTRIBUTES> attributes;
    std::array<bool,6> bases_present;
    Codes trade_codes;
public:
    Planet(int ps, int atmos, int temp, int hydro, int pop,
           int gov, int lawlev, int techlev, int sr, std::array<bool,6> bp);
    bool has_trade_code(const trade_code& tc) const;
    bool has_base_presence(const base_type& bt) const;
    int get_attribute(const planetary_attribute& which_attr) const;
    bool meets_environmental_limit() const;
    Codes get_trade_codes() const;
};

#endif
