#include <iostream>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <string.h>
#include "sort_algos.h"
using namespace std;

int main(int argv, char* argc[]) {
  srand(time(NULL)); 

  int n, m, k, N, n_1, i, num_of_experiments;
  string selected_algorithm;

  switch(atoi(argc[1])){ // Elejir el algoritmo a usar
    case 2: selected_algorithm = "bubble_sort"; break;
    case 3: selected_algorithm = "merge_sort"; break;
    case 4: selected_algorithm = "quick_sort"; break;
    default: selected_algorithm = "sort_std"; break;
  }


  cin>>n;
  vector<int> M_A(n);
  read_arr(M_A,n);

  string outfile_name = selected_algorithm + "_results.csv";
  ofstream outfile(outfile_name);
  string column_names = "n,time[ms]\n";
  outfile << column_names;

  i = 100, n_1 = 1, N = 5000, num_of_experiments = 10;

  for(int n = n_1; n <= N; n += i){
    double mm_total_time = 0;

    for(int j = 0; j < num_of_experiments; j++){ 
      long long single_execution_time = execution_time_ms(sort_arr, M_A, selected_algorithm);
      mm_total_time += single_execution_time;
    }
    double mm_avg_time = mm_total_time / num_of_experiments;
    outfile << n << "," << mm_avg_time <<endl;
  }
  outfile.close(); 
  return 0;
}
