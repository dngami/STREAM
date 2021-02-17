#include<iostream>
#include<vector>
#include<bits/stdc++.h>

using namespace std;

class LSearch{
  public:
   LSearch(vector<vector<double>> spacePoints,
          double (*d)(vector<double> , vector<double>),
          double k,
          double e,
          double e1,
          double e2){
    this->spacePoints = spacePoints;
    this-> d  = d;
    this->k = k;
    this->e = e;
    this->e1 = e1;
    this->e2 = e2;
    this->zMin = 0;
    this->indexesForShuffle.clear();
    this->g.clear();
    this->g.resize(spacePoints.size());
    int i;
    for(i=0;i<spacePoints.size();i++){
      indexesForShuffle.push_back(i);
      feasibleCenters.push_back(i);
    }
    this->zMax = findzMax();

  //  cout<<"zMax:"<<this->zMax<<endl;
  }

  vector<int> run(){

    double z = (zMin+zMax)/2;
    initialSolution(z);
    while(listOfMedians.size() != k && zMin < (1-e2)*zMax){
     //cout<<zMin<<" "<<zMax<<" "<<z<<endl;
     // for(int i=0;i<g.size();i++){
     //    cout << g[i] << " ";
     // }

     // cout << endl;

    // for(auto i:listOfMedians){
    //     cout << i.first << " ";
    //   }
    //   cout<<endl;
      FL(z);

      // for(auto i:listOfMedians){
      //    cout << i.first << " ";
      //  }
      // cout<<endl;
      if(listOfMedians.size()>k){
        zMin= z ;
      }
      else{
        zMax=z;
      }
      z = (zMin+zMax)/2;
    }

    vector <int> listOfMedianIndexes;
    for(auto i:listOfMedians){
      listOfMedianIndexes.push_back(i.first);
    }
    return listOfMedianIndexes;
  }

  private:
    vector<vector<double>> spacePoints;
    vector<int> feasibleCenters; //
    double k, e, e1,  e2 , zMin, zMax;
    double (*d)(vector<double> , vector<double>);
    vector<int> g;
    unordered_map<int,int> listOfMedians;
    vector <int> indexesForShuffle;

    vector <int> advantage_temp;
    double Cost;



  double findzMax(){
    double zMax = 0;
    int i;
    for(i=1;i<spacePoints.size();i++){
      zMax+= d(spacePoints[i],spacePoints[0]);
    }
    return zMax;
  }


  double randZeroToOne(){
      return rand() / (RAND_MAX + 1.);
  }


  double nearestCentreDistance(int index, int *c){
    int i;
    double dmin = DBL_MAX;
    for(auto x:listOfMedians){
      if (dmin>d(spacePoints[index],spacePoints[x.first])){
        dmin = d(spacePoints[index],spacePoints[x.first]);
        *c = x.first;
      }
    }
    return dmin;
  }

  void initialSolution(double z){
    srand(time(0));
    int i,c;
    double distance,samplingRatio,randomDouble;
    random_shuffle(indexesForShuffle.begin(),indexesForShuffle.end());
    listOfMedians[indexesForShuffle[0]]=0;
    //cout<<"rand shuffle:"<<indexesForShuffle[0]<<endl;
    for(i=1;i<indexesForShuffle.size();i++){
      distance = nearestCentreDistance(indexesForShuffle[i],&c);
      samplingRatio = (double)(distance)/z;
      randomDouble = randZeroToOne();
      if(randomDouble<=samplingRatio){

        listOfMedians[indexesForShuffle[i]]=0;
      }
    }

    // initialize the assignment function
    Cost = z*listOfMedians.size();
    for(i=0;i<spacePoints.size();i++){
      Cost+= nearestCentreDistance(i,&g[i]);
    }

    for(i=0;i<spacePoints.size();i++){
      listOfMedians[g[i]]++;
    }

    cout<<"after initial solution, number of medians = "<<listOfMedians.size()<<" Cost = "<<Cost<<endl;

  }

  double gain(int x, double z){
    double diff = 0;
    double diff_temp;
    for(int i=0;i<spacePoints.size();i++){
      diff_temp = d(spacePoints[i],spacePoints[x]) - d(spacePoints[i],spacePoints[g[i]]);
      if(diff_temp < 0){
        advantage_temp.push_back(i);
        diff += diff_temp;
      }
    }
  //  cout<<"diff:"<<diff<<" z:"<<z<<endl;
    return (z+diff);
  }

  void FL(double z){
    double Cost_dash = Cost;
    advantage_temp.clear();

    int index = 0;
    int currentCentre ;
    random_shuffle(feasibleCenters.begin(), feasibleCenters.end());
    while (Cost_dash > (1-e)*Cost && index<feasibleCenters.size() ) {
      currentCentre = feasibleCenters[index];
      double totalGain = gain(currentCentre,z);
    //  cout<<"TotalGain :"<<totalGain<<endl;
      //cout<<Cost_dash<<" "<<Cost<<endl;
      if(totalGain < 0){
        //cout<<"+ve gain"<<endl;
        Cost_dash = Cost_dash + totalGain;
        for(int i=0;i<advantage_temp.size();i++){
          listOfMedians[g[advantage_temp[i]]]--;
          if(listOfMedians[g[advantage_temp[i]]] == 0){
            listOfMedians.erase(g[advantage_temp[i]]);
          }
          g[advantage_temp[i]] = currentCentre;
          listOfMedians[currentCentre]++;
        }
      }
      index++;
      //index = (index+1)%feasibleCenters.size();
      //cout<<"index: "<<index<<endl;
    }
  }
};
