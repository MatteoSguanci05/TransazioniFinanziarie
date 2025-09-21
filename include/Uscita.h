#ifndef USCITA_H
#define USCITA_H

#include "Transazione.h"

class Uscita : public Transazione {
public:
    Uscita(double i, const std::string& d);
    void scriviTransizione(std::ostream& os) const override;
};

#endif // USCITA_H
