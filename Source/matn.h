#ifndef __MAT_N
#define __MAT_N

#include <fstream>
#include <vector>
#include "vecn.h"
using namespace std;

class matn
{
public:
	matn();
	matn(int rows, int columns);

	FILE* toCholmod();
	void fromCholmod(FILE *f);

	// Gets/Sets
	const double at(int i, int j) const { return m[i][j]; }
	void set(int i, int j, double value) { m[i][j] = value; }

private:
	vector< vector<double> > m;
};

vecn solveLS(matn A, vecn b);

#endif // VEC_N 