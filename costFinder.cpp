#include <bits/stdc++.h>

using namespace std;

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
    vector <vector <double> > medians;
    string spacePointsFile ;
    cin>>spacePointsFile;

    string mediansFile ;
    cin>>mediansFile;
    string myText;
    ifstream MyReadFile(spacePointsFile);
    while (getline (MyReadFile, myText)) {
        istringstream ss(myText);
        string word;
        vector<double> temp;
        while (ss >> word)
        {
            temp.push_back(stod(word));
        }
        spacePoints.push_back(temp);
    }
    MyReadFile.close();

    ifstream MyReadFile2(mediansFile);
    while (getline (MyReadFile2, myText)) {
        istringstream ss(myText);
        string word;
        vector<double> temp;
        while (ss >> word)
        {
            temp.push_back(stod(word));
        }
        medians.push_back(temp);
    }
    MyReadFile2.close();

    cout<<"Number of medians:"<<medians.size()<<endl;
    double Cost = 0;
    int i,j;
    double subCost;
    for(i=0;i<spacePoints.size();i++){
        subCost = DBL_MAX;
        for(j=0;j<medians.size();j++){
            subCost = min(subCost, SSQ(spacePoints[i],medians[j]));
        }
        Cost += subCost;
    }
    cout<<"SSQ Cost is:"<<Cost<<endl;


}
