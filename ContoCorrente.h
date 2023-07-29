//
// Created by ft001 on 18/07/2023.
//

#ifndef PROGETTO_CONTOCORRENTE_H
#define PROGETTO_CONTOCORRENTE_H
#include "Transazione.h"
#include <algorithm>
#include <exception>
class ContoCorrente {
public:
    void effettuaTransazione(const Transazione& transazione);
    void salvaSuFile(const string& nomeFile);
    void leggiDaFile(const string& nomeFile);
    void stampaTransazioni()const;
    double getSaldo() const;

    vector<Transazione> cercaTransazioniInBaseAllaData(const year_month_day& data) const;
    vector<Transazione> cercaTransazioniPerImporto(double importo) const;
    vector<Transazione> cercaTransazioniPerDescrizione(const string& descrizione) const;
    vector<Transazione> cercaTransazioniPerTipo(Transazione::TipoTransazione tipo) const;

    bool CancellaTransazioniPerData(const year_month_day& data);
    friend bool operator==(Transazione::TipoTransazione sx, Transazione::TipoTransazione dx){
        return sx == dx;
    }





private:
    double saldo = 0;
    vector<Transazione> transazioni;
    void aggiornaSaldo();
    vector<Transazione>::iterator trovaTransazione(const year_month_day& data, const string& descrizione);
};




#endif //PROGETTO_CONTOCORRENTE_H
