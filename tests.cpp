//
// Created by ft001 on 18/07/2023.
//
// tests.cpp
#include <gtest/gtest.h>
#include "Transazione.h"
#include "ContoCorrente.h"



TEST(ContoCorrenteTest, EffettuaTransazione) {
    ContoCorrente conto;

    // Verifica il saldo dopo alcune transazioni
    conto.effettuaTransazione(Transazione(100.0, "2023-07-22"));
    conto.effettuaTransazione(Transazione(-50.0, "2023-07-23"));
    conto.effettuaTransazione(Transazione(200.0, "2023-07-24"));
    EXPECT_EQ(conto.getSaldo(), 250.0);

    // Verifica il saldo dopo una transazione di 0
    conto.effettuaTransazione(Transazione(0.0, "2023-07-25"));
    EXPECT_EQ(conto.getSaldo(), 250.0);
}

TEST(ContoCorrenteTest, CercaTransazioniPerData) {
    ContoCorrente conto;

    conto.effettuaTransazione(Transazione(100.0, "2023-07-22"));
    conto.effettuaTransazione(Transazione(-50.0, "2023-07-23"));
    conto.effettuaTransazione(Transazione(200.0, "2023-07-24"));

    // Verifica la ricerca per data
    vector<Transazione> transazioniData = conto.cercaTransazioniInBaseAllaData("2023-07-23");
    EXPECT_EQ(transazioniData.size(), 1);
    EXPECT_EQ(transazioniData[0].getImporto(), -50.0);
}

TEST(ContoCorrenteTest, CancellaTransazioniPerData) {
    ContoCorrente conto;

    conto.effettuaTransazione(Transazione(100.0, "2023-07-22"));
    conto.effettuaTransazione(Transazione(-50.0, "2023-07-23"));
    conto.effettuaTransazione(Transazione(200.0, "2023-07-24"));

    // Verifica la cancellazione per data
    conto.CancellaTransazioniPerData("2023-07-23");
    EXPECT_EQ(conto.getSaldo(), 300.0); // Dopo la cancellazione rimangono solo 2 transazioni con importo 100 e 200

    // Verifica che non ci siano più transazioni del 2023-07-23
    vector<Transazione> transazioniData = conto.cercaTransazioniInBaseAllaData("2023-07-23");
    EXPECT_EQ(transazioniData.size(), 0);
}

TEST(ContoCorrenteTest, SalvaCaricaDaFile) {
    ContoCorrente conto;

    // Effettua alcune transazioni
    conto.effettuaTransazione(Transazione(100.0, "2023-07-22"));
    conto.effettuaTransazione(Transazione(-50.0, "2023-07-23"));
    conto.effettuaTransazione(Transazione(200.0, "2023-07-24"));

    // Salva le transazioni su file
    conto.salvaSuFile("test_transazioni.txt");

    // Crea un nuovo conto corrente e carica le transazioni da file
    ContoCorrente nuovoConto;
    nuovoConto.leggiDaFile("test_transazioni.txt");

    // Verifica che il saldo sia corretto dopo il caricamento da file
    EXPECT_EQ(nuovoConto.getSaldo(), conto.getSaldo());

    // Verifica che le transazioni siano le stesse dopo il caricamento da file
    vector<Transazione> transazioniConto = conto.cercaTransazioniInBaseAllaData("2023-07-22");
    vector<Transazione> transazioniNuovoConto = nuovoConto.cercaTransazioniInBaseAllaData("2023-07-22");
    EXPECT_EQ(transazioniConto.size(), transazioniNuovoConto.size());
    for (size_t i = 0; i < transazioniConto.size(); ++i) {
        EXPECT_EQ(transazioniConto[i].getImporto(), transazioniNuovoConto[i].getImporto());
        EXPECT_EQ(transazioniConto[i].getData(), transazioniNuovoConto[i].getData());
    }
}


