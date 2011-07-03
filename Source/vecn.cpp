#include "vecn.h"
#include <fstream>

vecn::vecn()
{
}

vecn::vecn(int size)
{
	for(int i = 0; i < size; ++i)
		v.push_back(0.0);
}

FILE* vecn::toCholmod(string name)
{
	if(v.size() == 0)
		return NULL;

	FILE *f = fopen(name.c_str(), "w");
	
	fprintf(f, "%d %d\n", v.size(), 1);

	for(int i = 0; i < v.size(); ++i) {
		fprintf(f, "%f\n", v[i]); 
	}

	return f;
}

void vecn::fromCholmod(char* f)
{
	int rows, cols;
	char header[200];
	//fgets(header, 200, f);
	fstream file;
	file.open(f);
	file.getline(header, 200);
	file >> rows >> cols;
	
	//fscanf(f, "%d %d", &rows, &cols);
	v.clear();
	double val;
	for(int i = 0; i < rows; ++i) {
		//fscanf(f, "%f", &val);
		file >> val;
		v.push_back(val);
	}
	file.close();
}