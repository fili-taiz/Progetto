//
// Created by ft001 on 18/07/2023.
//

#ifndef PROGETTO_CONTOCORRENTE_H
#define PROGETTO_CONTOCORRENTE_H
#include "Transazione.h"
class ContoCorrente {
public:
    void aggiungiTransazione(const Transazione& transazione);

    void salvaSuFile(const string& nomeFile);

    void leggiDaFile(const string& nomeFile);

    void stampaTransazioni() const;

    int getNumeroTransazioni()const;

    const Transazione& getTransazioneAtIndex(int index)const;

private:
    vector<Transazione> transazioni;
};




#endif //PROGETTO_CONTOCORRENTE_H
