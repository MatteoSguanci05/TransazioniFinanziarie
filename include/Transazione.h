#ifndef TRANSAZIONE_H
#define TRANSAZIONE_H

#include <string>
#include <stdexcept>
#include <iostream>
#include <fstream>

enum class TipoTransazione {
    ENTRATA,
    USCITA
};

class Transazione {
protected:
    TipoTransazione tipo;
    double importo;
    std::string descrizione;

public:
    // Costruttore
    Transazione(TipoTransazione t, double i, const std::string& d);

    // Distruttore virtuale
    virtual ~Transazione();

    // Getter
    TipoTransazione getTipo() const;
    double getImporto() const;
    std::string getDescrizione() const;

    // Setter
    void setTipo(TipoTransazione t);
    void setImporto(double i);
    void setDescrizione(const std::string& d);


    // scrittura delle transizioni
    virtual void scriviTransizione(std::ostream& os) const = 0;
};

#endif // TRANSAZIONE_H
