#ifndef DSETS_H
#define DSETS_H
#include <vector>

using std::vector;
using namespace std;



class DisjointSets {
  public:

    DisjointSets();

    void addelements(int num);

    int find(int elem);

    void setunion(int a, int b);

    int size(int elem);

  private:
    std::vector<int> vec;

};

#endif
