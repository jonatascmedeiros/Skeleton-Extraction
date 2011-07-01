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
FILE* matn::toCholmod(string name)
{
	if(m.size() == 0)
		return NULL;

	FILE *f = fopen(name.c_str(), "w");
	
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
	cholmod_sparse *Ac, *At, *AtA;
	cholmod_dense *xc, *bc, *Atb;
	cholmod_factor *Lc;

	// start CHOLMOD
	cholmod_common c;
	cholmod_start (&c);

	// convert matn to cholmod format
	FILE *filecc = A.toCholmod("cholmod_fileaux1.txt");
	fclose(filecc);
	filecc = fopen("cholmod_fileaux1.txt", "r");
	Ac = cholmod_read_sparse(filecc, &c);
	At = cholmod_transpose(Ac, 0, &c);
	AtA = cholmod_ssmult(At, Ac, 0, 1, 0, &c);
	fclose(filecc);
	

	// convert vecn to cholmod format 
	FILE *filecc2 = b.toCholmod("cholmod_fileaux2.txt");
	fclose(filecc2);
	filecc2 = fopen("cholmod_fileaux2.txt", "r");
	bc = cholmod_read_dense(filecc2, &c);
	
	// stupid cholmod
	double alpha[2] = {1, 1};
	Atb = bc;

	cholmod_sdmult(At, 0, alpha, 0, bc, Atb, &c);
	fclose(filecc2);

	filecc = fopen("cholmod_fileaux1.txt", "w");
	cholmod_write_sparse(filecc, AtA, NULL, "", &c);

	filecc2 = fopen("cholmod_fileaux2.txt", "w");
	cholmod_write_dense(filecc2, Atb, "", &c);

	// solve
	Lc = cholmod_analyze(AtA, &c);
	cholmod_factorize(AtA, Lc, &c);
	xc = cholmod_solve(CHOLMOD_A, Lc, Atb, &c);

	// copy x
	FILE *filecc3 = fopen("cholmod_getX.txt", "w");
	cholmod_write_dense(filecc3, xc, "", &c);
	fclose(filecc3);
	filecc3 = fopen("cholmod_getX.txt", "r");
	vecn x;
	x.fromCholmod(filecc3);
	fclose(filecc3);

	// free matrices
	cholmod_free_sparse(&Ac, &c);
	cholmod_free_sparse(&At, &c);
	cholmod_free_sparse(&AtA, &c);
	cholmod_free_dense(&xc, &c);
	cholmod_free_dense(&bc, &c);
	cholmod_free_dense(&Atb, &c);

	// finish CHOLMOD
	cholmod_finish (&c);

	return x;
}
