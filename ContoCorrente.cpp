//
// Created by ft001 on 18/07/2023.
//

#include "ContoCorrente.h"

void ContoCorrente::effettuaTransazione(const Transazione &transazione) {
    if (transazione.getTipo() == Transazione::TipoTransazione::ENTRATA) {
        transazioni.push_back(transazione);
        cout << "Deposito sul conto avvenuto con successo!" << endl;
    } else if (transazione.getTipo() == Transazione::TipoTransazione::USCITA) {
        // Verifica se c'è abbastanza saldo per il prelievo
        if (saldo + transazione.getImporto() >= 0) {
            transazioni.push_back(transazione);
            cout << "Prelievo avvenuto con successo!" << endl;
        } else {
            cout << "Impossibile effettuare il prelievo. Saldo insufficiente." << endl;
            return;
        }
    }

    if(transazione.getTipo() == Transazione::TipoTransazione::ENTRATA) {
        saldo += transazione.getImporto();
    } else{
        saldo-=transazione.getImporto();
    }
    cout << "Saldo corrente: " << getSaldo() << " euro" << endl;
}

void ContoCorrente::salvaSuFile(const std::string &nomeFile) {
    ofstream file(nomeFile);
    if (!file) {
        cerr << "Errore nell'apertura del file." << endl;
        return;
    }


    for (const Transazione& transazione : transazioni) {
        file << transazione.getData() << " " << transazione.getImporto() << std::endl;
        if (transazione.getTipo() == Transazione::TipoTransazione::ENTRATA) {
            file << "ENTRATA";
        } else {
            file << "USCITA";
        }
        file << endl;
    }

    file.close();
}

void ContoCorrente::leggiDaFile(const string &nomeFile) {
    transazioni.clear();
    ifstream file(nomeFile);
    if (file.is_open()) {
        string data;
        double importo;
        string tipoStr;
        while (file >> data >> importo >> tipoStr) {
            Transazione::TipoTransazione tipo;
            if (tipoStr == "ENTRATA") {
                tipo = Transazione::TipoTransazione::ENTRATA;
            } else if (tipoStr == "USCITA") {
                tipo = Transazione::TipoTransazione::USCITA;
            } else {
                cerr << "Errore nella lettura del tipo di transazione dal file." << endl;
                file.close();
                return;
            }
            transazioni.emplace_back(Transazione(importo, data, tipo));
        }
        file.close();
    } else {
        cerr << "Impossibile aprire il file " << nomeFile << " per la lettura." << endl;
    }
    // Aggiornare il saldo utilizzando le transazioni lette da file
    saldo = 0.0;
    for (const Transazione& transazione : transazioni) {
        saldo += transazione.getImporto();
    }
}


void ContoCorrente::stampaTransazioni() const {
    cout << "Transazioni:" << endl;
    for (const Transazione& trans : transazioni) {
        cout << "Data: " << trans.getData() << ", Importo: " << trans.getImporto() << " euro" << endl;
    }
}



double ContoCorrente::getSaldo() const {
    return saldo;
}

vector<Transazione> ContoCorrente::cercaTransazioniInBaseAllaData(const std::string &data) const {
    vector<Transazione> transazioniData;
    for(const Transazione& t: transazioni){
        if(t.getData() == data){
            transazioniData.push_back(t);
        }
    }
    return transazioniData;
}

void ContoCorrente::CancellaTransazioniPerData(const string& data) {
    double importoCancellato = 0.0;

    transazioni.erase(
            std::remove_if(transazioni.begin(), transazioni.end(), [data, &importoCancellato](const Transazione& tr) {
                if (tr.getData() == data) {
                    importoCancellato += tr.getTipo() == Transazione::TipoTransazione::ENTRATA ? tr.getImporto() : -tr.getImporto();
                    return true;
                }
                return false;
            }),
            transazioni.end()
    );

    saldo += importoCancellato;
    cout << "Le transazioni in data " << data << " sono state cancellate!" << endl;
    cout << "Saldo corrente dopo la cancellazione: " << getSaldo() << " euro" << endl;
}



