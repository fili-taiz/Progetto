//
// Created by ft001 on 18/07/2023.
//

#include "ContoCorrente.h"

void ContoCorrente::aggiungiTransazione(const Transazione &transazione) {
    transazioni.push_back(transazione);
}

void ContoCorrente::salvaSuFile(const std::string &nomeFile) {
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

void ContoCorrente::leggiDaFile(const std::string &nomeFile) {
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

void ContoCorrente::stampaTransazioni() const {
    for (const Transazione& transazione : transazioni) {
        cout << "Tipo: " << transazione.getTipo() << "| Importo: " << transazione.getImporto() << "\tEURO" << std::endl;
    }
}