// main.cpp

#include <iostream>
#include "ContoCorrente.h"

int main() {
    try {
        ContoCorrente conto;

        conto.effettuaTransazione(Transazione(100.0, year_month_day{2023_y/07/22}, "bonifico", Transazione::TipoTransazione::ENTRATA));
        conto.effettuaTransazione(Transazione(90.0, year_month_day{2023_y/07/23}, "prelievo", Transazione::TipoTransazione::USCITA));
        conto.effettuaTransazione(Transazione(5.0, year_month_day{2023_y/07/23}, "prelievo", Transazione::TipoTransazione::USCITA));
        conto.effettuaTransazione(Transazione(200.0, year_month_day{2023_y/07/24}, "bonifico", Transazione::TipoTransazione::ENTRATA));
        conto.effettuaTransazione(Transazione(90.0, year_month_day{2023_y/07/25}, "deposito", Transazione::TipoTransazione::ENTRATA));

        cout<<"\nTRANSAZIONI IN BASE ALLA DATA"<<endl;
        vector<Transazione> transazioniData = conto.cercaTransazioniInBaseAllaData(year_month_day{2023_y/07/23});
        cout << "Transazioni del 2023-07-23:" << endl;
        for (const Transazione& trans : transazioniData) {
            cout << "Importo: " << trans.getImporto() << " euro, Descrizione: " << trans.getDescrizione() << ", Tipo:" << trans.getTipo() << endl;
        }

        cout<<"\nTRANSAZIONI IN BASE ALL'IMPORTO"<<endl;
        double importoCercato = 90.0;
        vector<Transazione> transazioniPerImporto = conto.cercaTransazioniPerImporto(importoCercato);
        cout << "Transazioni con importo di " << importoCercato << " euro:" << endl;
        for (const Transazione& trans : transazioniPerImporto) {
            cout << "Data: " << trans.getData() << ", Descrizione: " << trans.getDescrizione() << ", Tipo: " << trans.getTipo() << endl;
        }

        cout<<"\nTRANSAZIONI IN BASE ALLA DESCRIZIONE"<<endl;
        string descrizioneCercata = "bonifico";
        vector<Transazione> transazioniPerDescrizione = conto.cercaTransazioniPerDescrizione(descrizioneCercata);
        cout << "Transazioni con descrizione \"" << descrizioneCercata << "\":" << endl;
        for (const Transazione& trans : transazioniPerDescrizione) {
            cout << "Data: " << trans.getData() << ", Importo: " << trans.getImporto() << " euro, Tipo: " << trans.getTipo() << endl;
        }

        cout<<"\nTRANSAZIONI IN BASE AL TIPO"<<endl;
        Transazione::TipoTransazione tipoCercato = Transazione::TipoTransazione::ENTRATA;
        vector<Transazione> transazioniPerTipo = conto.cercaTransazioniPerTipo(tipoCercato);

       cout<<"STAMPA LE TRANSAZIONI DI UN TIPO"<<endl;
        cout << "Transazioni di tipo " << (tipoCercato == Transazione::TipoTransazione::ENTRATA ? "ENTRATA" : "USCITA") << ":" << endl;
        for (const Transazione& trans : transazioniPerTipo) {
            cout << trans.toString() << endl;
        }

        conto.CancellaTransazioniPerData(year_month_day{2023_y/07/23});

        cout<<"\nSTAMPA TUTTE LE TRANSAZIONI"<<endl;
        conto.stampaTransazioni();

        cout<<"\nSALVA LE TRANSAZIONI SU FILE"<<endl;
        conto.salvaSuFile("transazioni.txt");

        cout<<"\nLEGGE LE TRANSAZIONI DA FILE"<<endl;
        conto.leggiDaFile("transazioni.txt");

        cout << "-----------" << endl;
    } catch (const exception& e) {
        cerr << "Errore: " << e.what() << endl;
    }

    return 0;
}
