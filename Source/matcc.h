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
	FILE* toCholmodArray(string name);
	void fromCholmod(char* f);
	void fromCholmodArray(char* f);

	void removeRow(int r);

	// Gets/Sets
	const double at(int i, int j) const;
	void set(int i, int j, double value);	

private:
	int _rows, _cols, _nnz;
	map<pair<int, int>, double> _m;
};

matcc solveLS(matcc A, matcc b);

#endif // __MATCC_H