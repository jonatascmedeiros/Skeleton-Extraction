//////////////////////////////////////////////////////////////////////////////////////
//  Perspective Contouring Project
//	Jonatas Medeiros
//	UFRGS - 2008
//
//	Mesh.cpp includes definitions for the Mesh class
//////////////////////////////////////////////////////////////////////////////////////

// Includes
#include <gl/glew.h>
#include "Mesh.h"
#include <fstream>
#include <limits>
#include <gl\glut.h>

const int Mesh::FIRST_INDEX = 1;

Mesh::Mesh()
    : minVert(numeric_limits<float>::max(), numeric_limits<float>::max(), numeric_limits<float>::max())
	, maxVert(-numeric_limits<float>::max(), -numeric_limits<float>::max(), -numeric_limits<float>::max())
{
	VerticeStruct vs;
    vs.pos = VECTOR3D(0, 0, 0);
    vs.n = VECTOR3D(0, 0, 0);
    v.push_back(vs);
	n.push_back(VECTOR3D(0, 0, 0));
	t.push_back(VECTOR3D(0, 0, 0));
    orMinVert = minVert;
    orMaxVert = maxVert;
}

void Mesh::clear(void)
{
	v.clear();
	t.clear();
	n.clear();
    e.clear();
	f.clear();
    g.clear();
    minVert = orMinVert;
    maxVert = orMaxVert;

    VerticeStruct vs;
    vs.pos = VECTOR3D(0,0,0);
    vs.n = VECTOR3D(0,0,0);

    v.push_back(vs);
    n.push_back(VECTOR3D(0,0,0));
    t.push_back(VECTOR3D(0,0,0));
}

void Mesh::draw(int group, unsigned int id, unsigned int sizeV, unsigned int sizeN, int flag)
{
    glEnable(GL_LIGHTING);    
    glPushMatrix();
    
    //if(group == 0)
    //    //glTranslated(-getCenterX(), -getCenterY(), -getCenterZ());
    //else
    //    glTranslatef(-g[group-1].getCenterX(), -g[group-1].getCenterY(), -g[group-1].getCenterZ());
  
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);       
    glColorPointer(3, GL_FLOAT, 0, (void*)(sizeof(GLfloat) * (sizeV + sizeN)));
    glNormalPointer(GL_FLOAT, 0, (void*)(sizeof(GLfloat) * sizeV));
    glVertexPointer(3, GL_FLOAT, 0, 0);
    if(flag == 0)
        glPolygonMode(GL_FRONT, GL_LINE);
    else
        glPolygonMode(GL_FRONT, GL_FILL);


    glDrawArrays(GL_TRIANGLES, 0, sizeV/3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glPopMatrix();    
    glDisable(GL_LIGHTING);
    glPolygonMode(GL_FRONT, GL_FILL);
}

void Mesh::GenerateNormals(void)
{
    vector<VECTOR3D> vs;
    vector<VECTOR3D> ns;
    	
	// for each face...
	for (vector<FaceStruct>::iterator itFace = f.begin(); itFace != f.end(); ++itFace)
	{
        vs.clear();
        ns.clear();
        VECTOR3D v1 = v[(*itFace).v[0]].pos;
		VECTOR3D v2 = v[(*itFace).v[1]].pos;
		VECTOR3D v3 = v[(*itFace).v[2]].pos;
		VECTOR3D u = v2 - v1;
		VECTOR3D w = v3 - v1;
        VECTOR3D vn = u.CrossProduct(w);
        for(vector<int>::iterator itVertex = (*itFace).v.begin(); itVertex != (*itFace).v.end(); ++itVertex)
        {
            v[(*itVertex)].n += vn;            
        }        
	}
    for(unsigned i = 0; i < v.size(); i++)
    {
        v[i].n.Normalize();
    }
}

void Mesh::AddVertex(VECTOR3D vx)
{
    VerticeStruct vs;
    vs.pos = vx;
    vs.n = VECTOR3D(0.0f, 0.0f, 0.0f);
    vs.area = 0.0f;
    vs.tested = false;
	v.push_back(vs);
	//  x bound assignation
	if (vx.x < minVert.x)
		minVert.x = vx.x;
	if (maxVert.x < vx.x)
		maxVert.x = vx.x;
	//  y
	if (vx.y < minVert.y)
		minVert.y = vx.y;
	if (maxVert.y < vx.y)
		maxVert.y = vx.y;
	//  z
	if (vx.z < minVert.z)
		minVert.z = vx.z;
	if (maxVert.z < vx.z)
		maxVert.z = vx.z;

    // Group 

    if(g.size() > 0)
    {
        if (vx.x < g.back().minVert.x)
		    g.back().minVert.x = vx.x;
	    if (g.back().maxVert.x < vx.x)
		    g.back().maxVert.x = vx.x;
	    //  y
	    if (vx.y < g.back().minVert.y)
		    g.back().minVert.y = vx.y;
	    if (g.back().maxVert.y < vx.y)
		    g.back().maxVert.y = vx.y;
	    //  z
	    if (vx.z < g.back().minVert.z)
		    g.back().minVert.z = vx.z;
	    if (g.back().maxVert.z < vx.z)
		    g.back().maxVert.z = vx.z;
    }
}

void Mesh::cleanTestedVs(void)
{
    for(unsigned int i = 0; i < v.size(); i++)
    {
        v[i].tested = false;
    }
}

bool Mesh::isNeighbor(int a, int b)
{
    for(unsigned int i = 0; i < v[a].neighbors.size(); i++)
        if(v[a].neighbors[i] == b)
            return true;
    return false;
}

double Mesh::omega(int a, int b, int* el)
{
    int c = -1, d = -1;
    unsigned int Nfaces = v[a].faces.size();
    unsigned int Nverts;
    for(unsigned int i = 0; i < Nfaces; i++)
    {
        Nverts = f[v[a].faces[i]].v.size();
        for(unsigned int j = 0; j < Nverts; j++)
        {
            if(f[v[a].faces[i]].v[j] == b)
            {
                if(f[v[a].faces[i]].v[(j+1)%Nverts] == a)
                {
                    if(c == -1)
                    {
                        c = f[v[a].faces[i]].v[(j+2)%Nverts];                        
                    }
                    else
                    {
                        d = f[v[a].faces[i]].v[(j+2)%Nverts];                        
                    }
                    break;
                }
                else
                {
                    if(c == -1)
                    {
                        c = f[v[a].faces[i]].v[(j+1)%Nverts];                        
                    }
                    else
                    {
                        d = f[v[a].faces[i]].v[(j+1)%Nverts];                       
                    }
                    break;
                }
            }
        }
        if(d != -1)
            break;
    }       

    VECTOR3D vec1 = v[a].pos - v[c].pos;
    VECTOR3D vec2 = v[b].pos - v[c].pos;
    vec1.Normalize();
    vec2.Normalize();
    double cosine = vec1.DotProduct(vec2);

    double angle = acos(cosine);
    double cotA;
    //cotA = cosine/(sin(angle) + 0.0001);
    if(equal(angle, M_PI/2))
    {
        cotA = 0.0;
    }
    else if(equal(angle, 0.0))
    {
        cotA = 999999.9;
    }
    else
        cotA = 1 / tan(angle);  
   
    vec1 = v[a].pos - v[d].pos;
    vec2 = v[b].pos - v[d].pos;
    vec1.Normalize();
    vec2.Normalize();
    cosine = vec1.DotProduct(vec2);

    angle = acos(cosine);
    double cotB;

    if(equal(angle, M_PI/2))
    {
        cotB = 0.0;
    }
    else if(equal(angle, 0.0))
    {
        cotB = 999999.9;
    }
    else
        cotB = 1 / tan(angle);  

    *el = -1;

    return cotA + cotB;
}

void Mesh::CalcAreas(void)
{
    double areaTotal = 0.0;
    VECTOR3D side0, side1, side2;
    double a, b, c, p, area;
    for(vector<FaceStruct>::const_iterator itFace = f.begin(); itFace != f.end(); ++itFace)
	{
        side0 = v[(*itFace).v[0]].pos - v[(*itFace).v[1]].pos;
        side1 = v[(*itFace).v[0]].pos - v[(*itFace).v[2]].pos;
        side2 = v[(*itFace).v[1]].pos - v[(*itFace).v[2]].pos;
        a = side0.GetLength();
        b = side1.GetLength();
        c = side2.GetLength();
        p = (a + b + c) / 2.0;
        area = sqrt(p*(p-a)*(p-b)*(p-c));
        areaTotal += area;
        for(unsigned int i = 0; i < (*itFace).v.size(); i++)
        {
            v[(*itFace).v[i]].area += area;
        }
    }
    averageArea =  areaTotal/((double)f.size());
}

void Mesh::UpdateOneRingAreas(void)
{
    VECTOR3D side0, side1, side2;
    float a, b, c, p, area;
    for(vector<FaceStruct>::const_iterator itFace = f.begin(); itFace != f.end(); ++itFace)
	{
        side0 = v[(*itFace).v[0]].pos - v[(*itFace).v[1]].pos;
        side1 = v[(*itFace).v[0]].pos - v[(*itFace).v[2]].pos;
        side2 = v[(*itFace).v[1]].pos - v[(*itFace).v[2]].pos;
        a = side0.GetLength();
        b = side1.GetLength();
        c = side2.GetLength();
        p = (a + b + c) / 2.0;
        area = sqrt(p*(p-a)*(p-b)*(p-c));
        for(unsigned int i = 0; i < (*itFace).v.size(); i++)
        {
            v[(*itFace).v[i]].currArea += area;
        }
    }
}
void Mesh::AddNeighbor(int i, int n)
{
    bool exists = false;
    for(unsigned j = 0; j < v[i].neighbors.size(); j++)
    {
        if(v[i].neighbors[j] == n)
        {
            exists = true;
            break;
        }
    }
    if(!exists)
        v[i].neighbors.push_back(n);
}
void Mesh::OrderNeighbors(void)
{
    for(unsigned int i = 0; i < v.size(); i++)
    {
        

    }
}
void Mesh::AddEdge(int v1, int v2, int face)
{
    bool found = false;
    for(unsigned int i = 0; i < v[v1].edges.size(); i++)
    {
        if((e[v[v1].edges[i]].v1 == v2) || (e[v[v1].edges[i]].v2 == v2))
        {
            e[v[v1].edges[i]].f2 = face;
            f[face].e.push_back(v[v1].edges[i]);
            found = true;
            break;
        }
    }
    if(!found)
    {
        EdgeStruct edge;
        edge.v1 = v1;
        edge.v2 = v2;
        edge.f1 = face;
        edge.f2 = -1;
        edge.used = false;
        v[v1].edges.push_back(e.size());
        v[v2].edges.push_back(e.size());
        f[face].e.push_back(e.size());
        e.push_back(edge);
    } 


    /*bool found = false;
    for(unsigned int i = 0; i < e.size(); i++)
    {
        if(((e[i].v1 == v1) && (e[i].v2 == v2)) ||
           ((e[i].v1 == v2) && (e[i].v2 == v1)))
        {
            e[i].f2 = f;  
            found = true;
            break;
        }      
    }
    if(!found)
    {
        EdgeStruct edge;
        edge.v1 = v1;
        edge.v2 = v2;
        edge.f1 = f;
        e.push_back(edge);
    }*/
}

int Mesh::NextFace(int edge, int face)
{
    if(e[edge].f1 == face)
        return e[edge].f2;
    return e[edge].f1;
}

void Mesh::NextEdges(int face, int edge, int* edge1, int* edge2)
{
    if(f[face].e[0] == edge)
    {
        *edge1 = f[face].e[1];
        *edge2 = f[face].e[2];
    }
    else if(f[face].e[1] == edge)
    {
        *edge1 = f[face].e[0];
        *edge2 = f[face].e[2];
    }
    else if(f[face].e[2] == edge)
    {
        *edge1 = f[face].e[0];
        *edge2 = f[face].e[1];
    }
}
bool Mesh::equal(double a, double b)
{
    if(fabs(a - b) < EPSILON)
        return true;
    return false;
}
void Mesh::disallocateEdges(void)
{
    for(unsigned int i = 0; i < e.size(); i++)
    {
        e[i].used = false;
    }
}