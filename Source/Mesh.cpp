#include <RX/Definitions.h>
#include <QDebug>
#include <QMap>
#include <QQueue>
#include <QFileInfo>
#include <QSet>
#include <QTextStream>
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
#include "Mesh.h"

using namespace OpenMesh;

// Mesh::Statistics
Mesh::Statistics::Statistics(const Mesh *mesh) 
{
	// bbox
	Mesh::CVIter v_it(mesh->vertices_begin());
	min = max = mesh->point3(v_it.handle());
	for (; v_it != mesh->vertices_end(); ++v_it) {
		vec3 v = mesh->point3(v_it.handle());
		min.x = std::min(min.x, v.x);
		min.y = std::min(min.y, v.y);
		min.z = std::min(min.z, v.z);
		max.x = std::max(max.x, v.x);
		max.y = std::max(max.y, v.y);
		max.z = std::max(max.z, v.z);
	}

	// face area
	float faceArea = 0;
	Mesh::CFIter f_it(mesh->faces_begin());
	for (; f_it != mesh->faces_end(); ++f_it) {
		faceArea += mesh->area(f_it.handle());
	}
	faceArea /= mesh->n_faces();

	ext = (max - min).norm();
}

// Mesh
Mesh::Mesh()
{
	request_face_normals();
	request_vertex_normals();
}

Mesh::~Mesh() 
{
	release_vertex_normals();
	release_face_normals();
}

const QVector<Mesh::VHandle> Mesh::adjacentVertices(const VHandle &vh) const
{
	QVector<VHandle> ring;

	for (CVVIter cvv_it(cvv_iter(vh)); cvv_it; ++cvv_it) {
		ring.push_back(cvv_it);
	}

	return ring;
}

const QVector<Mesh::FHandle> Mesh::adjacentFaces(const VHandle &vh) const 
{
	QVector<FHandle> ring;

	for (CVFIter cvf_it(cvf_iter(vh)); cvf_it; ++cvf_it) {
		ring.push_back(cvf_it);
	}

	return ring;
}

const Triplet<Mesh::VHandle> Mesh::faceVertices(const FHandle &fh) const 
{	
	Triplet<VHandle> fvh;
	
	CFVIter cfv_it(cfv_iter(fh));

	for (int i(0); i < 3; ++i, ++cfv_it)	
		fvh[i] = cfv_it;
	
	return fvh;
}

const float Mesh::area(const FHandle &fh) const 
{
	Triplet<Mesh::VHandle> vs = faceVertices(fh);
	return 0.5f * ((point3(vs.b) - point3(vs.a)) ^ (point3(vs.c) - point3(vs.a))).norm();
}

void Mesh::initOneRingArea(void)
{
	for(int i = 0; i < n_vertices(); i++)
		originalOneRingArea.append(getOneRingArea(Mesh::VHandle(i)));		
}

const double Mesh::getOneRingArea(const VHandle &vh) const
{
	QVector<Mesh::FHandle> neighborFaces = adjacentFaces(vh);
	double oneRingArea = 0.0;
	for(int i = 0; i < neighborFaces.size(); i++)
		oneRingArea += area(neighborFaces[i]);

	return oneRingArea;
}

// updates
bool Mesh::update() 
{
	update_normals();
	stats = Statistics(this);

	initOneRingArea();
	
	return true;
}

// rendering
bool Mesh::render() const 
{
	glBegin(GL_TRIANGLES);
	for (CFIter cf_it(faces_begin()); cf_it != faces_end(); ++cf_it) {
		CFVIter cfv_it(cfv_iter(cf_it));
		glNormal3fv(normal(cfv_it).data()); glVertex3fv(point(cfv_it).data()); ++cfv_it;
		glNormal3fv(normal(cfv_it).data()); glVertex3fv(point(cfv_it).data()); ++cfv_it;
		glNormal3fv(normal(cfv_it).data()); glVertex3fv(point(cfv_it).data());
	}
	glEnd();

	return true;
}

// file I/O
bool Mesh::read(const QString &file, IO::Options options) 
{
	PolyMesh_ArrayKernelT<> tmp;
	if (!IO::read_mesh(tmp, file.toStdString(), options))
		return false;

	tmp.triangulate();
	this->assign(tmp);
	
	return update();
}

bool Mesh::write(const QString &file, IO::Options options) 
{
	if (!IO::write_mesh(*this, file.toStdString(), options))
		return false;

	return true;
}

