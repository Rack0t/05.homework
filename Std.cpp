#include "Std.h"
#include <cmath>

Std::Std() : m_sum{0}, m_sum_of_squares{0}, m_count{0} {}

void Std::update(double next) {
    m_sum += next;
    m_sum_of_squares += next * next;
    m_count++;
}
double Std::eval() const {
    if (m_count < 2) {
        return 0; // Если чисел меньше двух, возвращаем 0
    }
    double mean = m_sum / m_count;
    double variance = (m_sum_of_squares - m_sum * mean) / (m_count - 1);
    return std::sqrt(variance);
}
const char *Std::name() const {
    return "std";
}