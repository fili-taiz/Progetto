//
// Created by ft001 on 18/07/2023.
//

#include "ContoCorrente.h"

void ContoCorrente::effettuaTransazione(const Transazione &transazione) {
    transazioni.push_back(transazione);
    if(transazione.getImporto() > 0){
        cout<<"Deposito sul conto avvenuto con successo!"<<endl;
    } else if(transazione.getImporto() < 0){
        cout<<"Prelievo avvenuto con successo!"<<endl;
    }
    saldo+=transazione.getImporto();
    cout<<"Saldo corrente:"<< getSaldo()<< "euro" << endl;
}

void ContoCorrente::salvaSuFile(const std::string &nomeFile) {
    ofstream file(nomeFile);
    if (!file) {
        cerr << "Errore nell'apertura del file." << endl;
        return;
    }


    for (const Transazione& transazione : transazioni) {
        file << transazione.getData() << " " << transazione.getImporto() << std::endl;
    }

    file.close();
}

void ContoCorrente::leggiDaFile(const string &nomeFile) {
    transazioni.clear();
    ifstream file(nomeFile);
    if (file.is_open()) {
        string data;
        double importo;
        while (file >> data >> importo) {
            transazioni.emplace_back(Transazione(importo, data));
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

void ContoCorrente::CancellaTransazioniPerData(const string &data) {
    double importo_canc = 0;
    transazioni.erase(
            std::remove_if(transazioni.begin(), transazioni.end(),
                           [data, &importo_canc](const Transazione& tr) {
                if(tr.getData() == data){
                    importo_canc+=tr.getImporto();
                    return true;
                }
                return false; }),
            transazioni.end()
    );

    saldo+=importo_canc;
    cout<<"Le transazioni in data \t"<<data<<"\tsono state cancellate!"<<endl;
    cout<<"Saldo corrente dopo la cancellazione:"<<getSaldo()<<"euro"<<endl;
}

