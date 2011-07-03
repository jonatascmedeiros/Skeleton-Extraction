#ifndef __MESH_H
#define __MESH_H

#ifdef _MSC_VER
#undef min
#undef max
#endif

#include <RX/vec3.h>
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <QString>
#include <QVector>
#include <QHash>
#include <QSet>

// screw good practice
using namespace OpenMesh;
using namespace RX;

// Triplet
template <typename T>
struct Triplet {
	T a, b, c;
	inline Triplet() {}
	inline Triplet(const T &a, const T &b, const T &c) : a(a), b(b), c(c) {}
	inline const T operator[](int n) const { return (&a)[n]; }
	inline T &operator[](int n) { return (&a)[n]; }
};

// Mesh
class Mesh : public TriMesh_ArrayKernelT<> 
{
public:
	struct Statistics 
	{
		vec3 min, max, center;
		float ext;
		float avgFaceArea;
		
		Statistics() : ext(0.0f), avgFaceArea(0.0) {}
		Statistics(const Mesh *mesh);
		const QString toString() const;
	};

	// Create/Destroy
	Mesh();
	virtual ~Mesh();

	// Operators
	const Mesh &operator=(const Mesh &mesh) 
	{
		this->assign(mesh);
		stats = mesh.stats;
		return *this;
	}

	// Sets
	void set_point3(const VHandle &vh, const vec3 &p) { set_point(vh, Point(p.floats())); }
	void set_point3(const int     idx, const vec3 &p) { set_point3(VHandle(idx), p); }
	
	void initOneRingArea(void);

	// Gets
	const vec3 point3(const VHandle &vh) const { return vec3(point(vh).data()); }
	const vec3 point3(const int     idx) const { return point3(VHandle(idx)); }
	const vec3 normal3(const VHandle &vh) const { return vec3(normal(vh).data()); }
	const vec3 normal3(const FHandle &fh) const { return vec3(normal(fh).data()); }

	const float avgArea() const { return stats.avgFaceArea; }

	const QVector<VHandle> adjacentVertices(const VHandle &vh) const;
	const QVector<FHandle> adjacentFaces(const VHandle &vh)   const;
	const Triplet<VHandle> faceVertices(const FHandle &fh) const;
	const float area(const FHandle &fh) const;

	const double getOneRingArea(const VHandle &vh) const;
	
	// Update
	void updateFace(const FHandle &fh) { update_normal(fh); }
	template <template <typename T> class C>
	void updateFaces(const C<FHandle> &fhs) { foreach(FHandle fh, fhs) updateFace(fh); }

	void updateVertex(const VHandle &vh) { update_normal(vh); }
	template <template <typename T> class C>
	void updateVertices(const C<VHandle> &vhs) { foreach(VHandle vh, vhs) updateVertex(vh); }

	bool update();

	// Render
	template <template <typename T> class C>
	void renderVertices(const C<VHandle> &vhs) const;
	template <template <typename T> class C>
	void renderFaces(const C<FHandle> &fhs) const;
	bool render() const;

	// File I/O
	bool read(const QString &file, IO::Options options = IO::Options::Default);
	bool write(const QString &file, IO::Options options = IO::Options::Default);

	// Properties
	Statistics stats;

	QVector<double> originalOneRingArea;
};

inline uint qHash(const Mesh::VHandle &vh) { return qHash(vh.idx()); }
inline uint qHash(const Mesh::FHandle &fh) { return qHash(fh.idx()); }

#include "Mesh.hpp"

#endif // __MESH_H
