#include "indices.h"
#include <assert.h>

using namespace std;


inline vec_t pow(int x, int y)
{
  return (vec_t) round (pow((double)x,(double)y));
}

vec_t numElems(int k, int m)
{
  return pow(m,k);
}

inline int getElem(vec_t v, int i, int m)
{
	assert( i >= 0 );
  return (v/(vec_t) pow(m,i))%m;
}

inline vec_t setElem(vec_t v, int i, int nval, int m)
{
  vec_t exp = (vec_t) pow(m,i);
  return v+(nval-getElem(v,i,m))*exp;
}

// To display indices vectors properly....    
void showVec(ostream & o, const vec_t & v, int k, int m)
{
  o << "[";
  for (int i=0;i<k;i++)
  {
    if (i>0)
    {  o << ","; }
    o << getElem(v,i,m);
  }
  o << "] ("<<v<<")";
}

vec_t project(vec_t v, const vector<int> & pos, int m)
{
      vec_t result = 0;
      for(int i=0;i< pos.size();i++)
      {
        int p = pos[i];
        result = setElem(result,i,getElem(v,p,m),m);
      }
      return result;
}

/*
alignVector restrictTo(alignVector v, const vector<int> & pos, int m)
{
	    vec_t result = 0;
      for(int i=0;i< pos.size();i++)
      {
        int p = pos[i];
        result = setElem(result,i,getElem(v,p,2*m),2*m);
      }
      return result;
	
//	return project(v, pos, 2*m);
}
*/
vec_t numVectors(int k, int m){
	return numElems(k, 2*m);
}
inline int getIndex(alignVector v,int i, int m){
	return getElem(v,i,2*m)%m;
}

inline bool getIsAligned(alignVector v,int i, int m){
	return getElem(v,i,2*m)>=m;
}
alignVector setIndex(alignVector v, int i, int nval, bool isAligned, int m){
	if (isAligned) 
	{
		nval += m;
	}
	return setElem(v, i, nval, 2*m);
}

// To display indices vectors properly....
void showVector(ostream & o, const alignVector & v, int k, int m)
{
  o << "[";
  for (int i=0;i<k;i++)
  {
    if (i>0)
    {  o << ","; }
    o << getIndex(v,i,m)<<"["<<getIsAligned(v,i,m)<<"]";
  }
  o << "] ("<<v<<")";
}

//*********************************************************************************//

vector<int> getUpperBound(int qLen, int tLen, int mConstraint){
	// the result ranges from 0 to (tLen-1)
	vector<int> result;
	for(int i=1; i<=qLen; i++){
		//floor, value to round up. 2.3 to 3.0 and -2.3 to -2.0
		double rt = ceil((double(tLen)/double(qLen))* i)+mConstraint;
		if(rt < 1){
			result.push_back(0);
		} else if (rt > tLen){
			result.push_back(tLen-1);
		} else {
			result.push_back(rt-1);
		}
	}
	return result;
}

vector<int> getLowerBound(int qLen, int tLen, int mConstraint){
	// the result ranges from 0 to (tLen-1)
	vector<int> result;
	for(int i=1; i<=qLen; i++){
		double lt = ceil(double(tLen)/double(qLen)* i)-mConstraint;
		if(lt < 1){
			result.push_back(0);
		} else if (lt > tLen){
			result.push_back(tLen-1);
		} else {
			result.push_back(lt-1);
		}
	}
	return result;
}

vector<int> getLocalBound( const vector<int> & bp, const vector<int> & bv, const vector<int> & gbBound){
	// bv ranges from 1 and the result ranges from 0 to (tLen-1)
	vector<int> result;
	for(int i=0; i<bp.size(); i++){
		result.push_back(gbBound[bv[bp[i]]-1]);
	}	
	return result;
}

vector<int> getBagBound(const vector<int> & bv, const vector<int> & gbBound){
	vector<int> result;
	for(int i=0; i<bv.size(); i++){
		result.push_back(gbBound[bv[i]-1]);
	}
	return result;
}

vector<int> getIndexBound(const vector<int> & indices, const vector<int> & gbBound){
	vector<int> result;
	for(int i=0; i<indices.size(); i++){
		result.push_back(gbBound[indices[i]]);
	}
	return result;
}

int getMappedDimension(vector<bool> isMapped){
	int result=0;
	for(int i=0; i<isMapped.size(); i++){
		result += isMapped[i] * pow(2, i);
	}
	return result;
}

void pointerToIndixMapping(int * mappedInfo, vector<int> & indices, vector<bool> & isMapped, int bagSize){
	for(int i=0; i<bagSize; i++){
		indices.push_back(mappedInfo[i]);
		isMapped.push_back(mappedInfo[bagSize + i]);
	}
}

void * allocateMatrix(int k, const int tte, const int dim, const vector<int> & upperBound, const vector<int> & lowerBound, int previousIndex){
	void * matrix;
	if (k>1){
		int index = tte-k;
		int bd = (lowerBound[index] < previousIndex ) ? (upperBound[index]-previousIndex+1) : (upperBound[index]-lowerBound[index]+1);
		matrix = (void *) malloc(bd * sizeof(void*));
		void ** Dmatrix = (void **) matrix;
		for (int d=0; d<bd; d++){
			Dmatrix[d] = allocateMatrix(k-1, tte, dim, upperBound, lowerBound, previousIndex+d);
		}
	} else {
		int index = tte-k;
		int bd = (lowerBound[index] < previousIndex ) ? (upperBound[index]-previousIndex+1) : (upperBound[index]-lowerBound[index]+1);
		matrix = (void *) malloc (bd * sizeof(void *));
		double ** Dmatrix = (double **) matrix;
		for (int d1=0; d1<bd; d1++){
			Dmatrix[d1] = (double *) malloc(dim * sizeof(double));
			for(int d2=0; d2<dim; d2++){
				Dmatrix[d1][d2] = DBL_MAX;
			}
		}
	}
	return matrix;
}

void * allocateChampion(int k, const int tte, const int dim1, const int dim2, const vector<int> & upperBound, const vector<int> & lowerBound, int previousIndex){
	void * matrix;
	if(k>1){		
		int index = tte-k;
		int bd = (lowerBound[index] < previousIndex ) ? (upperBound[index]-previousIndex+1) : (upperBound[index]-lowerBound[index]+1);
		matrix = (void *) malloc(bd * sizeof(void*));		
		void ** Dmatrix = (void **) matrix;
		for (int d=0; d<bd; d++){
			Dmatrix[d] = allocateChampion(k-1, tte, dim1, dim2, upperBound, lowerBound, previousIndex+d);
		}
	} else {	
		int index = tte-k;
		int bd = (lowerBound[index] < previousIndex ) ? (upperBound[index]-previousIndex+1) : (upperBound[index]-lowerBound[index]+1);
		matrix = (void *) malloc (bd *sizeof(void *));

		int *** Tmatrix = (int ***) matrix;
		for(int d1=0; d1<bd; d1++){
			Tmatrix[d1] = (int **) malloc(dim1 * sizeof(int *));
			for(int d2=0; d2<dim1; d2++){
				Tmatrix[d1][d2] = (int *) malloc(dim2 * sizeof(int ));
				for(int d3=0; d3<dim2; d3++){
					Tmatrix[d1][d2][d3] = -1;
				}
			}
		}
		
	}
	return matrix;
}

double getValue(void * matrix, const vector<int> & lowerBound, vector<int> indices, vector<bool> isMapped, int k, int previousIndex){
	if(k<indices.size()-1){
		int bd = (lowerBound[k] < previousIndex) ? previousIndex : lowerBound[k];		
		void ** Dmatrix = (void **) matrix;
		int d = indices[k] - bd;
		return getValue(Dmatrix[d], lowerBound, indices, isMapped, k+1, previousIndex + d);
	} else {
		int bd = (lowerBound[k] < previousIndex) ? previousIndex : lowerBound[k];	
		int d = indices[k] - bd;
		int dim=getMappedDimension(isMapped);
		return ((double **) matrix)[d][dim];	
	}	
}


int * getChampion(void * matrix, const vector<int> & lowerBound, vector<int> indices, vector<bool> isMapped, int k, int previousIndex){
	if(k<indices.size()-1){
		int bd = (lowerBound[k] < previousIndex) ? previousIndex : lowerBound[k];
		void ** Dmatrix = (void **) matrix;
		int d = indices[k] - bd;
		return getChampion(Dmatrix[d], lowerBound, indices, isMapped, k+1, previousIndex + d);
	} else {
		int bd = (lowerBound[k] < previousIndex) ? previousIndex : lowerBound[k];
		int d = indices[k] - bd;
		int dim=getMappedDimension(isMapped);
		return ((int ***) matrix)[d][dim];	
	}	
}


void assignValue(void * matrix, const vector<int> & lowerBound, vector<int> indices, vector<bool> isMapped, double score, int k, int previousIndex){
	if (k<indices.size()-1){
		int bd = (lowerBound[k] < previousIndex) ? previousIndex : lowerBound[k];
		void ** Dmatrix = (void **) matrix;
		int d = indices[k] - bd;
		assignValue(Dmatrix[d], lowerBound, indices,isMapped, score, k+1, previousIndex+d);
	} else {
		int bd = (lowerBound[k] < previousIndex) ? previousIndex : lowerBound[k];
		int d = indices[k] - bd;
		int dim=getMappedDimension(isMapped);
		((double **) matrix)[d][dim] = score;
	}
}

void assignChampion(void * matrix, const vector<int> & lowerBound, vector<int> indices, vector<bool> isMapped, vector<int> wholeIndices, vector<bool> wholeIsMapped, int k, int previousIndex){
	if (k<indices.size()-1){
		int bd = (lowerBound[k] < previousIndex) ? previousIndex : lowerBound[k];
		void ** Dmatrix = (void **) matrix;
		int d = indices[k] - bd;
		assignChampion(Dmatrix[d], lowerBound, indices,isMapped,wholeIndices, wholeIsMapped, k+1, previousIndex+d);
	} else {
		int bd = (lowerBound[k] < previousIndex) ? previousIndex : lowerBound[k];
		int d = indices[k] - bd;
		int dim1=getMappedDimension(isMapped);
		int dim2=2*wholeIndices.size();
		vector<int> whole;
		
		whole.insert(whole.end(), wholeIndices.begin(), wholeIndices.end());
		whole.insert(whole.end(), wholeIsMapped.begin(), wholeIsMapped.end());
		for(int i=0; i<dim2; i++){
			((int ***)matrix)[d][dim1][i]= whole[i];
		}
	}
}

void freeScoreMatrix(void * matrix, int k, const int tte, const vector<int> & upperBound, const vector<int> & lowerBound, int previousIndex){
	if(k>1){
		int index = tte-k;
		int bd = (lowerBound[index] < previousIndex ) ? (upperBound[index]-previousIndex+1) : (upperBound[index]-lowerBound[index]+1);
		void ** Dmatrix = (void **) matrix;
		for(int d=0; d<bd; d++){
			freeScoreMatrix(Dmatrix[d],k-1, tte, upperBound, lowerBound, previousIndex+d);
		}
	} else {
		int index = tte-k;
	  int bd = (lowerBound[index] < previousIndex ) ? (upperBound[index]-previousIndex+1) : (upperBound[index]-lowerBound[index]+1);
		double ** Dmatrix = (double **) matrix;
		for(int d=0; d<bd; d++){
			free(Dmatrix[d]);
		}
		free (matrix);
	}
}

void freeChampionMatrix(void * matrix, int k, const int tte, const vector<int> & upperBound, const vector<int> & lowerBound, int previousIndex, const int dim1){
	if(k>1){
		int index = tte-k;
    int bd = (lowerBound[index] < previousIndex ) ? (upperBound[index]-previousIndex+1) : (upperBound[index]-lowerBound[index]+1);
		void ** Dmatrix = (void **) matrix;
		for(int d=0; d<bd; d++){
			freeChampionMatrix(Dmatrix[d],k-1, tte, upperBound, lowerBound, previousIndex+d, dim1);
		}
	} else {
		int index = tte-k;
    int bd = (lowerBound[index] < previousIndex ) ? (upperBound[index]-previousIndex+1) : (upperBound[index]-lowerBound[index]+1);
		void ** Tmatrix = (void **) matrix;
		for(int d1=0; d1<bd; d1++){
			double ** Dmatrix = (double **) Tmatrix[d1];
			for(int d2=0; d2<dim1; d2++){
				free(Dmatrix[d2]);
			}
			free(Dmatrix);
		}
		free (Tmatrix);
	}
}

void restrictToIndicesIsMapping(vector<int> & indices, vector<bool> & isMapped, vector<int> & childIndices, vector<bool> & childIsMapped, vector<int> & commonindices){
	
	for (int i=0; i<commonindices.size(); i++){
		childIndices.push_back(indices[commonindices[i]]);
		childIsMapped.push_back(isMapped[commonindices[i]]);
	}
}

void getBestScore(const int idroot, 
		const vector<int> & lowerBound, 
		const vector<int> & upperBound,
		const int bagSize, 
		int m,
		int previousIndex,
		void ** result, 
		void ** champion, 					
		vector<int> & indices, 
		vector<bool> & isMapped,
		double & score, 
		int * & mappedInfo)
{
	if(indices.size() < bagSize ){
		int lbd = (lowerBound[indices.size()] < previousIndex) ? previousIndex : lowerBound[indices.size()];
		int ubd = upperBound[indices.size()];
		
		for(int d=lbd; d<=ubd; d++){
			indices.push_back(d);
			isMapped.push_back(true);
			getBestScore(idroot, lowerBound, upperBound, bagSize, m, d, result, champion, indices, isMapped, score,  mappedInfo);
			isMapped.pop_back();
			
			isMapped.push_back(false);
			getBestScore(idroot, lowerBound, upperBound, bagSize, m, d, result, champion, indices, isMapped, score, mappedInfo);
			isMapped.pop_back();
			
			indices.pop_back();
		}
	} else {
		double scoreTmp = getValue(result[idroot], lowerBound, indices, isMapped, 0, 0);
		if (  scoreTmp <= score ){
			score = scoreTmp;
			mappedInfo = getChampion(champion[idroot], lowerBound, indices, isMapped, 0, 0);
		}
	}
}

// get sub optimal alignment
void getSubOptimalScore( const int idroot,
		const vector<int> & lowerBound, 
		const vector<int> & upperBound,
		const int bagSize, 
		int previousIndex,
		void ** result, 					
		vector<int> & indices, 
		vector<bool> & isMapped,
		double & score, 
		vector<double> & subScore,
		double error)
{
	if(indices.size() < bagSize ){
		int lbd = (lowerBound[indices.size()] < previousIndex) ? previousIndex : lowerBound[indices.size()];
		int ubd = upperBound[indices.size()];
		
		for(int d=lbd; d<=ubd; d++){
			indices.push_back(d);
			isMapped.push_back(true);
			getSubOptimalScore(idroot, lowerBound, upperBound, bagSize, d, result, indices, isMapped, score, subScore, error);
			isMapped.pop_back();
			
			isMapped.push_back(false);
			getSubOptimalScore(idroot, lowerBound, upperBound, bagSize, d, result, indices, isMapped, score, subScore, error);
			isMapped.pop_back();
			
			indices.pop_back();
		}
	} else {
		double scoreTmp = getValue(result[idroot], lowerBound, indices, isMapped, 0, 0);
		subScore.push_back(scoreTmp);
		for(int i=0; i<indices.size(); i++){
			cout << indices[i] << " ";
		}
		for(int i=0; i<isMapped.size(); i++){
			cout << isMapped[i] << " ";
		}
		cout << endl;
		/*
		if (  scoreTmp >= score && scoreTmp <= score+error){
			subScore.push_back(scoreTmp);
		}
		*/
	}
}