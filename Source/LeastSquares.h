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

private:
	int _n;
	matcc _A;
	vecn _x, _WH, _b; 
	double _WL, _WHOriginal;	
};



#endif // __LEASTSQUARES_H