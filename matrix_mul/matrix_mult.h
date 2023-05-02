#include <iostream>
#include <vector>
#include <functional>
#include "prueba.h"

using namespace std;

template <typename Func>
long long execution_time_ms(Func function, const vector<vector<int> > &A, const vector<vector<int> > &B, string alg) {
  auto start_time = std::chrono::high_resolution_clock::now();
  function(A, B, alg);
  auto end_time = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
}

void read_matrix(vector<vector<int> > &M){
  for(auto &row : M)
    for(auto &element : row) cin>>element;
}

void print_matrix(const vector<vector<int> > &M){
  for(int i = 0; i < M.size(); i++){
    for(int j = 0; j < M[i].size(); j++)
      cout<<M[i][j]<<" ";
    cout<<endl;
  }
}

// Algo iterativo cuvico tradicional
vector<vector<int> > standard_mm(const vector<vector<int> > &A, const vector<vector<int> > &B) {
  int n = A.size();
  int m = A[0].size();
  int k = B[0].size();

  vector<vector<int> > C(n, vector<int>(k, 0));

  for(int i = 0; i < n; i++) 
    for(int j = 0; j < k; j++)
      for(int k = 0; k < m; k++)
        C[i][j] += A[i][k] * B[k][j];

  return C;
}

     

// Algoritmo iterativo cuvico optimizado para mantener la localidad de los datos
vector<vector<int> > standard_opt(const vector<vector<int> > &A, const vector<vector<int> > &B) {
  int n = A.size();
  int m = B.size();
  int p = B[0].size();

  vector<vector<int> > C(n, vector<int>(p, 0));

  for(int i = 0; i < n; i++){
    for(int k = 0; k < m; k++){
      for(int j = 0; j < p; j++){
        C[i][j] += A[i][k]*B[k][j];
      }
    }
  }


  return C;
} 

// Algoritmo de Strassen
vector<vector<int> > strassen_mm(const vector<vector<int> > &A, const vector<vector<int> > &B) {


  //Hacer que ambas matrices sean cuadradas
  //A = extend_A(A, B);
  //B = extend_B(A, B);

  int n = A.size();
  int p = B[0].size();
  //int m = A[0].size();
  //int k = B[0].size();

  if(n <= 1){
    vector<vector<int> > C(1, vector<int>(1, 0));
    C[0][0] = A[0][0]*B[0][0];
    return C;
  }

  vector<vector<int> > C(n, vector<int>(p, 0));

  int m = n/2;



  //Sub-matrices
  vector<vector<int> > A11(m, vector<int>(m, 0));
  vector<vector<int> > A12(m, vector<int>(m, 0));
  vector<vector<int> > A21(m, vector<int>(m, 0));
  vector<vector<int> > A22(m, vector<int>(m, 0));
  vector<vector<int> > B11(m, vector<int>(m, 0));
  vector<vector<int> > B12(m, vector<int>(m, 0));
  vector<vector<int> > B21(m, vector<int>(m, 0));
  vector<vector<int> > B22(m, vector<int>(m, 0));

  //llenar valores
  for (int i = 0; i < m; ++i){
    for (int j = 0; j < m; ++j)
    {
      A11[i][j] = A[i][j];
      A12[i][j] = A[i][j + m];
      A21[i][j] = A[i + m][j];
      A22[i][j] = A[i+ m][j + m];
      B11[i][j] = B[i][j];
      B12[i][j] = B[i][j + m];
      B21[i][j] = B[i + m][j];
      B22[i][j] = B[i + m][j + m];
    }
  }

  vector<vector<int> > S1(m, vector<int>(m, 0));
  vector<vector<int> > S2(m, vector<int>(m, 0));
  vector<vector<int> > S3(m, vector<int>(m, 0));
  vector<vector<int> > S4(m, vector<int>(m, 0));
  vector<vector<int> > S5(m, vector<int>(m, 0));
  vector<vector<int> > S6(m, vector<int>(m, 0));
  vector<vector<int> > S7(m, vector<int>(m, 0));
  vector<vector<int> > S8(m, vector<int>(m, 0));
  vector<vector<int> > S9(m, vector<int>(m, 0));
  vector<vector<int> > S10(m, vector<int>(m, 0));
  S1 = subtract(B12, B22, m);
  S2 = add(A11, A12, m);
  S3 = add(A21, A22, m);
  S4 = subtract(B21, B11, m);
  S5 = add(A11, A22, m);
  S6 = add(B11, B22, m);
  S7 = subtract(A12, A22, m);
  S8 = add(B21, B22, m);
  S9 = subtract(A11, A21, m);
  S10 = add(B11, B12, m);

  vector<vector<int> > P1(m, vector<int>(m, 0));
  vector<vector<int> > P2(m, vector<int>(m, 0));
  vector<vector<int> > P3(m, vector<int>(m, 0));
  vector<vector<int> > P4(m, vector<int>(m, 0));
  vector<vector<int> > P5(m, vector<int>(m, 0));
  vector<vector<int> > P6(m, vector<int>(m, 0));
  vector<vector<int> > P7(m, vector<int>(m, 0));
  P1 = strassen_mm(A11, S1);
  P2 = strassen_mm(S2, B22);
  P3 = strassen_mm(S3, B11);
  P4 = strassen_mm(A22, S4);
  P5 = strassen_mm(S5, S6);
  P6 = strassen_mm(S7, S8);
  P7 = strassen_mm(S9, S10);



  vector<vector<int> > C11(m, vector<int>(m, 0));
  vector<vector<int> > C12(m, vector<int>(m, 0));
  vector<vector<int> > C21(m, vector<int>(m, 0));
  vector<vector<int> > C22(m, vector<int>(m, 0));
  C11 = subtract(add(add(P5, P4, m), P6, m), P2, m);
  C12 = add(P1, P2, m);
  C21 = add(P3, P4, m);
  C22 = subtract(subtract(add(P5, P1, m), P3, m), P7, m);

  for(int i = 0; i < m; i++){
    for(int j = 0; j<m; j++){

      C[i][j] = C11[i][j];
      C[i][j+m] = C12[i][j];
      C[m+i][j] = C21[i][j];
      C[m+i][m+j] = C22[i][j];

    }
  }


  return C;
}





vector<vector<int> > matrix_multiplication(const vector<vector<int> > &A, const vector<vector<int> > &B, string alg){
  if (alg == "standard_mm")return standard_mm(A, B);
  else if (alg == "standard_opt")return standard_opt(A, B);
  else if (alg == "strassen_mm")return strassen_mm(A, B);
  else return standard_mm(A, B);
}


