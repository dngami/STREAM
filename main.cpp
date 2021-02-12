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
  int k=10;
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
    if(chunkSize==chunkLimit){
      chunkSize = 0;
      if(finalMedians.size()+k > memoryLimit){
        LSearch* lsearchObjTemp = new LSearch(finalMedians,SSQ,k,0.000000001,0.000000001,0.000000001);
        tempMedians = lsearchObjTemp->run();
        for(int i=0 ; i<tempMedians.size() ; i++){
          tempFinalMedians.push_back(finalMedians[tempMedians[i]]);
        }
        finalMedians = tempFinalMedians;
      }
      LSearch* lsearchObj = new LSearch(spacePoints,SSQ,k,0.000000001,0.000000001,0.000000001);
      vector <int> medians = lsearchObj->run();
      int i;
    //  cout<<"Number of medians:"<<medians.size()<<endl;
      for(int i=0;i<medians.size();i++){
      //  cout<<medians[i]<<" ";
        finalMedians.push_back(spacePoints[medians[i]]);
      }
      cout<<endl;
      spacePoints.clear();
    }
  }
  MyReadFile.close();

//  spacePoints = {{6,6},{6,8},{6,4},{8,6},{4,6},{-6,-6},{-6,-8},{-6,-4},{-8,-6},{-4,-6}};
  if(finalMedians.size()+k > memoryLimit){
    LSearch * lsearchObjTemp = new LSearch(finalMedians,SSQ,k,0.000000001,0.000000001,0.000000001);
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
