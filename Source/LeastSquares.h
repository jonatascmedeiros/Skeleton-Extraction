#ifndef __LEASTSQUARES_H
#define __LEASTSQUARES_H

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

private:
	int _n;
	matn _A;
	vecn _x, _b, _WH; 
	double _WL;
};



#endif // __LEASTSQUARES_H