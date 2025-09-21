#include "GestoreTransazioni.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

// Distruttore
GestoreTransazioni::~GestoreTransazioni() {
    for (auto& t : transazioni) { // distrugge tutti gli oggetti transazione presenti in mappa
        delete t.second;
    }
    transazioni.clear();

}

// Aggiungi una nuova transazione
void GestoreTransazioni::aggiungi(Transazione* t) {
    if (!t) { // cottrolla che il puntatore t non punti a nullptr
        throw std::invalid_argument("Transazione nulla");
    }
    transazioni[prossimoId++] = t; // aggiunge la transazione con key id corretto (il numero della transazione)
}

// Rimuovi una transazione dato l'id
void GestoreTransazioni::rimuovi(int id) {
    auto it = transazioni.find(id);
    if (it == transazioni.end()) {
        throw std::invalid_argument("ID non trovato");
    }
    delete it->second;
    transazioni.erase(it);
}

// Modifica una transazione esistente
void GestoreTransazioni::modifica(int id, TipoTransazione tipo, double importo, const std::string& descrizione) {
    auto it = transazioni.find(id);
    if (it == transazioni.end()) {
        throw std::invalid_argument("ID non trovato");
    }

    it->second->setTipo(tipo);
    it->second->setImporto(importo);
    it->second->setDescrizione(descrizione);
}

// Controlla se la mappa è vuota, metodo helper usato da stampa
bool GestoreTransazioni::vuoto() const {
    return transazioni.empty();
}

// Restituisce una transazione per id
Transazione* GestoreTransazioni::getTransazione(int id) const {
    auto it = transazioni.find(id);
    if (it == transazioni.end()) {
        throw std::invalid_argument("ID non trovato");
    }
    return it->second;
}

// Restituisce l'intera mappa (const reference)
const std::map<int, Transazione*>& GestoreTransazioni::getTransazioni() const {
    return transazioni;
}

// Salva tutte le transazioni su file
void GestoreTransazioni::salvaTutte(const std::string& nomeFile) const {
    std::ofstream ofs(nomeFile); // ofstream apre il file in scrittura
    if (!ofs) {
        throw std::runtime_error("Impossibile aprire il file per scrittura");
    }

    for (const auto& it : transazioni) {
        const Transazione* t = it.second; // puntatore all'oggetto Transazione
        ofs << (t->getTipo() == TipoTransazione::ENTRATA ? "ENTRATA" : "USCITA") // operatore ternario: se è di tipo Entrata scrivi Entrata altrimenti Uscita
            << " " << t->getImporto() << " " << t->getDescrizione() << "\n";
    }
}

// Carica tutte le transazioni da file
void GestoreTransazioni::carica(const std::string& nomeFile) {
    std::ifstream ifs(nomeFile); // if stream apre il file in lettura
    if (!ifs) { // se non è stato aperto lancia errore
        throw std::runtime_error("Impossibile aprire il file per lettura");
    }

    // Pulisce transazioni esistenti
    for (auto& it: transazioni) {
        delete it.second;
    }
    transazioni.clear(); // pulizia dei dati esistenti
    prossimoId = 1;

    std::string tipoStr, descrizione;
    double importo;

    while (ifs >> tipoStr >> importo >> descrizione) { // legge riga per riga esportando i valori nell'ordine in cui sono stati scritti
        if (tipoStr == "ENTRATA") {
            aggiungi(new Ingresso(importo, descrizione)); // importa ingresso
        } else if (tipoStr == "USCITA") {
            aggiungi(new Uscita(importo, descrizione)); // importa uscita
        } else {
            throw std::runtime_error("Tipo di transazione non valido nel file");
        }
    }
}

// Stampa tutte le transazioni
void GestoreTransazioni::stampa() const {
    if (vuoto()) {
        std::cout << "Nessuna transazione presente.\n";
        return;
    }
    for (const auto& it : transazioni) {
        std::cout << it.first << ": "
                  << it.second->getDescrizione()
                  << " (" << it.second->getImporto() << ")\n";
    }
}

