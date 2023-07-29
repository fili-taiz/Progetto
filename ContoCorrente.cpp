//
// Created by ft001 on 18/07/2023.
//

#include "ContoCorrente.h"
#include <sstream>
#include <iomanip>
#include <ctime>
year_month_day parseDate(const string& DataStr) {
    istringstream ss(DataStr);
    tm tm = {};
    ss >> std::get_time(&tm, "%Y-%m-%d");
    if (ss.fail()) {
        throw runtime_error("Errore nella conversione della data.");
    }
    return year(tm.tm_year + 1900) / month(tm.tm_mon + 1) / day(tm.tm_mday);
}

void ContoCorrente::effettuaTransazione(const Transazione& transazione) {
    const auto& transData = transazione.getData();
    if (!transData.ok()) {
        cout << "Data della transazione non valida" << endl;
        return;
    }

    Transazione::TipoTransazione tipoTransazione = transazione.getTipo();
    transazioni.push_back(transazione);

    if (tipoTransazione == Transazione::TipoTransazione::ENTRATA) {
        saldo += transazione.getImporto();
        cout << "Deposito sul conto avvenuto con successo!" << endl;
    } else if (tipoTransazione== Transazione::TipoTransazione::USCITA){
        // Verifica se c'è abbastanza saldo per il prelievo
        if (saldo >= transazione.getImporto()) {
            saldo -= transazione.getImporto();
            cout << "Prelievo avvenuto con successo!" << endl;
        } else {
            cout << "Impossibile effettuare il prelievo. Saldo insufficiente." << endl;
            return;
        }
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
        file << format("%Y-%m-%d", transazione.getData()) << " " << transazione.getImporto() << endl;
        file << Transazione::TipoTransazioneToChar(transazione.getTipo()) << endl;
    }

    file.close();
}

void ContoCorrente::leggiDaFile(const string &nomeFile) {
    transazioni.clear();
    ifstream file(nomeFile);
    if (file.is_open()) {
        string dataStr;
        double importo;
        char tipoChar;
        string descr;
        while (getline(file,dataStr, ' ') >> importo >> tipoChar) {
            Transazione::TipoTransazione tipo = Transazione::CharToTipoTransazione(tipoChar);
            file.ignore();
            getline(file, descr);
            year_month_day data = parseDate(dataStr);
            transazioni.emplace_back(importo, data, descr, tipo);
        }
        file.close();
    } else {
        cerr << "Impossibile aprire il file " << nomeFile << " per la lettura." << endl;
    }

    // Aggiornare il saldo utilizzando le transazioni lette da file
    aggiornaSaldo();
}


void ContoCorrente::stampaTransazioni() const {
    cout << "Transazioni:" << endl;
    for (const Transazione& trans : transazioni) {
        cout <<trans.toString()<<endl;
    }
}



double ContoCorrente::getSaldo() const {
    return saldo;
}

vector<Transazione> ContoCorrente::cercaTransazioniInBaseAllaData(const date::year_month_day& data) const {
    vector<Transazione> transazioniData;
    for(const Transazione& t: transazioni){
        if(t.getData() == data){
            transazioniData.push_back(t);
        }
    }
    return transazioniData;
}

bool ContoCorrente::CancellaTransazioniPerData(const year_month_day& data) {
    double importoCancellato = 0.0;
    bool cancellazioneAvvenuta = false;

    auto newEnd = remove_if(transazioni.begin(), transazioni.end(), [data, &importoCancellato, &cancellazioneAvvenuta](const Transazione& tr) {
        if (tr.getData() == data) {
            importoCancellato += tr.getImporto();
            cancellazioneAvvenuta = true;
            return true;
        }
        return false;
    });

    if (cancellazioneAvvenuta) {
        transazioni.erase(newEnd, transazioni.end());
        saldo += importoCancellato;
        cout << "Le transazioni in data " << format("%F", data) << " sono state cancellate!" << endl;
        cout << "Saldo corrente dopo la cancellazione: " << getSaldo() << " euro" << endl;
    } else {
        throw runtime_error("Nessuna transazione trovata in data " + format("%F", data) + ". La cancellazione non e' avvenuta.");
    }

    return cancellazioneAvvenuta;
}

//ritornare un booleano se non esiste la transazione da cancellare

vector<Transazione> ContoCorrente::cercaTransazioniPerTipo(Transazione::TipoTransazione tipo) const {
    vector<Transazione> transazioniTipo;
    for (const Transazione& t : transazioni) {
        if (t.getTipo() == tipo) {
            transazioniTipo.push_back(t);
        }
    }
    return transazioniTipo;
}

vector<Transazione> ContoCorrente::cercaTransazioniPerImporto(double importo) const {
    vector<Transazione> transazioniImporto;
    for (const Transazione& t : transazioni) {
        if (t.getImporto() == importo) {
            transazioniImporto.push_back(t);
        }
    }
    return transazioniImporto;
}

vector<Transazione> ContoCorrente::cercaTransazioniPerDescrizione(const string& descrizione) const {
    vector<Transazione> transazioniDescrizione;
    for (const Transazione& t : transazioni) {
        if (t.getDescrizione() == descrizione) {
            transazioniDescrizione.push_back(t);
        }
    }
    return transazioniDescrizione;
}

void ContoCorrente::aggiornaSaldo() {
    saldo = 0.0;
    for (const Transazione& transazione : transazioni) {
        if(transazione.getImporto() > 0){
            saldo+=transazione.getImporto();
        } else if(transazione.getImporto() < 0){
            saldo-=transazione.getImporto();
        }
    }
}

vector<Transazione>::iterator ContoCorrente::trovaTransazione(const year_month_day& data, const string& descrizione) {
    return std::find_if(transazioni.begin(), transazioni.end(), [data, descrizione](const Transazione& tr) {
        return (tr.getData() == data && tr.getDescrizione() == descrizione);
    });
}




