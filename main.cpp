#include <iostream>
#include "ContoCorrente.h"

int main() {
    ContoCorrente conto;

    conto.effettuaTransazione(Transazione(100.0, "2023-07-22")); // Entrata di 100 euro
    conto.effettuaTransazione(Transazione(-90.0, "2023-07-23")); // Uscita di 90 euro
    conto.effettuaTransazione(Transazione(-5.0, "2023-07-23")); // Uscita di 5 euro
    conto.effettuaTransazione(Transazione(200.0, "2023-07-24")); // Entrata di 200 euro


   vector<Transazione> transazioniData = conto.cercaTransazioniInBaseAllaData("2023-07-23");
    cout << "Transazioni del 2023-07-23:" << endl;
    for (const Transazione& trans : transazioniData) {
        cout << "Importo: " << trans.getImporto() << " euro" << endl;
    }

    conto.CancellaTransazioniPerData("2023-07-23");
    cout << "Saldo corrente dopo cancellazione: " << conto.getSaldo() << " euro" << endl;

    // Stampa tutte le transazioni
    conto.stampaTransazioni();

    // Salva le transazioni su file
    conto.salvaSuFile("transazioni.txt");

    // Legge le transazioni da file
    conto.leggiDaFile("transazioni.txt");

    cout<<"-----------"<<endl;


    return 0;
}
