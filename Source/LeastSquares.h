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

	/* Guilherme */
	void updateMesh2(Mesh *mesh);
	void setup(const Mesh &mesh);
	void solveSystem();
	void updateSytem(const Mesh &mesh);



private:
	int _n;
	matcc _A;
	vecn _x, _b, _WH; 
	double _WL;


	/* Guilherme */
	vecn _y, _z;
	matn _L; //contraction restrictions matrix (nxn)
	matn _V; //vertices coordinates matrix (nx3)
	matn _B; //zero matrix (nx3)
	matn _WLMatrix; //contraction weights (nxn)
	matn _WHMatrix; //atraction weights (nxn)
	double _WLConst;
	double _WH0; //initial value for atraction weights
	double _WL0; //initial value for contraction weights
	double _SL; //rate between contraction weights between two iterations
	vecn _A0; //initial area of the 1 neightborhood ring for each vertex
	vecn _AT; //actual area of the 1 neightborhood ring for each vertex


};



#endif // __LEASTSQUARES_H