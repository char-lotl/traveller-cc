#include <array>
//#include <i*stream>
#include "Planet.h"
#include "Codes.h"

const bool INDUSTRIAL_ATMOS[] = {true, true, true, false, true, false, false,
                                 true, false, true, false, false, false,
                                 false, false, false};
// Industrial atmos values are 0-2, 4, 7, and 9.

const int ATMOS_TECH_REQ[] = {8, 8, 5, 5, 3, [7] = 3, [9] = 3, 8,
                              9, 10, 5, 5, 8};
// Tech level requirements for different atmos types.

bool int_in_range(const int& num, const int& lower, const int& upper);

long generate_tc_long(const int& planet_size, const int& atmosphere,
                      const int& hydrology, const int& population,
                      const int& tech_level);

Planet::Planet(int ps, int atmos, int temp, int hydro, int pop,
               int gov, int lawlev, int techlev, int sr,
               std::array<bool,6> bp) :
attributes{ps, atmos, temp, hydro, pop, gov, lawlev, techlev, sr},
bases_present(bp),
trade_codes(generate_tc_long(ps, atmos, hydro, pop, techlev))
{
    
}

bool Planet::has_trade_code(const trade_code& tc) const {
    return trade_codes.include_code(tc);
}

bool Planet::has_base_presence(const base_type& bt) const {
    return bases_present[bt];
}

int Planet::get_attribute(const planetary_attribute& which_attr) const {
    return attributes[which_attr];
}

bool Planet::meets_environmental_limit() const {
    return attributes[TECHNOLOGY_LEVEL] >= ATMOS_TECH_REQ[attributes[ATMOSPHERE]];
}

Codes Planet::get_trade_codes() const {
    return trade_codes;
}

bool int_in_range(const int& num, const int& lower, const int& upper) {
    return ((num >= lower) && (num <= upper));
}

long generate_tc_long(const int& planet_size, const int& atmosphere,
                      const int& hydrology, const int& population,
                      const int& tech_level) {
    //std::co*t << planet_size << " " << atmosphere << " " <<
    //hydrology << " " << population << " " << tech_level << "\n";
    
    
    long trade_codes = 0;
    
    trade_codes |= (int_in_range(atmosphere, 4, 9) &&
                    int_in_range(hydrology, 4, 8) &&
                    int_in_range(population, 5, 7)) ? Codes::FLAGS[AGRICULTURAL] : 0;
    // Agricultural
    
    trade_codes |= ((planet_size == 0) && (atmosphere == 0) &&
                    (hydrology == 0)) ? Codes::FLAGS[ASTEROID] : 0;
    // Asteroid
    
    trade_codes |= (population == 0) ? Codes::FLAGS[BARREN] : 0;
    // Barren
    
    trade_codes |= ((atmosphere >= 2) && (hydrology == 0)) ? Codes::FLAGS[DESERT] : 0;
    // Desert
    
    trade_codes |= ((atmosphere >= 10) && (hydrology >= 1)) ?
        Codes::FLAGS[FLUID_OCEANS] : 0;
    // Fluid (non-water) Oceans
    
    trade_codes |= ((planet_size >= 5) && int_in_range(atmosphere, 4, 9) &&
                    int_in_range(hydrology, 4, 8)) ? Codes::FLAGS[GARDEN] : 0;
    // Garden
    
    trade_codes |= (population >= 9) ? Codes::FLAGS[HIGH_POPULATION] : 0;
    // High Population
    
    trade_codes |= (tech_level >= 12) ? Codes::FLAGS[HIGH_TECHNOLOGY] : 0;
    // High Technology
    
    trade_codes |= (int_in_range(atmosphere, 0, 1) &&
                    (hydrology >= 1)) ? Codes::FLAGS[ICE_CAPPED] : 0;
    // Ice-Capped
    
    trade_codes |= (INDUSTRIAL_ATMOS[atmosphere] &&
                    (population >= 9)) ? Codes::FLAGS[INDUSTRIAL] : 0;
    // Industrial
    
    trade_codes |= (int_in_range(population, 1, 3)) ?
        Codes::FLAGS[LOW_POPULATION] : 0;
    // Low Population
    
    trade_codes |= (tech_level <= 5) ? Codes::FLAGS[LOW_TECHNOLOGY] : 0;
    // Low Technology
    
    trade_codes |= (int_in_range(atmosphere, 0, 3) &&
                    int_in_range(hydrology, 0, 3) &&
                    (population >= 6)) ? Codes::FLAGS[NON_AGRICULTURAL] : 0;
    // Non-Agricultural
    
    trade_codes |= int_in_range(population, 4, 6) ? Codes::FLAGS[NON_INDUSTRIAL] : 0;
    // Non-Industrial
    
    trade_codes |= (int_in_range(atmosphere, 2, 5) &&
                    int_in_range(hydrology, 0, 3)) ? Codes::FLAGS[POOR] : 0;
    // Poor
    
    trade_codes |= (((atmosphere == 6) || (atmosphere == 8)) &&
                    int_in_range(population, 6, 8)) ? Codes::FLAGS[RICH] : 0;
    // Rich
    
    trade_codes |= (atmosphere == 0) ? Codes::FLAGS[VACUUM] : 0;
    // Vacuum
    
    trade_codes |= (hydrology == 10) ? Codes::FLAGS[WATER_WORLD] : 0;
    // Water World
    
    return trade_codes;
}
