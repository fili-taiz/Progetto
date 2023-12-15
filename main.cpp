// main.cpp

#include <iostream>
#include "ContoCorrente.h"
int main() {
    try {
        ContoCorrente conto;
        conto.effettuaTransazione(Transazione(100.0, year_month_day{2023_y / 07 / 22}, "bonifico",
                                              Transazione::TipoTransazione::ENTRATA));
        conto.effettuaTransazione(
                Transazione(90.0, year_month_day{2023_y / 07 / 23}, "prelievo", Transazione::TipoTransazione::USCITA));
        conto.effettuaTransazione(
                Transazione(5.0, year_month_day{2023_y / 07 / 23}, "finanziamento", Transazione::TipoTransazione::USCITA));
        conto.effettuaTransazione(Transazione(200.0, year_month_day{2023_y / 07 / 24}, "bonifico",
                                              Transazione::TipoTransazione::ENTRATA));
        conto.effettuaTransazione(
                Transazione(90.0, year_month_day{2023_y / 07 / 25}, "prelievo", Transazione::TipoTransazione::USCITA));

        conto.salvaSuFile("transazioni.txt");

        cout << "\nTRANSAZIONI IN BASE ALLA DATA" << endl;
        vector<Transazione> transazioniData = conto.cercaTransazioniInBaseAllaData(year_month_day{2023_y / 07 / 23});
        cout << "Transazioni del 2023-07-23:" << endl;
        for (const Transazione &trans: transazioniData) {
            cout << "Importo: " << trans.getImporto() << " euro, Descrizione: " << trans.getDescrizione() << ", Tipo:"
                 << trans.getTipo() << endl;
        }
            cout << "\nCANCELLA TRANSAZIONI PER DATA" << endl;
            try {
                conto.CancellaTransazioniPerData(year_month_day{2023_y / 07 / 23});
            } catch (const exception &e) {
                cerr << "Errore durante la cancellazione delle transazioni in base alla data: " << e.what() << endl;
            }

        cout << "\nTRANSAZIONI IN BASE ALL'IMPORTO" << endl;
        double importoCercato = 90.0;
        vector<Transazione> transazioniPerImporto = conto.cercaTransazioniPerImporto(importoCercato);
        cout << "Transazioni con importo di " << importoCercato << " euro:" << endl;
        for (const Transazione &trans: transazioniPerImporto) {
            cout << "Data: " << trans.getData() << ", Descrizione: " << trans.getDescrizione() << ", Tipo: "
                 << trans.getTipo() << endl;
        }

        cout << "\nTRANSAZIONI IN BASE ALLA DESCRIZIONE" << endl;
        string descrizioneCercata = "bonifico";
        vector<Transazione> transazioniPerDescrizione = conto.cercaTransazioniPerDescrizione(descrizioneCercata);
        cout << "Transazioni con descrizione \"" << descrizioneCercata << "\":" << endl;
        for (const Transazione &trans: transazioniPerDescrizione) {
            cout << "Data: " << trans.getData() << ", Importo: " << trans.getImporto() << " euro, Tipo: "
                 << trans.getTipo() << endl;
        }

        cout << "\nTRANSAZIONI IN BASE AL TIPO" << endl;
        Transazione::TipoTransazione tipoCercato = Transazione::TipoTransazione::ENTRATA;
        vector<Transazione> transazioniPerTipo = conto.cercaTransazioniPerTipo(tipoCercato);

        cout << "STAMPA LE TRANSAZIONI DI UN TIPO" << endl;
        cout << "Transazioni di tipo " << (tipoCercato == Transazione::TipoTransazione::ENTRATA ? "ENTRATA" : "USCITA")
             << ":" << endl;
        for (const Transazione &trans: transazioniPerTipo) {
            cout << trans.toString() << endl;
        }

        Transazione::TipoTransazione tipoCercato2 = Transazione::TipoTransazione::USCITA;
        vector<Transazione> transazioniPerTipo2 = conto.cercaTransazioniPerTipo(tipoCercato2);
        cout << "Transazioni di tipo " << (tipoCercato2 == Transazione::TipoTransazione::USCITA ? "USCITA" : "ENTRATA")
             << ":" << endl;
        for (const Transazione &trans: transazioniPerTipo2) {
            cout << trans.toString() << endl;

        }

        cout << "\nCANCELLA TRANSAZIONI PER IMPORTO" << endl;
        double importoDaCancellare = 100.0;
        try {
            conto.CancellaTransazioniPerImporto(importoDaCancellare);
        } catch (const exception &e) {
            cerr << "Errore durante la cancellazione delle transazioni per importo: " << e.what() << endl;
        }


        conto.leggiDaFile("transazioni.txt");


    } catch (const exception &e) {
        cerr << "Errore: " << e.what() << endl;
    }

    return 0;
}
