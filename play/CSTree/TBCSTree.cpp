#include "TBCSTree.h"

// class PQNode
PQNode::PQNode(double error, CSNode *ptr)
{
	this->error = error;
	this->ptr = ptr;
}

double PQNode::getError() const
{
	return error; 	
}

void PQNode::setError(double error)
{
	this->error = error;
}

bool PQNode::operator< (const PQNode & p) const
{
	return this->error < p.getError();
}

bool PQNode::compareNode(double error)
{
	if(this->error > error){
		return true;
	}
	return false;
}


// class CSNode

CSNode::CSNode(double error, vector<int> bagIndex, vector<vector<int> > mappedInfo)
{
	this->error = error;
	this->bagIndex = bagIndex;
	this->mappedInfo = mappedInfo;	
}

CSNode * CSNode::getParent()
{
	return parent;	
}

void CSNode::setParent(CSNode * p)
{
	this->parent = p;	
	
}
CSNode * CSNode::getFirstChild()
{
	return firstchild;	
}

void CSNode::setFirstChild(CSNode * c)
{
	this->firstchild = c;	
}

CSNode * CSNode::getNextSibling()
{
	return nextsibling;	
}

void CSNode::setNextSibling(CSNode * c)
{
	this->nextsibling = c;
}

double CSNode::getError()
{
	return error;	
}
vector<int> CSNode::getBagIndex()
{
	return bagIndex;	
}
vector<vector<int> > CSNode::getMappedInfo()
{
	return mappedInfo;	
}

// class TBCSTree
TBCSTree::TBCSTree(CSNode * rootCSNode, PQNode * pqNode, int KBest)
{
	this->KBest = KBest;
	this->root = rootCSNode;
	pq.insert(*pqNode);	
}

CSNode * TBCSTree::getRoot()
{
	return root;	
}

bool TBCSTree::compareTopInPQ(double error)
{	
	if(pq.size() < KBest){
		return true;
	}
	set<PQNode>::iterator it = pq.end();
	PQNode pNode = *it;
	if (pNode.compareNode(error)){
		return true;
	}
	return false;
}

bool TBCSTree::insertChild(CSNode *p, CSNode *c)
{
	CSNode * q;
	if(root != NULL){
		if(p->getFirstChild() == NULL){   // if the node has the first child
			p->setFirstChild(c);
		} else{
			q = p->getFirstChild();
			while(q->getNextSibling() != NULL){
				q=q->getNextSibling();
			}
			cout << "set next sibling" << endl;
			q->setNextSibling(c);
			cout << "set next sibling over" << endl;
		}
		c->setParent(p);
	} else {
		return false;   // the tree is empty	
	}
	return true;
}

/*
bool TBCSTree::updateTree(CSNode * p, CSNode *c, PQNode *q);
{
	insertChild(p,c);
	pq.push(*q);
	if(pq.size() > KBest){
		PQNode pqNode = pq.top();
		
		pq.pop();
	}
}
*/


// test code
void TBCSTree::showPQ()
{
	cout << "The size of pq is " << pq.size() << endl;
	
	for(set<PQNode>::iterator it=pq.begin(); it!=pq.end(); it++){
		PQNode pNode = *it;
		cout << pNode.getError() << endl;
	}
	
}

void TBCSTree::preOrderTraverse(CSNode * t, void(*visit)(CSNode*))
{
	if(t!=NULL){
		visit(t);
		preOrderTraverse(t->getFirstChild(), visit);
		preOrderTraverse(t->getNextSibling(), visit);	
	}
}

void TBCSTree::preOrderTraverse(void(*visit)(CSNode *))
{
	cout << "preordertraverse begins" << endl;
	preOrderTraverse(root, visit);	
}


void visit(CSNode * c){
		vector<int> bagIndex = c->getBagIndex();
		vector<vector<int> > mappedInfo = c->getMappedInfo();
		cout << "error: " << c->getError() << endl;
		cout << "bagIndex:";
		for(int i=0; i<bagIndex.size(); i++){
			cout << bagIndex[i] << " ";
		}
		cout << endl;
		cout << "mappedInfo:" << endl;
		for(int i=0; i<mappedInfo.size(); i++){
			vector<int> info = mappedInfo[i];
			for(int j=0; j<info.size(); j++){
				cout << info[j] << " ";
			}
			cout << endl;
		}
		
}