#include "../include/GestoreTransazioni.h"
#include <gtest/gtest.h> // libreria per i test
#include <filesystem> // liberia per lavorare con i file

const std::string fileName = "test_movimenti.txt";

//TEST 1: creazione transizioni
TEST(TransazioneTest, Creazione) {
    Ingresso t1(1000.0, "Stipendio");
    Uscita t2(50.0, "Spesa");

    EXPECT_EQ(t1.getTipo(), TipoTransazione::ENTRATA)<<"ERRORE: tipo non corretto";
    EXPECT_EQ(t2.getTipo(), TipoTransazione::USCITA)<<"ERRORE: tipo non  corretto";
    EXPECT_DOUBLE_EQ(t1.getImporto(), 1000.0)<<"ERRORE: l'importo non è corretto";
    EXPECT_DOUBLE_EQ(t2.getImporto(), 50.0)<<"ERRORE: l'importo non è corretto";
    EXPECT_EQ(t1.getDescrizione(),"Stipendio")<<"ERRORE: la descrizione non è corretta";
    EXPECT_EQ(t2.getDescrizione(), "Spesa")<<"ERRORE: la descrizione non è corretta";
}

//TEST 2: aggiunta transazioni
TEST(GestoreTransazioniTest, Aggiungi) {
    GestoreTransazioni g;
    g.aggiungi(new Ingresso(1200.0, "Stipendio_Mese"));
    g.aggiungi(new Uscita(70.0, "Bollette"));

    EXPECT_FALSE(g.vuoto());
}

//TEST 3: salvataggio e caricamento fyle
TEST(GestoreTransazioniTest, SalvaECarica) {
    // Pulizia iniziale
    if (std::filesystem::exists(fileName)) {
        std::filesystem::remove(fileName);
    }

    GestoreTransazioni g;
    g.aggiungi(new Ingresso(1200.0, "Stipendio_Mese"));
    g.aggiungi(new Uscita(70.0, "Bollette"));
    g.salvaTutte(fileName);

    GestoreTransazioni g2;
    g2.carica(fileName);

    EXPECT_FALSE(g2.vuoto());

    // Pulizia finale
    if (std::filesystem::exists(fileName)) {
        std::filesystem::remove(fileName);
    }
}

// TEST 4: modifica di una transazione
TEST(GestoreTransazioniTest, Modifica) {
    if (std::filesystem::exists(fileName)) {
        std::filesystem::remove(fileName);
    }

    GestoreTransazioni g;
    g.aggiungi(new Ingresso(1000.0, "Stipendio"));
    g.salvaTutte(fileName);

    GestoreTransazioni g2;
    g2.carica(fileName);

    g2.modifica(1, TipoTransazione::ENTRATA, 1300.0, "Stipendio_Modificato");
    g2.salvaTutte(fileName);

    GestoreTransazioni g3;
    g3.carica(fileName);

    EXPECT_DOUBLE_EQ(g3.getTransazione(1)->getImporto(), 1300.0);
    EXPECT_EQ(g3.getTransazione(1)->getDescrizione(), "Stipendio_Modificato");

    if (std::filesystem::exists(fileName)) {
        std::filesystem::remove(fileName);
    }
}

//TEST 5: rimozione transazione
TEST(GestoreTransazioniTest, Rimozione) {
    GestoreTransazioni g;
    g.aggiungi(new Ingresso(1000.0, "Stipendio"));
    g.aggiungi(new Uscita(70.0, "Bollette"));

    g.rimuovi(2);

    EXPECT_EQ(g.getTransazioni().size(), 1);
}

