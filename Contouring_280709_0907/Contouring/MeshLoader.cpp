//////////////////////////////////////////////////////////////////////////////////////
//  Perspective Contouring Project
//	Jonatas Medeiros
//	UFRGS - 2008
//
//	MeshLoader.cpp includes definitions for the MeshLoader class
//////////////////////////////////////////////////////////////////////////////////////

#include "MeshLoader.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

//	skip a line
void MeshLoader::skipLine(istream& is)
{
    char next;
	is >> std::noskipws;
    while( (is >> next) && ('\n' != next) );
}

//	skip a comment line
bool MeshLoader::skipCommentLine(istream& is)
{
	char next;
	while( is >> std::skipws >> next ) 
    {
		is.putback(next);
		if ('#' == next)
			skipLine(is);
		else
			return true;
    }
    return false;
}

bool MeshLoader::processLine(Mesh* mesh, istream& is)
{
	string ele_id;
	float x, y, z;    
	
	if (!(is >> ele_id))
		return false;
	
	if ("mtllib" == ele_id)
    {
		string strFileName;
		is >> strFileName;
	}
	else if ("usemtl" == ele_id)
    {
		string strMtlName;
		is >> strMtlName;
	}
	else if ("v" == ele_id)
    {	
        //	vertex data
		is >> x >> y >> z;
		//mesh->AddVertex(VECTOR3D(1000.0f * x, 1000.0f * y, 1000.0f * z));
        mesh->AddVertex(VECTOR3D(x, y, z));
	}
	else if ("vt" == ele_id)
    {
        // texture data
		is >> x >> y >> z;
		is.clear();                           // is z (i.e. w) is not available, have to clear error flag.
		mesh->AddTextureCoord(VECTOR3D(x, y, z));
	}
	else if ("vn" == ele_id)
    {	
        // normal data
		is >> x >> y >> z;
		if(!is.good()) {                     // in case it is -1#IND00
			x = y = z = 0.0;
			is.clear();
			skipLine(is);
		}
		mesh->AddNormal(VECTOR3D(x, y, z));
	}
	else if ("f" == ele_id)
    {	
                                //	face data
								//	face treatment
								//  Note: obviously this technique only works for convex polygons with ten verts or less.
		int vi[10];                               // vertex indices.
		int ni[10] = { -1, -1, -1, -1, };         // normal indices.
		int ti[10] = { -1, -1, -1, -1, };         // tex indices.
		int i = 0;
		for (char c; i<10; ++i)
        {
			if(!mesh->hasTextureCoords() && !mesh->hasNormals())
				is >> vi[i];
			else if(!mesh->hasTextureCoords())
				is >> vi[i] >> c >> c >> ni[i];
			else if(!mesh->hasNormals())
				is >> vi[i] >> c >> ti[i];
			else
				is >> vi[i] >> c >> ti[i] >> c >>  ni[i];
			
			if(!is.good())
				break;
		}
		//	Create the polygon face
		FaceStruct face;
        for (int k=0; k < i; ++k)
		{
			face.v.push_back(vi[k]);
            face.n.push_back(ni[k]);
			face.t.push_back(ti[k]);
            mesh->AddNeighbor(vi[k], vi[(k+1)%i]);
            mesh->AddNeighbor(vi[k], vi[(k+2)%i]);
            mesh->v[vi[k]].faces.push_back(mesh->f.size());            
        }
		mesh->AddFace(face);
        for (int k=0; k < i; ++k)
		{
            mesh->AddEdge(vi[k], vi[(k+1)%i], mesh->f.size() - 1);
        }
		is.clear();
	}
    else if("g" == ele_id || "o" == ele_id)
    {
        Group g;
        g.start = mesh->f.size();
        string name;
        is >> name;
        g.name = name;
        mesh->g.push_back(g);
    }
	else
		skipLine(is);
	return true;
}

bool MeshLoader::load(Mesh* mesh, const string& strFileName)
{
	ifstream mf(strFileName.c_str(), ios::in|ios::ate);
	if (!mf)
		return false;
	const int fileSize = mf.tellg(); 
	mf.seekg (0, ios::beg);
	if (0 == fileSize)
		return false;

   	mesh->clear();

    int percent = 10;
    cout << "Loading model file: " << strFileName << endl << endl;
	while(skipCommentLine(mf)) 
	{
        if ((fileSize > 1024*1024) && (100*mf.tellg()/fileSize >= percent))
        {
			percent = 100*mf.tellg()/fileSize;
			percent = (percent/10)*10;
			cout << "  " << percent << " % done...\n" << endl;
			percent += 10;
		}

		if (false == processLine(mesh, mf))
			break;
	}

    cout << "  " << "100 % done.\n" << endl;    
	mf.close();  

	return true;
}