#ifndef  PCT_H
#define  PCT_H

#include "IStatistics.h"
#include <vector>

class PCT : public IStatistics {
public:
    PCT(double pct);
    void update(double next) override;
    double eval() const override;
    const char * name() const override;
private:
    double m_pct;
    std::vector<double> m_numbers;
};

#endif // PCT_H
