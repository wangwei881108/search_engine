#ifndef _TRACEBACKCSTREE_H_
#define _TRACEBACKCSTREE_H_

#include <iostream>
#include <vector>
#include <set>
#include <limits>
#include <cfloat>

using namespace std;


class CSNode
{
private:
	double error;
	vector<int> bagIndex;
	vector<vector<int> > mappedInfo;
	CSNode * parent;
	CSNode * firstchild, *nextsibling;
public:
	CSNode(double error, vector<int> bagIndex, vector<vector<int> > mappedInfo);
	
	CSNode * getParent();
	void setParent(CSNode * p);
	CSNode * getFirstChild();
	void setFirstChild(CSNode * c);
	CSNode * getNextSibling();
	void setNextSibling(CSNode * c);	
	double getError();
	vector<int> getBagIndex();
	vector<vector<int> > getMappedInfo();

};

class PQNode
{
private:
	double error;
	CSNode *ptr;
//	CSNode *leafPtr;
public:
	PQNode();
	PQNode(double error, CSNode *ptr);
	double getError() const;
	void setError(double error);
	bool operator< (const PQNode & p) const;
	bool compareNode(double error);
};


class TBCSTree{
private:
	CSNode * root;
	int KBest;
	set<PQNode> pq;
	
	//test
	void preOrderTraverse(CSNode * t, void(*visit)(CSNode*));

public:
	TBCSTree(CSNode * rootCSNode, PQNode * pqNode, int KBest);
	CSNode * getRoot();
	bool compareTopInPQ(double error);
	bool insertChild(CSNode *p, CSNode *c);
	bool updateTree(CSNode * p, CSNode *c, PQNode *q);   // insert the node in the tree and update the reference in priority queue
	
	//test
	void showPQ();
	void preOrderTraverse(void(*visit)(CSNode *));

};


void visit(CSNode * c);


#endif