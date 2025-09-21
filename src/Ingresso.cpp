#include "Ingresso.h"
#include <iomanip>

Ingresso::Ingresso(double i, const std::string& d)
    : Transazione(TipoTransazione::ENTRATA, i, d) {}

void Ingresso::scriviTransizione(std::ostream& os) const {
    os << "ENTRATA" << ' ' << importo << ' ' << descrizione;
}
