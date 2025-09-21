#ifndef GESTORETRANSAZIONI_H
#define GESTORETRANSAZIONI_H

#include "Transazione.h"
#include "Ingresso.h"
#include "Uscita.h"
#include <map>
#include <string>

class GestoreTransazioni {
private:
    std::map<int, Transazione*> transazioni;
    int prossimoId = 1;

public:
    GestoreTransazioni() = default;
    ~GestoreTransazioni();

    // Operazioni di base
    void aggiungi(Transazione* t);
    void rimuovi(int id);
    void modifica(int id, TipoTransazione tipo, double importo, const std::string& descrizione);

    // Accesso ai dati
    bool vuoto() const; // un metodo helper che controlla che la mappa non sia vuota usato da stampa
    Transazione* getTransazione(int id) const; // metodo getter della singola Transazione
    const std::map<int, Transazione*>& getTransazioni() const; // metodo getter dell'intera mappa di transazione gestita dal gestore

    // Operazioni su file
    void salvaTutte(const std::string& nomeFile) const; // salva le transazione su file
    void carica(const std::string& nomeFile); // legge e carica le transazioni da file sulla mappa

    // Visualizza
    void stampa() const;
};

#endif // GESTORETRANSAZIONI_H
