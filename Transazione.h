//
// Created by ft001 on 18/07/2023.
//

#ifndef PROGETTO_TRANSAZIONE_H
#define PROGETTO_TRANSAZIONE_H


#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Transazione {
public:
    Transazione(const string& tipo_, double importo_) : tipo(tipo_), importo(importo_){};

    string getTipo() const;

    double getImporto() const;

private:
    string tipo;
    double importo;
};


#endif //PROGETTO_TRANSAZIONE_H
