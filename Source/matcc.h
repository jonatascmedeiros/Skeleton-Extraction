#ifndef __MATCC_H
#define __MATCC_H

#include <fstream>
#include <vector>
#include <map>
#include "vecn.h"
using namespace std;

class matcc
{
public:
	matcc();
	matcc(int rows, int columns);

	FILE* toCholmod(string name);
	void fromCholmod(FILE *f);

	void removeRow(int r);

	// Gets/Sets
	const double at(int i, int j) const;
	void set(int i, int j, double value);	

private:
	int _rows, _cols, _nnz;
	map<pair<int, int>, double> _m;
};

vecn solveLS(matcc A, vecn b);

#endif // __MATCC_H