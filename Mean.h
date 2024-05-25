#ifndef MEAN_H
#define MEAN_H

#include "IStatistics.h"

class Mean : public IStatistics {
public:
    Mean();
    void update(double next) override;
    double eval() const override;
    const char * name() const override;
private:
    double m_sum;
    size_t m_count;
};

#endif // MEAN_H
