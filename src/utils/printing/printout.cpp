#include "Printer.h"
#include "printout.h"

const utils::printing::Printer& utils::printing::printout() {
    static const utils::printing::Printer p{};
    
    return p;
}
