#include "bag.h"

using namespace std;


    // Adds an index to current bag, should keep the index list sorted.
    void Bag::addIndex(int index)
    {
      // TODO: use binary search to keep vector sorted
      // for the moment, crashes loudly if indices are not added in the right order!
      if (indices.size()>0)
      {
        assert(indices[indices.size()-1]<index);
      }
      indices.push_back(index);
    }

    void Bag::insertIndex(int index)
    {
        if(!hasPos(index))
        {
            int i = 0 ;
            while(i<indices.size() && index>indices[i])
                i++ ;
            indices.insert(indices.begin()+i, index) ;
        }
    }

    vector<int> Bag::getIndices() const
    {
      return indices;
    }

    int Bag::getIndex(int i)
    {
        return indices[i] ;
    }

    int Bag::getPosOfIndex(int index) const
    {
      for(int i=0; i<indices.size();i++)
  		{
  			int j =indices[i]-1;
  			if (j==index)
  			return i;
  		}
      return -1;
    }




    // Returns the positions in current bag that are not found in the given bag b.
    vector<int> Bag::getDiff(const Bag & b)
    {
      vector<int> result;
      int i=0;
      int j=0;
      while ((i<indices.size())&&(j<b.indices.size()))
      {
        // Either the first elements of both bags are equal
        // => Skip them and move on...
        if (indices[i]==b.indices[j])
        {
          i++; j++;
        }
        // Otherwise, they differ on their first position...
        else
        {
          // ...if the first position in current bag is smaller than that of the "other" bag b,
          // then it will not be found in any subsequent position of b (remember that positions
          // are sorted increasingly), and it must be returned...
          if (indices[i]<b.indices[j])
          {
            result.push_back(i);
            i++;
          }
          // ...otherwise it is larger, and we may still find this position somewhere further in bag b.
          else
          {
            j++;
          }
        }
      }
      // We know either i or j is past some bag capacity...
      //... if it is j (and only it), then the position found at i is not in bag b and must be returned...
      while (i<indices.size())
      {
        result.push_back(i);
        i++;
      }
      return result;
    }

    int Bag::isIncluded(const Bag & b)
    {
        if(getDiff(b).size() == 0)
            return 1;
        else
            return 0;
    }

    // Returns the common positions of current bag and argument.
    vector<int> Bag::getCommon(const Bag & b)
    {
      vector<int> result;
      int i=0;
      int j=0;
      while ((i<indices.size())&&(j<b.indices.size()))
      {
        // Either the first elements of both bags are equal
        // => Skip them and move on...
        if (indices[i]==b.indices[j])
        {
          result.push_back(i);
          i++; j++;
        }
        // Otherwise, they differ on their first position...
        else
        {
          // ...if the first position in current bag is smaller than that of the "other" bag b,
          // then it will not be found in any subsequent position of b (remember that positions
          // are sorted increasingly), and it must be returned...
          if (indices[i]<b.indices[j])
          {
            i++;
          }
          // ...otherwise it is larger, and we may still find this position somewhere further in bag b.
          else
          {
            j++;
          }
        }
      }
      return result;
    }

    int Bag::size() const{
      return indices.size();
    }

    void Bag::clearIndices(){
        indices.clear() ;
    }

    int Bag::hasPos(int pos){
        for(int i=0; i<indices.size(); i++)
        {
            if(pos==getIndex(i))
                return 1;
        }
        return 0;
    }
