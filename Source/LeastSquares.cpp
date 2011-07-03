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
	double a = mesh.avgArea();
	_WL = 0.5;// 0.001 * sqrt(a);
    
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
			if(tan(angle) != 0.0)
				cotA = 1.0 / tan(angle);
			else
				cotA = 10000;


			v1 = mesh.point3(Mesh::VHandle(i)) - mesh.point3(commonNeighbors[1]);
			v2 = mesh.point3(neighbors[j]) - mesh.point3(commonNeighbors[1]);
			v1.normalize();	v2.normalize();
			dotProduct = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
			angle = acos(dotProduct);
			if(tan(angle) != 0.0)
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


/* Guilherme */
void LeastSquares::updateMesh2(Mesh* mesh)
{
	for(int i = 0; i < _n; ++i)
		mesh->set_point3(i, vec3(_x.at(i), _y.at(i), _z.at(i)));
	mesh->update();
}

void LeastSquares::setup(const Mesh &mesh)
{
	
	_n = mesh.n_vertices();  
	_L = matn(_n, _n);
	_V = matn(_n, 3);
	_B = matn(_n, 3);

	for (int i = 0; i < _n; i++) {
		_V.set(i, 0, mesh.point3(Mesh::VHandle(i)).x);
		_V.set(i, 1, mesh.point3(Mesh::VHandle(i)).y);
		_V.set(i, 2, mesh.point3(Mesh::VHandle(i)).z);
	}

	_SL = 2.0;
	_WH0 = 1.0;
	_WLConst = 0.0001;

	for(int i = 0; i < _n; ++i) //fill B matrix with 0
    {
		_B.set(i, 0, 0);
		_B.set(i, 1, 0);
		_B.set(i, 2, 0);
    }

	for(int i = 0; i < _n; ++i) //fill L matrix with 0
	{
		for(int j = 0; j < _n; ++j)
		{
			_L.set(i,j,0.0);
		}
	}

	/* define the values for the L matrix and the A0 and AT vectors */

	_A0 = vecn(_n); // remove in the update stage
	_AT = vecn(_n); // remove in the update stage
	QVector<Mesh::FHandle> faces;
	QVector<Mesh::VHandle> vertices;
	double area = 0.0;
	for(int i = 0; i < _n; ++i)
	{		
		
		/* Fill A0 and AT vectors. 
		A0 has for, each vertex, the area of the ring defined by the adjacent faces for the original mesh.
		AT has for, each vertex, the area of the ring defined by the adjacent faces for the new, contracted, version of the mesh.
		*/

		faces = mesh.adjacentFaces(mesh.vertex_handle(i));
		area = 0.0;
		for (QVector<OpenMesh::PolyConnectivity::FaceHandle>::Iterator f_it = faces.begin(); f_it != faces.end(); ++f_it) {			
			area += mesh.area(*f_it);
		}
		_A0.set(i, area); // remove in the update stage
		_AT.set(i, area);

		
		/* Define values for the L matrix
		Not done yet */

		//vertices = mesh.adjacentVertices(mesh.vertex_handle(i));
		//_L.set(i,i, 0.0);
		//for (QVector<OpenMesh::PolyConnectivity::VertexHandle>::Iterator v_it = vertices.begin(); v_it != vertices.end(); ++v_it) {	
			
			//_L.set(i,v_it->idx(), );
			//_L.set(i,i, _L.at(i,i) - _L.at(i,v_it->idx()));
		//}

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
			//omega *= _WLMatrix;		

			//for (int k = 0, offs = 0; k < 3; ++k, offs += _n)
			_L.set(i, neighbors[j].idx(), omega);
		}
		_L.set(i, i, omegaSummation);
	}

	/* define values for the weighting matrixes */

	_WLMatrix = matn(_n, _n); // remove in the update stage
	_WHMatrix = matn(_n, _n); // remove in the update stage
	for(int i = 0; i < _n; ++i)
	{	
		_WLMatrix.set(i,i,_SL*_WLConst*sqrt(_AT.at(i)));
		_WHMatrix.set(i,i,1.0); // remove in the update stage
		_WHMatrix.set(i,i,_WHMatrix.at(i,i)*sqrt(_A0.at(i)/_AT.at(i)));
	}
	
}

void LeastSquares::solveSystem()
{
	_A = matn(2*_n, _n);

	/* we solve three systems, one for each vertex coordinate */
	
	/* upper half of matrix A = WL * L */
	for (int i = 0; i < _n; i++) {
		for (int j = 0; j < _n; j++) {
			_A.set(i,j,_WLMatrix.at(i,i)*_L.at(i,j));
		}
	}

	/* lower half of matrix A = WH */
	for (int i = 0; i < _n; i++) {
		for (int j = 0; j < _n; j++) {
			_A.set(_n+i,j,_WHMatrix.at(i,j));
		}
	}

	_b = vecn(2*_n);

	/* upper half of _b = 0 */
	for (int i = 0; i < _n; i++) {
		_b.set(i,0);
	}
	/* lower half of _b = WH * V */
	for (int i = 0; i < _n; i++) {
		_b.set(_n+i,_WHMatrix.at(i,i)*_V.at(i,0));
	}

	/* first solve of X coordinates */
	_x = solveLS(_A, _b);

	/* change lower half of _b to use y coordinates */
	for (int i = 0; i < _n; i++) {
		_b.set(_n+i,_WHMatrix.at(i,i)*_V.at(i,1));
	}

	/* solve of Y coordinates */
	_y = solveLS(_A, _b);

	/* change lower half of _b to use z coordinates */
	for (int i = 0; i < _n; i++) {
		_b.set(_n+i,_WHMatrix.at(i,i)*_V.at(i,2));
	}

	/* solve of z coordinates */
	_z = solveLS(_A, _b);
		
}

void LeastSquares::updateSytem(const Mesh &mesh)
{
	
	for (int i = 0; i < _n; i++) {
		_V.set(i, 0, mesh.point3(Mesh::VHandle(i)).x);
		_V.set(i, 1, mesh.point3(Mesh::VHandle(i)).y);
		_V.set(i, 2, mesh.point3(Mesh::VHandle(i)).z);
	}
		
	for(int i = 0; i < _n; ++i) //fill B matrix with 0
    {
		_B.set(i, 0, 0);
		_B.set(i, 1, 0);
		_B.set(i, 2, 0);
    }
	
	/* update AT vector */

	QVector<Mesh::FHandle> faces;
	QVector<Mesh::VHandle> vertices;
	double area = 0.0;
	for(int i = 0; i < _n; ++i)
	{		
		
		/* 
		AT has for, each vertex, the area of the ring defined by the adjacent faces for the new, contracted, version of the mesh.
		*/

		faces = mesh.adjacentFaces(mesh.vertex_handle(i));
		area = 0.0;
		for (QVector<OpenMesh::PolyConnectivity::FaceHandle>::Iterator f_it = faces.begin(); f_it != faces.end(); ++f_it) {			
			area += mesh.area(*f_it);
		}		
		_AT.set(i, area);		
	}

	/* update values for the weighting matrixes */		
	for(int i = 0; i < _n; ++i)
	{	
		_WLMatrix.set(i,i,_SL*_WLMatrix.at(i,i));		
		_WHMatrix.set(i,i,_WH0*sqrt(_A0.at(i)/_AT.at(i)));
	}
	
}

