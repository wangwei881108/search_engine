#ifndef _ADJLISTGRAPH_H_
#define _ADJLISTGRAPH_H_
#include "C.h"

struct VerT{
    int bagIndex;
    vector<int> pIndex;
};

struct ArcT{
    double weight;
    vector<int> tIndex;
};

void InputArc(){

}

class AdjListGraph
{
protected:
    struct ArcTNode
    {
        int adjvex;
        struct ArcT arc;
    };
    struct VerTNode
    {
        struct VerT vex;
        list<ArcTNode> arcs;
    };

    vector<VerTNode> vexs;
    int ArcNum;
    bool Weight;
    bool Directed;


public:
    AdjListGraph(){
        ArcNum=0;
        Directed = false;
    }

    bool eqVerT(VerT u, VerT v) {
        if (u.bagIndex != v.bagIndex){
            return false;
        }
        if (u.pIndex.size() != v.pIndex.size()){
            return false;
        }
        for(int i=0; i<u.pIndex.size(); i++){
            if (u.pIndex[i] != v.pIndex[i]){
                return false;
            }
        }
        return true;
    }

    int LocateVex(VerT u)
    {
        for(int i=0; i<vexs.size(); i++){
            bool eqTmp = eqVerT(u, vexs[i].vex);
            if ( eqTmp ){
                return i;
            }
        }
        return -1;
    }

    void InsertVex(VerT v){
        VerTNode vv;
        vv.vex = v;
        vexs.push_back(vv);
    }

    bool InsertArc(VerT u, VerT v, double weightTmp, vector<int> tIndexTmp){
        ArcTNode e;
        int i,j;
        i = LocateVex(u);
        j = LocateVex(v);
        if (i<0 || j<0){
            return false;
        }
        ArcNum ++;
        e.adjvex = j;
        e.arc.weight = weightTmp;
        for(int i=0; i<tIndexTmp.size(); i++){
            e.arc.tIndex.push_back(tIndexTmp[i]);
        }
        vexs[i].arcs.push_front(e);
        if(Directed){
            e.adjvex = i;
            vexs[j].arcs.push_front(e);
        }
        return true;
    }

    void displayNode(){
        for(int i=0; i<vexs.size(); i++){
            VerTNode vv = vexs[i];
            cout << "The bag index is: " << vv.vex.bagIndex << " ";
            for(int j=0; j<vv.vex.pIndex.size(); j++){
                cout << vv.vex.pIndex[j] << " ";
            }
            cout << endl;
        }
    }

    string outRelation(){
        string result;
        result.append("graph G {\n\n");
        for (int i=0; i<vexs.size(); i++){
            string strtmp = "\tbag";
            VerTNode vexNode = vexs[i];
            int indexx = i+1;
            strtmp.append(to_string(indexx));
            strtmp.append(" [label=\"");
            strtmp.append("BagId ");
            strtmp.append(to_string(vexNode.vex.bagIndex));
            strtmp.append(" ");
            for(int j=0; j<vexNode.vex.pIndex.size(); j++){
                strtmp.append(to_string(vexNode.vex.pIndex[j]));
                strtmp.append(" ");
            }
            strtmp.append("\"]\n");
            result.append(strtmp);
        }
        result.append("\n");
        for(int i=0; i<vexs.size(); i++){
        	VerTNode vexNode = vexs[i];
        	list<ArcTNode>::iterator iter;
        	for(iter=vexNode.arcs.begin(); iter!=vexNode.arcs.end(); ++iter){
        		struct ArcTNode arcTmp = *iter;
        		result.append("\tbag");
        		result.append(to_string(i));
        		result.append(" -- bag");
        		result.append(to_string(arcTmp.adjvex));
        		result.append("\n");
        	}
        }
        
        result.append("\n}\n");
        /*
  			VerTNode vexNode = vexs[0];
  			list<ArcTNode>::iterator iter;
  			for(iter=vexNode.arcs.begin(); iter!=vexNode.arcs.end(); ++iter){
  					struct ArcTNode arcTmp = *iter;
  					cout << arcTmp.adjvex << endl;
  			}
  			*/
				return result;
    }

};
#endif