#include "funcval.h"
#include <vector>
#include <algorithm>
#include <ostream>
#include <iterator>
#include <iomanip>

void printFunctionTable(std::ostream & out, double begin, double end, int steps, double func(double)) {
	std::vector<double> v(steps);
	double const delta { (end - begin) / (steps - 1)};
	for(int i = 0; i < steps; i++) {
		v[i] = begin + i * delta;
	}

	generate(v.begin(), v.end(),[begin, delta, i=0]() mutable{return begin + (i++)*delta; });
	out << "x\t";
	std::ostream_iterator<double> oi{out,"\t"};
	copy(v.begin(), v.end(), oi);
	out << "\nf(x)\t";
	transform(v.begin(), v.end(), oi, func);
	out << "\n";
}
