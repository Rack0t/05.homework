#ifndef STD_H
#define STD_H

#include "IStatistics.h"

class Std : public IStatistics {
public:
    Std();
    void update(double next) override;
    double eval() const override;
    const char * name() const override;
private:
    double m_sum;
    double m_sum_of_squares;
    size_t m_count;
};

#endif // STD_H
