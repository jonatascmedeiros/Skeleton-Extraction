#ifndef __LEASTSQUARES_H
#define __LEASTSQUARES_H

#include "matcc.h"
#include "matn.h"
#include "vecn.h"
#include "Mesh.h"

class LeastSquares
{
public:
	void createMatrix(const Mesh &mesh);
	bool solve();
	
	void updateMesh(Mesh *mesh);
	void updateWeights(Mesh *mesh);
	void updateMatrices(const Mesh &mesh);
	
	int iteration;	

	void createMatrix2(const Mesh &mesh);
	void updateMesh2(Mesh *mesh);
	void updateMatrices2(const Mesh &mesh);

private:
	int _n;
	matcc _A, _x, _b;
	vecn _WH; 
	double _WL, _WHOriginal;	
};



#endif // __LEASTSQUARES_H