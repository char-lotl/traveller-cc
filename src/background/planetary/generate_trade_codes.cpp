#include "Planet.h"
#include "GenerationVariant.h"

#include "generate_trade_codes.h"
#include "generate_planet.h"

Codes generate_trade_codes(const GenerationVariant& gv){
    while (true) {
        Planet p(generate_planet(gv));
        if (p.get_attribute(POPULATION) == 0) continue;
        else return p.get_trade_codes();
    }
}
