#include <set>
#include <iostream>

using namespace std;

class PQNode
{
public:
	double error;
	int num;

	PQNode(double error, int num){
		this->error = error;
		this->num = num;
	}
	bool operator< (const PQNode & p) const{
		return error < p.error;
	}
};

int main(){
	set<PQNode> pq;
	PQNode n1(10.0,1);
	PQNode n2(20.0,2);
	PQNode n3(5.0, 3);
	pq.insert(n1);
	pq.insert(n2);
	pq.insert(n3);
	
	set<PQNode>::iterator it;
	for(it = pq.begin(); it!=pq.end(); it++){
		cout << (*it).error << endl;
	}


}


