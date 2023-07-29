#include <gtest/gtest.h>
#include "ContoCorrente.h"

TEST(ContoCorrenteTest, TestEffettuaTransazione) {
    ContoCorrente conto;
    Transazione entrata(100.0, "2023-07-22", Transazione::TipoTransazione::ENTRATA);
    Transazione uscita(90.0, "2023-07-23", Transazione::TipoTransazione::USCITA);

    conto.effettuaTransazione(entrata);
    conto.effettuaTransazione(uscita);

    // Test saldo corrente dopo le transazioni
    EXPECT_DOUBLE_EQ(conto.getSaldo(), 10.0);
}

TEST(ContoCorrenteTest, TestCercaTransazioniInBaseAllaData) {
    ContoCorrente conto;
    Transazione entrata1(100.0, "2023-07-22", Transazione::TipoTransazione::ENTRATA);
    Transazione uscita1(90.0, "2023-07-23", Transazione::TipoTransazione::USCITA);
    Transazione uscita2(5.0, "2023-07-23", Transazione::TipoTransazione::USCITA);
    Transazione entrata2(200.0, "2023-07-24", Transazione::TipoTransazione::ENTRATA);
    Transazione entrata3(90.0, "2023-07-23", Transazione::TipoTransazione::ENTRATA);

    conto.effettuaTransazione(entrata1);
    conto.effettuaTransazione(uscita1);
    conto.effettuaTransazione(uscita2);
    conto.effettuaTransazione(entrata2);
    conto.effettuaTransazione(entrata3);

    vector<Transazione> transazioniData = conto.cercaTransazioniInBaseAllaData("2023-07-23");

    // Test numero di transazioni in base alla data
    EXPECT_EQ(transazioniData.size(), 2);
}

TEST(ContoCorrenteTest, TestCancellaTransazioniPerData) {
    ContoCorrente conto;
    Transazione entrata1(100.0, "2023-07-22", Transazione::TipoTransazione::ENTRATA);
    Transazione uscita1(90.0, "2023-07-23", Transazione::TipoTransazione::USCITA);
    Transazione uscita2(5.0, "2023-07-23", Transazione::TipoTransazione::USCITA);
    Transazione entrata2(200.0, "2023-07-24", Transazione::TipoTransazione::ENTRATA);
    Transazione entrata3(90.0, "2023-07-23", Transazione::TipoTransazione::ENTRATA);

    conto.effettuaTransazione(entrata1);
    conto.effettuaTransazione(uscita1);
    conto.effettuaTransazione(uscita2);
    conto.effettuaTransazione(entrata2);
    conto.effettuaTransazione(entrata3);

    conto.CancellaTransazioniPerData("2023-07-23");

    // Test saldo corrente dopo la cancellazione delle transazioni
    EXPECT_DOUBLE_EQ(conto.getSaldo(), 300.0);
}