#ifndef _INPUT_SCORE_H
#define _INPUT_SCORE_H

#include "C.h"

struct scoreScan{
    vector<int> index;
    double contrib;
    double nodeScore;
};

class InputScore{
private:
    vector<vector<struct scoreScan> > bagInfo;

public:
    void CreateFromFile(string fileName){
        const char *path = fileName.c_str();
        ifstream inFile;
        inFile.open(path, ios::in);
        string strtmp;
        vector<struct scoreScan> oneInfo;

        while(getline(inFile, strtmp, '\n')){
            if (strtmp[0] == 'B' and !oneInfo.empty()){
                bagInfo.push_back(oneInfo);
                oneInfo.clear();
                continue;
            }

            if(strtmp[0] == 'B'){
                continue;
            }
            struct scoreScan ss;
            vector<int> indexTmp;
            double contribTmp;
            double nodeScoreTmp;
            dealWithLine(strtmp, indexTmp, contribTmp, nodeScoreTmp);

            ss.index = indexTmp;
            ss.contrib = contribTmp;
            ss.nodeScore = nodeScoreTmp;
            oneInfo.push_back(ss);
        }
        bagInfo.push_back(oneInfo);
    }

    vector<struct scoreScan> getOneDIndex(int index){
      return bagInfo[index];
    }

    void dealWithLine(string strtmp, vector<int> & indexTmp, double & contribTmp, double & nodeScoreTmp){
      vector<string> part = split(strtmp, " ");
      int posC = strtmp.find_first_of("c");
      int pos = posC/2;
      string::size_type sz;
      for(int i=0; i<pos; i++){
        int temp = stoi(part[i], &sz);
        indexTmp.push_back(temp);
      }

      string con = part[pos+1];

      contribTmp = stod(con, &sz);

      con = part[pos+3];
      nodeScoreTmp = stod(con, &sz);
    }

    vector<string> split(const string &s, const string &seperator){
        vector<string> result;
        typedef string::size_type string_size;
        string_size i = 0;

        while(i != s.size()){

          int flag = 0;
          while(i != s.size() && flag == 0){
          flag = 1;
          for(string_size x = 0; x < seperator.size(); ++x)
            if(s[i] == seperator[x]){
              ++i;
              flag = 0;
              break;
            }
          }

          flag = 0;
          string_size j = i;
          while(j != s.size() && flag == 0){
          for(string_size x = 0; x < seperator.size(); ++x)
            if(s[j] == seperator[x]){
              flag = 1;
              break;
            }
            if(flag == 0)
              ++j;
          }

          if(i != j){
            result.push_back(s.substr(i, j-i));
            i = j;
          }
        }
        return result;
      }



};

#endif