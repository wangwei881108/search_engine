#include "suboptimal.h"
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>

using namespace std;

int main(){
	
	vector<int> ei1(4,100);
	vector<int> mi1(4,110);
	hyperEdge edge1;
	edge1.edgeIndex = ei1;
	edge1.mappedInfo = mi1;
	vector<int> J_index1(4,120);
	candElem c1;
	c1.weight = 50.1;
	c1.outEdge = edge1;
	c1.J_index = J_index1;

	vector<int> ei2(5,200);
    vector<int> mi2(5,210);
	hyperEdge edge2;
	edge2.edgeIndex = ei2;
	edge2.mappedInfo = mi2;
	vector<int> J_index2(5,220);
	candElem c2;
	c2.weight = 60.1;
	c2.outEdge = edge2;
	c2.J_index = J_index2;

	vector<int> ei3(6,300);
    vector<int> mi3(6,310);
	hyperEdge edge3;
	edge3.edgeIndex = ei3;
	edge3.mappedInfo = mi3;
	vector<int> J_index3(6,320);
	candElem c3;
	c3.weight = 70.1;
	c3.outEdge = edge3;
	c3.J_index = J_index3;

	vector<int> ei4(7,400);
    vector<int> mi4(7,410);
	hyperEdge edge4;
	edge4.edgeIndex = ei4;
	edge4.mappedInfo = mi4;
	vector<int> J_index4(7,420);
	candElem c4;
	c4.weight = 80.1;
	c4.outEdge = edge3;
	c4.J_index = J_index3;

//	map<hyperNode, priority_queue<candElem, vector<candElem>, comparison> > mymap;

	priority_queue<candElem, vector<candElem>, comparison> pq1;
	pq1.push(c2);
	pq1.push(c1);
	pq1.push(c3);
	priority_queue<candElem, vector<candElem>, comparison> pq2;
	pq2.push(c3);
	pq2.push(c4);
	pq2.push(c2);

	unordered_map<hyperNode, priority_queue<candElem, vector<candElem>, comparison> > mymap;
	
	hyperNode hn1;
	hyperNode hn2;
	vector<int> ni1(2,500);
	vector<int> mpp1(2,510);
	hn1.nodeIndex = ni1;
	hn1.mappedInfo = mpp1;

	vector<int> ni2(2,530);
	vector<int> mpp2(2,540);

	hn2.nodeIndex = ni2;
	hn2.mappedInfo = mpp2;
	
	mymap[hn1] = pq1;
	mymap[hn2] = pq2;
	
	priority_queue<candElem, vector<candElem>, comparison> pq3;
	pq3 = mymap[hn1];
	
	candElem ce = pq3.top();
	cout << ce.weight << endl;
	pq3.pop();
	ce = pq3.top();
	cout << ce.weight << endl;
	pq3.pop();
	ce = pq3.top();
	cout << ce.weight << endl;
	
	priority_queue<candElem, vector<candElem>, comparison> pq4;
	pq4 = mymap[hn2];
	candElem ce2 = pq4.top();
	cout << ce2.weight << endl;
	pq4.pop();
	ce2 = 	pq4.top();
	cout << ce2.weight << endl;
	
	pq4.pop();
	ce2 = pq4.top();
	cout << ce2.weight << endl;




/* test 1 ******************************
	unordered_map<hyperNode, int> mymap;
	hyperNode hn1;
	hyperNode hn2;
	vector<int> ni1(2,500);
	vector<int> mpp1(2,510);
	hn1.nodeIndex = ni1;
	hn1.mappedInfo = mpp1;

	vector<int> ni2(2,530);
	vector<int> mpp2(2,540);

	hn2.nodeIndex = ni2;
	hn2.mappedInfo = mpp2;

	mymap[hn1] = 5;
	mymap[hn2] = 10;
	cout << mymap[hn2] << endl;
*/

	return 0;
}
