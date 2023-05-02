#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

template <typename Func>
long long execution_time_ms(Func function, const vector<int> &A, string alg) {
  auto start_time = std::chrono::high_resolution_clock::now();
  function(A, alg);
  auto end_time = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
}

void read_arr(vector<int> &M, int largo_a_definir_como_usar){
  for(int i = 0; i<largo_a_definir_como_usar; i++)
    cin>>M[i];
}

void print_arr(const vector<int> &M, int largo_a_definir_como_usar){
  for(int i = 0; i < largo_a_definir_como_usar; i++){
    for(int j = 0; j < largo_a_definir_como_usar; j++)
      cout<<M[i]<<" ";
    cout<<endl;
  }
}

//Implementacion de bubble sort
vector<int> bubble_sort(vector<int> A) {
  int n = A.size(), temp;

  for(int i=0;i<n-1;i++){
    for(int j=0;j<n-1;j++){
      if(A[j]>A[j+1]){
        temp = A[j];
        A[j] = A[j + 1];
        A[j + 1] = temp;
      }
    }
  }

  return A;
}
vector<int> merge_al(vector<int> l, vector<int> r){

  vector<int> result;

  while(!l.empty() && !r.empty()){

    if (l[0] <= r[0]){
      result.push_back(l[0]);
      l.erase(l.begin());
    }else{
      result.push_back(r[0]);
      r.erase(r.begin());
    }

  }
  //Para los elementos restantes
  while(!l.empty()){
    result.push_back(l[0]);
    l.erase(l.begin());
  }

  while(!r.empty()){
    result.push_back(r[0]);
    r.erase(r.begin());
  }

  return result;

}  


vector<int> merge_sort(vector<int> A) {

  int n = A.size();

  if (n==1){
    return A;
  }

  vector<int> l(A.begin(), A.begin() + n/2);
  vector<int> r(A.begin() + n/2, A.end());

  l = merge_sort(l);
  r = merge_sort(r);


  return merge_al(l, r);
}
   

vector<int> quick_sort( vector<int> A) {

  if(A.size() <=1 ){
    return A;
  }

  int pivot = A[0];
  vector<int> r, l, e; //derecha, izquierda e iguales
  for(int i = 0; i < A.size(); i++){
    if(A[i]<pivot){
      l.push_back(A[i]);
    }
    else if(A[i]>pivot){
      r.push_back(A[i]);
    }else{
      e.push_back(A[i]);
    }
  }

  l = quick_sort(l);
  r = quick_sort(r);

  vector<int> new_A;

  new_A.reserve(l.size()+r.size()+e.size());
  new_A.insert(new_A.end(), l.begin(), l.end());
  new_A.insert(new_A.end(), e.begin(), e.end());
  new_A.insert(new_A.end(), r.begin(), r.end());

  return new_A;

} 


vector<int> sort_std( vector<int> A) {
  int n = A.size();
  std::sort(A.begin(),A.end());
  return A;
}



vector<int> sort_arr(const vector<int> &A, string alg){
  if(alg == "bubble_sort") return bubble_sort(A);
  else if (alg == "merge_sort") return merge_sort(A);
  else if (alg == "quick_sort") return quick_sort(A);
  else if (alg == "sort_std") return sort_std(A);
  return sort_std(A);
}
