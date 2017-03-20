#include <iostream>

using namespace std;

int main(){
	double value = 1e-8;
	double value2 = 1e-9;
	cout << "part 1: " << value/(value+value2) << " and " << value2/(value+value2) << endl;
	return 0;
}
