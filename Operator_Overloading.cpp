// Author: Khush Lalchandani
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class Rec {

public:
  char orderDate[16];
  char region[16];
  char rep[16];
  char item[64];
  int units;
  float price;
  inline bool operator==(const Rec rhs) {
    if ((strcmp(orderDate, rhs.orderDate) == 0) && (strcmp(item, rhs.item)==0) && (strcmp(rep, rhs.rep) == 0) && (units != 0) && (rhs.units != 0)) {
      return true;
    } else {
      return false;
    }
  }
  Rec operator+(const Rec rhs) {
    Rec sum;
    sum.units = units + rhs.units;
    return sum;
  }
  Rec() {}

  float total() const { return units * price; }
};
ostream &operator<<(ostream &lhs, const Rec rhs) {
  lhs << rhs.orderDate << "," << rhs.rep << "," << rhs.item;
  return lhs;
}

bool compareByTotal(const Rec &a, const Rec &b) {
  return a.total() < b.total();
}
int main() {
  std::cout << "Hello More Sales Data!  :)\n";

  ifstream file("SalesDataP5.csv");
  if (!file.is_open()) {
    cout << "Error: Unable to open file.\n";
    return 1;
  }

  const int maxRecords = 50; // Maximum number of records
  Rec records[maxRecords];   // Use a standard array for storing records
  int recordCount = 0;       // Counter for the number of records read

  string tempLine;
  while (getline(file, tempLine)) {
    if (recordCount < maxRecords) {
      // Assuming CSV format: orderDate,region,rep,item,unit,price
      Rec &rec = records[recordCount];
      if (sscanf(tempLine.c_str(), "%[^,],%[^,],%[^,],%[^,],%d,%f",
                 &rec.orderDate[0], &rec.region[0], &rec.rep[0], &rec.item[0],
                 &rec.units, &rec.price) == 6) {
        recordCount++;
      }
    } else {
      cout << "Warning: Maximum record limit reached.\n";
      break;
    }
  }
  
  file.close();
  for (int i = 0; i < recordCount; i++) {
    for (int j = i + 1; j < recordCount; j++) {
      if (records[i] == records[j]) {
        records[i] = records[j] + records[i];
        records[j].units = 0;
      }
    }
  }

  sort(records, records + recordCount, compareByTotal);
  for (int i = 0; i < recordCount; i++) {
    if (records[i].units > 0) {
      cout << records[i] << ", " << records[i].total() << endl;
    }
  }
  return 0;
}
