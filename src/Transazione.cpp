#include "Transazione.h"


// Costruttore
Transazione::Transazione(TipoTransazione t, double i, const std::string& d): tipo(t), importo(i), descrizione(d) {
    if (i < 0) {
        throw std::invalid_argument("Importo non può essere negativo");
    }
}

// Distruttore virtuale
Transazione::~Transazione() = default;

// Getter
TipoTransazione Transazione::getTipo() const { return tipo; }
double Transazione::getImporto() const { return importo; }
std::string Transazione::getDescrizione() const { return descrizione; }

// Setter
void Transazione::setTipo(TipoTransazione t) { tipo = t; }

void Transazione::setImporto(double i) {
    if (i < 0) throw std::invalid_argument("Importo non può essere negativo");
    importo = i;
}

void Transazione::setDescrizione(const std::string& d) {
    descrizione = d;
}


