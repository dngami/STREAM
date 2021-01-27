#include<iostream>
#include<vector>
#include<stdio>

#include<bits/stdc++.h>

using namespace std;

class LSearch{
  private:
    vector<vector<double>> spacePoints;
    vector<double> feasibleCenters;
    double k, e, e1,  e2 , zMin, zMax;
    double (*d)(vector<double> , vector<double>);
    vector<int> g;
    vector<int> listOfMedians;

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
    this->zMax = findzMax() ;
  }

  double findzMax(){

  }

  void initialSolution(double z){

  }

  void FL(){

  }

}
