#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>

class IStatistics {
public:
	virtual ~IStatistics() {}

	virtual void update(double next) = 0;
	virtual double eval() const = 0;
	virtual const char * name() const = 0;
};

class Min : public IStatistics {
public:
	Min() : m_min{std::numeric_limits<double>::max()} {
	}

	void update(double next) override {
		if (next < m_min) {
			m_min = next;
		}
	}

	double eval() const override {
		return m_min;
	}

	const char * name() const override {
		return "min";
	}

private:
	double m_min;
};

class Max : public IStatistics {
public:
    Max() : m_max{std::numeric_limits<double>::min()} {
    }
    void update(double next) override {
        if (next > m_max) {
            m_max = next;
        }
    }
    double eval() const override {
        return m_max;
    }

    const char * name() const override {
        return "max";
    }

private:
    double m_max;
};

class Mean : public IStatistics {

public:
    Mean() : m_mean{0}, count_val{0} { }
    void update(double next) override {
        count_val++;
        m_mean += next;
        //m_mean = m_mean / i;
    }
    double eval() const override {
        return m_mean / count_val;
    }

    const char * name() const override {
        return "mean";
    }

private:
    double m_mean;
    int count_val;
};

class Std : public IStatistics{

public:
    Std() : m_sum{0}, m_sum_of_squares{0}, m_count{0} {}

    void update(double next) override {
        m_sum += next;
        m_sum_of_squares += next * next;
        m_count++;
    }

    double eval() const override {
        if (m_count < 2) {
            return 0; // Если чисел меньше двух, возвращаем 0
        }
        double mean = m_sum / m_count;
        double variance = (m_sum_of_squares - m_sum * mean) / (m_count - 1);
        return std::sqrt(variance);
    }

    const char * name() const override {
        return "std";
    }

private:
    double m_sum;
    double m_sum_of_squares;
    size_t m_count;
};

class PCT90 : public IStatistics {
private:
    std::vector<double> m_numbers;

public:

    void update(double next) override {
        m_numbers.push_back(next);
    }

    double eval() const override {
        if (m_numbers.empty()) {
            return 0; // Если нет чисел, возвращаем 0
        }
        std::vector<double> sorted_numbers = m_numbers;
        std::sort(sorted_numbers.begin(), sorted_numbers.end());
        size_t index = static_cast<size_t>(std::ceil(0.9 * sorted_numbers.size())) - 1;
        return sorted_numbers[index];
    }

    const char * name() const override {
        return "pct90";
    }
};

class PCT95 : public IStatistics {
private:
    std::vector<double> m_numbers;

public:

    void update(double next) override {
        m_numbers.push_back(next);
    }

    double eval() const override {
        if (m_numbers.empty()) {
            return 0; // Если нет чисел, возвращаем 0
        }
        std::vector<double> sorted_numbers = m_numbers;
        std::sort(sorted_numbers.begin(), sorted_numbers.end());
        size_t index = static_cast<size_t>(std::ceil(0.95 * sorted_numbers.size())) - 1;
        return sorted_numbers[index];
    }

    const char * name() const override {
        return "pct95";
    }
};

int main() {

	const size_t statistics_count = 6;
	IStatistics *statistics[statistics_count];

	statistics[0] = new Min{};
    statistics[1] = new Max{};
    statistics[2] = new Mean{};
    statistics[3] = new Std{};
    statistics[4] = new PCT90{};
    statistics[5] = new PCT95{};

	double val = 0;
	while (std::cin >> val) {
		for (size_t i = 0; i < statistics_count; ++i) {
			statistics[i]->update(val);
		}
	}

	// Handle invalid input data
	if (!std::cin.eof() && !std::cin.good()) {
		std::cerr << "Invalid input data\n";
		return 1;
	}

	// Print results if any
	for (size_t i = 0; i < statistics_count; ++i) {
		std::cout << statistics[i]->name() << " = " << statistics[i]->eval() << std::endl;
	}

	// Clear memory - delete all objects created by new
	for (size_t i = 0; i < statistics_count; ++i) {
		delete statistics[i];
	}

	return 0;
}