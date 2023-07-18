//
// Created by ft001 on 18/07/2023.
//

#ifndef PROGETTO_TRANSAZIONI_H
#define PROGETTO_TRANSAZIONI_H


#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Transazione {
public:
    Transazione(const string& tipo_, double importo_) : tipo(tipo_), importo(importo_);

    string getTipo() const;

    double getImporto() const {
        return importo;
    }

private:
    string tipo;
    double importo;
};

class ContoCorrente {
public:
    void aggiungiTransazione(const Transazione& transazione) {
        transazioni.push_back(transazione);
    }

    void salvaSuFile(const string& nomeFile) {
        ofstream file(nomeFile);
        if (!file) {
            cerr << "Errore nell'apertura del file." << std::endl;
            return;
        }

        for (const Transazione& transazione : transazioni) {
            file << transazione.getTipo() << "|" << transazione.getImporto() << std::endl;
        }

        file.close();
    }

    void leggiDaFile(const string& nomeFile) {
        transazioni.clear();
        ifstream file(nomeFile);
        if (!file) {
            std::cerr << "Errore nell'apertura del file." << std::endl;
            return;
        }

        string linea;
        while (std::getline(file, linea)) {
            std::string tipo;
            double importo;
            size_t separatorePos = linea.find('|');
            if (separatorePos != string::npos) {
                tipo = linea.substr(0, separatorePos);
                importo = stod(linea.substr(separatorePos + 1));
                Transazione transazione(tipo, importo);
                transazioni.push_back(transazione);
            }
        }

        file.close();
    }

    void stampaTransazioni() const {
        for (const Transazione& transazione : transazioni) {
            cout << "Tipo: " << transazione.getTipo() << "| Importo: " << transazione.getImporto() << "\tEURO" << std::endl;
        }
    }

private:
    vector<Transazione> transazioni;
};


#endif //PROGETTO_TRANSAZIONI_H
