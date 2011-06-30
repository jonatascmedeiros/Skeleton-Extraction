#include "matn.h"
#include "vecn.h"
#include "LeastSquares.h"

using namespace std;

void LeastSquares::createMatrix(const Mesh &mesh)
{
	_n = mesh.n_vertices();  
	_A = matn(_n*6, _n*3);
	_x = vecn(_n*3);
	_b = vecn(_n*6);
	
	//float wl = 100 * sqrt(mesh.avgArea());
	//taucsType *wh = new taucsType[n];
    
    for(int i = 0; i < _n; ++i)
    {
		_b.set(i, 0);
		_b.set(i+_n, 0);
		_b.set(i+2*_n, 0);
        _b.set(i+3*_n, mesh.point3(i).x);
        _b.set(i+4*_n, mesh.point3(i).y);
        _b.set(i+5*_n, mesh.point3(i).z);
    }

	// laplacian constraints
	for (int i = 0; i < _n; ++i) 
	{
		// init L's center weight
		for (int k = 0, offs = 0; k < 2; ++k, offs += _n)
			_A.set(offs+i, offs+i, 1.0);

		// neighbors weight
		QVector<Mesh::VHandle> neighbors = mesh.adjacentVertices(Mesh::VHandle(i));
		for(int j = 0; j < neighbors.size(); ++j) 
		{
			double w = -1.0f / (double)(neighbors.size());

			for (int k = 0, offs = 0; k < 2; ++k, offs += _n)
				_A.set(offs+i, offs+neighbors[j].idx(), w);
		}
	}

	// anchor constraints
	for(int i = 0; i < _n; ++i)
	{
		_A.set(3*_n+i, i, mesh.point3(i).x);
		_A.set(4*_n+i, i, mesh.point3(i).y);
		_A.set(5*_n+i, i, mesh.point3(i).z);	
	}

}

bool LeastSquares::solve()
{
	// solve Ax=b
	_x = solveLS(_A, _b);
	return true;
}

void LeastSquares::updateMesh(Mesh* mesh)
{
	for(int i = 0; i < _n; ++i)
		mesh->set_point3(i, vec3(_x.at(i), _x.at(i+_n), _x.at(i+2*_n)));
	mesh->update();
}

void LeastSquares::updateWeights(Mesh* meshc)
{
}