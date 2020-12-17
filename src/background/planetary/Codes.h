#ifndef CODES_H
#define CODES_H

//#include <list>
#include <vector>
#include <string>

enum trade_code {
    AGRICULTURAL,
    ASTEROID,
    BARREN,
    DESERT,
    FLUID_OCEANS,
    GARDEN,
    HIGH_POPULATION,
    HIGH_TECHNOLOGY,
    ICE_CAPPED,
    INDUSTRIAL,
    LOW_POPULATION,
    LOW_TECHNOLOGY,
    NON_AGRICULTURAL,
    NON_INDUSTRIAL,
    POOR,
    RICH,
    VACUUM,
    WATER_WORLD
};

class Codes {
public:
    long trade_codes_long;
    // the class's only data member!
    
    constexpr Codes(const long& tcl) : trade_codes_long(tcl) {}
    Codes(const bool& all_or_nothing);
    bool include_code(const trade_code& tc) const;
    bool empty() const;
    bool overlaps(const Codes& c) const;
    //std::list<trade_code> get_codes_as_list() const;
    std::vector<trade_code> get_codes_as_vector() const;
    Codes add_code(const trade_code& tc) const;
    Codes intersect(const Codes& c) const;
    
    static constexpr int TOTAL_TRADE_CODES = 18;
    static constexpr long FLAGS[TOTAL_TRADE_CODES] = {
        [AGRICULTURAL] = 1 << AGRICULTURAL,
        [ASTEROID] = 1 << ASTEROID,
        [BARREN] = 1 << BARREN,
        [DESERT] = 1 << DESERT,
        [FLUID_OCEANS] = 1 << FLUID_OCEANS,
        [GARDEN] = 1 << GARDEN,
        [HIGH_POPULATION] = 1 << HIGH_POPULATION,
        [HIGH_TECHNOLOGY] = 1 << HIGH_TECHNOLOGY,
        [ICE_CAPPED] = 1 << ICE_CAPPED,
        [INDUSTRIAL] = 1 << INDUSTRIAL,
        [LOW_POPULATION] = 1 << LOW_POPULATION,
        [LOW_TECHNOLOGY] = 1 << LOW_TECHNOLOGY,
        [NON_AGRICULTURAL] = 1 << NON_AGRICULTURAL,
        [NON_INDUSTRIAL] = 1 << NON_INDUSTRIAL,
        [POOR] = 1 << POOR,
        [RICH] = 1 << RICH,
        [VACUUM] = 1 << VACUUM,
        [WATER_WORLD] = 1 << WATER_WORLD
    };
    static const trade_code TCS[TOTAL_TRADE_CODES];
    static const std::string TC_STRINGS[TOTAL_TRADE_CODES];
};

#endif
