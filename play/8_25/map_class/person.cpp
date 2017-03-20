#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

typedef struct Person{
public:
	string phone;
	string name;
	string address;
	
	bool operator== (const Person &p) const
	{
		return this->phone == p.phone && this->name == p.name && this->address==p.address;	
	}
	
} Person;


namespace std{
	template <>
	struct hash<Person>{
		size_t operator() (const Person &p) const{
		return ((hash<string>()(p.phone)^ (hash<string>()(p.name) << 1)) >> 1) ^ (hash<string>()(p.address) << 1);
		}	
	};	
	
}



int main(){
	
	unordered_map<Person, string> phoneMap;
	Person p1;
	p1.name = "Alain";
	p1.phone = "162626261";
	p1.address = "LRI";

	Person p2;
	p2.name = "Yann";
	p2.phone = "383838383";
	p2.address = "LIX";
	
	phoneMap.insert(make_pair(p1, "wei"));
	phoneMap.insert(make_pair(p2, "wang"));
	
	string ss = phoneMap[p1];
	cout << ss << endl;
	
	return 0;	
}