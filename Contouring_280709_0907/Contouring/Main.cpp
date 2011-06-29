//////////////////////////////////////////////////////////////////////////////////////
//  Perspective Contouring Project
//	Jonatas Medeiros
//	UFRGS - 2009
//
//////////////////////////////////////////////////////////////////////////////////////

// Includes
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <ctime>

#include "Maths/Maths.h"
#include "Mesh.h"
#include "MeshLoader.h"
#include "textfile.h"
#include <gl/glew.h>
#include <AntTweakBar.h>
#include <gl\freeglut.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>
#ifndef WIN32
#include <unistd.h>
#include <pthread.h>
#endif
#define TAUCS_CORE_DOUBLE
extern "C" {
#include "taucs.h"
}

using namespace std;

// Rendering variables
COLOR mainBgColor;
GLfloat camZoom, camTX, camTY, camRotX, camRotY, camScale, funcTX;
float scaleFactor;
bool drawModel;
GLdouble modelViewMatrix[16], projectionMatrix[16];
GLint viewportMatrix[4];
GLint tanAttLoc, flatNAttLoc, widthAttLoc;
double maxWidthFuncWindow;
int mainWindow, mainWindowWidth, mainWindowHeight;

float widthMaster, spaceMaster, silMaster;

// Shader variables
GLuint vp, vn, vs, fp, fn, phongShader, normalMapShader, SilShader, fbo, depthBuffer, normalMap;

// Geometry variables
Mesh mesh;
int nSkeletons;
vector<VECTOR3D> skeleton;
GLuint idMesh, idMeshEdge;    
int verticesSize, normalsSize, verticesEdgeSize, normalsEdgeSize, tangentsEdgesSize, flatNormalsEdgesSize;
float widthMIN; 
float distMIN;
float silMAX;
float scaleROIWidth;
int CP;

// Control variables
vector<VECTOR3D> screenPoints;
int currFile, currGroup, lastx, lasty, nMeshes;
bool hasModel, doingSketch, doingROISketch, editingCP, movingPanels;
string nameOpt, groupOpt;    
VECTOR3D lastp;
unsigned char buttons[3];
vector<string> fileNames;
vector<int> menuIDs;
TwBar *drawBar, *parBar, *advBar, *modBar;
int currSide;
int selectedSkeleton, selectedROI, selectedFunc, selectedCP;
bool showFuncWindow;

// Solver variables
taucs_ccs_matrix* A;
double* B;
double* X;
double WL;
//vector<double> WH;
double* WH;
vector<bool> eliminated;
vector<map<int, double>> L;
vector<map<int, double>> Lt;
vector<map<int, double>> AtA;
unsigned int N;
int nnz;



// Rendering functions
void TW_CALL ButtonCallback(void *clientData);
void CalcAtA(Mesh* meshc);
void CalcB(Mesh* meshc);
float CalcDist(VECTOR3D a, VECTOR3D b);
void CalcL(Mesh* meshc);
void CompactMatrix(void);
void CreateInterface(void);
void CreateMatrices(); 
bool Equal(double a, double b);
void exit_func(void);
void TW_CALL GetCallback(void *value, void *clientData);
COLOR GetColor(int index);
bool GLInit(int w, int h);
void Keyboard_Main(unsigned char key, int x, int y);
bool LoadFileNames(void);
void Motion_Main(int x,int y);
void Mouse_Main(int b,int s,int x,int y);
double MultLinePerCol(unsigned int i, unsigned int j);
bool OutsideWindow(int x, int y, bool isMainWindow);
void PassMotion_Main(int x,int y);
void PrintProgramInfoLog(GLuint obj);
void PrintShaderInfoLog(GLuint obj);
VECTOR3D ProjectOneCPMesh(int x, int y);
void Render_Main(void);
void Reset(void);
void Reshape_Main(int w, int h);
void ResetCam(void);
void ResetDrawFlags(void);
void TW_CALL SetCallback(const void *value, void *clientData);
void SetLights(void);
void SetShaders(void);
double* Solve(Mesh mesh);
void Special_Main(int key, int x, int y);
void UpdateMesh(Mesh* meshc);
void UpdateWeights(Mesh* meshc);
void VBOLoadFullModel(void);

// ------- Functions ------- 
void TW_CALL ButtonCallback(void *clientData)
{
    int ID = *(int*)(clientData);
    switch(ID)
    {
        case 103 : // New drawing
            Reset();
            break; 
        case 101 : 
           
            break;
        case 102 : 
            
            break;
        case 401 : // Load model file
            if(currFile > 0)
            {
                string fNames;
                fNames.clear();
                fNames.append("../../Models/");
                fNames.append(fileNames[currFile]);
                if(MeshLoader::load(&mesh, fNames))
                {
                    mesh.CalcAreas();
                    //skeleton.clear();
                    /*cout << "AdjMatrix:" << endl;
                    for(unsigned int i = 0; i < mesh.v.size(); i++)
                    {
                        for(unsigned int j = 0; j < mesh.adjMatrix[i].size(); j++)
                        {
                            cout << mesh.adjMatrix[i][j] << " ";
                        }
                        cout << endl;
                    }*/
                    
                    mesh.GenerateNormals();
                    VBOLoadFullModel(); 
                    
                    float meshHeight = mesh.maxVert.y - mesh.minVert.y;
                    scaleFactor = 1.0f/meshHeight;

                    hasModel = true;
                    // Group string creation
                    groupOpt.clear();
                    groupOpt.append(" LoadModel/Group val='0 {All");
                    groupOpt.append("}");
                    char buff[50];
                    unsigned int i = 1;
	                while(mesh.g.size() >= i)
                    {
                        groupOpt.append(", ");
                        _itoa_s(i, buff, 10);
                        groupOpt.append(buff);
                        groupOpt.append(" {");
                        groupOpt.append(mesh.g[i-1].name);
                        groupOpt.append("}");
                        i++;
                    }
                    groupOpt.append("'");
                    TwDefine(groupOpt.c_str()); 
                    currGroup = 0;
                    ResetCam();
                    Reset();
                }
                else
                {
                    hasModel = false;
                }
            }
            break;
        case 404 : 
            
            break;
        case 405:             
            
            break;
        case 403 : // Create Skeleton            
            CreateMatrices();
            double* X = Solve(mesh);
            skeleton.clear();
            /*for(unsigned int i = 0; i < mesh.v.size()-1; i++)
            {
                skeleton.push_back(VECTOR3D(X[i], X[i+(mesh.v.size()-1)], X[i+2*(mesh.v.size()-1)]));
            }*/
            taucs_free(X);

			UpdateMesh(&mesh);

            //mesh.n.clear();
            //for(unsigned int i = 0; i < mesh.v.size() - 1; i++)
            //{
            //    mesh.v[i+1].pos.x = X[i][0];
            //    //mesh.v[i+1].pos.x = X[i];
            //    mesh.v[i+1].pos.y = X[i][1];
            //    mesh.v[i+1].pos.z = X[i][2];
            //    mesh.v[i+1].n = VECTOR3D(0.0, 0.0, 0.0);
            //}  
            ////delete[] X;
            //mesh.generateNormals();


           /* for(unsigned int i = 0; i < mesh.v.size(); i++)
            {
                mesh.v[i+1].pos.x = solver.X[i];
            }
            mesh.n.clear();
            for(unsigned int i = 0; i < mesh.v.size(); i++)
            {
                mesh.v[i].n = VECTOR3D(0.0, 0.0, 0.0);
            }*/
            
            break;        
    }
}

void CalcAtA(Mesh* meshc)
{
    cout << "starting CalcAtA..." << endl;
    unsigned int index = 0;
    double mult;
    nnz = 0;
    map<int, bool> done;
    unsigned int neighbor;
    while(index < N)
    {
        done.clear();
        AtA[index].clear();
        for(unsigned int j = 0; j < meshc->v[index+1].neighbors.size(); j++)
        {
            for(unsigned int k = 0; k < meshc->v[meshc->v[index+1].neighbors[j]].neighbors.size(); k++)
            {
                neighbor = meshc->v[meshc->v[index+1].neighbors[j]].neighbors[k] - 1;
                if(!done[neighbor] && neighbor <= index)
                {
                    mult = MultLinePerCol(index, neighbor);
                    if(!Equal(mult, 0.0))
                    {
                        nnz++;
                        AtA[index][neighbor] = mult;
                        AtA[neighbor][index] = mult;
                    }
                    done[neighbor] = true;
                }
            }
            neighbor = meshc->v[index+1].neighbors[j] - 1;
            if(!done[neighbor] && neighbor <= index)
            {
                mult = MultLinePerCol(index, neighbor);
                if(!Equal(mult, 0.0))
                {
                    nnz++;
                    AtA[index][neighbor] = mult;
                    AtA[neighbor][index] = mult;                    
                }
                done[neighbor] = true;
            }                 
        }
        if(!done[index])
        {
            mult = MultLinePerCol(index, index);
            if(!Equal(mult, 0.0))
            {
                nnz++;
                AtA[index][index] = mult; 
            }
        }       
        AtA[index][index] += (WH[index] * WH[index]);
        if(Equal(AtA[index][index], WH[index] * WH[index]))
            nnz++;
        index++;
    }    
}

void CalcB(Mesh* meshc)
{
    for(unsigned int i = 0; i < N; i++)
    {
        B[i] = meshc->v[i+1].pos.x * WH[i] * WH[i];
        B[i+(N)] = meshc->v[i+1].pos.y * WH[i] * WH[i];
        B[i+(2*N)] = meshc->v[i+1].pos.z * WH[i] * WH[i];
    }
}

float CalcDist(VECTOR3D a, VECTOR3D b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}

void CalcL(Mesh* meshc)
{
    cout << "starting CalcL..." << endl;
    double omegaSum;
    double omega;   
    omegaSum = 0.0;  
    int count = 0;
    map<int, double>::iterator iter;
    for(unsigned int i = 0; i < N; i++)
    {
        L[i].clear();
        for(unsigned int k = 0; k < meshc->v[i+1].neighbors.size(); k++)
        {
            unsigned int j = meshc->v[i+1].neighbors[k];
            if((j-1) < i)
            {
                int el;
                omega = meshc->omega(i+1, j, &el);
                //omega = mesh.omega(i+1, j);
                if(omega != 0.0) /*&& !eliminated[i])*/
                {
                    double w = omega * WL;
                    L[i][j-1] = w;
                    L[j-1][i] = w;
                    omegaSum -= w;
                    //L[j-1][j-1] -= w;
                }
                else if(el != -1)
                {
                    // Eliminate lines i, j-1 and el-1
                   /* eliminated[i] = true;
                    eliminated[j-1] = true;
                    eliminated[el-1] = true;*/

                    if(!eliminated[i])
                    {
                        for(iter = L[i].begin(); iter != L[i].end(); iter ++)
                        {
                            if(iter->first >= i)
                                break;
                            L[iter->first][iter->first] += iter->second;
                        }
                        eliminated[i] = true;
                        count++;
                    }
                    if(!eliminated[j-1])
                    {
                        for(iter = L[j-1].begin(); iter != L[j-1].end(); iter ++)
                        {
                            if(iter->first >= j-1)
                                break;
                            L[iter->first][iter->first] += iter->second;
                        }
                        eliminated[j-1] = true;
                        count++;
                    }
                    if(!eliminated[el-1])
                    {
                        for(iter = L[el-1].begin(); iter != L[el-1].end(); iter ++)
                        {
                            if(iter->first >= el-1)
                                break;
                            L[iter->first][iter->first] += iter->second;
                        }
                        eliminated[el-1] = true;
                        count++;
                    }
                    
                }
            }
        }
        L[i][i] = omegaSum;
        omegaSum = 0.0;        
    }  
    for(unsigned int i = 0; i < N; i++)
    {
        for(iter = L[i].begin(); iter != L[i].end(); iter++)
        {
            if(iter->first >= i)
                break;
            L[iter->first][iter->first] -= iter->second;
        }       
    }
    /*cout << "maxCos: " << meshc->maxCos << endl;  
    cout << "minCos: " << meshc->minCos << endl;*/ 
    cout << "count2: " << count << endl;
    for(unsigned ggg = 0; ggg < N; ggg ++)
    {
        if(eliminated[ggg])
        {
            cout << ggg + 1 << endl;
            cout << meshc->v[ggg+1].pos.x << " " << meshc->v[ggg+1].pos.y << " " << meshc->v[ggg+1].pos.z << endl;
        }
    }
}

void CompactMatrix(void)
{
    cout << "Compacting A matrix..." << endl;
    unsigned int k, l;
    map<int, double>::iterator iter;
    k = 0; l = 0;
    bool first;
    for(unsigned int i = 0; i < N; i++)
    {
        first = true; 
        for(iter = AtA[i].begin(); iter != AtA[i].end(); iter++)
        {
            if(iter->first < i)
                continue;
            A->values.d[k] = iter->second;
            A->rowind[k] = iter->first;
            if(first)
            {
                A->colptr[l] = k;
                l++;
                first = false;
            }
            k++;            
        }    
    }
    A->colptr[l] = k;    
}

void CreateInterface(void)
{
	// Set menu IDs vector
	menuIDs.reserve(1000);
	menuIDs.clear();
    
	TwDefine(" GLOBAL iconpos=topright help='Perspective Contouring Project\n Jonatas Medeiros' ");
    // Create Draw Bar
	drawBar = TwNewBar("Draw");
	TwDefine(" Draw position='1 1' size='180 190' valuesWidth=50 "); // default size = 200 320
    /*TwAddVarRW(drawBar, "Grid", TW_TYPE_BOOLCPP, &(drawGrid), "");*/
    TwAddVarRW(drawBar, "3D model", TW_TYPE_BOOLCPP, &(drawModel), "");
   // TwAddVarRW(drawBar, "Sketch lines", TW_TYPE_BOOLCPP, &(drawSketching), "");
    //TwAddVarRW(drawBar, "Strokes", TW_TYPE_BOOLCPP, &(drawStrokes), "");
	TwAddSeparator(drawBar, NULL, NULL);
    menuIDs.push_back(101);
    TwAddButton(drawBar, "InitSketch", ButtonCallback, &(menuIDs[0]), "label = 'Init Skeleton Sketch'");
	menuIDs.push_back(102);
    TwAddButton(drawBar, "InitSketchROI", ButtonCallback, &(menuIDs[1]), "label = 'Init ROI Sketch'");
	TwAddSeparator(drawBar, NULL, NULL);
    menuIDs.push_back(103);
    TwAddButton(drawBar, "NewDrawing", ButtonCallback, &(menuIDs[2]), "label = 'New Drawing'");
    TwAddSeparator(drawBar, NULL, NULL);
    menuIDs.push_back(104);
    TwType FuncType = TwDefineEnum("FuncType", NULL, 0);
    TwAddVarCB(drawBar, "Function", FuncType, SetCallback, GetCallback, &(menuIDs[3]), "val = '0 {spacing}, 1 {width}, 2 {silhouette}' ");
	
	
	// Create Parameters Bar
	//parBar = TwNewBar("Parameters");
	//TwDefine(" Parameters iconify help='Set line drawing parameters.' position='1 132' size='200 295' valuesWidth=80 ");

	//menuIDs.push_back(201);
	//TwType sideType = TwDefineEnum("sideType", NULL, 0);
	//TwAddVarCB(parBar, "Side", sideType, SetCallback, GetCallback, &(menuIDs[3]), " val='0 {LEFT}, 1 {RIGHT}, 2 {BOTH}' ");
	//
	//TwAddSeparator(parBar, NULL, NULL);	

	//menuIDs.push_back(202);
	//TwAddVarCB(parBar, "BetaS (/100)", TW_TYPE_FLOAT, SetCallback, GetCallback, &(menuIDs[4]), " min=0.1 max=100.0 step=0.1 ");
	//menuIDs.push_back(203);
	//TwAddVarCB(parBar, "GamaS", TW_TYPE_FLOAT, SetCallback, GetCallback, &(menuIDs[5]), " min=-100.0 max=0.9 step=0.1 ");
	//
	//TwAddSeparator(parBar, NULL, NULL);
	//
	//menuIDs.push_back(204);
	//TwAddVarCB(parBar, "BetaL", TW_TYPE_FLOAT, SetCallback, GetCallback, &(menuIDs[6]), " min=0.0 max=10.0 step=0.001 ");
	//menuIDs.push_back(205);
	//TwAddVarCB(parBar, "GamaL", TW_TYPE_FLOAT, SetCallback, GetCallback, &(menuIDs[7]), " min=-1.0 max=100.0 step=0.1 ");
	//
	//TwAddSeparator(parBar, NULL, NULL);
	//
	//menuIDs.push_back(206);
	//TwAddVarCB(parBar, "BetaW", TW_TYPE_FLOAT, SetCallback, GetCallback, &(menuIDs[8]), " min=0.1 max=100.0 step=0.1 ");
	//menuIDs.push_back(207);
	//TwAddVarCB(parBar, "GamaW", TW_TYPE_FLOAT, SetCallback, GetCallback, &(menuIDs[9]), " min=-500.0 max=0.9 step=10.0 ");
	//
	//TwAddSeparator(parBar, NULL, NULL);
	//
	//menuIDs.push_back(208);
	//TwAddVarCB(parBar, "BetaSil", TW_TYPE_FLOAT, SetCallback, GetCallback, &(menuIDs[10]), " min=0.0 max=10.0 step=0.001 ");
	//menuIDs.push_back(209);
	//TwAddVarCB(parBar, "GamaSil", TW_TYPE_FLOAT, SetCallback, GetCallback, &(menuIDs[11]), " min=-1.0 max=1000.0 step=1.0 ");
	//
	//TwAddSeparator(parBar, NULL, NULL);
	//
	//menuIDs.push_back(210);
	//TwAddVarCB(parBar, "Min spacing", TW_TYPE_FLOAT, SetCallback, GetCallback, &(menuIDs[12]), " min=1.0 max=10.0 step=0.1 ");
	//menuIDs.push_back(211);
	//TwAddVarCB(parBar, "Min width", TW_TYPE_FLOAT, SetCallback, GetCallback, &(menuIDs[13]), " min=0.001 max=1.0 step=0.001 ");
	//menuIDs.push_back(212);
	//TwAddVarCB(parBar, "Max sil width", TW_TYPE_FLOAT, SetCallback, GetCallback, &(menuIDs[14]), " min=0.01 max=1.0 step=0.01 ");

	//// Create Advanced Bar
	//advBar = TwNewBar("Advanced");
	//TwDefine(" Advanced iconify help='Advanced configuration.' position='1 428' size='200 70' valuesWidth=70 ");
	//menuIDs.push_back(301);
	////TwAddVarCB(advBar, "NULL0", TW_TYPE_FLOAT, SetCallback, GetCallback, &(menuIDs[14]), " min=0.01 max=1.0 step=0.01 ");
	//menuIDs.push_back(302);
	////TwAddVarCB(advBar, "NULL1", TW_TYPE_FLOAT, SetCallback, GetCallback, &(menuIDs[15]), " min=0.5 max=5.0 step=0.5 ");
	//menuIDs.push_back(303);
	//TwAddVarCB(advBar, "NSplinePoints", TW_TYPE_INT32, SetCallback, GetCallback, &(menuIDs[17]), " min=1 max=500 step=1 ");

    // Create Model Bar
	modBar = TwNewBar("LoadModel");
    TwDefine(" LoadModel label='Load Model' position='1 192' size='180 85' valuesWidth=70 ");
	TwType modelFileType = TwDefineEnum("modelFileType", NULL, 0);
    TwAddVarRW(modBar, "File", modelFileType, &(currFile), nameOpt.c_str());
	menuIDs.push_back(401);
    TwAddButton(modBar, "Load", ButtonCallback, &(menuIDs[4]), " label='Load file' key=Return help='Load the file specified in File name' ");
    menuIDs.push_back(402);
    TwType groupType = TwDefineEnum("groupType", NULL, 0);
    TwAddVarCB(modBar, "Group", groupType, SetCallback, GetCallback,  &(menuIDs[5]), groupOpt.c_str());
    menuIDs.push_back(403);
    TwAddButton(modBar, "CreateSkeleton", ButtonCallback, &(menuIDs[6]), " label='Create Skeleton' help='Create the mesh Skeleton' ");
    menuIDs.push_back(404);
    /*TwAddButton(modBar, "ExtractSections", ButtonCallback, &(menuIDs[7]), " label='Extract Sections' help='Extract sections from the mesh' ");
    menuIDs.push_back(405);
    TwAddButton(modBar, "FindSectionROI", ButtonCallback, &(menuIDs[8]), " label='Find ROI Sections' help='Find the sections affected by the ROI' ");*/

}

void CreateMatrices()
{
    cout << "creating matrices..." << endl;
    //WH.clear();    
    N = mesh.v.size() - 1;
    cout << "WL" << endl;
    WL = 100.0 * sqrt(mesh.averageArea);
    //WL = mesh->averageArea;
    //WL = 13.55;
    //WL = 3.0;
    cout << WL << endl;
    cout << mesh.averageArea << endl;
    
    cout << "creating B matrix..." << endl;
    B = (double*)taucs_vec_create(N*3, TAUCS_DOUBLE);
    X = (double*)taucs_vec_create(N*3, TAUCS_DOUBLE);
    WH = (double*)taucs_vec_create(N, TAUCS_DOUBLE);
    for(unsigned int i = 0; i < N; i++)
    {
        //WH.push_back(1.0);
        WH[i] = 1.0;
        B[i] = mesh.v[i+1].pos.x;
        B[i+(N)] = mesh.v[i+1].pos.y;
        B[i+(2*N)] = mesh.v[i+1].pos.z;
        eliminated.push_back(false);
    }    
   
    cout << "creating L matrix..." << endl;
    map<int, double> empty;
    double omegaSum;
    double omega;      
    omegaSum = 0.0;  
    mesh.maxCos = 0.0;
    mesh.minCos = 0.0;
    int count = 0;
    map<int, double>::iterator iter;

    for(unsigned int i = 0; i < N; i++)
    {
        L.push_back(empty);
        Lt.push_back(empty);
        for(unsigned int k = 0; k < mesh.v[i+1].neighbors.size(); k++)
        {
            unsigned int j = mesh.v[i+1].neighbors[k];
            if((j-1) < i)
            {
                int el;
                omega = mesh.omega(i+1, j, &el);
                //omega = mesh.omega(i+1, j);
                if((omega != 0.0) /*&& !eliminated[i]*/)
                {
                    double w = omega * WL;
                    L[i][j-1] = w;
                    L[j-1][i] = w;
                    omegaSum -= w;

                    //L[j-1][j-1] -= w;
                }
                else if(el != -1)
                {
                   /* if(!eliminated[i])
                    {
                        eliminated[i] = true;
                        WH[i] = 10.0;
                        B[i] *= (WH[i] * WH[i]); 
                        B[i+(N)] *= (WH[i] * WH[i]); 
                        B[i+(2*N)] *= (WH[i] * WH[i]); 
                    }
                    if(!eliminated[j-1])
                    {
                        eliminated[j-1] = true;
                        WH[j-1] = 10.0;
                        B[j-1] *= (WH[j-1] * WH[j-1]); 
                        B[j-1+(N)] *= (WH[j-1] * WH[j-1]); 
                        B[j-1+(2*N)] *= (WH[j-1] * WH[j-1]); 
                    }
                    if(!eliminated[el-1])
                    {
                        eliminated[el-1] = true;
                        WH[el-1] = 10.0;
                        B[el-1] *= (WH[el-1] * WH[el-1]); 
                        B[el-1+(N)] *= (WH[el-1] * WH[el-1]); 
                        B[el-1+(2*N)] *= (WH[el-1] * WH[el-1]); 
                    }*/

                    // Eliminate lines i, j-1 and el-1
                    if(!eliminated[i])
                    {
                        /*for(iter = L[i].begin(); iter != L[i].end(); iter ++)
                        {
                            if(iter->first >= i)
                                break;
                            L[iter->first][iter->first] += iter->second;
                        }*/
                        eliminated[i] = true;
                        count++;
                    }
                    if(!eliminated[j-1])
                    {
                       /* for(iter = L[j-1].begin(); iter != L[j-1].end(); iter ++)
                        {
                            if(iter->first >= j-1)
                                break;
                            L[iter->first][iter->first] += iter->second;
                        }*/
                        eliminated[j-1] = true;
                        count++;
                    }
                    if(!eliminated[el-1])
                    {
                        /*if((el - 1) < i)
                        {
                            for(iter = L[el-1].begin(); iter != L[el-1].end(); iter ++)
                            {
                                if(iter->first >= el-1)
                                    break;
                                L[iter->first][iter->first] += iter->second;
                            }
                        }*/
                        eliminated[el-1] = true;
                        count++;
                    }
                    
                }
            }
        }
        L[i][i] = omegaSum;
        omegaSum = 0.0;        
    } 
   /* eliminated[0] = true;
    eliminated[1] = true;
    eliminated[2] = true;
    eliminated[3] = true;
    eliminated[4] = true;
    eliminated[5] = true;*/
    /*eliminated[55] = true;*/
    //eliminated[9993] = true;
   /* WH[9993] = 100.0;
    B[9993] *= (WH[9993] * WH[9993]); 
    B[9993+(N)] *= (WH[9993] * WH[9993]); 
    B[9993+(2*N)] *= (WH[9993] * WH[9993]); */
    /*eliminated[56] = true;
    WH[56] = 100.0;
    B[56] *= (WH[56] * WH[56]); 
    B[56+(N)] *= (WH[56] * WH[56]); 
    B[56+(2*N)] *= (WH[56] * WH[56]);
    eliminated[57] = true;
    WH[57] = 100.0;
    B[57] *= (WH[57] * WH[57]); 
    B[57+(N)] *= (WH[57] * WH[57]); 
    B[57+(2*N)] *= (WH[57] * WH[57]);*/
   

    for(unsigned int i = 0; i < N; i++)
    {
        for(iter = L[i].begin(); iter != L[i].end(); iter++)
        {
            if(iter->first >= i)
                break;
            L[iter->first][iter->first] -= iter->second;
        }     
    }

   /* for(unsigned int i = 0; i < N; i++)
    {
        if(!eliminated[i])
        {
            for(iter = L[i].begin(); iter != L[i].end(); iter++)
            {
                Lt[iter->first][i] = iter->second;
            }
        }
    }*/

  

    /*cout << "maxCos: " << mesh.maxCos << endl;  
    cout << "minCos: " << mesh.minCos << endl; */ 
    cout << "count1: " << count << endl;
    for(unsigned ggg = 0; ggg < N; ggg ++)
    {
        if(eliminated[ggg])
        {
            cout << ggg + 1 << endl;
            cout << mesh.v[ggg+1].pos.x << " " << mesh.v[ggg+1].pos.y << " " << mesh.v[ggg+1].pos.z << endl;
        }
    } 

    /*cout << "L" << endl;
    for(unsigned int i = 0; i < N; i++)
    {
        for(iter = L[i].begin(); iter != L[i].end(); iter++)
        {
            cout << "[" << iter->first << "]: "<< iter->second << " ";
        }
        cout << endl;
    }*/

    cout << "starting CalcAtA..." << endl;
    unsigned int index = 0;
    double mult;
    nnz = 0;
    map<int, bool> done;
    unsigned int neighbor;
    
    while(index < N)
    {
        done.clear();
        AtA.push_back(empty);
        for(unsigned int j = 0; j < mesh.v[index+1].neighbors.size(); j++)
        {
            for(unsigned int k = 0; k < mesh.v[mesh.v[index+1].neighbors[j]].neighbors.size(); k++)
            {
                neighbor = mesh.v[mesh.v[index+1].neighbors[j]].neighbors[k] - 1;
                if(!done[neighbor] && neighbor <= index)
                {
                    mult = MultLinePerCol(index, neighbor);
                    if(!Equal(mult, 0.0))
                    {
                        nnz++;
                        AtA[index][neighbor] = mult;
                        AtA[neighbor][index] = mult;
                    }
                    done[neighbor] = true;
                }
            }
            neighbor = mesh.v[index+1].neighbors[j] - 1;
            if(!done[neighbor] && neighbor <= index)
            {
                mult = MultLinePerCol(index, neighbor);
                if(!Equal(mult, 0.0))
                {
                    nnz++;
                    AtA[index][neighbor] = mult;
                    AtA[neighbor][index] = mult;                    
                }
                done[neighbor] = true;
            }                 
        }
        if(!done[index])
        {
            mult = MultLinePerCol(index, index);
            if(!Equal(mult, 0.0))
            {
                nnz++;
                AtA[index][index] = mult; 
            }
        }
        AtA[index][index] += (WH[index] * WH[index]); 
               
        if(Equal(AtA[index][index], WH[index] * WH[index]))
            nnz++;        
        index++;
    } 
   
    cout << "AtA" << endl;
   /* for(iter = AtA[9993].begin(); iter != AtA[9993].end(); iter++)
    {
        cout << "[" << iter->first << "]: "<< iter->second << " ";
    }*/
    /*for(unsigned int i = 0; i < N; i++)
    {
        for(iter = AtA[i].begin(); iter != AtA[i].end(); iter++)
        {
            cout << "[" << iter->first << "]: "<< iter->second << " ";
        }
        cout << endl;
    }*/

    A = taucs_ccs_create(N, N, nnz, TAUCS_DOUBLE | TAUCS_SYMMETRIC | TAUCS_LOWER);
    
    CompactMatrix(); 
    
    cout << "matrices created." << endl;     
}

void DrawGrid(void)
{
    glBegin(GL_LINES);
	for(float i = -30.0f; i <= 30.0f; i += 1.0)
	{
        if(i == 0)
            glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
        else
            glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
      
		glVertex3f(i, -30.0f, 0.0f);
        glVertex3f(i, 30.0f, 0.0f);
        
        if(i == 0)
            glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
        else
            glColor4f(0.0f, 0.0f, 0.0f, 1.0f);

		glVertex3f(30.0f, i, 0.0f);
        glVertex3f(-30.0f, i, 0.0f);
	}
	glEnd();
}

bool Equal(double a, double b)
{
    if(fabs(a - b) < EPSILON)
        return true;
    return false;
}

void exit_func(void)
{
    TwTerminate();
    glDeleteFramebuffersEXT(1, &(fbo));
    glDeleteRenderbuffersEXT(1, &(depthBuffer));
    glDeleteBuffers(1,&(idMesh)); 
    glDeleteBuffers(1,&(idMeshEdge));
}

void TW_CALL GetCallback(void *value, void *clientData)
{
	int ID = *(int*)(clientData);
	switch(ID)
	{		
        case 402 : // Groups
            *(int *)value = currGroup;
            break;
        case 104 : // Functions
            *(int *)value = selectedFunc;
            break;
	}		
}

COLOR GetColor(int index)
{
    switch(index)
    {
        case 0:
            return white;
            break;
        case 1:
            return black;
            break;
        case 2:
            return red;
            break;
        case 3:
            return green;
            break;
        case 4:
            return blue;
            break;
        case 5:
            return yellow;
            break;
        case 6: 
            return magenta;
            break;
        default:
            return cyan;
            break;
    }
}

bool GLInit(int w, int h)
{
    if (GLEW_EXT_framebuffer_object)
    {
        // Create framebuffer
        glGenFramebuffersEXT(1, &fbo);
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
        
        // Create depthbuffer
        glGenRenderbuffersEXT(1, &depthBuffer);
        glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, depthBuffer);

        // Format depthbuffer and connect it to the framebuffer
        glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, w, h);
        glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, depthBuffer);
        
        // Create normal texture        
        glGenTextures(1, &normalMap);
        glBindTexture(GL_TEXTURE_2D, normalMap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F_ARB,  w, h, 0, GL_RGB, GL_FLOAT, NULL);    
    
        // Connect the normal texture to the framebuffer
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, normalMap, 0);

        GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
        if(status != GL_FRAMEBUFFER_COMPLETE_EXT)
        {
            cout << "status" << status << endl;
        }  
    } 

    

	// Set viewport
	glViewport(0, 0, w, h);	
    mainWindowHeight = h;
    mainWindowWidth = w;    

	// Set up projection matrix
	glMatrixMode(GL_PROJECTION);							
	// Reset matrix
	glLoadIdentity();	
	// Set perspective
	gluPerspective(5.0f, (float)w/(float)h, 5.0f, 100.0f);	
	// Load identity modelview
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Set colors
	glClearColor(	mainBgColor.r,
					mainBgColor.g,
					mainBgColor.b,
					mainBgColor.a);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	// Shading
	glShadeModel(GL_FLAT);
	// Depth
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
    
    glAlphaFunc(GL_GREATER, 0);

	// Set pointer to the screen center
	glutWarpPointer(400, 300);
	// Cull back face
	glEnable(GL_CULL_FACE);

    SetLights();  
    SetShaders(); 
    glGenBuffers(1, &idMesh);
    glGenBuffers(1, &idMeshEdge);

	return true;
}

void Keyboard_Main(unsigned char key, int x, int y)
{
	if( !TwEventKeyboardGLUT(key, x, y) )  // send event to AntTweakBar
    {
		switch(key)
		{
			case 27:
				exit(0);
				break;           
		}
	}
    glutPostRedisplay();
}

bool LoadFileNames(void)
{
    ifstream fileName("../../Models/meshes.txt", ios::in);
	if (!fileName)
		return false;
    string name;
    nMeshes = 0;
    nameOpt.append("label='File name' val='0 {None");
    nameOpt.append("}");
    fileNames.clear();
    fileNames.push_back(name);
    char buff[50];
	while(fileName >> name)
    {
        nMeshes++;
        nameOpt.append(", ");
        _itoa_s(nMeshes, buff, 10);
        nameOpt.append(buff);
        nameOpt.append(" {");
        nameOpt.append(name);
        nameOpt.append("}");
        fileNames.push_back(name);
    }
    nameOpt.append("'");
	fileName.close();

	return true;
}

int main(int argc, char** argv)				
{
    _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

    // Initialize variables
    spaceMaster = 0.05f;
    widthMaster = 0.05f;
    silMaster = 0.1f;  
    lastx = 0;
    lasty = 0;
    buttons[0] = 0;
    buttons[1] = 0;
    buttons[2] = 0;
	currFile = 0;
    currGroup = 0;
    nMeshes = 0;
    hasModel = false;
    doingSketch = false;
    doingROISketch = false;
    editingCP = false;
    mainBgColor = white;
	camZoom = 30.0f;
	camTX = 0.0f;
    camTY = 0.0f;
    camScale = 1.0f;
	camRotX = 0.0f;
    camRotY = 0.0f;
    funcTX = 0.0f;
	drawModel = true;
   	mainWindowWidth = 1052;
	mainWindowHeight = 789;
    nSkeletons = 0;
    selectedCP = 0;
    silMAX = 1.0;
    showFuncWindow = false;
    maxWidthFuncWindow = 210.0;
    editingCP = false;

    // Initialize GLUT
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    // Create main window
    glutInitWindowPosition(10, 10);
    glutInitWindowSize(mainWindowWidth, mainWindowHeight); 
    mainWindow = glutCreateWindow("Perspective Contouring");

    // Set glut callbacks
	glutMouseFunc(Mouse_Main);
	glutMotionFunc(Motion_Main);
	glutPassiveMotionFunc(PassMotion_Main);
	glutKeyboardFunc(Keyboard_Main);
	glutSpecialFunc(Special_Main);
    glutDisplayFunc(Render_Main);
	glutReshapeFunc(Reshape_Main);	
	TwGLUTModifiersFunc(glutGetModifiers);    
    	

        // Initialize AntTweakBar
	TwInit(TW_OPENGL, NULL);
	TwWindowSize(mainWindowWidth, mainWindowHeight);
    
 
    atexit(exit_func);
	
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));      
    }
	
	// Call other initialization functions 
	LoadFileNames();
	CreateInterface();
    GLInit(mainWindowWidth, mainWindowHeight);

	// Main loop			
	glutMainLoop();
   
	return 0;								
}

void Motion_Main(int x,int y)
{
	if( !TwEventMouseMotionGLUT(x, y) )  // send event to AntTweakBar
    { 
		// Get difference between this position and last one
		int diffx = x - lastx;
		int diffy = y - lasty;

		// Update last position aquired
		lastx = x;
		lasty = y; 
       

       // Rotation
        if(buttons[0] && !buttons[1] && !buttons[2] && !doingSketch && !editingCP)
		{
            camRotX += (float) 0.5f * diffy;
			camRotY += (float) 0.5f * diffx;	
            glutPostRedisplay();
            return;
        }

        // Translation
        if(buttons[1] && !buttons[0] && !buttons[2] && !doingSketch)
        {
            camTX += (float) 0.05f * diffx;
			camTY -= (float) 0.05f * diffy;
            glutPostRedisplay();
            return;
        }

        // Zooming
        if(buttons[2] && !buttons[0] && !buttons[1] && !doingSketch)
		{
			camZoom -= (float) 0.05f * diffx;
            glutPostRedisplay();
            return;
		}	
	}
	glutPostRedisplay();
}

void Mouse_Main(int b,int s,int x,int y)
{
	if( !TwEventMouseButtonGLUT(b, s, x, y) )  // send event to AntTweakBar
    {	
		// Update last position selected
		lastx = x;
		lasty = y;

		// Get modifiers
		int specialKey = glutGetModifiers();		
		
		// Check which button was pressed
		switch(b)
		{
			case GLUT_LEFT_BUTTON: // if left
               

                buttons[0] = ((GLUT_DOWN==s)?1:0); // Update state of the button (used in the motion function)
				break;
			case GLUT_MIDDLE_BUTTON: // if middle
				buttons[1] = ((GLUT_DOWN==s)?1:0); // just update the state (there's no selection with this button)
				break;
			case GLUT_RIGHT_BUTTON: // if right				
				buttons[2] = ((GLUT_DOWN==s)?1:0); // Update the button state
				break;
			default:
				break;		
		}		
	}
	glutPostRedisplay();
}

double MultLinePerCol(unsigned int i, unsigned int j)
{
    double result = 0.0;
    map<int, double>::iterator iter;
    //iter = Lt[i].begin();
    //for(iter = Lt[i].begin(); iter != Lt[i].end(); iter++)
    //{
    //    if((!Equal(Lt[j][iter->first], 0.0))/* && (!eliminated[iter->first])*/)
    //    {
    //        result += iter->second * Lt[j][iter->first];
    //    }
    //}

    iter = L[i].begin();
    for(iter = L[i].begin(); iter != L[i].end(); iter++)
    {
        if((!Equal(L[j][iter->first], 0.0)) && (!eliminated[iter->first]))
        {
            result += iter->second * L[j][iter->first];
        }
    }
    return result;
}

void PassMotion_Main(int x,int y)
{
	if( !TwEventMouseMotionGLUT(x, y) )  // send event to AntTweakBar
    {
		// Nothing to write here!
	}
    TwDraw();
    glutSwapBuffers();
}

void PrintProgramInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

	glGetProgramiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 0)
    {
        //infoLog = (char *)malloc(infologLength);
        infoLog = new char[infologLength];
        glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("%s\n",infoLog);
        delete[] infoLog;
    }
}

void PrintShaderInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

    glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 0)
    {
        //infoLog = (char *)malloc(infologLength);
        infoLog = new char[infologLength];
        glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog); 
        printf("%s\n",infoLog);
        delete[] infoLog;
    }
}

void Render_Main()
{
    // Clear background
	glClearColor(	mainBgColor.r,
					mainBgColor.g,
					mainBgColor.b,
					mainBgColor.a);  

    glEnable (GL_BLEND); glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    
   
	// Set camera position
    glMatrixMode(GL_MODELVIEW); 
    glPushMatrix();
	glLoadIdentity();  

    //glTranslatef(mesh.getCenterX(), mesh.getCenterY(), mesh.minVert.z);// - ((mesh.maxVert.x - mesh.minVert.x) * (mesh.maxVert.y - mesh.minVert.y))*20.0f);
    glTranslatef(camTX,camTY,-camZoom);
       
    
    glRotatef(camRotY,0,1,0);
    glRotatef(camRotX,1,0,0);
    glScalef(scaleFactor, scaleFactor, scaleFactor);
    glScaled(camScale, camScale, camScale);

   /* if(!skeletons.empty())
    {
        for(unsigned int i = 0; i < skeletons[selectedSkeleton].silVertices.size(); i++)
        {
            glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
            glPointSize(4.0f);
            glBegin(GL_POINTS);
            glVertex3fv(mesh.v[skeletons[selectedSkeleton].silVertices[i]].pos);
            glEnd();
            glPointSize(1.0f);
        }
    }*/
    
   
     

   

    /*if(!skeletons.empty())
    {
        if(!skeletons[0].ROIs.empty())
        {

            glLineWidth(2.0);
            glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

            glBegin(GL_LINE_STRIP);
                for(unsigned int k = 0; k < skeletons[0].sections[skeletons[0].ROIs[0].first].vertices.size(); k++)
                {
                    glVertex3fv(skeletons[0].sections[skeletons[0].ROIs[0].first].vertices[k].position);
                }
                if(skeletons[0].sections[skeletons[0].ROIs[0].first].closed)
                    glVertex3fv(skeletons[0].sections[skeletons[0].ROIs[0].first].vertices[0].position);
            glEnd();

            glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
            glBegin(GL_LINE_STRIP);
                for(unsigned int k = 0; k < skeletons[0].sections[skeletons[0].ROIs[0].last].vertices.size(); k++)
                {
                    glVertex3fv(skeletons[0].sections[skeletons[0].ROIs[0].last].vertices[k].position);
                }
                if(skeletons[0].sections[skeletons[0].ROIs[0].last].closed)
                    glVertex3fv(skeletons[0].sections[skeletons[0].ROIs[0].last].vertices[0].position);
            glEnd();

            glLineWidth(1.0);
        }
    }*/
   

   



   /* for(unsigned int k = 0; k < skeletons.size(); k++)
    {
        for(unsigned int i = 0; i < skeletons[k].sectionsToRender.size(); i++)
        {
            glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
            glBegin(GL_TRIANGLE_STRIP);
            for(unsigned int j = 0; j < skeletons[k].sections[skeletons[k].sectionsToRender[i].index].vertices.size(); j++)
            {
                glVertex3fv(skeletons[k].sections[skeletons[k].sectionsToRender[i].index].vertices[j].position - skeletons[k].sectionsToRender[i].width * skeletons[k].sections[skeletons[k].sectionsToRender[i].index].vertices[j].binormal);   
                glVertex3fv(skeletons[k].sections[skeletons[k].sectionsToRender[i].index].vertices[j].position + skeletons[k].sectionsToRender[i].width * skeletons[k].sections[skeletons[k].sectionsToRender[i].index].vertices[j].binormal);              

            }
                glVertex3fv(skeletons[k].sections[skeletons[k].sectionsToRender[i].index].vertices[0].position - skeletons[k].sectionsToRender[i].width * skeletons[k].sections[skeletons[k].sectionsToRender[i].index].vertices[0].binormal);   
                glVertex3fv(skeletons[k].sections[skeletons[k].sectionsToRender[i].index].vertices[0].position + skeletons[k].sectionsToRender[i].width * skeletons[k].sections[skeletons[k].sectionsToRender[i].index].vertices[0].binormal);              
            glEnd();
        }
    }*/

    //if(skeleton.size() > 0)
    //{
    //    //glUseProgram(phongShader);
    //    glPolygonMode(GL_FRONT, GL_LINE);
    //    glColor4f(0.0, 0.0, 0.0, 1.0);
    //    glBegin(GL_TRIANGLES);
    //    for(unsigned int i = 0; i < mesh.f.size(); i++)
    //    {
    //        for(unsigned int j = 0; j < mesh.f[i].v.size(); j++)
    //        {
    //           /* if((mesh.f[i].v[j] - 1) == 9994)
    //                glColor4f(1.0, 0.0, 0.0, 1.0);
    //            else if((mesh.f[i].v[j] - 1) == 9996)
    //                glColor4f(0.0, 1.0, 0.0, 1.0);
    //            else if((mesh.f[i].v[j] - 1) == 1878)
    //                glColor4f(0.0, 0.0, 1.0, 1.0);
    //            else if((mesh.f[i].v[j] - 1) == 10002)
    //                glColor4f(1.0, 0.0, 1.0, 1.0);
    //            else 
    //                glColor4f(0.0, 0.0, 0.0, 1.0);*/

    //            glVertex3f(skeleton[(mesh.f[i].v[j] - 1)].x, skeleton[(mesh.f[i].v[j] - 1)].y, skeleton[(mesh.f[i].v[j] - 1)].z);
    //        }
    //    }
    //    glEnd();
    //    glPointSize(10.0);
    //    
    //    glBegin(GL_POINTS);
    //        glColor4f(1.0, 0.0, 0.0, 1.0);
    //        glVertex3f(skeleton[9993].x, skeleton[9993].y, skeleton[9993].z);
    //       /* glColor4f(0.0, 1.0, 0.0, 1.0);
    //        glVertex3f(skeleton[1877].x, skeleton[1877].y, skeleton[1877].z);
    //        glColor4f(0.0, 0.0, 1.0, 1.0);
    //        glVertex3f(skeleton[1880].x, skeleton[1880].y, skeleton[1880].z);
    //        glColor4f(1.0, 1.0, 0.0, 1.0);
    //        glVertex3f(skeleton[9995].x, skeleton[9995].y, skeleton[9995].z);
    //        glColor4f(1.0, 0.0, 1.0, 1.0);
    //        glVertex3f(skeleton[10001].x, skeleton[10001].y, skeleton[10001].z);
    //        glColor4f(0.0, 1.0, 1.0, 1.0);
    //        glVertex3f(skeleton[9987].x, skeleton[9987].y, skeleton[9987].z);*/
    //       /* glColor4f(1.0, 0.0, 0.0, 1.0);
    //        glVertex3f(skeleton[55].x, skeleton[55].y, skeleton[55].z);
    //        glColor4f(0.0, 1.0, 0.0, 1.0);
    //        glVertex3f(skeleton[56].x, skeleton[56].y, skeleton[56].z);
    //        glColor4f(0.0, 0.0, 1.0, 1.0);
    //        glVertex3f(skeleton[57].x, skeleton[57].y, skeleton[57].z);*/
    //    glEnd();
    //        

    //    //glUseProgram(0);

    //   /* glColor4f(0.0, 0.0, 1.0, 1.0); 
    //    glBegin(GL_LINES);
    //    for(unsigned int i = 0; i < mesh.f.size(); i++)
    //    {
    //        for(unsigned int j = 0; j < mesh.f[i].v.size(); j++)
    //        {
    //            glVertex3f(skeleton[(mesh.f[i].v[j] - 1)].x, skeleton[(mesh.f[i].v[j] - 1)].y, skeleton[(mesh.f[i].v[j] - 1)].z);
    //            glVertex3f(mesh.v[mesh.f[i].v[j]].pos.x, mesh.v[mesh.f[i].v[j]].pos.y, mesh.v[mesh.f[i].v[j]].pos.z);
    //        }
    //    }
    //    glEnd();*/       
    //}
   
    if(drawModel && hasModel)
    {
        glUseProgram(phongShader);
        mesh.draw(currGroup, idMesh, verticesSize, normalsSize, 1); 
        glUseProgram(0);
    }

	// Draw menu bars
	TwDraw(); 

    glPopMatrix();

	glutSwapBuffers();	
}

void Reset(void)
{
	//ResetCam();
	ResetDrawFlags();     
    nSkeletons = 0;                    
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}

void ResetCam(void)
{
	camZoom = 30.0;
	camTX = camTY = 0.0;
	camRotX = camRotY = 0.0;
    camScale = 1.0;
}

void ResetDrawFlags(void)
{
	
    drawModel = true;	
}

void Reshape_Main(int w, int h)
{
	if(h == 0)
		h = 1;	
    mainWindowHeight = h;
    mainWindowWidth = w;
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective( 5.0, (float)w/(float)h, 5.0f, 100.0f );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	// Pass the window size to AntTweakBar
	TwWindowSize(w, h);

    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
    // New depthbuffer
    glDeleteRenderbuffersEXT(1, &(depthBuffer));
    glGenRenderbuffersEXT(1, &depthBuffer);
    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, depthBuffer);
    glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, w, h);
    glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, depthBuffer);
        
    // New normal texture
    glDeleteTextures(1, &normalMap);
    glGenTextures(1, &normalMap);
    glBindTexture(GL_TEXTURE_2D, normalMap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F_ARB,  w, h, 0, GL_RGB, GL_FLOAT, NULL);
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, normalMap, 0);
    GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
    if(status != GL_FRAMEBUFFER_COMPLETE_EXT)
    {
        cout << "status " << status << endl;
    } 

    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);    
}

void TW_CALL SetCallback(const void *value, void *clientData)
{
	int ID = *(int*)(clientData);
	switch(ID)
	{	
        case 104 : // Function
           
            break;
        case 402 : // Group
            currGroup = *(const int *)value;
            if (currGroup == 0)
                VBOLoadFullModel();
            else
            {
                vector<float> vertices;
                vector<float> normals;
                vertices.clear();
                normals.clear();
                vector<FaceStruct>::const_iterator itFaceEnd;
                if(mesh.g.size() == currGroup)
                    itFaceEnd = mesh.f.end();
                else
                    itFaceEnd = mesh.f.begin() + mesh.g[currGroup].start;
                for (vector<FaceStruct>::const_iterator itFace = mesh.f.begin() + mesh.g[currGroup-1].start; itFace != itFaceEnd; ++itFace)
	            {
                    for(unsigned int i = 0; i < 3; i++)
                    {
                        vertices.push_back(mesh.v[(*itFace).v[i]].pos.x);
                        vertices.push_back(mesh.v[(*itFace).v[i]].pos.y);
                        vertices.push_back(mesh.v[(*itFace).v[i]].pos.z);
                    }  
                }          

                if(mesh.hasNormals())
                {
                    for (vector<FaceStruct>::const_iterator itFace = mesh.f.begin() + mesh.g[currGroup-1].start; itFace != itFaceEnd; ++itFace)
	                {
                        for(unsigned int i = 0; i < 3; i++)
                        {
                            normals.push_back(mesh.n[(*itFace).n[i]].x);
                            normals.push_back(mesh.n[(*itFace).n[i]].y);
                            normals.push_back(mesh.n[(*itFace).n[i]].z);
                        }                                                 
                    }
                }
                else
                {
                    for (vector<FaceStruct>::const_iterator itFace = mesh.f.begin() + mesh.g[currGroup-1].start; itFace != itFaceEnd; ++itFace)
	                {
                        for(unsigned int i = 0; i < 3; i++)
                        {
                            normals.push_back(mesh.v[(*itFace).v[i]].n.x);
                            normals.push_back(mesh.v[(*itFace).v[i]].n.y);
                            normals.push_back(mesh.v[(*itFace).v[i]].n.z);
                        }                                                 
                    }
                } 
                verticesSize = vertices.size();
                glBindBuffer(GL_ARRAY_BUFFER, idMesh);
                glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (vertices.size() + normals.size()), 0, GL_STATIC_DRAW);
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * vertices.size(), &vertices[0]);  
                glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), sizeof(GLfloat) * normals.size(), &normals[0]);               
            }

            break;
	}
}

void SetLights(void)
{
    map<int, double> m;
    map<int, double> n;
    map<int, double>::iterator iter;

    m[1] = 10.0;
    m[2] = 20.0;
    m[3] = 30.0;

    n[1] = 2.0;
    n[4] = 3.0;
    n[5] = 4.0;

    for(iter = m.begin(); iter != m.end(); iter++)
    {
        cout << n[iter->first] << endl;
    }

    // light 0
	GLfloat light_pos[] = {0.0f, 0.0f, 5.0f, 1.0f};
    GLfloat light_Ka[]  = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat light_Kd[]  = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat light_Ks[]  = {1.0f, 1.0f, 1.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);
	glEnable(GL_LIGHT0);

    GLfloat material_Ka[] = {0.3f, 0.3f, 0.1f, 0.3f};
    GLfloat material_Kd[] = {0.4f, 0.4f, 0.0f, 0.2f};
    GLfloat material_Ks[] = {0.6f, 0.6f, 0.1f, 0.1f};
    GLfloat material_Ke[] = {0.1f, 0.1f, 0.0f, 0.0f};
    GLfloat material_Se = 30.0f;

    

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_Se);	
}

void SetShaders(void)
{
	char *vsp, *fsp, *vsn, *fsn, *vss;

	vp = glCreateShader(GL_VERTEX_SHADER);
    vn = glCreateShader(GL_VERTEX_SHADER);
    vs = glCreateShader(GL_VERTEX_SHADER);
	fp = glCreateShader(GL_FRAGMENT_SHADER);	
    fn = glCreateShader(GL_FRAGMENT_SHADER);

	vsp = textFileRead("VS_Phong.txt");
    vsn = textFileRead("VS_Normals.txt");
    vss = textFileRead("VS_Sil.txt");
	fsp = textFileRead("FS_Phong.txt");
    fsn = textFileRead("FS_Normals.txt");

	const char * vvp = vsp;
    const char * vvn = vsn;
    const char * vvs = vss;
	const char * ffp = fsp;
    const char * ffn = fsn;

	glShaderSource(vp, 1, &vvp,NULL);
    glShaderSource(vn, 1, &vvn,NULL);
    glShaderSource(vs, 1, &vvs,NULL);
	glShaderSource(fp, 1, &ffp,NULL);
    glShaderSource(fn, 1, &ffn,NULL);

	taucs_free(vsp);taucs_free(vsn);taucs_free(vss);taucs_free(fsp);taucs_free(fsn);

	glCompileShader(vp);
    cout << "InfoLog of phong vertice shader:" << endl; 
    PrintShaderInfoLog(vp);
    glCompileShader(vn);
    cout << "InfoLog of normalMap vertice shader:" << endl; 
    PrintShaderInfoLog(vn);
    glCompileShader(vs);
    cout << "InfoLog of Sil vertice shader:" << endl; 
    PrintShaderInfoLog(vs);
	glCompileShader(fp);
    cout << "InfoLog of phong fragment shader:" << endl;
    PrintShaderInfoLog(fp);
    glCompileShader(fn);
    cout << "InfoLog of normalMap fragment shader:" << endl;
    PrintShaderInfoLog(fn);

	phongShader = glCreateProgram();
    normalMapShader = glCreateProgram();
    SilShader = glCreateProgram();
	
	glAttachShader(phongShader, vp);
    glAttachShader(phongShader, fp);
    glAttachShader(normalMapShader, vn);
    glAttachShader(normalMapShader, fn);
    glAttachShader(SilShader, vs);

	glLinkProgram(phongShader);
    cout << "InfoLog of phongShader program:" << endl;
    PrintProgramInfoLog(phongShader);
    glLinkProgram(normalMapShader);
    cout << "InfoLog of normalMapShader program:" << endl;
    PrintProgramInfoLog(normalMapShader);
    glLinkProgram(SilShader);
    cout << "InfoLog of SilShader program:" << endl;
    PrintProgramInfoLog(SilShader);
}

double* Solve(Mesh meshc)
{
    int i = 1;
    taucs_logfile("stdout");
    char* options[] = { "taucs.factor.LLT=true", NULL }; 
    while(i > 0)
    {
        if(taucs_linsolve(A, NULL, 3, X, B, options, NULL) != TAUCS_SUCCESS)
        {
            cout << "Solve failed!" << endl;
        }      
        UpdateMesh(&meshc);
        if(i > 1)
        {
           
            cout << "Update finished." << endl;
            UpdateWeights(&meshc);
            CalcL(&meshc);            
            CalcAtA(&meshc);
            taucs_ccs_free(A);
            A = taucs_ccs_create(N, N, nnz, TAUCS_DOUBLE | TAUCS_SYMMETRIC | TAUCS_LOWER);
            CompactMatrix();
            CalcB(&meshc);
        }               
        i--;
    } 
    L.clear();
    AtA.clear();  

    taucs_free(B);
    taucs_ccs_free(A);
    taucs_free(WH);

    return X;
}

void Special_Main(int key, int x, int y)
{
	if( !TwEventSpecialGLUT(key, x, y) )  // send event to AntTweakBar
    {
		// Nothing to write here!
	}
    glutPostRedisplay();
}

void UpdateMesh(Mesh* meshc)
{
    float MAXDist = 0.0f;
    int MAXi = -1;
    for(unsigned int i = 0; i < N; i++)
    {
        float dist = CalcDist(meshc->v[i+1].pos, VECTOR3D(X[i], X[i+N], X[i+(2*N)]));
        if(dist > MAXDist)
        {
            MAXDist = dist;
            MAXi = i;
        }
        //if(Equal(meshc->v[i+1].pos.x, X[i]) && Equal(meshc->v[i+1].pos.y, X[i+N]) && Equal(meshc->v[i+1].pos.z, X[i+(2*N)]))
        //{
        //    cout << "Equal: " << i+1 << endl;
        //   /* cout << meshc->v[i+1].pos.x << " " << X[i] << endl;
        //    cout << meshc->v[i+1].pos.y << " " << X[i+N] << endl;
        //    cout << meshc->v[i+1].pos.z << " " << X[i+(2*N)] << endl;*/
        //}
       
        meshc->v[i+1].pos.x = X[i];
        meshc->v[i+1].pos.y = X[i+N];
        meshc->v[i+1].pos.z = X[i+(2*N)];
        meshc->v[i+1].currArea = 0.0;         
    } 
    cout << "MAXDist: " << MAXDist << ", i: " << MAXi + 1 << endl;
}

void UpdateWeights(Mesh* meshc)
{
    WL *= 2.0;
    double smallerArea = 10000.0;
    double biggestWH = 0.0;
    double smallestWH = 10000.0;
    int biggestWHindex = -1;
    int smallestWHindex = -1;
    meshc->UpdateOneRingAreas();
    for(unsigned int i = 0; i < N; i++)
    {
        if(meshc->v[i+1].currArea < smallerArea)
            smallerArea = meshc->v[i+1].currArea;
            //cout << "currArea: " << meshc->v[i+1].currArea << "v: " << i+1 << endl;
        //if(!eliminated[i])
        /*{*/
            //if(meshc->v[i+1].currArea >= 0.00001)
                WH[i] = sqrt(meshc->v[i+1].area/meshc->v[i+1].currArea);
            /*else
                WH[i] = 100.0;*/

            /*if(WH[i] > 1.5)
                WH[i] = 1.5;*/
        /*}*/
        /*else
            WH[i] = 1.0;*/
        if(WH[i] > biggestWH)
        {
            biggestWH = WH[i];
            biggestWHindex = i;
        }
        if(WH[i] < smallestWH)
        {
            smallestWH = WH[i];
            smallestWHindex = i;
        }
    }
    //cout << "smallerArea: " << smallerArea << endl;
    cout << "biggestWH: " << biggestWH << ", index: " << biggestWHindex << endl;
    cout << "smallestWH: " << smallestWH << ", index: " << smallestWHindex << endl;
}

void VBOLoadFullModel(void)
{
    vector<float> vertices;
    vector<float> normals;
    vector<float> colors;
    vertices.clear();
    normals.clear();
    colors.clear();
    for(unsigned int i = 0; i < mesh.f.size(); i++)
    {
        for(unsigned int j = 0; j < 3; j++)
        {
            vertices.push_back(mesh.v[mesh.f[i].v[j]].pos.x);
            vertices.push_back(mesh.v[mesh.f[i].v[j]].pos.y);
            vertices.push_back(mesh.v[mesh.f[i].v[j]].pos.z);
        }                                          
    }

    if(mesh.hasNormals())
    {
        for(unsigned int i = 0; i < mesh.f.size(); i++)
        {
            for(unsigned int j = 0; j < 3; j++)
            {
                normals.push_back(mesh.n[mesh.f[i].n[j]].x);
                normals.push_back(mesh.n[mesh.f[i].n[j]].y);
                normals.push_back(mesh.n[mesh.f[i].n[j]].z);
            }                                                 
        }
    }
    else
    {
        for(unsigned int i = 0; i < mesh.f.size(); i++)
        {
            for(unsigned int j = 0; j < 3; j++)
            {
                normals.push_back(mesh.v[mesh.f[i].v[j]].n.x);
                normals.push_back(mesh.v[mesh.f[i].v[j]].n.y);
                normals.push_back(mesh.v[mesh.f[i].v[j]].n.z);
            }                                                 
        }
    } 

    for(unsigned int i = 0; i < mesh.f.size(); i++)
    {
        for(unsigned int j = 0; j < 3; j++)
        {            
            COLOR color = GetColor(mesh.v[mesh.f[i].v[j]].skIndex);
            colors.push_back(color.r);
            colors.push_back(color.g);
            colors.push_back(color.b);
        }                                          
    }

    verticesSize = vertices.size();
    normalsSize = normals.size();
    glBindBuffer(GL_ARRAY_BUFFER, idMesh);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (vertices.size() + normals.size() + colors.size()), 0, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * vertices.size(), &vertices[0]);  
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), sizeof(GLfloat) * normals.size(), &normals[0]);  
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (vertices.size() + normals.size()), sizeof(GLfloat) * colors.size(), &colors[0]);
}





































