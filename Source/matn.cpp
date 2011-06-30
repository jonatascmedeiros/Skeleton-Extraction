#include <fstream>
#include <string>
#include <cholmod.h>
#include "matn.h"
	

matn::matn()
{
}

matn::matn(int rows, int columns)
{
	for(int i = 0; i < rows; ++i) {
		vector<double> v1;
		for(int j = 0; j < columns; ++j) {
			v1.push_back(0.0);
		}
		m.push_back(v1);
	}
}


// convert to matrix market format
FILE* matn::toCholmod()
{
	if(m.size() == 0)
		return NULL;

	FILE *f = fopen("cholmod_fileaux", "w+");
	
	int zeros = 0;
	for(int i = 0; i < m.size(); ++i) {
		for(int j = 0; j < m[i].size(); ++j) {
			if(m[i][j] != 0.0) ++zeros;
		}
	}

	fprintf(f, "%d %d %d\n", m.size(), m[0].size(), zeros);

	for(int i = 0; i < m.size(); ++i) {
		for(int j = 0; j < m[i].size(); ++j) {
			if(m[i][j] != 0.0)
				fprintf(f, "%d %d %f\n", i+1, j+1, m[i][j]); 
		}
	}

	return f;
}

void matn::fromCholmod(FILE* f)
{
	/*
	int zeros = 0;
	for(int i = 0; i < m.size(); ++i) {
		for(int j = 0; j < m[i].size(); ++j) {
			if(m[i][j] != 0.0) ++zeros;
		}
	}

	fprintf(f, "%d %d %d\n", m.size(), m[0].size(), zeros);

	for(int i = 0; i < m.size(); ++i) {
		for(int j = 0; j < m[i].size(); ++j) {
			if(m[i][j] != 0.0)
				fprintf(f, "%d %d %f\n", i+1, j+1, m[i][j]); 
		}
	}

	return f;
	*/
}

vecn solveLS(matn A, vecn b)
{
	cholmod_sparse *Ac;
	cholmod_dense *xc, *bc;
	cholmod_factor *Lc;

	// start CHOLMOD
	cholmod_common c;
	cholmod_start (&c);

	// convert matn to cholmod format
	FILE *filecc = A.toCholmod();
	Ac = cholmod_read_sparse(filecc, &c);
	fclose(filecc);

	// convert vecn to cholmod format
	filecc = b.toCholmod();
	bc = cholmod_read_dense(filecc, &c);
	fclose(filecc);

	// solve
	Lc = cholmod_analyze(Ac, &c);
	cholmod_factorize(Ac, Lc, &c);
	xc = cholmod_solve(CHOLMOD_A, Lc, bc, &c);

	// copy x
	cholmod_write_dense(filecc, xc, "", &c);
	vecn x;
	x.fromCholmod(filecc);
	fclose(filecc);

	// free matrices
	cholmod_free_sparse(&Ac, &c);
	cholmod_free_dense(&xc, &c);
	cholmod_free_dense(&bc, &c);

	// finish CHOLMOD
	cholmod_finish (&c);

	return x;
}
