#ifndef _BAG_H
#define _BAG_H

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>

#include <assert.h>

using namespace std;

class Bag{
  private:
    vector<int> indices;
  public:
    // Adds an index to current bag, should keep the index list sorted.
    void addIndex(int index);
    void insertIndex(int index) ;

    vector<int> getIndices() const;
    int         getIndex(int i) ;

    int getPosOfIndex(int i) const;

    void clearIndices() ;

    int hasPos(int pos) ;

    // Returns the elements in current bag that are not found in the given bag b.
    vector<int> getDiff(const Bag & b);
    // Returns the common elements of current bag and argument.
    vector<int> getCommon(const Bag & b);
    // Does the current bag included in the bag b?
    int isIncluded(const Bag & b) ;

    // To display bags properly....
    friend ostream & operator<<(ostream & o, const Bag & b)
    {
      o << "Bag: ";
      return o << b.toString();
    }

    int size() const;

    string toString() const    {
      ostringstream o;
      o << "[";
      for (int i=0;i<indices.size();i++)
      {
        if (i>0)
        {  o << ","; }
        o << indices[i];
      }
      o << "]";
      return o.str();
    }


};

#endif
