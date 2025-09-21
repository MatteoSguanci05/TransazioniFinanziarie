#ifndef INGRESSO_H
#define INGRESSO_H

#include "Transazione.h"

class Ingresso : public Transazione {
public:
    Ingresso(double i, const std::string& d);
    void scriviTransizione(std::ostream& os) const override;
};

#endif // INGRESSO_H
