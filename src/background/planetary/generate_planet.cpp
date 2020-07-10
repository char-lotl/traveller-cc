#include <array>
#include "Planet.h"
#include "utils/Roller.h"
#include "GenerationVariant.h"

#include "utils/utils.h"
#include "generate_planet.h"

const int TEMP_DM_ATMOS[] = {10, 10, -2, -2, -1, -1, 0, 0, 1, 1, 2, 6, 6, 2, -1, 2};
const int HYDRO_DM_ATMOS[] = {-4, -4, 0, 0, 0, 0, 0, 0, 0, 0, -4, -4, -4, 0, 0, 0};
const int STARPORT_TABLE[] = {[2] = 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5};

const int BASE_PRESENCE_STARPORT[][6] = {{13, 13, 13, 13, 13, 13},
                                        {13, 13, 13, 13, 13, 12},
                                        {13, 7, 13, 13, 13, 12},
                                        {13, 8, 10, 10, 10, 10},
                                        {8, 8, 10, 6, 8, 12},
                                        {8, 10, 8, 4, 6, 13}};

//const int BERTHING_MULT_STARPORT[] = {0, 0, 10, 100, 500, 1000};

const int TECH_DM_STARPORT[] = {-4, 0, 0, 2, 4, 6};
const int TECH_DM_SIZE[] = {2, 2, 1, 1, 1, 0, 0, 0, 0, 0, 0};
const int TECH_DM_ATMOS[] = {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1};
const int TECH_DM_HYDRO[] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2};
const int TECH_DM_POP[] = {-10, 1, 1, 1, 1, 1, 0, 0, 0, 1, 2, 3, 4};
const int TECH_DM_GOV[] = {1, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, -2, -2, 0};

int generate_planet_atmosphere(const int& planet_size,
                               const GenerationVariant& gv);

int generate_planet_hydrology(const int& planet_size,
                              const int& atmosphere,
                              const int& temperature,
                              const GenerationVariant& gv);

int generate_planet_population(const int& planet_size,
                               const int& atmosphere,
                               const GenerationVariant& gv);

int generate_planet_government(const int& population);

Planet generate_planet(const GenerationVariant& gv){
    // obviously we need stuff here
    
    int planet_size = Roller::roll2d6() - 2;
    
    int atmosphere = generate_planet_atmosphere(planet_size, gv);
    
    int temperature = Roller::roll2d6() + TEMP_DM_ATMOS[atmosphere];
    // Since we're only calculating temperature to determine hydrology,
    // the "swinging temperature" behavior of atm 0 and 1 is only of
    // interest in that it creates roasting conditions.
    // We also don't care about negative temperatures.
    
    int hydrology = generate_planet_hydrology(planet_size, atmosphere,
                                              temperature, gv);
    
    int population = generate_planet_population(planet_size, atmosphere, gv);
    
    int government = generate_planet_government(population);
    
    int law_level = Roller::roll2d6() + government - 7;
    if (law_level < 0) law_level = 0;
    // law level goes as high as 18.
    // 16=G, 17=H, 18=I in the world profile.
    if (population == 0) law_level = 0;
    
    int starport_row = Roller::roll2d6();
    if (gv == GenerationVariant::REALISM) {
        starport_row += (population - 7);
        if (starport_row < 0) starport_row = 0;
    }
    
    int starport_rating = STARPORT_TABLE[starport_row];
    if (population == 0) starport_rating = 0; // probably a good rule
    
    //int berthing_cost = Roller::rolld6() * BERTHING_MULT_STARPORT[starport_rating];
    // hasn't been implemented yet, probably won't be.
    
    std::array<bool,6> bases_present;
    for (int i = 0; i < 6; i++) {
        bases_present[i] =
            (Roller::roll2d6() >= BASE_PRESENCE_STARPORT[starport_rating][i]);
    }
    
    int tech_level = Roller::rolld6() + TECH_DM_STARPORT[starport_rating] +
        TECH_DM_SIZE[planet_size] + TECH_DM_ATMOS[atmosphere] +
        TECH_DM_HYDRO[hydrology] + TECH_DM_POP[population] +
        TECH_DM_GOV[government];
    if (tech_level < 0) tech_level = 0;
    if (population == 0) tech_level = 0;
    
    Planet p(planet_size, atmosphere, temperature, hydrology,
             population, government, law_level, tech_level,
             starport_rating, bases_present);
    return p;
}

int generate_planet_atmosphere(const int& planet_size,
                               const GenerationVariant& gv) {
    int atmosphere = Roller::roll2d6() + planet_size - 7;
    if (gv != GenerationVariant::STANDARD) { // space opera + hard science
        if (planet_size < 3) atmosphere = 0;
        else if (planet_size < 5) {
            if (atmosphere < 6) atmosphere = atmosphere / 3;
                // 0, 1, 2 -> 0; 3, 4, 5 -> 1
            else atmosphere = 10;
        }
    }
    if (atmosphere < 0) atmosphere = 0;
    
    return atmosphere;
}

int generate_planet_hydrology(const int& planet_size,
                              const int& atmosphere,
                              const int& temperature,
                              const GenerationVariant& gv) {
    int hydrology = Roller::roll2d6() + planet_size - 7 + HYDRO_DM_ATMOS[atmosphere];
    if (atmosphere != 13) { // atmos D will retain moisture regardless of temp
        if (temperature >= 10) hydrology -= 2; // hot temp is -2 DM
        if (temperature >= 12) hydrology -= 4; // roasting temp is -6 DM
    }
    if (gv != GenerationVariant::STANDARD) { // space opera + hard science
        if ((planet_size >= 3) && (planet_size <= 4) && (atmosphere == 10))
            hydrology -= 6;
        if (atmosphere < 2) hydrology -= 6;
        if ((atmosphere == 2) || (atmosphere == 3) ||
            (atmosphere == 11) || (atmosphere == 12)) hydrology -= 4;
    }
    
    if (planet_size <= 1) hydrology = 0; // too small to retain liquid
    if (hydrology < 0) hydrology = 0; // bounds enforcement
    if (hydrology > 10) hydrology = 10; // same
    
    return hydrology;
}

int generate_planet_population(const int& planet_size,
                               const int& atmosphere,
                               const GenerationVariant& gv) {
    int population = Roller::roll2d6() - 2;
    if (gv == GenerationVariant::REALISM) {
        if (planet_size < 3) population -= 1;
        if (planet_size == 10) population -= 1;
        if ((atmosphere == 5) || (atmosphere == 6) || (atmosphere == 8))
            population += 1;
        else population -= 1;
    }
    if (population < 0) population = 0; // bound enforcement. higher pops are okay!
    return population;
}

int generate_planet_government(const int& population) {
    int government = Roller::roll2d6() + population - 7;
    if (government < 0) government = 0;
    if (government > 13) government = 13;
    if (population == 0) government = 0;
    return government;
}
