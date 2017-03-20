#ifndef _TREE_DECOMPOSITION_H
#define _TREE_DECOMPOSITION_H
#include <fstream>
#include <iostream>
#include <regex>
#include <unordered_map>

#include "bag.h"
#include "indices.h"

using namespace std;


#define NEVER_VISITED -1
#define CURRENTLY_VISITING -2

class TreeDecomposition{
	private:
		vector<Bag> bags;
		vector<vector<int> > arcs;
		vector<vector<int> > backarcs;
		vector<int> bounds ;

		void getComputationOrderRec(int bagId, int & nextRank, int* ranks);
		Bag bagFromNode(string text);
	public:
		vector<int> getComputationOrder();

		Bag getBag(int id);

		// Adds a bag to the decomposition and returns its identifier.
		int addBag(Bag b);
		// Replace bag with index i with a new bag b (and conserve parents and child
		int replaceBag(int i, Bag b) ;

		void addArc(int idfrom, int idto);
		void delArc(int idfrom, int idto);

		// Returns the supposedly single root of the tree-decomposition
		int getRoot();

		int size();

		int getParent(int id);

		vector<int> getChildrenIds(int id);

		// TODO: Return the number of assignments for positions that are inherited from
		// the father of bag id. Basically, n^(bags[i].size()-bags[i].diff(father)), but
		// we might want to use a more compact encoding.
		long getNumIndicesFromFather(int id, int n);

		vector<int> getBounds();

		int getBagWithPos(int i, int j); // Return an index bag of a bag containing the two positions i and j (first one in a depth search)

		int getBagWithHighPos(); // Return an index bag of a bag containing the highest position of the td

		// Set the root to "newRoot"
		void changeRoot(int newRoot) ;

		// add a sub-tree-decomposition "sub" to the bag "bagId" considering recRoot as the root of "sub"
		void addSubTreeDecRec(int bagId, TreeDecomposition & sub, int recRoot) ;

		// search for the first bag "b" from the root containing "pos", and ad the pos to every bags between the root and b
		void updatePos(int pos);

		// To display TreeDecompositions properly....
		friend ostream & operator<<(ostream & o, const TreeDecomposition & td)
		{
			o << "TreeDec: ["<<endl;
			for (int i=0;i<td.bags.size();i++)
			{
				o << "  B" << i << ": "<< td.bags[i] << endl;
			}
			for (int i=0;i<td.bags.size();i++)
			{
				for (int j=0;j<td.arcs[i].size();j++)
				{
					int to = td.arcs[i][j];
					o << "  B" << i << " -> B"<< to << endl;
				}
			}
			return o << "]";
		}

		// To display TreeDecompositions graphvizically....
		void exportAsDot(const string & path);
		void importAsDot(const string & path);
		
		// Get dimension for initialization of the score matrix
		vector<int> getDimensionMatrix();
};



#endif
