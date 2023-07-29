#include <gtest/gtest.h>
#include "Transazione.h"
#include "ContoCorrente.h"

// Test della classe Transazione
TEST(TransazioneTest, TestCostruttore) {
    // Test costruttore con dati validi
    year_month_day data{2023_y / 07 / 22};
    Transazione trans1(100.0, data, "bonifico", Transazione::TipoTransazione::ENTRATA);

    ASSERT_DOUBLE_EQ(trans1.getImporto(), 100.0);
    ASSERT_EQ(trans1.getData(), data);
    ASSERT_EQ(trans1.getDescrizione(), "bonifico");
    ASSERT_EQ(trans1.getTipo(), Transazione::TipoTransazione::ENTRATA);

    // Test costruttore con descrizione vuota
    Transazione trans2(50.0, data, "", Transazione::TipoTransazione::USCITA);

    ASSERT_DOUBLE_EQ(trans2.getImporto(), 50.0);
    ASSERT_EQ(trans2.getData(), data);
    ASSERT_EQ(trans2.getDescrizione(), "");
    ASSERT_EQ(trans2.getTipo(), Transazione::TipoTransazione::USCITA);
}

// Test della classe ContoCorrente
TEST(ContoCorrenteTest, TestEffettuaTransazione) {
    ContoCorrente conto;

    year_month_day data1{2023_y / 07 / 22};
    conto.effettuaTransazione(Transazione(100.0, data1, "bonifico", Transazione::TipoTransazione::ENTRATA));

    year_month_day data2{2023_y / 07 / 23};
    conto.effettuaTransazione(Transazione(90.0, data2, "prelievo", Transazione::TipoTransazione::USCITA));

    ASSERT_DOUBLE_EQ(conto.getSaldo(), 10.0);
}

TEST(ContoCorrenteTest, TestCercaTransazioniPerImporto) {
    ContoCorrente conto;
    year_month_day data1{2023_y / 07 / 22};
    conto.effettuaTransazione(Transazione(100.0, data1, "bonifico", Transazione::TipoTransazione::ENTRATA));

    year_month_day data2{2023_y / 07 / 23};
    conto.effettuaTransazione(Transazione(90.0, data2, "prelievo", Transazione::TipoTransazione::USCITA));

    year_month_day data3{2023_y / 07 / 24};
    conto.effettuaTransazione(Transazione(50.0, data3, "prelievo", Transazione::TipoTransazione::USCITA));

    year_month_day data4{2023_y / 07 / 25};
    conto.effettuaTransazione(Transazione(200.0, data4, "bonifico", Transazione::TipoTransazione::ENTRATA));

    vector<Transazione> transazioniPerImporto = conto.cercaTransazioniPerImporto(90.0);
    ASSERT_EQ(transazioniPerImporto.size(), 1);
    ASSERT_DOUBLE_EQ(transazioniPerImporto[0].getImporto(), 90.0);
}

TEST(ContoCorrenteTest, TestCercaTransazioniPerDescrizione) {
    ContoCorrente conto;
    year_month_day data1{2023_y / 07 / 22};
    conto.effettuaTransazione(Transazione(100.0, data1, "bonifico", Transazione::TipoTransazione::ENTRATA));

    year_month_day data2{2023_y / 07 / 23};
    conto.effettuaTransazione(Transazione(90.0, data2, "prelievo", Transazione::TipoTransazione::USCITA));

    year_month_day data3{2023_y / 07 / 24};
    conto.effettuaTransazione(Transazione(50.0, data3, "prelievo", Transazione::TipoTransazione::USCITA));

    year_month_day data4{2023_y / 07 / 25};
    conto.effettuaTransazione(Transazione(200.0, data4, "bonifico", Transazione::TipoTransazione::ENTRATA));

    vector<Transazione> transazioniPerDescrizione = conto.cercaTransazioniPerDescrizione("bonifico");
    ASSERT_EQ(transazioniPerDescrizione.size(), 2);
    ASSERT_EQ(transazioniPerDescrizione[0].getDescrizione(), "bonifico");
    ASSERT_EQ(transazioniPerDescrizione[1].getDescrizione(), "bonifico");
}

TEST(ContoCorrenteTest, TestCercaTransazioniPerTipo) {
    ContoCorrente conto;
    year_month_day data1{2023_y / 07 / 22};
    conto.effettuaTransazione(Transazione(100.0, data1, "bonifico", Transazione::TipoTransazione::ENTRATA));

    year_month_day data2{2023_y / 07 / 23};
    conto.effettuaTransazione(Transazione(90.0, data2, "prelievo", Transazione::TipoTransazione::USCITA));

    year_month_day data3{2023_y / 07 / 24};
    conto.effettuaTransazione(Transazione(50.0, data3, "prelievo", Transazione::TipoTransazione::USCITA));

    year_month_day data4{2023_y / 07 / 25};
    conto.effettuaTransazione(Transazione(200.0, data4, "bonifico", Transazione::TipoTransazione::ENTRATA));

    vector<Transazione> transazioniEntrata = conto.cercaTransazioniPerTipo(Transazione::TipoTransazione::ENTRATA);
    ASSERT_EQ(transazioniEntrata.size(), 2);
    ASSERT_EQ(transazioniEntrata[0].getTipo(), Transazione::TipoTransazione::ENTRATA);
    ASSERT_EQ(transazioniEntrata[1].getTipo(), Transazione::TipoTransazione::ENTRATA);

    vector<Transazione> transazioniUscita = conto.cercaTransazioniPerTipo(Transazione::TipoTransazione::USCITA);
    ASSERT_EQ(transazioniUscita.size(), 2);
    ASSERT_EQ(transazioniUscita[0].getTipo(), Transazione::TipoTransazione::USCITA);
    ASSERT_EQ(transazioniUscita[1].getTipo(), Transazione::TipoTransazione::USCITA);
}

TEST(ContoCorrenteTest, TestCancellaTransazioniPerData) {
    ContoCorrente conto;
    year_month_day data1{2023_y / 07 / 22};
    conto.effettuaTransazione(Transazione(100.0, data1, "bonifico", Transazione::TipoTransazione::ENTRATA));

    year_month_day data2{2023_y / 07 / 23};
    conto.effettuaTransazione(Transazione(90.0, data2, "prelievo", Transazione::TipoTransazione::USCITA));

    year_month_day data3{2023_y / 07 / 24};
    conto.effettuaTransazione(Transazione(50.0, data3, "prelievo", Transazione::TipoTransazione::USCITA));

    year_month_day data4{2023_y / 07 / 25};
    conto.effettuaTransazione(Transazione(200.0, data4, "bonifico", Transazione::TipoTransazione::ENTRATA));

    ASSERT_TRUE(conto.CancellaTransazioniPerData(data2));
    ASSERT_FALSE(conto.CancellaTransazioniPerData(year_month_day{2023_y / 07 / 26}));
}



// Test case per il metodo CancellaTransazioniPerImporto
TEST(ContoCorrenteTest, CancellaTransazioniPerImporto) {
    ContoCorrente conto;

    // Aggiungiamo alcune transazioni al conto
    conto.effettuaTransazione(Transazione(100.0, year_month_day{2023_y / 07 / 22}, "bonifico", Transazione::TipoTransazione::ENTRATA));
    conto.effettuaTransazione(Transazione(90.0, year_month_day{2023_y / 07 / 23}, "prelievo", Transazione::TipoTransazione::USCITA));
    conto.effettuaTransazione(Transazione(200.0, year_month_day{2023_y / 07 / 24}, "bonifico", Transazione::TipoTransazione::ENTRATA));
    conto.effettuaTransazione(Transazione(90.0, year_month_day{2023_y / 07 / 25}, "prelievo", Transazione::TipoTransazione::USCITA));

    // Cancella transazioni con importo 90.0
    ASSERT_NO_THROW(conto.CancellaTransazioniPerImporto(100.0));

    // Verifica che le transazioni con importo 90.0 siano state rimosse
    vector<Transazione> transazioniPerImporto = conto.cercaTransazioniPerImporto(100.0);
    ASSERT_EQ(transazioniPerImporto.size(), 0);

    // Verifica che il saldo sia stato aggiornato correttamente dopo la cancellazione
    ASSERT_EQ(conto.getSaldo(), 380.0);
}


