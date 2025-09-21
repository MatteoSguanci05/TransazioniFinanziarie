#include "Uscita.h"

Uscita::Uscita(double i, const std::string& d)
    : Transazione(TipoTransazione::USCITA, i, d) {}

void Uscita::scriviTransizione(std::ostream& os) const {
    os << "USCITA" << ' ' << importo << ' ' << descrizione;
}
