#include "../include/GestoreTransazioni.h"
#include <gtest/gtest.h>
#include <filesystem>

const std::string fileName = "test_movimenti.txt";

// === TEST 1: Creazione transazioni ===
TEST(TransazioneTest, Creazione) {
    Ingresso t1(1000.0, "Stipendio");
    Uscita t2(50.0, "Spesa");

    EXPECT_EQ(t1.getTipo(), TipoTransazione::ENTRATA);
    EXPECT_EQ(t2.getTipo(), TipoTransazione::USCITA);
    EXPECT_DOUBLE_EQ(t1.getImporto(), 1000.0);
    EXPECT_EQ(t2.getDescrizione(), "Spesa");
}

// === TEST 2: Aggiunta transazioni in gestore ===
TEST(GestoreTransazioniTest, Aggiungi) {
    GestoreTransazioni g;
    g.aggiungi(new Ingresso(1200.0, "Stipendio_Mese"));
    g.aggiungi(new Uscita(70.0, "Bollette"));

    EXPECT_FALSE(g.vuoto());
}

// === TEST 3: Salvataggio e caricamento da file ===
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

// === TEST 4: Modifica di una transazione ===
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

// === TEST 5: Rimozione transazione ===
TEST(GestoreTransazioniTest, Rimozione) {
    GestoreTransazioni g;
    g.aggiungi(new Ingresso(1000.0, "Stipendio"));
    g.aggiungi(new Uscita(70.0, "Bollette"));

    g.rimuovi(2);

    EXPECT_EQ(g.getTransazioni().size(), 1);
}

