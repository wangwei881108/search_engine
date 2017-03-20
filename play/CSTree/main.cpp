#include "TBCSTree.h"

using namespace std;

int main(){
	// Checking priority queue
	double rootError = 0.0;
	vector<int> rootIndices(4,50);
	vector<int> rootInfo1(4,51);
	vector<int> rootInfo2(4,52);
	vector<vector<int> > rootMappedInfo;
	rootMappedInfo.push_back(rootInfo1);
	rootMappedInfo.push_back(rootInfo2);
	CSNode rootCSNode(rootError, rootIndices, rootMappedInfo);
	TBCSTree tbTree(&rootCSNode);

	cout << "output root information" << endl;
	cout << tbTree.getRoot()->getError() << endl;
	vector<int> tmp = tbTree.getRoot()->getBagIndex();
	for(int i=0; i<tmp.size(); i++){
		cout << tmp[i] << "  ";
	}
	cout << endl;

	// Checking CSNode, insert one child
	vector<int> indices(4,100);
	vector<vector<int> > mappedInfo;
	vector<int> info1(4,110);
	vector<int> info2(4,120);

	mappedInfo.push_back(info1);
	mappedInfo.push_back(info2);
	double error = 100.1;
	CSNode csNode(error, indices, mappedInfo);
	bool result = tbTree.insertChild(tbTree.getRoot(),&csNode);
	cout << "The insertion 1 result is " << result << endl;
	cout << "I have arrived here 1" << endl;

	// Checking CSNode, insert another node
	vector<int> indices2(4,200);
	vector<vector<int> > mappedInfo2;

	vector<int> info21(4,210);
	vector<int> info22(4,220);

	mappedInfo2.push_back(info21);
	mappedInfo2.push_back(info22);
	double error2 = 200.1;
	CSNode csNode2(error2, indices2, mappedInfo2);
	cout << "I have arrived here 2" << endl;
	result = tbTree.insertChild(tbTree.getRoot(), &csNode2);
	cout << "The insertion 2 result is " << result << endl;


	// Checking CSNode, insert the third node
	vector<int> indices3(4,300);
	vector<vector<int> > mappedInfo3;

	vector<int> info31(4,310);
    vector<int> info32(4,320);

	mappedInfo3.push_back(info31);
	mappedInfo3.push_back(info32);
	double error3 = 300.1;
	CSNode csNode3(error3, indices3, mappedInfo3);
	result = tbTree.insertChild(&csNode, &csNode3);
	cout << "The insertion 3 result is " << result << endl;


	cout << "I have arrived here" << endl;
	tbTree.preOrderTraverse(*visit);
	cout << "I have finished here " << endl;


}
