//
// Created by ft001 on 18/07/2023.
//

#include "Transazione.h"


Transazione::Transazione(double importo, year_month_day data, const string &descrizione, TipoTransazione tipo)
        : importo(importo), data(data), descrizione(descrizione), tipo(tipo) {}

double Transazione::getImporto() const {
    return importo;
}

year_month_day Transazione::getData() const {
    return data;
}

Transazione::TipoTransazione Transazione::getTipo() const {
    return tipo;
}

string Transazione::getDescrizione() const {
    return descrizione;
}

string Transazione::toString() const {
    string tipoStr = (tipo == TipoTransazione::ENTRATA) ? "E" : "U";
    stringstream ss;
    ss << "Data: " << data << ", Importo: " << importo << " euro, Tipo: " << tipoStr << ", Descrizione: "
       << descrizione;
    return ss.str();
}

ostream &operator<<(ostream &os, Transazione::TipoTransazione tipo) {
    switch (tipo) {
        case Transazione::TipoTransazione::ENTRATA:
            os << "ENTRATA";
            break;
        case Transazione::TipoTransazione::USCITA:
            os << "USCITA";
            break;
    }
    return os;
}

bool Transazione::operator==(const Transazione &otherobj) const {
    return (importo == otherobj.importo) &&
           (data == otherobj.data) &&
           (descrizione == otherobj.descrizione) &&
           (tipo == otherobj.tipo);

}

Transazione::TipoTransazione Transazione::CharToTipoTransazione(char c) {
    return (c == 'E') ? TipoTransazione::ENTRATA : TipoTransazione::USCITA;
}

char Transazione::TipoTransazioneToChar(TipoTransazione tipo) {
    return (tipo == TipoTransazione::ENTRATA) ? 'E' : 'U';
}