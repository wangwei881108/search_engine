//Algo6-4.cpp 验证HashTable类的成员函数
#include "C.h"
#include "C4-1.h"
const int EMPTY=0;
const int TOMB=-1;
typedef int KeyType;
#include "HashTable.h"
#include "Func6-3.cpp"
void main()
{
	HashTable<HD> h;
	int i, j, n, p=0;
	bool m;
	HD e;
	KeyType k;
	ifstream fin("F6-4.txt");
	fin>>n;
	for(i=0; i<n; i++)
	{
		InputFromFile(fin, e);
		j=h.InsertHash(e);
		if(j==DUPLICATE)
		{
			cout<<"哈希表中已有关键字为"<<e.key<<"的数据，无法再插入数据";
			Visit(e);
			cout<<endl;
		}
		if(j==UNSUCCESS)
			j=h.InsertHash(e);
	}
	fin.close();
	cout<<"按哈希地址的顺序遍历哈希表："<<endl;
	h.TraverseHash(Visit);
	if(h.type==1)
	{
		cout<<"请输入待删除数据的关键字：";
		InputKey(k);
		m=h.DeleteHash(k, e);
		if(m)
		{
			cout<<"成功删除数据";
			Visit(e);
			cout<<endl;
		}
	}
	cout<<"请输入待查找数据的关键字：";
	InputKey(k);
	n=0;
	j=h.SearchHash(k, p, n);
	if(j==SUCCESS)
	{
		Visit(h.GetElem(p));
		cout<<endl;
	}
	else
		cout<<"未找到"<<endl;
	if(h.type==1)
	{
		cout<<"插入数据，请输入待插入数据的关键字：";
		InputKey(e.key);
		cout<<"请输入待插入数据的order：";
		cin>>e.order;
		j=h.InsertHash(e);
		cout<<"按哈希地址的顺序遍历哈希表："<<endl;
		h.TraverseHash(Visit);
	}
}

