#include "matcc.h"
#include "matn.h"
#include "vecn.h"
#include "LeastSquares.h"

using namespace std;

//void LeastSquares::createMatrix(const Mesh &mesh)
//{
//	_n = mesh.n_vertices();  
//	_A = matcc(_n*6, _n*3);
//	_x = vecn(_n*3);
//	_b = vecn(_n*6);
//	_WH = vecn(_n);
//	double a = mesh.avgArea();
//	_WL = 100 * sqrt(a);
//	//_WL = 0.0;
//	_WHOriginal = 1.0;
//
//    
//    for(int i = 0; i < _n; ++i)
//    {
//		_b.set(i, 0);
//		_b.set(i+_n, 0);
//		_b.set(i+2*_n, 0);
//        _b.set(i+3*_n, mesh.point3(i).x * _WHOriginal);
//        _b.set(i+4*_n, mesh.point3(i).y * _WHOriginal);
//        _b.set(i+5*_n, mesh.point3(i).z * _WHOriginal);
//		_WH.set(i, _WHOriginal);
//    }
//
//	// laplacian constraints
//	for (int i = 0; i < _n; ++i) 
//	{
//		double omegaSummation = 0.0;
//		// neighbors weight
//		QVector<Mesh::VHandle> neighbors = mesh.adjacentVertices(Mesh::VHandle(i));
//		QVector<Mesh::VHandle> commonNeighbors;
//		for(int j = 0; j < neighbors.size(); ++j) 
//		{
//			// Find common neighbors
//			commonNeighbors.clear();
//			QVector<Mesh::VHandle> neighborsOfNeighbor = mesh.adjacentVertices(neighbors[j]);
//			for(int k = 0; k < neighbors.size(); ++k) 
//				for(int m = 0; m < neighborsOfNeighbor.size(); ++m)
//					if(neighbors[k].idx() == neighborsOfNeighbor[m].idx())
//						commonNeighbors.append(neighbors[k]);
//			
//			// Calculate omega	
//			vec3 v1, v2;
//			v1 = mesh.point3(Mesh::VHandle(i)) - mesh.point3(commonNeighbors[0]);
//			v2 = mesh.point3(neighbors[j]) - mesh.point3(commonNeighbors[0]);
//			v1.normalize();	v2.normalize();
//			float dotProduct = v1 * v2;
//			float angle = acos(dotProduct);
//			float cotA, cotB;
//			if(tan(angle) != 0.0)
//				cotA = 1.0 / tan(angle);
//
//			v1 = mesh.point3(Mesh::VHandle(i)) - mesh.point3(commonNeighbors[1]);
//			v2 = mesh.point3(neighbors[j]) - mesh.point3(commonNeighbors[1]);
//			v1.normalize();	v2.normalize();
//			dotProduct = v1 * v2;
//			angle = acos(dotProduct);
//			if(tan(angle) != 0.0)
//				cotB = 1.0 / tan(angle);
//
//			
//			double omega = cotA + cotB;	
//			omegaSummation -= omega;
//			omega *= _WL;		
//
//			for (int k = 0, offs = 0; k < 3; ++k, offs += _n)
//				_A.set(offs+i, offs+neighbors[j].idx(), omega);
//		}
//		for (int k = 0, offs = 0; k < 3; ++k, offs += _n)
//			_A.set(offs+i, offs+i, omegaSummation * _WL);
//	}
//
//	// anchor constraints
//	for(int i = 0; i < _n; ++i)
//	{
//		_A.set(3*_n+i, i, _WH.at(i));
//		_A.set(4*_n+i, i+_n,  _WH.at(i));
//		_A.set(5*_n+i, i+2*_n,  _WH.at(i));	
//	}
//}

void LeastSquares::createMatrix2(const Mesh &mesh)
{
	_n = mesh.n_vertices();  
	_A = matcc(_n*2, _n);
	_x = matcc(_n, 3);
	_b = matcc(_n, 3);
	_WH = vecn(_n);
	double a = mesh.avgArea();
	//_WL = 100 * sqrt(a);
	//_WL = 1.0; // torus
	_WL = 1.0; //bitorus
	//_WL = 0.1;
	_WHOriginal = 1.0;

    
    for(int i = 0; i < _n; ++i)
    {
		_b.set(i, 0, mesh.point3(i).x * _WHOriginal * _WHOriginal);
        _b.set(i, 1, mesh.point3(i).y * _WHOriginal * _WHOriginal);
        _b.set(i, 2, mesh.point3(i).z * _WHOriginal * _WHOriginal);
		_WH.set(i, _WHOriginal);
    }

	// laplacian constraints
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
			float dotProduct = v1 * v2;
			float angle = acos(dotProduct);
			float cotA, cotB;
			if(tan(angle) != 0.0)
				cotA = 1.0 / tan(angle);

			v1 = mesh.point3(Mesh::VHandle(i)) - mesh.point3(commonNeighbors[1]);
			v2 = mesh.point3(neighbors[j]) - mesh.point3(commonNeighbors[1]);
			v1.normalize();	v2.normalize();
			dotProduct = v1 * v2;
			angle = acos(dotProduct);
			if(tan(angle) != 0.0)
				cotB = 1.0 / tan(angle);
			
			double omega = cotA + cotB;	
			omegaSummation -= omega;
			omega *= _WL;		

			_A.set(i, neighbors[j].idx(), omega);
		}
		_A.set(i, i, omegaSummation * _WL);
	}

	// anchor constraints
	for(int i = 0; i < _n; ++i)
	{
		_A.set(_n+i, i, _WH.at(i));		
	}	
}

bool LeastSquares::solve()
{
	// solve Ax=b
	_x = solveLS(_A, _b);
	return true;
}

//void LeastSquares::updateMesh(Mesh* mesh)
//{
//	for(int i = 0; i < _n; ++i)
//		mesh->set_point3(i, vec3(_x.at(i), _x.at(i+_n), _x.at(i+2*_n)));
//	mesh->update();	
//}

void LeastSquares::updateMesh2(Mesh* mesh)
{
	for(int i = 0; i < _n; ++i)
		mesh->set_point3(i, vec3(_x.at(i, 0), _x.at(i, 1), _x.at(i, 2)));
	mesh->update();	
}

void LeastSquares::updateWeights(Mesh* meshc)
{
	for(int i = 0; i < _n; ++i)
	{
		double currArea =  meshc->getOneRingArea(Mesh::VHandle(i));
		double areaRatio;
		if(abs(currArea) > 0.000001)
			areaRatio = meshc->originalOneRingArea[i] / currArea;
		else
			areaRatio = 1000000;
			
		_WH.set(i, _WHOriginal * sqrt(areaRatio));
	}

	_WL *= 2.0;	
}

//void LeastSquares::updateMatrices(const Mesh &mesh)
//{
//	int index = 0;
//
//	for (int i = 0; i < _n; ++i) 
//	{
//		bool eliminated = false;
//		double omegaSummation = 0.0;
//		// neighbors weight
//		QVector<Mesh::VHandle> neighbors = mesh.adjacentVertices(Mesh::VHandle(i));
//		QVector<Mesh::VHandle> commonNeighbors;
//		for(int j = 0; j < neighbors.size(); ++j) 
//		{
//			// Find common neighbors
//			commonNeighbors.clear();
//			QVector<Mesh::VHandle> neighborsOfNeighbor = mesh.adjacentVertices(neighbors[j]);
//			for(int k = 0; k < neighbors.size(); ++k) 
//				for(int m = 0; m < neighborsOfNeighbor.size(); ++m)
//					if(neighbors[k].idx() == neighborsOfNeighbor[m].idx())
//						commonNeighbors.append(neighbors[k]);
//			
//			// Calculate omega	
//			vec3 v1, v2;
//			v1 = mesh.point3(Mesh::VHandle(i)) - mesh.point3(commonNeighbors[0]);
//			v2 = mesh.point3(neighbors[j]) - mesh.point3(commonNeighbors[0]);
//			v1.normalize();	v2.normalize();
//			float dotProduct = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
//			float angle = acos(dotProduct);
//			float cotA, cotB;
//			if(abs(tan(angle)) > 0.0001)
//				cotA = 1.0 / tan(angle);
//			else
//			{
//				_A.removeRow(index);
//				eliminated = true;
//				index--;
//				break;
//			}
//
//			v1 = mesh.point3(Mesh::VHandle(i)) - mesh.point3(commonNeighbors[1]);
//			v2 = mesh.point3(neighbors[j]) - mesh.point3(commonNeighbors[1]);
//			v1.normalize();	v2.normalize();
//			dotProduct = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
//			angle = acos(dotProduct);
//			if(abs(tan(angle)) > 0.0001)
//				cotB = 1.0 / tan(angle);
//			else
//			{
//				_A.removeRow(index);
//				eliminated = true;
//				index--;
//				break;
//			}
//			
//			double omega = cotA + cotB;	
//			omegaSummation -= omega;
//			omega *= _WL;		
//
//			for (int k = 0, offs = 0; k < 3; ++k, offs += _n)
//				_A.set(offs+index, offs+neighbors[j].idx(), omega);
//		}
//		if(!eliminated)
//			for (int k = 0, offs = 0; k < 3; ++k, offs += _n)
//				_A.set(offs+index, offs+index, omegaSummation * _WL);
//
//		index++;
//	}
//
//	// anchor constraints
//	for(int i = 0; i < _n; ++i)
//	{
//		_A.set(3*_n+i, i, _WH.at(i));
//		_A.set(4*_n+i, i+_n,  _WH.at(i));
//		_A.set(5*_n+i, i+2*_n,  _WH.at(i));	
//	}	
//
//	for(int i = 0; i < index; ++i)
//    {
//		_b.set(i, 0);
//		_b.set(i+index, 0);
//		_b.set(i+2*index, 0);       	
//    }
//
//	for(int i = 0; i < _n; ++i)
//    {
//		_b.set(i+3*_n, _WH.at(i) * mesh.point3(i).x);
//        _b.set(i+4*_n, _WH.at(i) * mesh.point3(i).y);
//        _b.set(i+5*_n, _WH.at(i) * mesh.point3(i).z);	
//	}
//}

void LeastSquares::updateMatrices2(const Mesh &mesh)
{
	int index = 0;

	for (int i = 0; i < _n; ++i) 
	{
		bool eliminated = false;
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
			if(abs(tan(angle)) > 0.000001)
				cotA = 1.0 / tan(angle);
			else
			{
				_A.removeRow(index);
				eliminated = true;
				index--;
				break;
			}

			v1 = mesh.point3(Mesh::VHandle(i)) - mesh.point3(commonNeighbors[1]);
			v2 = mesh.point3(neighbors[j]) - mesh.point3(commonNeighbors[1]);
			v1.normalize();	v2.normalize();
			dotProduct = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
			angle = acos(dotProduct);
			if(abs(tan(angle)) > 0.000001)
				cotB = 1.0 / tan(angle);
			else
			{
				_A.removeRow(index);
				eliminated = true;
				index--;
				break;
			}
			
			double omega = cotA + cotB;	
			omegaSummation -= omega;
			omega *= _WL;		

			_A.set(index, neighbors[j].idx(), omega);
		}
		if(!eliminated)
			_A.set(index, index, omegaSummation * _WL);

		index++;

		_b.set(i, 0, _WH.at(i) * _WH.at(i) * mesh.point3(i).x);
        _b.set(i, 1, _WH.at(i) * _WH.at(i) * mesh.point3(i).y);
        _b.set(i, 2, _WH.at(i) * _WH.at(i) * mesh.point3(i).z);	
	}

	for(int i = 0; i < _n; i++)
	{
		_A.set(index+i, i, _WH.at(i));
	}
}