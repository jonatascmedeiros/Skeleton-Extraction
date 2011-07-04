#include <cholmod.h>
#include "matcc.h"

matcc::matcc()
: _rows(0), _cols(0), _nnz(0)
{
}

matcc::matcc(int rows, int columns)
: _rows(rows), _cols(columns), _nnz(0)
{
}

FILE* matcc::toCholmod(string name)
{
	FILE *f = fopen(name.c_str(), "w");

	fprintf(f, "%d %d %d\n", _rows, _cols, _nnz);

	map<pair<int, int>, double>::iterator i;
	for(i = _m.begin(); i != _m.end(); ++i) {
		fprintf(f, "%d %d %f\n", (*i).first.first, (*i).first.second, (*i).second); 
	}

	return f;
}

FILE* matcc::toCholmodArray(string name)
{
	FILE *f = fopen(name.c_str(), "w");
	
	fprintf(f, "%d %d\n", _rows, _cols);

	for(int j = 0; j < 3; j++)
		for(int i = 0; i < _rows; i++)
		{
			fprintf(f, "%f\n", at(i, j)); 
		}
			
	return f;	
}

void matcc::fromCholmod(char* f)
{
	char header[200];
	fstream file;
	file.open(f);
	file.getline(header, 200);
	file >> _rows >> _cols >> _nnz;
	
	_m.clear();
	int i, j;
	double val;
	for(int i = 0; i < _rows; ++i)
	{
		file >> i >> j >> val;
		set(i, j, val);
	}
	file.close();
}

void matcc::fromCholmodArray(char* f)
{
	char header[200];
	fstream file;
	file.open(f);
	file.getline(header, 200);
	file >> _rows >> _cols;
	
	_m.clear();
	int i, j;
	double val;
	for(int j = 0; j < _cols; ++j)
		for(int i = 0; i < _rows; ++i)
		{
			file >> val;
			set(i, j, val);
		}
	file.close();
}

const double matcc::at(int i, int j) const
{
	pair<int, int> p = pair<int, int>(i, j);
	if(_m.find(p) == _m.end())
		return 0.0;
	else
		return _m.find(p)->second;
}

void matcc::set(int i, int j, double value)
{
	if(value == 0.0)
		return;

	pair<int, int> p = pair<int, int>(i, j);
	if(_m.find(p) == _m.end())
		++_nnz;

	_m[p] = value;
}

void matcc::removeRow(int r)
{
	map<pair<int, int>, double> newM;

	map<pair<int, int>, double>::iterator i;
	for(i = _m.begin(); i != _m.end(); ++i) {

		if((*i).first.first < r)
			newM[(*i).first] = (*i).second;

		if((*i).first.first == r)
			--_nnz;

		if((*i).first.first > r)
			newM[pair<int,int>((*i).first.first-1, (*i).first.second)] = (*i).second;
	}

	--_rows;
	_m = newM;
}

matcc solveLS(matcc A, matcc b)
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
	At = cholmod_transpose(Ac, 1, &c);
	fclose(filecc);
	filecc = fopen("cholmod_fileaux1.txt", "w");
	AtA = cholmod_ssmult(At, Ac, 0, 1, 0, &c);
	cholmod_write_sparse(filecc, AtA, NULL, "", &c);
	fclose(filecc);	

	// convert vecn to cholmod format 
	FILE *filecc2 = b.toCholmodArray("cholmod_fileaux2.txt");
	fclose(filecc2);
	filecc2 = fopen("cholmod_fileaux2.txt", "r");
	Atb = cholmod_read_dense(filecc2, &c);
	fclose(filecc2);

	// stupid cholmod
	//Atb = cholmod_ones(Ac->ncol, 1, Ac->xtype, &c);
	
	//double alpha[2] = {1, 0};
	//double beta[2] = {0, 0};

	//filecc = fopen("cholmod_fileaux1.txt", "w");
	//cholmod_write_dense(filecc, Atb, "", &c);
	//fclose(filecc);

	//cholmod_sdmult(At, 0, alpha, beta, bc, Atb, &c);
	
	filecc2 = fopen("cholmod_fileaux2.txt", "w");
	cholmod_write_dense(filecc2, Atb, "", &c);
	fclose(filecc2);

	// solve
	AtA->stype = 1;
	Lc = cholmod_analyze(AtA, &c);
	cholmod_factorize(AtA, Lc, &c);
	xc = cholmod_solve(CHOLMOD_A, Lc, Atb, &c);

	// copy x
	FILE *filecc3 = fopen("cholmod_getX.txt", "w");
	cholmod_write_dense(filecc3, xc, "", &c);
	fclose(filecc3);
	//std::fstream filecc4;
	//filecc4.open("cholmod_getX2.txt");
	//filecc3 = fopen("cholmod_getX2.txt", "r");
	matcc x;
	x.fromCholmodArray("cholmod_getX.txt");
	//filecc4.close();
	//fclose(filecc3);

	// free matrices
	cholmod_free_sparse(&Ac, &c);
	cholmod_free_sparse(&At, &c);
	cholmod_free_sparse(&AtA, &c);
	cholmod_free_dense(&xc, &c);
	//cholmod_free_dense(&bc, &c);
	cholmod_free_dense(&Atb, &c);

	// finish CHOLMOD
	cholmod_finish (&c);

	return x;
}