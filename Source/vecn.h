#ifndef __VEC_N
#define __VEC_N

#include <vector>
using namespace std;

class vecn
{
public:
	vecn();
	vecn(int size);

	FILE *toCholmod(string name);
	//void fromCholmod(FILE *f);
	void fromCholmod(char* f);

	// Gets/Sets
	const double at(int i) const { return v[i]; }
	void set(int i, double value) { v[i] = value; }

private:
	vector<double> v;
};


#endif // VEC_N