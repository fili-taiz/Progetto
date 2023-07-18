#include <iostream>
#include "ContoCorrente.h"

int main() {
    ContoCorrente conto1;

    Transazione t1("Entrata", 431.0);
    Transazione t2("Uscita", 500.0);
    Transazione t3("Entrata", 832.0);
    Transazione t4("Entrata", 12.0);
    Transazione t5("Uscita", 999.5);

    conto1.aggiungiTransazione(t1);
    conto1.aggiungiTransazione(t2);
    conto1.aggiungiTransazione(t3);
    conto1.aggiungiTransazione(t4);
    conto1.aggiungiTransazione(t5);

    conto1.salvaSuFile("C:\\Users\\ft001\\Desktop\\Elaborato\\transazioni.txt");

    conto1.leggiDaFile("C:\\Users\\ft001\\Desktop\\Elaborato\\transazioni.txt");

    conto1.stampaTransazioni();

    ContoCorrente conto2;

    Transazione c1("Entrata", 10111);
    Transazione c2("Entrata", 20299);
    Transazione c3("Uscita", 10876.98);
    Transazione c4("Entrata", 21876);
    Transazione c5("Uscita", 876.65);

    conto2.aggiungiTransazione(c1);
    conto2.aggiungiTransazione(c2);
    conto2.aggiungiTransazione(c3);
    conto2.aggiungiTransazione(c4);
    conto2.aggiungiTransazione(c5);

    conto2.salvaSuFile("C:\\Users\\ft001\\Desktop\\Elaborato\\transazioni2.txt");

    conto2.leggiDaFile("C:\\Users\\ft001\\Desktop\\Elaborato\\transazioni2.txt");

    conto2.stampaTransazioni();

    return 0;
}
