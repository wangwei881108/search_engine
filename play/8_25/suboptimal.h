#ifndef _SUBOPTIMAL_H_
#define _SUBOPTIMAL_H_

#include <vector>
#include <utility>
#include <set>
#include <sstream>
#include <unordered_map>
#include <queue>
//#include <treedecomposition.h>

using namespace std;

struct calculatingContext{
    int bagIndex;
    vector<int> bd;
    vector<int> bv;
    vector<int> children;
    vector<vector<int> > commonindices;
    vector<int> basePairCalculating;
    set<pair<int, int> > consectiveIndex;
    set<pair<int, int> > basePairIndex;
};

typedef struct hyperEdge{
    vector<int> edgeIndex;
    vector<int> mappedInfo;
} hyperEdge;

typedef struct hyperNode{
    vector<int> nodeIndex;
    vector<int> mappedInfo;
    int bagIndex;
    bool operator== (const hyperNode &other) const
    {
        return ((nodeIndex == other.nodeIndex) && (mappedInfo==other.mappedInfo));
    }
} hyperNode;

namespace std
{
    template<>
    struct hash<hyperNode>
    {
        size_t operator() (const hyperNode& node) const
        {
            ostringstream oss;
            for(size_t i=0; i<node.nodeIndex.size(); i++){
                oss << node.nodeIndex[i];
            }
            for(size_t i=0; i<node.mappedInfo.size(); i++){
                oss << node.mappedInfo[i];
            }
            string s = oss.str();
            return hash<string>()(s);
        }
    };
}

typedef struct candElem{
    double weight;
    hyperEdge outEdge;
    vector<int> J_index;
} candElem;

struct comparison
{
    bool operator() (const candElem & a, const candElem &b)
    {
        return a.weight > b.weight;
    }
};

typedef unordered_map<hyperNode, vector<candElem> > vertexVector;
typedef unordered_map<hyperNode, priority_queue<candElem, vector<candElem>, comparison> >  vertexPQueue;


void LazyKthBest(hyperNode& node, int ck, int KBest, vertexVector& D_hat, vertexPQueue& cand);


#endif

//???? function vector<struct hyperNode> outNhodes;