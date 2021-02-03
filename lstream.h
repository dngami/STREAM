#include<iostream>
#include<vector>
#include<bits/stdc++.h>

using namespace std;

class LSearch{
  private:
    vector<vector<double>> spacePoints;
    vector<int> feasibleCenters; //
    double k, e, e1,  e2 , zMin, zMax;
    double (*d)(vector<double> , vector<double>);
    vector<int> g;
    vector<int> listOfMedians;
    vector <int> indexesForShuffle;

    vector <int> advantage_temp;


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
    }
   // this->zMax = findzMax() ;
  }

  // double findzMax(){

  // }
  double randZeroToOne(){
      return rand() / (RAND_MAX + 1.);
  }


  double nearestCentreDistance(int index, int *c){
    int i;
    double dmin = DBL_MAX;
    for(i=0;i<listOfMedians.size();i++){
      if (dmin>d(spacePoints[index],spacePoints[listOfMedians[i]])){
        dmin = d(spacePoints[index],spacePoints[listOfMedians[i]]);
        *c = listOfMedians[i];
      }
    }
    return dmin;
  }

  void initialSolution(double z){
    int i,c;
    double distance,samplingRatio,randomDouble;


    random_shuffle(indexesForShuffle.begin(),indexesForShuffle.end());
    listOfMedians.push_back(indexesForShuffle[0]);

    for(i=1;i<indexesForShuffle.size();i++){
      distance = nearestCentreDistance(indexesForShuffle[i],&c);
      samplingRatio = (double)(distance)/z;
      randomDouble = randZeroToOne();
      if(randomDouble<=samplingRatio){
        listOfMedians.push_back(indexesForShuffle[i]);
      }
    }

    // initialize the assignment function

    for(i=0;i<spacePoints.size();i++){
      nearestCentreDistance(i,&g[i]);
    }

  }

  double gain(int x){
    double diff = 0;
    double diff_temp;
    for(int i=0;i<spacePoints.size();i++){
      diff_temp = d(spacePoints[i],spacePoints[x]) - d(spacePoints[i],spacePoints[g[i]]);
      if(diff_temp < 0){
        advantage_temp.push_back(i);
        diff += diff_temp;
      }
    }

    return (z+diff);
  }




  void FL(){

    double Cost;
    double Cost_dash;
    advantage_temp.clear();

    int index = 0;

    // random_shuffle(feasabile_centres)
    while (Cost_dash < (1-e)*Cost ) {
      currentCentre = feasibleCenters[index];
      double totalGain = gain(currentCentre);
      if(totalGain < 0){
        Cost_dash = Cost + totalGain;
        for(int i=0;i<advantage_temp.size();i++){
          listOfMedians[g[advantage_temp[i]]]--;
          if(listOfMedians[g[advantage_temp[i]]] == 0){
            listOfMedians.erase(g[advantage_temp[i]]);
          }
          g[advantage_temp[i]] = currentCentre;
          listOfMedians[currentCentre]++;
        }
      }



      index = (index + 1)%(feasibleCenters.size());
    }








  }

};
