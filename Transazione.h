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
    Transazione(double importo_, const string& data_);


    double getImporto() const;

    string getData() const;

//data e conto d'uscita o d'ingresso (valore negativo o positivo)

private:
    double importo;
    string data;
};


#endif //PROGETTO_TRANSAZIONE_H
