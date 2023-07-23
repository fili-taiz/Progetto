//
// Created by ft001 on 18/07/2023.
//

#include "Transazione.h"


Transazione::Transazione(double importo_, const string& data_) : importo(importo_), data(data_) {}

double Transazione::getImporto() const {
    return importo;
}

string Transazione::getData() const {
    return data;
}