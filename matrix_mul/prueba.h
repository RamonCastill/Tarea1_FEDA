#include <iostream>
#include <vector>
#include <functional>

using namespace std;

template <typename Func>
vector<vector<int> > extend_B(vector<vector<int> > &A, vector<vector<int> > &B){
  int m = max(A.size(), B.size());
  int n = max(A[0].size(), B[0].size());

  for(int i = 0; i<B.size(); i++){
    for(int j = B[0].size(); j<n; j++){
      B[i].push_back(0);
    }
  }
  for (int i = B.size(); i < m; ++i){
    vector<int> row(n,0);
    B.push_back(row);
  }
  return B;
}
vector<vector<int> > add(const vector<vector<int> > &A, const vector<vector<int> > &B, int k){

   vector<vector<int> > C(k, vector<int>(k, 0));

   for(int i = 0; i<k; i++){
    for(int j = 0; j<k; j++){
      C[i][j] = A[i][j] + B[i][j];
    }
   }
   return C;
}

vector<vector<int> > subtract(const vector<vector<int> > &A, const vector<vector<int> > &B, int k){

   vector<vector<int> > C(k, vector<int>(k, 0));

   for(int i = 0; i<k; i++){
    for(int j = 0; j<k; j++){
      C[i][j] = A[i][j] - B[i][j];
    }
   }
  return C;
}
