//
// Created by ft001 on 18/07/2023.
//

#ifndef PROGETTO_TRANSAZIONE_H
#define PROGETTO_TRANSAZIONE_H


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "date/include/date/date.h"

using namespace std;
using namespace date;

class Transazione {
public:

    enum class TipoTransazione {
        ENTRATA,
        USCITA
    };

    Transazione(double importo, year_month_day data, const string &descrizione, TipoTransazione tipo);

    double getImporto() const;

    year_month_day getData() const;

    TipoTransazione getTipo() const;

    string getDescrizione() const;

    string toString() const;

    friend ostream &operator<<(ostream &os, TipoTransazione tipo);

    bool operator==(const Transazione &otherobj) const;

    static TipoTransazione CharToTipoTransazione(char c);

    static char TipoTransazioneToChar(TipoTransazione tipo);

private:
    double importo;
    year_month_day data;
    TipoTransazione tipo;
    string descrizione;
};


#endif //PROGETTO_TRANSAZIONE_H

//aggiungere una stringa di descrizione es. bonifico e che la data sia più sicura

