#include <iostream>
#include <fstream>
#include <string>
#include "treedecomposition.h"
#include "bag.h"
#include <getopt.h>
#include <vector>
#include "AdjListGraph.h"
#include "InputScore.h"


using namespace std;


void help(string what)
{
    string text = "";
    if (what.size() > 0) {
        text.append("[ ");
        text.append(what);
        text.append(" ]\n\n");
    }
    text.append("'aligner' aligns an RNAML structure with a given RNA sequence.\n\n");
    text.append("Usage: aligner -i score_path -t td.dot -q length_of_query -s length_of_target\n");
    text.append("-i <path>: input score path\n");
    text.append("-t <path>: tree decomposition of structure in dot format\n");
    text.append("-q       : the length of the query structure\n");
    text.append("-s       : the length of the target sequence\n");
    cerr << text << "\n";
}

void produceNode(int bagIndex,
    int indexSize,
    vector<int> indices,
    vector<bool> isMapped,
    int m,
    AdjListGraph & outGraph,
    int previousIndex)
{
    if(indices.size() < indexSize){
        for(int d=0; d<m-previousIndex; d++){
        		int currentIndex = previousIndex+d;
            indices.push_back(currentIndex);
            isMapped.push_back(true);
            produceNode(bagIndex, indexSize, indices, isMapped, m, outGraph,currentIndex);
            isMapped.pop_back();

            isMapped.push_back(false);
            produceNode(bagIndex, indexSize, indices, isMapped, m, outGraph, currentIndex);
            isMapped.pop_back();

            indices.pop_back();
        }
    } else {
        VerT vTmp;
        vTmp.bagIndex = bagIndex;
        for(int i=0; i<indices.size(); i++){
            vTmp.pIndex.push_back(indices[i]);
        }
        for(int i=0; i<isMapped.size(); i++){
            vTmp.pIndex.push_back(isMapped[i]);
        }
        outGraph.InsertVex(vTmp);
    }

}


int main(int argc, char * argv[]){
    string td_path;
    string score_path;
    string output_path;
    int qLen;
    int sLen;
    string argdef = "hi:t:q:s:o:";
    int opt;

    while ((opt = getopt(argc, argv, argdef.c_str())) != EOF) {
        switch(opt) {
            case 'h':
                help("");
                exit(1);
                break;
            case 'i':
                score_path = optarg;
                break;
            case 't':
                td_path = optarg;
                break;
            case 'q':
                qLen = atoi(optarg);
                break;
            case 's':
                sLen = atoi(optarg);
                break;
            case 'o':
                output_path = optarg;
                break;
            default:
                cerr << "Unsupported argument" << "\n";
        }
    }

    if (td_path.size() == 0) {
        help("No path provided for the tree decomposition");
        exit(1);
    }
    if (score_path.size() == 0) {
        help("No path provided for the sequence to compare");
        exit(1);
    }
//    cout << score_path << " " << td_path << " " << qLen << " " << sLen << endl;

    TreeDecomposition td;
    td.importAsDot( td_path );

    AdjListGraph outGraph;
    VerT start;
    start.bagIndex = -1;
    outGraph.InsertVex(start);


    vector<int> ranks = td.getComputationOrder();
    for(int i=0; i<ranks.size(); i++){
        int id = ranks[i];
        Bag b = td.getBag(id);

        // bp will hold the set of positions inherited from the parent
        // It will be empty by default, e.g. in the absence of a parent
        int idparent = td.getParent(id);

        vector<int> bp;
        if (idparent!=-1)
        {
             bp = b.getCommon(td.getBag(idparent));
        } else {
            for(int bdi=0; bdi<b.size(); bdi++){
                bp.push_back(bdi);
            }
        }
        // bv ranges from 1 to qLength;
        vector<int> bv = b.getIndices();
        vector<int> indices;
        vector<bool> isMapped;
        produceNode(id, bp.size(), indices, isMapped, sLen, outGraph, 0);

    }

    VerT endNode;
    endNode.bagIndex = -2;
    outGraph.InsertVex(endNode);

    InputScore ScoreIndex;
    ScoreIndex.CreateFromFile(score_path);

    int count=0;
    for(int i=0; i<ranks.size(); i++){
        // get all the score case.
        vector<struct scoreScan> scoreTmp = ScoreIndex.getOneDIndex(count);

        int id = ranks[i];
        Bag b = td.getBag(id);
//        cout << b << endl;

        // bp will hold the set of positions inherited from the parent
        // It will be empty by default, e.g. in the absence of a parent
        int idparent = td.getParent(id);

        vector<int> bp;
        if (idparent!=-1)
        {
             bp = b.getCommon(td.getBag(idparent));
        } else {
            for(int bdi=0; bdi<b.size(); bdi++){
                bp.push_back(bdi);
            }
        }

        // Precomputing the list/number of indices shared with
        // current bag's own children. This precomputation will
        // be handy for projecting main vectors on their children
        // or parent index spaces.
        vector<int> children = td.getChildrenIds(id);
        vector<vector<int> > commonindices;

        for (int j=0;j<children.size();j++)
        {
            int p = children[j];
            Bag child = td.getBag(p);
            vector<int> bc = b.getCommon(child);
            commonindices.push_back(bc);
        }


        for(int j=0; j<scoreTmp.size(); j++){
            struct scoreScan sss = scoreTmp[j];
      /*      
            for(int in1=0; in1<sss.index.size(); in1++){
            		cout << sss.index[in1] << " ";
            }
            cout << sss.contrib << " ";
            cout << sss.nodeScore << " ";
       */     
            VerT toNode;
			//			cout << endl;

            toNode.bagIndex = id;
            for(int jj=0; jj<bp.size(); jj++){
            	toNode.pIndex.push_back(sss.index[bp[jj]]);
            }

            for(int jj=0; jj<bp.size(); jj++){
                toNode.pIndex.push_back(sss.index[ bp[jj]+ sss.index.size()/2 ]);
            }


						
						int location1 = outGraph.LocateVex(toNode);
			//			cout << "toNode bag: " << location1 << endl;
						/*
						cout << "bagIndex: " << toNode.bagIndex << " " ;
						for (int k=0; k<toNode.pIndex.size(); k++){
							cout << toNode.pIndex[k] << " ";
						}
						
						cout << endl;*/
						
						if(children.empty()){
            	VerT fromvv;
            	fromvv.bagIndex = -1;
            	int location2 = outGraph.LocateVex(fromvv);
       //     	cout << "fromNode: "<< location2 << endl;
            	outGraph.InsertArc(fromvv, toNode, sss.contrib, sss.index);
            } else {
            	for(int jj=0;jj<children.size();jj++){
              	vector<int> bc = commonindices[jj];
              	VerT fromvvv;
                fromvvv.bagIndex = children[jj];
                for(int jjj=0; jjj<bc.size(); jjj++){
                	fromvvv.pIndex.push_back(sss.index[bc[jjj]]);
                }
                for(int jjj=0; jjj<bc.size(); jjj++){
                	fromvvv.pIndex.push_back(sss.index[ bc[jjj] + sss.index.size()/2 ]);
                }
                outGraph.InsertArc(fromvvv, toNode, sss.contrib, sss.index);
            //    cout <<  "fromNode: " << outGraph.LocateVex(fromvvv) << " ";
            	
            	}
       //     	cout << endl;
          	}
								/*
                vector<VerT> fromNodeV;
                if(children.empty()){
                    VerT fromvv;
                    fromvv.bagIndex = -1;
                     outGraph.InsertArc(fromvv, toNode, sss.contrib, sss.index);
                } else {
                    for(int jj=0;jj<children.size();jj++){
                        vector<int> bc = commonindices[jj];
                        VerT fromvvv;
                        fromvvv.bagIndex = children[jj];
                        for(int jjj=0; jjj<bc.size(); jjj++){
                            fromvvv.pIndex.push_back(sss.index[bc[jjj]]);
                        }
                        for(int jjj=0; jjj<bc.size(); jjj++){
                            fromvvv.pIndex.push_back(sss.index[ bc[jjj] + sss.index.size()/2 ]);
                        }
                        outGraph.InsertArc(fromvvv, toNode, sss.contrib, sss.index);
                    }
                }
                */
           
        }
        count ++; 
        
    }
//		outGraph.displayNode();
    cout << outGraph.outRelation();


	return 0;
}