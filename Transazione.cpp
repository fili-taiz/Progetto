//
// Created by ft001 on 18/07/2023.
//

#include "Transazione.h"


Transazione::Transazione(const std::string &tipo, double importo) {}

string Transazione::getTipo() const {
    return tipo;
}

double Transazione::getImporto() const {
    return importo;
}