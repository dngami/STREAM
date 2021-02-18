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
  int k;
  cout<<"Required No. of Medians, K : ";
  cin>>k;

  double e=0.0001, e1=0.0001, e2= 0.00000001;

  int chunkLimit;// = 500;
  cout<<"Chunk Size Limit: ";
  cin>>chunkLimit;

  int chunkSize = 0;
  int memoryLimit = 500;
  string myText;
  string inputFileName;//="test";
  cout<<"Input dataset file name: ";
  cin>>inputFileName;
  ifstream MyReadFile(inputFileName);

  vector <int> medians;
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
        tempMedians.clear();
        tempFinalMedians.clear();
        tempMedians = lsearchObjTemp->run();
        for(int i=0 ; i<tempMedians.size() ; i++){
          tempFinalMedians.push_back(finalMedians[tempMedians[i]]);
        }
        finalMedians.clear();
        finalMedians = tempFinalMedians;
      }
      LSearch* lsearchObj = new LSearch(spacePoints,SSQ,k,e,e1,e2);
      medians.clear();
      medians = lsearchObj->run();
      cout<<"Number of medians:"<<medians.size()<<endl;
      for(int i=0;i<medians.size();i++){
        finalMedians.push_back(spacePoints[medians[i]]);
      }
      cout<<"Number of Final medians:"<<finalMedians.size()<<endl;
      cout<<endl;
      spacePoints.clear();
    }
  }
  MyReadFile.close();

  if(finalMedians.size()>k){ // finalMedians.size()>k
    tempMedians.clear();
    tempFinalMedians.clear();
    LSearch * lsearchObjTemp = new LSearch(finalMedians,SSQ,k,e,e1,e2);
    tempMedians = lsearchObjTemp->run();
    for(int i=0 ; i<tempMedians.size() ; i++){
      tempFinalMedians.push_back(finalMedians[tempMedians[i]]);
    }
    finalMedians.clear();
    finalMedians = tempFinalMedians;
  }
  cout<<endl<<"Total no. of medians: "<<finalMedians.size()<<endl;

  ofstream MyWriteFile(inputFileName+"_output");

  for(int i=0;i<finalMedians.size();i++)

  MyWriteFile<<finalMedians[i][0]<<"   "<<finalMedians[i][1]<<endl;
  return 0;
}
