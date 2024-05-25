#include "PCT.h"
#include <algorithm>
#include <iostream>
#include <string>

PCT::PCT(double pct) : m_pct(pct) {
    if ( pct < 0.0 || pct > 1.0 ) {
        std::cout << "Invalid argument. Percentile must be between 0.0 and 1.0" << std::endl;
        exit(1);
    }
}
void PCT::update(double next) {
    m_numbers.push_back(next);
}
double PCT::eval() const {
    if (m_numbers.empty()){
        return 0;
    }
    std::vector<double> sorted_numbers = m_numbers;
    std::sort(sorted_numbers.begin(), sorted_numbers.end());
    size_t index = static_cast<size_t>(std::ceil(m_pct * sorted_numbers.size())) - 1;
    return sorted_numbers[index];
}
const char *PCT::name() const {
    static std::string pct_name = "pct" + std::to_string(static_cast<int>(m_pct * 100));
    return pct_name.c_str();
}
