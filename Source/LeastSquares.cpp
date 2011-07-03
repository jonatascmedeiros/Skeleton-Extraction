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
	_WH = vecn(_n);
	_WL = 1.0;
	
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
		_WH.set(i, 1.0);
    }

	// laplacian constraints
	
	//for (int i = 0; i < _n; ++i) 
	//{
	//	// init L's center weight
	//	for (int k = 0, offs = 0; k < 2; ++k, offs += _n)
	//		_A.set(offs+i, offs+i, 1.0);

	//	// neighbors weight
	//	QVector<Mesh::VHandle> neighbors = mesh.adjacentVertices(Mesh::VHandle(i));
	//	for(int j = 0; j < neighbors.size(); ++j) 
	//	{
	//		double w = -1.0f / (double)(neighbors.size());

	//		for (int k = 0, offs = 0; k < 2; ++k, offs += _n)
	//			_A.set(offs+i, offs+neighbors[j].idx(), w);
	//	}
	//}
	
	for (int i = 0; i < _n; ++i) 
	{
		double omegaSummation = 0.0;
		// neighbors weight
		QVector<Mesh::VHandle> neighbors = mesh.adjacentVertices(Mesh::VHandle(i));
		QVector<Mesh::VHandle> commonNeighbors;
		for(int j = 0; j < neighbors.size(); ++j) 
		{
			// Find common neighbors
			commonNeighbors.clear();
			QVector<Mesh::VHandle> neighborsOfNeighbor = mesh.adjacentVertices(neighbors[j]);
			for(int k = 0; k < neighbors.size(); ++k) 
				for(int m = 0; m < neighborsOfNeighbor.size(); ++m)
					if(neighbors[k].idx() == neighborsOfNeighbor[m].idx())
						commonNeighbors.append(neighbors[k]);
			
			// Calculate omega	
			vec3 v1, v2;
			v1 = mesh.point3(Mesh::VHandle(i)) - mesh.point3(commonNeighbors[0]);
			v2 = mesh.point3(neighbors[j]) - mesh.point3(commonNeighbors[0]);
			v1.normalize();	v2.normalize();
			float dotProduct = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
			float angle = acos(dotProduct);
			float cotA, cotB;
			if(tan(angle) > 0.0)
				cotA = 1.0 / tan(angle);

			v1 = mesh.point3(Mesh::VHandle(i)) - mesh.point3(commonNeighbors[1]);
			v2 = mesh.point3(neighbors[j]) - mesh.point3(commonNeighbors[1]);
			v1.normalize();	v2.normalize();
			dotProduct = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
			angle = acos(dotProduct);
			if(tan(angle) > 0.0)
				cotB = 1.0 / tan(angle);
			
			double omega = cotA + cotB;	
			omegaSummation -= omega;
			omega *= _WL;		

			for (int k = 0, offs = 0; k < 3; ++k, offs += _n)
				_A.set(offs+i, offs+neighbors[j].idx(), omega);
		}
		for (int k = 0, offs = 0; k < 3; ++k, offs += _n)
			_A.set(offs+i, offs+i, omegaSummation * _WL);
	}

	// anchor constraints
	for(int i = 0; i < _n; ++i)
	{
		_A.set(3*_n+i, i, _WH.at(i));
		_A.set(4*_n+i, i+_n,  _WH.at(i));
		_A.set(5*_n+i, i+2*_n,  _WH.at(i));	
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
	for(int i = 0; i < _n; ++i)
	{
		double areaRatio = meshc->originalOneRingArea[i] / meshc->getOneRingArea(Mesh::VHandle(i));
		_WH.set(i, sqrt(areaRatio));
	}

	_WL *= 2.0;	
}

void LeastSquares::updateMatrices(const Mesh &mesh)
{
	for(int i = 0; i < _n; ++i)
    {
		_b.set(i, 0);
		_b.set(i+_n, 0);
		_b.set(i+2*_n, 0);
        _b.set(i+3*_n, _WH.at(i) * mesh.point3(i).x);
        _b.set(i+4*_n, _WH.at(i) * mesh.point3(i).y);
        _b.set(i+5*_n, _WH.at(i) * mesh.point3(i).z);		
    }

	for (int i = 0; i < _n; ++i) 
	{
		double omegaSummation = 0.0;
		// neighbors weight
		QVector<Mesh::VHandle> neighbors = mesh.adjacentVertices(Mesh::VHandle(i));
		QVector<Mesh::VHandle> commonNeighbors;
		for(int j = 0; j < neighbors.size(); ++j) 
		{
			// Find common neighbors
			commonNeighbors.clear();
			QVector<Mesh::VHandle> neighborsOfNeighbor = mesh.adjacentVertices(neighbors[j]);
			for(int k = 0; k < neighbors.size(); ++k) 
				for(int m = 0; m < neighborsOfNeighbor.size(); ++m)
					if(neighbors[k].idx() == neighborsOfNeighbor[m].idx())
						commonNeighbors.append(neighbors[k]);
			
			// Calculate omega	
			vec3 v1, v2;
			v1 = mesh.point3(Mesh::VHandle(i)) - mesh.point3(commonNeighbors[0]);
			v2 = mesh.point3(neighbors[j]) - mesh.point3(commonNeighbors[0]);
			v1.normalize();	v2.normalize();
			float dotProduct = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
			float angle = acos(dotProduct);
			float cotA, cotB;
			if(tan(angle) > 0.0)
				cotA = 1.0 / tan(angle);
			else
				cotA = 10000;

			v1 = mesh.point3(Mesh::VHandle(i)) - mesh.point3(commonNeighbors[1]);
			v2 = mesh.point3(neighbors[j]) - mesh.point3(commonNeighbors[1]);
			v1.normalize();	v2.normalize();
			dotProduct = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
			angle = acos(dotProduct);
			if(tan(angle) > 0.0)
				cotB = 1.0 / tan(angle);
			else
				cotB = 10000;
			
			double omega = cotA + cotB;	
			omegaSummation -= omega;
			omega *= _WL;		

			for (int k = 0, offs = 0; k < 3; ++k, offs += _n)
				_A.set(offs+i, offs+neighbors[j].idx(), omega);
		}
		for (int k = 0, offs = 0; k < 3; ++k, offs += _n)
			_A.set(offs+i, offs+i, omegaSummation * _WL);
	}

	// anchor constraints
	for(int i = 0; i < _n; ++i)
	{
		_A.set(3*_n+i, i, _WH.at(i));
		_A.set(4*_n+i, i+_n,  _WH.at(i));
		_A.set(5*_n+i, i+2*_n,  _WH.at(i));	
	}	
}