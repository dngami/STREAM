#include "lstream.h"

double SSQ(vector <double> v1, vector <double> v2 ){
  double ssq = 0;
  int i;
  for(i=0;i<v1.size();i++){
    ssq+= (v1[i]-v2[i])*(v1[i]-v2[i]);
  }
  return ssq;
}

int main(){
  vector <vector <double> > spacePoints;
  int k=8;

  double e=0.0001, e1=0.0001, e2= 0.00000001;

  int chunkLimit = 500;
  int chunkSize = 0;
  int memoryLimit = 500;
  string myText;
  string fileName;
  cout<<"Input dataset file name"<<endl;
  cin>>fileName;
  ifstream MyReadFile(fileName);
  vector <vector <double> > finalMedians;
  vector <vector <double> > tempFinalMedians;
  vector<int> tempMedians;
  int chunkNumber = 0;

  while (getline (MyReadFile, myText)) {
     istringstream ss(myText);
     string word;
     vector<double> temp;
    while (ss >> word)
    {
      temp.push_back(stod(word));
    }
    spacePoints.push_back(temp);
    chunkSize++;

    if(chunkSize==chunkLimit|| MyReadFile.peek()==EOF ){
      chunkSize = 0;
      cout<<"Chunk Number: "<<chunkNumber++<<endl;
      if(finalMedians.size()+k > memoryLimit){
        LSearch* lsearchObjTemp = new LSearch(finalMedians,SSQ,k,e,e1,e2);
        tempMedians = lsearchObjTemp->run();
        for(int i=0 ; i<tempMedians.size() ; i++){
          tempFinalMedians.push_back(finalMedians[tempMedians[i]]);
        }
        finalMedians = tempFinalMedians;
      }
      LSearch* lsearchObj = new LSearch(spacePoints,SSQ,k,e,e1,e2);
      vector <int> medians = lsearchObj->run();
      int i;
      cout<<"Number of medians:"<<medians.size()<<endl;
      for(int i=0;i<medians.size();i++){
      //  cout<<medians[i]<<" ";
        finalMedians.push_back(spacePoints[medians[i]]);
      }
      cout<<"Number of Final medians:"<<finalMedians.size()<<endl;
      cout<<endl;
      spacePoints.clear();
    }
  }
  MyReadFile.close();

  if(finalMedians.size()>k){ // finalMedians.size()>k
    LSearch * lsearchObjTemp = new LSearch(finalMedians,SSQ,k,e,e1,e2);
    tempMedians = lsearchObjTemp->run();
    for(int i=0 ; i<tempMedians.size() ; i++){
      tempFinalMedians.push_back(finalMedians[tempMedians[i]]);
    }
    finalMedians = tempFinalMedians;
  }


  cout<<endl<<"Total no. of medians: "<<finalMedians.size()<<endl;
  for(int i=0;i<finalMedians.size();i++)
  cout<<finalMedians[i][0]<<"   "<<finalMedians[i][1]<<endl;
  return 0;
}
