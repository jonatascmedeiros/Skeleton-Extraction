//////////////////////////////////////////////////////////////////////////////////////
//  Perspective Contouring Project
//	Jonatas Medeiros
//	UFRGS - 2008
//
//	Mesh.h includes headers for the Mesh class
//////////////////////////////////////////////////////////////////////////////////////

#ifndef MESH_H
#define MESH_H

// Includes
#include "Maths/Maths.h"
#include <vector>
#include <limits>

using namespace std;

struct FaceStruct
{
	FaceStruct(void){v.reserve(3); n.reserve(3); t.reserve(3);}

	vector<int> v;
	vector<int> n;
	vector<int> t;
    vector<int> e;
};

struct VerticeStruct
{
	VECTOR3D pos;
	VECTOR3D n;	
    double area;
    double currArea;
    int skIndex;
    bool tested;
    int closest;
    vector<int> silVertices;
    vector<int> neighbors;
    vector<int> faces;
    vector<int> edges;
};

struct EdgeStruct
{
    int v1, v2, f1, f2;
    bool used;
};

struct Group
{
    Group(void):minVert(numeric_limits<float>::max(), numeric_limits<float>::max(), numeric_limits<float>::max())
	, maxVert(-numeric_limits<float>::max(), -numeric_limits<float>::max(), -numeric_limits<float>::max()){}

    float getCenterX() const { return (minVert.x + maxVert.x) * 0.5f; }
    float getCenterY() const { return (minVert.y + maxVert.y) * 0.5f; }
    float getCenterZ() const { return (minVert.z + maxVert.z) * 0.5f; }

    int start;
    string name;
    VECTOR3D minVert;
	VECTOR3D maxVert;
};

// The Mesh class keeps loaded mesh information like vertices, normals and texture coordinates.
class Mesh
{
public:
    Mesh();
	vector<VerticeStruct> v;
    vector<EdgeStruct> e;
	vector<VECTOR3D> n;
	vector<VECTOR3D> t;
	vector<FaceStruct> f;
    vector<Group> g;
    VECTOR3D minVert;
	VECTOR3D maxVert;
    VECTOR3D orMinVert;
	VECTOR3D orMaxVert;
    double averageArea;
    static const int FIRST_INDEX;
    double maxCos;
    double minCos;

	void clear(void);
	void draw(int group, unsigned int id, unsigned int sizeV, unsigned int sizeN, int flag);
	const bool hasNormals() const { return static_cast<int>(n.size()) > FIRST_INDEX; }
	const bool hasTextureCoords() const { return static_cast<int>(t.size()) > FIRST_INDEX; }
    void GenerateNormals(void);
    void AddVertex(VECTOR3D v);
    void AddTextureCoord(VECTOR3D tn) { t.push_back(tn); }
	void AddNormal(VECTOR3D vn) { n.push_back(vn); }
	void AddFace(FaceStruct face) { f.push_back(face); }
    void AddNeighbor(int i, int n);
    float getCenterX() const { return (minVert.x + maxVert.x) * 0.5f; }
    float getCenterY() const { return (minVert.y + maxVert.y) * 0.5f; }
    float getCenterZ() const { return (minVert.z + maxVert.z) * 0.5f; }
    bool isNeighbor(int a, int b);
    double omega(int a, int b, int* el);
    //double omega(int a, int b);
    void CalcAreas(void);
    void UpdateOneRingAreas(void);
    void OrderNeighbors(void);
    void AddEdge(int v1, int v2, int f);
    int NextFace(int edge, int face);
    void NextEdges(int face, int edge, int* edge1, int* edge2);
    bool equal(double a, double b);
    void disallocateEdges(void);
    void cleanTestedVs(void);
};

#endif	//MESH_H