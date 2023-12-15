//
// Created by ft001 on 18/07/2023.
//

#include "ContoCorrente.h"
#include <sstream>
#include <iomanip>

year_month_day parseDate(const string &DataStr) {
    istringstream ss(DataStr);
    tm tm = {};
    ss >> get_time(&tm, "%Y-%m-%d");
    if (ss.fail()) {
        throw runtime_error("Errore nella conversione della data.");
    }
    return year(tm.tm_year + 1900) / month(tm.tm_mon + 1) / day(tm.tm_mday);
}

void ContoCorrente::effettuaTransazione(const Transazione &transazione) {
    const auto &transData = transazione.getData();
    if (!transData.ok()) {
        cout << "Data della transazione non valida" << endl;
        return;
    }

    Transazione::TipoTransazione tipoTransazione = transazione.getTipo();
    transazioni.push_back(transazione);

    if (tipoTransazione == Transazione::TipoTransazione::ENTRATA) {
        saldo += transazione.getImporto();
        cout << "Deposito sul conto avvenuto con successo!" << endl;
    } else if (tipoTransazione == Transazione::TipoTransazione::USCITA) {
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


void ContoCorrente::salvaSuFile(const string &nomeFile) {
    ofstream file(nomeFile);
    if (!file) {
        cerr << "Errore nell'apertura del file." << endl;
        return;
    }
    for (const Transazione &transazione: transazioni) {
        file << format("%Y-%m-%d", transazione.getData()) << " " << transazione.getImporto()
             << Transazione::TipoTransazioneToChar(transazione.getTipo()) << " " << transazione.getDescrizione()
             << endl;
    }

    file.close();
}

void ContoCorrente::leggiDaFile(const string &nomeFile) {
    transazioni.clear();
    this->saldo = 0;
    ifstream file(nomeFile);
    string tmp;
    if (!file.is_open()) {
        cerr << "Impossibile aprire il file " << nomeFile << " per la lettura." << endl;
        return;
    }

    try {
        while (getline(file, tmp)) {
            if (!file) {
                cerr << "Errore nella lettura dei dati dalla transazione." << endl;
                break;
            }

            string dataStr;
            double importo;
            char tipoChar;
            string descr;
            stringstream ss(tmp);
            string parola;
            vector<string> tokens;
            while (!ss.eof()) {
                getline(ss, parola, ' ');
                tokens.push_back(parola);
            }
            dataStr = tokens[0];
            tipoChar = tokens[1].back();
            importo = stod(tokens[1]);
            descr = tokens[2];

            Transazione::TipoTransazione tipoTr = (tipoChar == 'E') ? Transazione::TipoTransazione::ENTRATA
                                                                    : Transazione::TipoTransazione::USCITA;

            Transazione nuovaTransazione(importo, parseDate(dataStr), descr, tipoTr);
            transazioni.push_back(nuovaTransazione);
            if (tipoTr == Transazione::TipoTransazione::ENTRATA) {
                this->saldo += importo;
            }
            else {
                this->saldo -= importo;
            }
            ss.clear();

        }
        file.close();
    } catch (const exception &e) {
        cerr << "Errore durante la lettura del file: " << e.what() << endl;
        file.close();
        return;
    }

    //aggiornaSaldo();
}

double ContoCorrente::getSaldo() const {
    return saldo;
}

vector<Transazione> ContoCorrente::cercaTransazioniInBaseAllaData(const date::year_month_day &data) const {
    vector<Transazione> transazioniData;
    for (const Transazione &t: transazioni) {
        if (t.getData() == data) {
            transazioniData.push_back(t);
        }
    }
    return transazioniData;
}

bool ContoCorrente::CancellaTransazioniPerData(const year_month_day &data) {
    double importoCancellato = 0.0;
    bool cancellazioneAvvenuta = false;

    auto newEnd = remove_if(transazioni.begin(), transazioni.end(),
                            [data, &importoCancellato, &cancellazioneAvvenuta](const Transazione &tr) {
                                if (tr.getData() == data) {
                                    double tmp = tr.getImporto();
                                    tmp = tr.getTipo() == Transazione::TipoTransazione::USCITA ? tmp : -tmp;
                                    importoCancellato += tmp;
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
        throw runtime_error(
                "Nessuna transazione trovata in data " + format("%F", data) + ". La cancellazione non e' avvenuta.");
    }
    if (cancellazioneAvvenuta) {
        ofstream canc("transazioni.txt");
        canc.close();
        salvaSuFile("transazioni.txt");
    }
    return cancellazioneAvvenuta;
}

vector<Transazione> ContoCorrente::cercaTransazioniPerTipo(Transazione::TipoTransazione tipo) const {
    vector<Transazione> transazioniTipo;
    for (const Transazione &t: transazioni) {
        if (t.getTipo() == tipo) {
            transazioniTipo.push_back(t);
        }
    }
    return transazioniTipo;
}

vector<Transazione> ContoCorrente::cercaTransazioniPerImporto(double importo) const {
    vector<Transazione> transazioniImporto;
    for (const Transazione &t: transazioni) {
        if (t.getImporto() == importo) {
            transazioniImporto.push_back(t);
        }
    }
    return transazioniImporto;
}

vector<Transazione> ContoCorrente::cercaTransazioniPerDescrizione(const string &descrizione) const {
    vector<Transazione> transazioniDescrizione;
    for (const Transazione &t: transazioni) {
        if (t.getDescrizione() == descrizione) {
            transazioniDescrizione.push_back(t);
        }
    }
    return transazioniDescrizione;
}

void ContoCorrente::aggiornaSaldo() {
    saldo = 0.0;
    for (const Transazione &transazione: transazioni) {
        if (transazione.getImporto() > 0) {
            saldo += transazione.getImporto();
        } else if (transazione.getImporto() < 0) {
            saldo -= transazione.getImporto();
        }
    }
}

bool ContoCorrente::CancellaTransazioniPerImporto(double importo) {
    double importoCancellato = 0.0;
    bool cancellazioneAvvenuta = false;

    auto newEnd = remove_if(transazioni.begin(), transazioni.end(),
                            [importo, &importoCancellato, &cancellazioneAvvenuta](const Transazione &tr) {
                                if (tr.getImporto() == importo) {
                                    double tmp = tr.getImporto();
                                    tmp = tr.getTipo() == Transazione::TipoTransazione::USCITA ? tmp : -tmp;
                                    importoCancellato += tmp;
                                    cancellazioneAvvenuta = true;
                                    return true;
                                }
                                return false;
                            });

    if (cancellazioneAvvenuta) {
        transazioni.erase(newEnd, transazioni.end());
        saldo += importoCancellato;
        cout << "Le transazioni con importo " << importo << " euro sono state cancellate!" << endl;
        cout << "Saldo corrente dopo la cancellazione: " << getSaldo() << " euro" << endl;
    } else {
        throw runtime_error("Nessuna transazione trovata con importo " + to_string(importo) +
                            " euro. La cancellazione non e' avvenuta.");
    }
    if (cancellazioneAvvenuta) {
        ofstream canc("transazioni.txt");
        canc.close();
        salvaSuFile("transazioni.txt");
    }
    return cancellazioneAvvenuta;
}

size_t ContoCorrente::getNumeroTransazioni() const {
    return transazioni.size();
}

