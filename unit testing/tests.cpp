#include <gtest/gtest.h>
#include "../Transazione.h"
#include "../ContoCorrente.h"

TEST(TransazioneTest, TestCostruttore) {
    // Test costruttore con dati validi
    year_month_day data{2023_y / 07 / 22};
    Transazione trans1(100.0, data, "bonifico", Transazione::TipoTransazione::ENTRATA);

    ASSERT_DOUBLE_EQ(trans1.getImporto(), 100.0);
    ASSERT_EQ(trans1.getData(), data);
    ASSERT_EQ(trans1.getDescrizione(), "bonifico");
    ASSERT_EQ(trans1.getTipo(), Transazione::TipoTransazione::ENTRATA);

    Transazione trans2(50.0, data, "", Transazione::TipoTransazione::USCITA);

    ASSERT_DOUBLE_EQ(trans2.getImporto(), 50.0);
    ASSERT_EQ(trans2.getData(), data);
    ASSERT_EQ(trans2.getDescrizione(), "");
    ASSERT_EQ(trans2.getTipo(), Transazione::TipoTransazione::USCITA);
}

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

TEST(ContoCorrenteTest, TestCancellaTransazioniPerDataEsistente) {
    ContoCorrente conto;
    year_month_day data1{2023_y / 07 / 22};
    year_month_day data2{2023_y / 07 / 23};

    conto.effettuaTransazione(Transazione(100.0, data1, "bonifico", Transazione::TipoTransazione::ENTRATA));
    conto.effettuaTransazione(Transazione(90.0, data2, "prelievo", Transazione::TipoTransazione::USCITA));

    ASSERT_TRUE(conto.CancellaTransazioniPerData(data2));

    vector<Transazione> transazioniData = conto.cercaTransazioniInBaseAllaData(data2);
    ASSERT_EQ(transazioniData.size(), 0);
}

TEST(ContoCorrenteTest, TestCancellaTransazioniPerDataInesistente) {
    ContoCorrente conto;
    year_month_day data1{2023_y / 07 / 22};
    year_month_day data2{2023_y / 07 / 24};

    conto.effettuaTransazione(Transazione(100.0, data1, "bonifico", Transazione::TipoTransazione::ENTRATA));

    ASSERT_THROW(conto.CancellaTransazioniPerData(data2), runtime_error);

    ASSERT_DOUBLE_EQ(conto.getSaldo(), 100.0);
}

TEST(ContoCorrenteTest, TestCancellaTransazioniPerDataConEccezione) {
    ContoCorrente conto;
    year_month_day data1{2023_y / 07 / 22};
    year_month_day data2{2023_y / 07 / 23};

    conto.effettuaTransazione(Transazione(100.0, data1, "bonifico", Transazione::TipoTransazione::ENTRATA));
    conto.effettuaTransazione(Transazione(90.0, data2, "prelievo", Transazione::TipoTransazione::USCITA));

    ASSERT_THROW(conto.CancellaTransazioniPerData(data2), runtime_error);

    ASSERT_DOUBLE_EQ(conto.getSaldo(), 100.0);
}

TEST(ContoCorrenteTest, TestCancellaTransazioniPerImportoEsistente) {
    ContoCorrente conto;

    conto.effettuaTransazione(
            Transazione(100.0, year_month_day{2023_y / 07 / 22}, "bonifico", Transazione::TipoTransazione::ENTRATA));
    conto.effettuaTransazione(
            Transazione(90.0, year_month_day{2023_y / 07 / 23}, "prelievo", Transazione::TipoTransazione::USCITA));
    conto.effettuaTransazione(
            Transazione(200.0, year_month_day{2023_y / 07 / 24}, "bonifico", Transazione::TipoTransazione::ENTRATA));

    ASSERT_NO_THROW(conto.CancellaTransazioniPerImporto(90.0));

    vector<Transazione> transazioniImporto = conto.cercaTransazioniPerImporto(90.0);
    ASSERT_EQ(transazioniImporto.size(), 0);

    ASSERT_DOUBLE_EQ(conto.getSaldo(), 300.0);
}

TEST(ContoCorrenteTest, TestCancellaTransazioniPerImportoInesistente) {
    ContoCorrente conto;

    conto.effettuaTransazione(
            Transazione(100.0, year_month_day{2023_y / 07 / 22}, "bonifico", Transazione::TipoTransazione::ENTRATA));
    conto.effettuaTransazione(
            Transazione(90.0, year_month_day{2023_y / 07 / 23}, "prelievo", Transazione::TipoTransazione::USCITA));

    ASSERT_THROW(conto.CancellaTransazioniPerImporto(200.0), std::runtime_error);

    ASSERT_DOUBLE_EQ(conto.getSaldo(), 10.0);
}

TEST(ContoCorrenteTest, TestCancellaTransazioniPerImportoConEccezione) {
    ContoCorrente conto;

    conto.effettuaTransazione(
            Transazione(100.0, year_month_day{2023_y / 07 / 22}, "bonifico", Transazione::TipoTransazione::ENTRATA));
    conto.effettuaTransazione(
            Transazione(90.0, year_month_day{2023_y / 07 / 23}, "prelievo", Transazione::TipoTransazione::USCITA));

    ASSERT_THROW(conto.CancellaTransazioniPerImporto(90.0), std::runtime_error);

    ASSERT_DOUBLE_EQ(conto.getSaldo(), 10.0);
}

TEST(ContoCorrenteTest, TestCercaTransazioniInBaseAllaData) {

    ContoCorrente conto;
    year_month_day data1{2023_y / 07 / 22};
    conto.effettuaTransazione(Transazione(100.0, data1, "bonifico", Transazione::TipoTransazione::ENTRATA));

    year_month_day data2{2023_y / 07 / 23};
    conto.effettuaTransazione(Transazione(90.0, data2, "prelievo", Transazione::TipoTransazione::USCITA));

    year_month_day data3{2023_y / 07 / 24};
    conto.effettuaTransazione(Transazione(50.0, data3, "prelievo", Transazione::TipoTransazione::USCITA));

    year_month_day data4{2023_y / 07 / 25};
    conto.effettuaTransazione(Transazione(200.0, data4, "bonifico", Transazione::TipoTransazione::ENTRATA));

    year_month_day dataDaCercare{2023_y / 07 / 23};
    vector<Transazione> transazioniTrovate = conto.cercaTransazioniInBaseAllaData(dataDaCercare);

    ASSERT_EQ(transazioniTrovate.size(), 1);
    ASSERT_EQ(transazioniTrovate[0].getData(), dataDaCercare);
}

TEST(ContoCorrenteTest, TestSalvaSuFile) {
    ContoCorrente conto;
    year_month_day data1{2023_y / 07 / 22};
    conto.effettuaTransazione(Transazione(100.0, data1, "bonifico", Transazione::TipoTransazione::ENTRATA));

    year_month_day data2{2023_y / 07 / 23};
    conto.effettuaTransazione(Transazione(90.0, data2, "prelievo", Transazione::TipoTransazione::USCITA));

    const string nomeFile = "test_transazioni.txt";

    conto.salvaSuFile(nomeFile);

    ifstream file(nomeFile);
    ASSERT_TRUE(file.is_open());

    string linea;
    getline(file, linea);
    ASSERT_EQ(linea, "2023-07-22 100.0 E bonifico");

    getline(file, linea);
    ASSERT_EQ(linea, "2023-07-23 90.0 U prelievo");

    file.close();
}

TEST(ContoCorrenteTest, TestLeggiDaFile) {
    ofstream inputFile("test_input.txt");
    inputFile << "2023-07-22 100.0 E bonifico" << std::endl;
    inputFile << "2023-07-23 90.0 U prelievo" << std::endl;
    inputFile.close();

    ContoCorrente conto;

    ASSERT_NO_THROW(conto.leggiDaFile("test_input.txt"));

    ASSERT_EQ(conto.getNumeroTransazioni(), 2);
    ASSERT_DOUBLE_EQ(conto.getSaldo(), 10.0);

    ASSERT_THROW(conto.leggiDaFile("file_inesistente.txt"), runtime_error);

    remove("test_input.txt");
}

