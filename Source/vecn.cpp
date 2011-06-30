#include "vecn.h"

vecn::vecn()
{
}

vecn::vecn(int size)
{
	for(int i = 0; i < size; ++i)
		v.push_back(0.0);
}

FILE* vecn::toCholmod()
{
	if(v.size() == 0)
		return NULL;

	FILE *f = fopen("cholmod_fileaux", "w+");
	
	fprintf(f, "%d %d\n", v.size(), 1);

	for(int i = 0; i < v.size(); ++i) {
		fprintf(f, "%f\n", v[i]); 
	}

	return f;
}

void vecn::fromCholmod(FILE* f)
{
	int rows, cols;
	fscanf(f, "%d %d", &rows, &cols);

	v.clear();
	double val;
	for(int i = 0; i < rows; ++i) {
		fscanf(f, "%f", &val);
		v.push_back(val);
	}
}