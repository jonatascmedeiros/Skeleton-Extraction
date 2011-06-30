#include "taucsaddon.h"

class SparseSolver {
protected:
	taucs_ccs_matrix * m_A;
	taucs_ccs_matrix * m_AT;
	taucs_ccs_matrix * m_ATA;

	// is set to true iff m_A is symmetric positive definite
	bool  m_SPD;

	void * m_factorATA;
	void * m_factorA;
	void * m_etree; // for the factor update
	
	// placeholder, so that we don't need to allocate space every time
	// the space is allocated when a factor for ATA is created
	std::vector<taucsType> m_ATb;

	// helper map to create A
	std::vector< std::map<int,taucsType> > m_colsA;

	// the dimensions of the A matrix
	int m_numRows;
	int m_numCols; 

public:

	SparseSolver(int numRows, int numCols, bool isSPD = false) 
		: m_A(NULL)
		, m_AT(NULL)
		, m_ATA(NULL)
		, m_ATb(NULL)
		, m_factorATA(NULL)
		, m_factorA(NULL)
		, m_etree(NULL)
		, m_numRows(numRows)
		, m_numCols(numCols)
		, m_colsA(numCols)
		, m_SPD(isSPD)
	{};

	~SparseSolver() { ClearObject();}

public:

	void ClearObject();

	// adds a new entry to the sparse matrix A
	// i and j are 0-based
	// if the A^T A matrix had been factored, this will destroy the factor
	void AddIJV(const int i, const int j, const taucsType v);

	// updates the entry in A by adding the value v to the current value
	// i and j are 0-based
	// if the A^T A matrix had been factored, this will destroy the factor
	void AddToIJV(const int i, const int j, const taucsType v);

	// Sets the status of a matrix - whether SPD or not
	void SetSPD(bool isSPD) {m_SPD = isSPD;}

	// allows to add an anchored vertex without destroying the factor, if there was one
	// i is the anchor's number (i.e. the index of the mesh vertex that is anchored is i)
	// w is the weight of the anchor in the original Ax=b system. HAS TO BE POSITIVE!!
	// if there was no factor for A^T A, this will simply add an anchor row to the Ax=b system
	// if there was a factor, the factor will be updated, approximately at the cost of
	// a single solve.
	void AddAnchor(const int i, const taucsType w);

	// Will create A^T A and its factorization, as well as store A^T
	// returns true on success, false otherwise
	bool FactorATA();

	// Will create A and its factorization. If A is spd then Cholesky factor, otherwise LU
	// returns true on success, false otherwise
	// Assumes A is square and invertible
	bool FactorA();
	// Will create *symbolic* factorization of ATA and return it; returns NULL on failure
	void * SymbolicFactorATA();

	taucs_ccs_matrix * GetATA_Copy();

	// Will create the actual numerical factorization of the present ATA matrix
	// with the same non-zero pattern as created by SymbolicFactorATA()
	bool FactorATA_UseSymbolic(void * symbFactor,
							  taucs_ccs_matrix ** PAP,
							  int * perm,
							  int * invperm);

	// Solves the normal equations for Ax = b, namely A^T A x = A^T b
	// it is assumed that enough space is allocated in x
	// Uses the factorization provided in factor
	// numRhs should be the the number of right-hand sides stored in b (and respectively,
	// there should be enough space allocated in the solution vector x)
	// returns true on success, false otherwise
	bool SolveATA_UseFactor(void * factor, 
							taucs_ccs_matrix * PAP,
							int * perm,
							int * invperm,
							const taucsType * b, taucsType * x, const int numRhs);

	// Solves the normal equations for Ax = b, namely A^T A x = A^T b
	// it is assumed that enough space is allocated in x
	// If a factorization of A^T A exists, it will be used, otherwise it will be created
	// numRhs should be the the number of right-hand sides stored in b (and respectively,
	// there should be enough space allocated in the solution vector x)
	// returns true on success, false otherwise
	bool SolveATA(const taucsType * b, taucsType * x, const int numRhs); 

	// Same as SolveATA only that this solves the actual system Ax = b
	// It is assumed that A is rectangular and invertible
	bool SolveA(const taucsType * b, taucsType * x, const int numRhs); 

	// The version of SolveATA with 3 right-hand sides
	// returns true on success, false otherwise
	bool SolveATA3(const taucsType * bx, const taucsType * by, const taucsType * bz,
						 taucsType * x,        taucsType * y,        taucsType * z);

	// The version of SolveATA with 2 right-hand sides
	// returns true on success, false otherwise
	bool SolveATA2(const taucsType * bx, const taucsType * by,
						 taucsType * x,        taucsType * y);

// Matrix utility routines

	// Stores the result of Matrix*v in result.
	// v can have numCols columns; then the result is stored column-wise as well
	// It is assumed space is allocaed in result!
	// v cannot be the same pointer as result
	void MultiplyMatrixVector(const taucsType * v, taucsType * result, const int numCols) const;

	// Multiplies the matrix by diagonal matrix D from the left, stores the result
	// in the columns of res
	void MultiplyDiagMatrixMatrix(const taucsType * D, SparseSolver & res) const;

	// Multiplies the matrix by the given matrix B from the right
	// and stores the result in the columns of res
	// isSPD tells us whether the result should be SPD or not
	// retuns false if the dimensions didn't match (in such case res is unaltered), otherwise true
	bool MultiplyMatrixRight(const SparseSolver & B, SparseSolver & res,const bool isSPD) const;

	// Transposes the matrix 
	// and stores the result in the columns of res
	bool Transpose(SparseSolver & res) const;

	// will remove the rows startInd-endInd (including ends, zero-based) from the matrix
	// will discard any factors	
	bool DeleteRowRange(const int startInd, const int endInd);

	// will remove the columns startInd-endInd (including ends, zero-based) from the matrix
	// will discard any factors	
	bool DeleteColumnRange(const int startInd, const int endInd);

	// copies columns startInd through endInd (including, zero-based) from the matrix to res matrix
	// previous data in res, including factors, is erased.
	bool CopyColumnRange(const int startInd, const int endInd, SparseSolver & res) const;

	// copies rows startInd through endInd (including, zero-based) from the matrix to res matrix
	// previous data in res, including factors, is erased.
	bool CopyRowRange(const int startInd, const int endInd, SparseSolver & res) const;

	bool MultiplyRows(const int startInd, const int endInd, const double val);

	// returns the dimensions of the A matrix
	void GetAMatrixSize(int & numRows, int & numCols) const;

protected:
	// Will create ATA matrix and AT matrix (in ccs format).
	void CreateATA();
	// Will create A matrix (in ccs format)
	void CreateA();

	void ClearFactorATA();
	void ClearFactorA();
	void ClearMatricesATA(); // clears m_A, m_ATA, m_AT
	void ClearMatricesA(); // clears the m_A matrix
};



inline void SparseSolver::ClearObject() {
	ClearFactorATA();
	ClearFactorA();
	ClearMatricesATA();
	ClearMatricesA();

	m_ATb.clear();
	m_etree = NULL;
	m_numCols = 0;
	m_numRows = 0;
	m_colsA.clear();
}

// adds a new entry to the sparse matrix A
// i and j are 0-based
// if the A^T A matrix had been factored, this will destroy the factor
inline void SparseSolver::AddIJV(const int i, const int j, const taucsType v) {
	ClearFactorATA();
	ClearFactorA();
	ClearMatricesATA();
	ClearMatricesA();

	m_colsA[j][i] = v;

	// update number of rows
	if ((i+1) > m_numRows)
		m_numRows = i+1;
}

// updates the entry in A by adding the value v to the current value
// i and j are 0-based
// if the A^T A matrix had been factored, this will destroy the factor
inline void SparseSolver::AddToIJV(const int i, const int j, const taucsType v) {
	ClearFactorATA();
	ClearFactorA();
	ClearMatricesATA();
	ClearMatricesA();

	// if no such entry existed
	if (m_colsA[j].find(i) == m_colsA[j].end())
		m_colsA[j][i] = 0;

	m_colsA[j][i] += v;

	// update number of rows
	if ((i+1) > m_numRows)
		m_numRows = i+1;
}

inline taucs_ccs_matrix * SparseSolver::GetATA_Copy() {
	if (! m_ATA) {
		CreateATA();
	}

	return MatrixCopy(m_ATA);
}

// returns the dimensions of the A matrix
inline void SparseSolver::GetAMatrixSize(int & numRows, int & numCols) const {
	numRows = m_numRows;
	numCols = m_numCols;
}
