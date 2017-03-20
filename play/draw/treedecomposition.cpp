#include "treedecomposition.h"

using namespace std;


#define NEVER_VISITED -1
#define CURRENTLY_VISITING -2

void TreeDecomposition::getComputationOrderRec(int bagId, int & nextRank, int* ranks)
{
	// This means there is a loop in the tree... bad Karma!
	assert(ranks[bagId]!=CURRENTLY_VISITING);
	// If node has already been visited, do nothing
	if (ranks[bagId]==NEVER_VISITED)
	{
		// Otherwise mark node as currently being visited
		ranks[bagId] = CURRENTLY_VISITING;
		// Visit and assign rank to children
		for (int j=0;j<arcs[bagId].size();j++)
		{
			int childId = arcs[bagId][j];
			getComputationOrderRec(childId, nextRank, ranks);
		}
		// then, once every child has a rank, pick the next available rank
		ranks[bagId] = nextRank;
		nextRank++;
	}
}

Bag TreeDecomposition::bagFromNode(string text)
{
	Bag b;
	std::vector<int> ids;
	// Split the content and return a series of indices
	std::istringstream iss(text);
	std::string token;
	while (std::getline(iss, token, ' ')) {
		std::regex nuc(".*([a-zA-Z])([0-9]+)$");
		std::smatch fnuc;
		std::regex_search(token, fnuc, nuc);
		if (fnuc.size() > 1) {
			string nucl = fnuc[1];
			int nid;
			istringstream( fnuc[2] ) >> nid;
			ids.push_back( nid );
		} else {
			cerr << "Can't read bag content: " << token << endl;
		}
	}
	// Add the ids in order in the bag
	std::sort( ids.begin(), ids.end());
	for (int nid : ids) {
		b.addIndex( nid );
	}
	return b;
}

vector<int> TreeDecomposition::getComputationOrder()
{
	vector<int> result;
	int * ranks = new int[bags.size()];
	for (int i=0;i<bags.size();i++)
	{
		ranks[i] = NEVER_VISITED;
		result.push_back(-1);
	}
	int nextRank = 0;
	getComputationOrderRec(getRoot(), nextRank, ranks);
	for (int i=0;i<bags.size();i++)
	{ result[ranks[i]] = i; }
	return result;
}

Bag TreeDecomposition::getBag(int id)
{
	return bags[id];
}


// Adds a bag to the decomposition and returns its identifier.
int TreeDecomposition::addBag(Bag b)
{
	bags.push_back(b);
	arcs.push_back(vector<int>());
	backarcs.push_back(vector<int>());
	return bags.size()-1;
}

int TreeDecomposition::replaceBag(int i, Bag b)
{
	assert(bags[i].getDiff(b).size()==0);
	bags[i] = b;

	return i ;
}

void TreeDecomposition::addArc(int idfrom, int idto)
{
	arcs[idfrom].push_back(idto);
	backarcs[idto].push_back(idfrom);
}

void TreeDecomposition::delArc(int idfrom, int idto)
{
	// Search for idto in arcs[idfrom]
	int ind = 0 ;
	while(ind < arcs[idfrom].size() && arcs[idfrom][ind] != idto)
	{
		ind++ ;
	}
	if(ind < arcs[idfrom].size())
		arcs[idfrom].erase(arcs[idfrom].begin()+ind);

	// Search for idfrom in backarcs[idto]
	ind=0 ;
	while(ind < backarcs[idto].size() && arcs[idto][ind] != idfrom)
	{
		ind++ ;
	}
	if(ind < arcs[idto].size())
		backarcs[idto].erase(backarcs[idto].begin()+ind);
}

// Returns the supposedly single root of the tree-decomposition
int TreeDecomposition::getRoot()
{
	int* countIncoming = new int[bags.size()];
	for (int i=0;i<bags.size();i++)
	{
		countIncoming[i] = 0;
	}
	for (int i=0;i<bags.size();i++)
	{
		for (int j=0;j<arcs[i].size();j++)
		{
			int to = arcs[i][j];
			countIncoming[to]++;
		}
	}
	int root = -1;
	for (int i=0;i<bags.size();i++)
	{
		if (countIncoming[i] == 0)
		{
			// Check if more than one node has no incoming edge.
			assert(root==-1);
			root = i;
		}
	}
	return root;
}

int TreeDecomposition::size()
{
       return bags.size();
}

int TreeDecomposition::getParent(int id)
{
	assert(backarcs[id].size()<2);
	if (backarcs[id].size()>0)
		return backarcs[id][0];
	else
		return -1;
}

vector<int> TreeDecomposition::getChildrenIds(int id)
{
	return arcs[id];
}


vector<int> TreeDecomposition::getBounds()
{
	return bounds ;
}

int TreeDecomposition::getBagWithPos(int i, int j)
{
	vector<int> order = getComputationOrder();
	for(int n=0; n<order.size(); n++)
	{
		Bag b = getBag(order[n]) ;
		if(b.getPosOfIndex(i)!=-1 &&  b.getPosOfIndex(j)!=-1)
			return order[n];
	}
	return -1;
}

int TreeDecomposition::getBagWithHighPos()
{
	int result = -1 ;
	vector<int> order = getComputationOrder();
	for(int n=0; n<order.size(); n++)
	{
		Bag b = getBag(order[n]) ;
		if(b.getIndex(b.size()-1) > result )
			result = order[n];
	}
	return result ;
}

void TreeDecomposition::changeRoot(int newRoot)
{
	int curr = newRoot ;
	while(getParent(curr) !=-1)
	{
		// Get the parent index of newRoot
		int p = getParent(curr) ;
		// delete/add arcs and backarcs
		delArc(p,curr) ;
		addArc(curr,p) ;
		curr = p ;
	}
}

void TreeDecomposition::addSubTreeDecRec(int bagId, TreeDecomposition & sub, int curr)
{
	// Add the curr bag of the subtreedec
	int nextId = addBag(sub.getBag(curr)) ;
	// Link the bag to the treedec with bagId
	addArc(bagId,nextId) ;
	// Rec call for all children of curr
	for(int i=0; i<sub.getChildrenIds(curr).size() ; i++)
	{
		addSubTreeDecRec(nextId, sub, sub.getChildrenIds(curr)[i]) ;
	}
}

void TreeDecomposition::updatePos(int pos)
{
	vector<int> order = getComputationOrder();
	// from the order, check one by one the node, beginning from max(order) <=> the root, to min(order) and stop at the first bag containing pos
	int i = order.size()-1 ;
	Bag b = getBag(order[i]) ;
	while(i > 0 && !b.hasPos(pos))
	{
		i-- ;
		b = getBag(order[i]) ;
	}
	if( i>0 || b.hasPos(pos))
	{
		// Then, from this bag b of index order[i], 'backarc' to the root and add pos
		int r = getRoot() ;
		int curInd = order[i] ;
		do
		{
			curInd = getParent(curInd) ;
			getBag(curInd).insertIndex(pos) ;
		}while(curInd != getRoot());
	}
}

void TreeDecomposition::exportAsDot(const string & path)
{
	ofstream out(path.c_str());
	out << "digraph G {"<<endl;
	out << "  node [shape=\"rectangle\"];"<<endl;
	for (int i=0;i<bags.size();i++)
	{
		for (int j=0;j<arcs[i].size();j++)
		{
			int to = arcs[i][j];
			out << "  \"" << bags[i].toString() << "\" -- \""<< bags[to].toString()  << "\";"<< endl;
		}
	}
	out << "}";
}

void TreeDecomposition::importAsDot(const string & path)
{
	ifstream input(path.c_str());
	if ( input.is_open() ) {
		string line;
		unordered_map <string, int> map;
		while (getline(input, line)) {
			// Get bags
			std::regex node("[ \\t]*(.+?) *\\[label=\" *(.+?) *\"\\]$");
			std::smatch fnode;
			std::regex_search(line, fnode, node);
			// Found a bag: retrieve it
			if (fnode.size() > 2) {
				string bag_name = fnode[1];
				string bag_content = fnode[2];
				// Create a bag and add it to the tree, which gives an id
				Bag b = bagFromNode(bag_content);
				int bag_index = addBag(b);
				map[ bag_name ] = bag_index;
			}
			else {
				// Get arcs
				std::regex arc("[ \\t]*(.+) -- (.+)$");
				std::smatch farc;
				std::regex_search(line, farc, arc);
				// Found an arc: retrieve it
				if (farc.size() > 2) {
					string bag1 = farc[1];
					string bag2 = farc[2];
					// Retrieve the bags name in the tree
					int id1 = map[ bag1 ];
					int id2 = map[ bag2 ];
					addArc(id1, id2);
				}
			}
		}
		input.close();
	} else {
		cerr << "Couldn't open the file: " << path << endl;
	}
}	
	//
vector<int> TreeDecomposition::getDimensionMatrix()
{
	vector<int> result;
	vector<int> ranks = getComputationOrder();
	for(int i=0; i<ranks.size(); i++){
		Bag b = getBag(i);
		int idparent = getParent(i);
		vector<int> bp;
   	if (idparent!=-1)
   	{
     	bp = b.getCommon(getBag(idparent));
     	result.push_back(bp.size());
   	} else {
   		result.push_back(b.size());	
   	}
	}	
	return result;
}


