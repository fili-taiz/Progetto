//
// Created by ft001 on 18/07/2023.
//

#ifndef PROGETTO_CONTOCORRENTE_H
#define PROGETTO_CONTOCORRENTE_H
#include "Transazione.h"
#include "algorithm"
class ContoCorrente {
public:
    void effettuaTransazione(const Transazione& transazione);

    void salvaSuFile(const string& nomeFile);

    void leggiDaFile(const string& nomeFile);

    double getSaldo() const;

    void stampaTransazioni() const;

    vector<Transazione> cercaTransazioniInBaseAllaData(const string& data) const;


    void CancellaTransazioniPerData(const string& data);




private:
    double saldo = 0;
    vector<Transazione> transazioni;
};




#endif //PROGETTO_CONTOCORRENTE_H
