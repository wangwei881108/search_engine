#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int main(){

	ostringstream oss;
	vector<int> a1;
	a1.push_back(0);
	a1.push_back(-1);
	a1.push_back(2);

	for(int i=0; i<a1.size(); i++){
		oss << a1[i];
	}
	
	cout << "I arrive herer" << endl;
	string s = oss.str();
	cout << s << endl;
	
	return 0;
}


