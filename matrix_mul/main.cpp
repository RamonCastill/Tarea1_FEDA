#include <iostream>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <string.h>
#include "matrix_mult.h"
using namespace std;

int main(int argv, char* argc[]) {
  srand(time(NULL)); 

  int a, n, m, k, N, n_1, i, num_of_experiments;
  string selected_algorithm;

  switch(atoi(argc[1])){ // Eledor el algoritmo a usar
    case 2: selected_algorithm = "standard_opt"; break;
    case 3: selected_algorithm = "strassen_mm"; break;
    default: selected_algorithm = "standard_mm"; break;
  }


  cin>>a>>m>>k;
  vector<vector<int> > M_A(a,vector<int>(m,0)), M_B(m,vector<int>(k,0));
  read_matrix(M_A); 
  read_matrix(M_B);

  string outfile_name = selected_algorithm + "_results.csv";
  ofstream outfile(outfile_name);
  string column_names = "n,time[ms]\n";
  outfile << column_names;

  i = 100, n_1 = 1, N = 5000, num_of_experiments = 10;

  for(int n = n_1; n <= N; n += i){
    double mm_total_time = 0;

    for(int j = 0; j < num_of_experiments; j++){ 
      long long single_execution_time = execution_time_ms(matrix_multiplication, M_A, M_B, selected_algorithm);
      mm_total_time += single_execution_time;
    }
    double mm_avg_time = mm_total_time / num_of_experiments;
    outfile << n << "," << mm_avg_time <<endl;
  }
  outfile.close(); 
  return 0;
}
