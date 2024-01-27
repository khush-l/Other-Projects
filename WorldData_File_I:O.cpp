//Author: Khush Lalchandani
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

struct CountryData {
    string name;
    double value;
};
int findN(string str, char c,int n){
  int val = 0;
  for(int i =0; i < str.length(); i++) {
    if (str[i] == c) {
      val +=1;
    }
    if (val == n){
      return i;
    }
  }
  return -1;
}
void bubble_sort(CountryData* countries, int length){
  double a;
  string str;
  for (int i=0; i<length; i++){
    for (int n = 0; n+1<length-i;n++){
      if (countries[n].value < countries[n+1].value){
        a = countries[n].value;
        countries[n].value = countries[n+1].value;
        countries[n+1].value = a;

        str = countries[n].name;
        countries[n].name = countries[n+1].name;
        countries[n+1].name = str;
      }
    }
  }
}

int main() {
  CountryData countries[227];
  CountryData categories[200];
  string line;
  int numCountries=0;
  int counter=0;
  int numLeft=0;
  ifstream myfile ("WPP2015_MORT_F07_1_LIFE_EXPECTANCY_0_BOTH_SEXES.csv");
  if (myfile.is_open())
  {
    for(int i =0;i<31;++i) {
      getline(myfile, line);
    }
    bool developed = false;
    while (getline(myfile,line))
      {
        int countryindex= line.find("\"Estimates\"") + 13;
        int endIndex = line.find("\"",countryindex);
        int dif = endIndex-countryindex;
        countries[numCountries].name=line.substr(countryindex, dif);

        int startind = findN(line, ',', 15) +1;
        int endind = findN(line, ',', 16);
        int dif1 = endind-startind;
        countries[numCountries].value = stod(line.substr(startind, dif1));
        if (numLeft==0){
          developed=false;
        }
        if (developed==true){
          categories[counter].name=line.substr(countryindex, dif);
          categories[counter].value = stod(line.substr(startind, dif1));
            counter++;
        }
         if (line.substr(countryindex, dif)=="EUROPE"){
          developed = true;
           numLeft=43;
        }
        if (line.substr(countryindex, dif)=="NORTHERN AMERICA"){
          developed = true;
          numLeft=2;
        }
        if (line.substr(countryindex, dif)=="Australia/New Zealand"){
          categories[counter].name=line.substr(countryindex, dif);
          categories[counter].value = stod(line.substr(startind, dif1));
          counter++;
        }
        if (line.substr(countryindex, dif)=="Japan"){
          categories[counter].name=line.substr(countryindex, dif);
          categories[counter].value = stod(line.substr(startind, dif1));
          counter++;
        }
        numCountries++;

      }
    myfile.close();
  }
    int length = sizeof(countries)/sizeof(countries)[0];
  bubble_sort(countries, length);
  bubble_sort(categories, sizeof(categories)/sizeof(categories)[0]);
  int place;
  for(int i=0;i<47;i++){
    if(categories[i].name=="United States of America"){
      place = i+1;
    }
  }
  int valu=0;
  for(int i = 0;i<227;i++){
    if(countries[i].name=="United States of America"){
      valu = i+1;
    }
  }
  cout<<"The United States ranked "<<valu<<"th within all of the countries."<<endl;
  cout<<"The United States ranked "<<place<<"th within the most developed countries."<<endl;
}