#include "GestoreTransazioni.h"
#include <iostream>

int main() {
    try {
        GestoreTransazioni gestore;

        // Aggiungo alcune transazioni in memoria
        gestore.aggiungi(new Ingresso(2000.0, "Stipendio_Settembre"));
        gestore.aggiungi(new Uscita(55.5, "Spesa_Supermercato"));

        // Salvo tutte le transazioni (sovrascrive il file)
        gestore.salvaTutte("movimenti.txt");

        // Creo un nuovo gestore e carico dal file
        GestoreTransazioni g2;
        g2.carica("movimenti.txt");

        // Stampo quelle lette
        g2.stampa();

        // Modifico elemento id=1 (se esiste) e salvo di nuovo
        g2.modifica(1, TipoTransazione::ENTRATA, 2100.0, "Stipendio_Ottobre");
        g2.salvaTutte("movimenti.txt");

    } catch (const std::exception& e) {
        std::cerr << "Errore: " << e.what() << '\n';
        return 1;
    }

    return 0;
}

