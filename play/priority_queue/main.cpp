#include <vector>
#include <queue>
#include <iostream>
#include <functional>  
using namespace std;


/*
struct PQNode{
	double error;
};

struct compNode{
	bool operator()(PQNode & p, PQNode & q){
		if(p.error > q.error){
			return true;
		}else{
			return false;	
		}
	}
};
*/

/*
class PQNode
{
public:
	double error;                 
	bool operator< (PQNode * a){
		return error < a->error;
	}
	bool operator> (PQNode * a){
		return error > a->error;
	}

};
*/


int main(){
	priority_queue<PQNode,vector<PQNode>,compNode > pq2;
	
	vector<PQNode> b(4);
	b[0].error = 1.6;
	b[1].error = 0.8;
	b[2].error = 4.8;
	b[3].error = 3.2;

	for(int i=0; i<4; i++){
		pq2.push(b[i]);
	}

	for(int i=0; i<4; i++){
		cout << pq2.top().error << endl;
		pq2.pop();
	}

}

 