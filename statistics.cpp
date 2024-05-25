#include <iostream>
#include "IStatistics.h"
#include "Min.h"
#include "Max.h"
#include "Mean.h"
#include "Std.h"
#include "PCT.h"

int main() {

	const size_t statistics_count = 6;
	IStatistics *statistics[statistics_count] = {
            new Min(),
            new Max(),
            new Mean(),
            new Std(),
            new PCT(0.9),
            new PCT(0.95)
    };

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