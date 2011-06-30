#ifndef ___TAUCS_INTERFACE_OLGA
#define ___TAUCS_INTERFACE_OLGA
#include "taucsaddon.h"

// has to be called in the beginning before starting to work with the library
void InitTaucsInterface(bool enableLog = false);

// initializes a new matrix; returns the matrix ID
// if isSPD is true, the matrix is going to be symmetric positive definite, and only
// lower triangle values will be taken into account when building the matrix
// (so there is no need to fill in the upper triangle, but it is possible)
int  CreateMatrix(const int numRows, const int numCols, const bool isSPD = false);
// releases the matrix 
void ReleaseMatrix(const int id);

// has to be called in the end after finishing working with the library
void DeinitTaucsInterface();

// adds a new entry to the sparse matrix A
// i and j are 0-based
// if the A^T A matrix had been factored, this will destroy the factor
void SetMatrixEntry(const int id, const int i, const int j, const taucsType v);

// updates the entry in A by adding the value v to the current value
// it is assumed the entry is there already; otherwise it is though of as 0
// i and j are 0-based
// if the A^T A matrix had been factored, this will destroy the factor
void AddToMatrixEntry(const int id, const int i, const int j, const taucsType v);

// explicitly states that the matrix is spd or not
bool SetSPD(const int id, const bool isSPD);

// allows to add an anchored vertex without destroying the factor, if there was one
// i is the anchor's number (i.e. the index of the mesh vertex that is anchored is i)
// w is the weight of the anchor in the original Ax=b system. HAS TO BE POSITIVE!!
// if there was no factor for A^T A, this will simply add an anchor row to the Ax=b system
// if there was a factor, the factor will be updated, approximately at the cost of
// a single solve.
void AddAnchor(const int id, const int i, const taucsType w);


// Will create A^T A and its factorization, as well as store A^T
// returns true on success, false otherwise
bool FactorATA(const int id);

// Solves the normal equations for Ax = b, namely A^T A x = A^T b
// it is assumed that enough space is allocated in x
// If a factorization of A^T A exists, it will be used, otherwise it will be created
// numRhs should be the the number of right-hand sides stored in b (and respectively,
// there should be enough space allocated in the solution vector x)
// returns true on success, false otherwise
bool SolveATA(const int id, const taucsType * b, taucsType * x, const int numRhs); 

// Factors the A matrix alone. Assumes that A is square. If A is spd then Cholesky factoring is applied; otherwise LU
bool FactorA(const int id);

// Solve the square system Ax = b
// It is assumed that A is square and invertible;
bool SolveA(const int id, const taucsType * b, taucsType * x, const int numRhs); 

// The version of SolveATA with 3 right-hand sides
// returns true on success, false otherwise
bool SolveATA3(const int id, const taucsType * bx, const taucsType * by, const taucsType * bz,
								   taucsType * x,        taucsType * y,        taucsType * z);

// The version of SolveATA with 2 right-hand sides
// returns true on success, false otherwise
bool SolveATA2(const int id, const taucsType * bx, const taucsType * by,
								   taucsType * x,        taucsType * y);
/*
The following three functions are used to solve LS systems with different A matrices, 
which however have the same non-zero structure.
To speed up the factorization step, we can precompute the symbolic factor part.

Assume A1, A2, A3,... are matrices with the same non-zero pattern. The order of action should be:

// create the A1 matrix, fill in its entries
// now, first creation of the symbolic factor:
int idSymbFactorA1 = SymbolicFactor(idA1);

// factor A1 and use the factor to solve the system
FactorATA_UseSymbolic(idA1, idSymbFactorA1);

// Use the A1 factor for as many solves as you need...
SolveATA_UseFactor(idA1, idSymbFactorA1, b, x, 3);
// . . .

// now reuse the factor for another matrix A2 with the same nonzero structure:
FactorATA_UseSymbolic(idA2, idSymbFactorA1);
// from now on idSymbFactorA1 can only be used for A2 solves, until we numerically
// refactor for another matrix

SolveATA_UseFactor(idA2, idSymbFactorA1);
// . . . as many times as needed

// reuse again: can also change values of existing matrix!
SetMatrixEntry(idA2, 0, 0, 17);
...
FactorATA_UseSymbolic(idA2, idSymbFactorA1);
SolveATA_UseFactor(idA2, idSymbFactorA1);
// . . . as many times as needed

*/

// Will create *symbolic* factorization of ATA and store it aside
// returns the id of the factor stored, to be used later to factor; -1 if failed
// other matrices with the same zero structure
int SymbolicFactorATA(const int matrixId);

// Will create the actual numerical factorization of the given ATA matrix
// provided the symbolic factor with id factorId
bool FactorATA_UseSymbolic(const int matrixID, const int symbFactorId);

// Will solve the LS system using the precomputed factor
bool SolveATA_UseFactor(const int matrixId, const int factorId, const taucsType * b, taucsType * x, const int numRhs); 

// will free the factor
void ReleaseFactor(const int factorId);


// Vector functions

// VectorAdd stores the result of v1 + v2 in result; assumes all the three vectors
// have allocated size of length elements
// result may be the same pointer as v1 or v2
void VectorAdd(const taucsType * v1, const taucsType * v2, taucsType * result, int length);

// VectorSubtract stores the result of v1 - v2 in result; assumes all the three vectors
// have allocated size of length elements
// result may be the same pointer as v1 or v2
void VectorSubtract(const taucsType * v1, const taucsType * v2, taucsType * result, int length);

// Stores the result of Matrix*v in result.
// v can have numCols columns; then the result is stored column-wise as well
// This means that we can multiply several vectors by the same matrix in one function call.
// It is assumed space is allocated in result!
// v cannot be the same pointer as result
bool MultiplyMatrixVector(const int idMatrix, const taucsType * v, taucsType * result, const int numCols);

// Computes D*Matrix and stores the result in Res
// D holds the diagonal values
bool MultiplyDiagMatrixMatrix(const int idMatrix, const taucsType * D, const int idRes);

// Multiplies the A matrix by the given matrix B from the right
// and stores the result in the columns of res
// isSPD tells us whether the result should be SPD or not
bool MultiplyMatrixMatrix(const int idA, const int idB, const int idRes, const bool isSPD);

// Transposes the given matrix
// and stores the result in idRes
bool TransposeMatrix(const int idA, const int idRes);


// will remove the rows startInd-endInd (including ends, zero-based) from Matrix
// will discard any factors
bool DeleteRowRange(const int idMatrix, const int startInd, const int endInd);

// will remove the columns startInd-endInd (including ends, zero-based) from Matrix
// will discard any factors
bool DeleteColumnRange(const int idMatrix, const int startInd, const int endInd);

// copies columns startInd through endInd (including, zero-based) from A to B
// previous data in B, including factors, is erased.
bool CopyColumnRange(const int idA, const int startInd, const int endInd, const int idB); 

// copies rows startInd through endInd (including, zero-based) from A to B
// previous data in B, including factors, is erased.
bool CopyRowRange(const int idA, const int startInd, const int endInd, const int idB); 

bool MultiplyRows(const int idA, const int startInd, const int endInd, double val); 

// returns the dimensions of the queried matrix
bool GetAMatrixSize(const int idA, int & numRows, int & numCols);


#endif // ___TAUCS_INTERFACE_OLGA
