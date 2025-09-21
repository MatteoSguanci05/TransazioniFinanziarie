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

// Salva su file
void Transazione::salva(const std::string& nomeFile) const {
    std::ofstream ofs(nomeFile, std::ios::app); // ofs oggetto scrittorio, apertura file in modalità append
    if (!ofs.is_open()) { // se il file non viene aperto correttamente
        throw std::runtime_error("Impossibile aprire file per scrittura: " + nomeFile);
    }

    scriviTransizione(ofs); // polimorfismo in base al tipo dinamico viene chiamat il metodo corretto
    ofs << '\n';

    if (!ofs.good()) { // good resituisce True, Operazione è andata a buon fine
        throw std::runtime_error("Errore scrittura su file: " + nomeFile);
    }
}
