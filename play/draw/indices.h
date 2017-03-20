#ifndef _INDICES_H
#define _INDICES_H

#include <cstdlib>
#include <iostream>
#include <vector>
#include <cfloat>
#include <algorithm>
#include "math.h"


using namespace std;


template <class T> ostream & operator<<(ostream & o, const vector<T> & v)
{
      o << "[";
      for (int i=0;i<v.size();i++)
      {
        if (i>0)
        {  o << ","; }
        o << v[i];
      }
      return o << "]";
}



typedef long long int vec_t;


typedef vec_t alignVector;


vec_t numVectors(int k, int m);
int getIndex(alignVector v,int i, int m);
bool getIsAligned(alignVector v,int i, int m);
alignVector setIndex(alignVector v, int i, int nval, bool isAligned, int m);
alignVector restrictTo(alignVector v, const vector<int> & pos, int m);
//

void showVector(ostream & o, const alignVector & v, int k, int m);

//*******************************************************************************//
vector<int> getUpperBound( int qLen, int tLen, int mConstraint);
vector<int> getLowerBound( int qLen, int tLen, int mConstraint);
vector<int> getLocalBound( const vector <int> & bp, const vector<int> & bv, const vector<int> & gbBound);
vector<int> getBagBound(const vector<int> & bv, const vector<int> & gbBound);
vector<int> getIndexBound(const vector<int> & indices, const vector<int> & gbBound);

void * allocateMatrix(int k, const int tte, const int dim, const vector<int> & upperBound, const vector<int> & lowerBound, int previousIndex);
void * allocateChampion(int k, const int tte, const int dim1, const int dim2, const vector<int> & upperBound, const vector<int> & lowerBound, int previousIndex);
void assignValue(void * matrix, const vector<int> & lowerBound, vector<int> indices, vector<bool> isMapped, double score, int k, int previousIndex);
void assignChampion(void * matrix, const vector<int> & lowerBound, vector<int> indices, vector<bool> isMapped, vector<int> wholeIndices, vector<bool> wholeIsMapped, int k, int previousIndex);
double getValue(void * matrix, const vector<int> & lowerBound, vector<int> indices, vector<bool> isMapped, int k, int previousIndex);
int * getChampion(void * matrix, const vector<int> & lowerBound, vector<int> indices, vector<bool> isMapped, int k, int previousIndex);

void freeScoreMatrix(void * matrix, int k, const int tte, const vector<int> & upperBound, const vector<int> & lowerBound, int previousIndex);
void freeChampionMatrix(void * matrix, int k, const int tte, const vector<int> & upperBound, const vector<int> & lowerBound, int previousIndex, const int dim1);
void restrictToIndicesIsMapping(vector<int> & indices, vector<bool> & isMapped, vector<int> & childIndices, vector<bool> & childIsMapped, vector<int> & commonindices);
void getBestScore(const int idroot, const vector<int> & lowerBound, const vector<int> & upperBound, const int bagSize, int m, int previousIndex, void ** result, void ** champion, vector<int> & indices, vector<bool> & isMapped, double & score, int * & mappedInfo);
void pointerToIndixMapping(int * mappedInfo, vector<int> & indices, vector<bool> & isMapped, int bagSize);

//*******************************************************************************//
//********************* get sub-optimal alignment *******************************//
//*******************************************************************************//
void getSubOptimalScore(const int idroot, const vector<int> & lowerBound, const vector<int> & upperBound, const int bagSize, int previousIndex, void ** result, vector<int> & indices, vector<bool> & isMapped, double & score, vector<double> & subScore, double error);


#endif
