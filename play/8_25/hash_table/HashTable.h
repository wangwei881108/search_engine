#ifndef _HAXI_H_
#define _HAXI_H_

#include <iostream>

#define EQ(a,b) ((a) == (b))


using namespace std;

const int SUCCESS=1;
const int UNSUCCESS=0;
const int DUPLICATE=-1;

const int EMPTY = 0;
const int TOMB = -1;

const int N=4;
int hashsize[n] = {11,19,37,73};



typedef int KeyType;
typedef struct HD
{
	KeyType key;
	int order;	
} D;

class HashTable
{
	D *elem;
	int count, length;  // length is the size of the hash table
	int sizeindex;
	int *rando;	
	
	int Hash(KeyType Key)
	{
		return Key%length;   //length is the size of the hash table	
	}
	
	int Hash2(KeyType Key)
	{
		return Key % (length-2);
	}
	
	Void Random()
	{
		bool *ra = new bool[length];
		rand = new int[length];
		
		// Initialization of ra
		for (int i=0; i<length; i++){
			ra[i] = false;
		}
		
		// give values to rando
		for(int i=0; i<length; i++){
			do
			{
				rando[i] = rand() % (length-1) + 1;
				if(!ra[rando[i]]){
					ra[rando[i]] = true;
				} else {
					rando[i] = 0;
				}
			} while (rando[i] ==0);
			cout << "rando[" << i << "]=" << rando[i] << endl;
		}
	}
	
	// *********************************************
	int d(int i, KeyType Key)
	{
		switch(type)
		{
			case 0: return i;
			case 1: return ((i+1)/2) * ((i+1)/2) * (int)pow(-1, i-1);
			case 2: return i*Hash2(Key);
			case 3: return rando[i];
			default: return i;
		}	
		
	}
	
	
	// *********************************************
	
	// get the address p which is the ith collision of Key
	void collision(KeyType Key, int &p, int i)
	{
		p=(Hash(Key) + d(i,Key)) % length;
		if(p<0){
			p=p+length;
		}
	}
	
	// *********************************************
	void RecreateHashTable()
	{
		
	}
	
	
public:
	
	// Function 1
	int type; // the type of probing method
	
	// Function 2
	HashTable()
	{
		count = 0;
		sizeindex=0; length = hashsize[sizeindex];
		
		elem = new D[length];
		assert (elem!=NULL);
	
		for(int i=0; i<length; i++){
			elem[i].key = EMPTY;
		}	
		
		cout << "Please choose the method for probing:0: linear; 1:qua; 2;3random : ";
		cin >> type;
		if(type==3){
			Random();	
		} else {
			rando = NULL;	
		}
	}
	
	// Function 3
	~HashTable()
	{
		if (elem != NULL){
			delete []elem;
		} 	
		if(type==3){
			delete []rando;
		}
	}
	
	
	//Function 4, c is the number of collision 
	bool SearchHash(KeyType Key, int &p, int &c)
	{
		int c1, tomb=-1;   // tomb: the position of the first tomb, c1 is the number of collision
		p=Hash(Key);
		
		while(elem[p].key==TOMB || elem[p].key != EMPTY && !EQ(Key,elem[p].key)){
			
		}
	}
	
	
	
	
};



#endif