#include<iostream>

#include<math/linalg/matrix.hpp>
#include<random/lcg.hpp>

#include<iomanip>
#include<chrono>
using namespace fetch::math::linalg;

typedef float data_type;
typedef fetch::memory::Array< data_type > container_type;
typedef Matrix<data_type,container_type>  matrix_type;
typedef typename matrix_type::vector_register_type vector_register_type;

Matrix<data_type, container_type> RandomMatrix(int n, int m) {
  static fetch::random::LinearCongruentialGenerator gen;
  Matrix<data_type,container_type> m1(n, m);
  for(std::size_t i=0; i < n; ++i)
    for(std::size_t j=0; j < m; ++j)
      m1(i,j) = gen.AsDouble();
  return m1;
}



void add_kernel(vector_register_type const &a,
                vector_register_type const &b,
                vector_register_type &c ){
  c =   a + b;
}

void add_kernel2(data_type const &a,
                 data_type const &b,
                 data_type &c ){
  c =  a + b;
}


void test_add( std::size_t const &N, data_type const *ptr1, data_type const *ptr2, data_type  *ptr3) {
  for(std::size_t i=0; i < N; ++i) {
    ptr3[i] = ptr1[i] + ptr2[i];
  }
}

void test_multiply( std::size_t const &N, data_type const *ptr1, data_type const *ptr2, data_type  *ptr3) {
  for(std::size_t i=0; i < N; ++i) {
    ptr3[i] = ptr1[i] * ptr2[i];
  }
}

using namespace std::chrono;

void benchmark_add(Matrix<data_type,container_type> &m1,  Matrix<data_type,container_type> &m2,  Matrix<data_type, container_type>  &ret) 
{
  std::cout << "Addition" << std::endl;
  std::cout << "========" << std::endl;  
  high_resolution_clock::time_point t1 = high_resolution_clock::now();
  for(std::size_t i=0; i < 1000; ++i) {
    ret.Add(m1, m2);   
  }

  high_resolution_clock::time_point t2 = high_resolution_clock::now();
  for(std::size_t i=0; i < 1000; ++i) {
    test_add(m1.size(), m1.data().pointer(), m2.data().pointer(), ret.data().pointer());   
  }

  high_resolution_clock::time_point t3 = high_resolution_clock::now();  
  duration<double> time_span1 = duration_cast<duration<double>>(t2 - t1);
  duration<double> time_span2 = duration_cast<duration<double>>(t3 - t2);  
  std::cout << "Builtin method: " << time_span1.count() << " seconds." << std::endl;
  std::cout << "Manual: " << time_span2.count() << " seconds." << std::endl;  
}

void benchmark_multiply(Matrix<data_type,container_type> &m1,  Matrix<data_type,container_type> &m2,  Matrix<data_type, container_type>  &ret) 
{
  std::cout << "Multiply" << std::endl;
  std::cout << "========" << std::endl;  
  high_resolution_clock::time_point t1 = high_resolution_clock::now();
  for(std::size_t i=0; i < 1000; ++i) {
    ret.Multiply(m1, m2);   
  }

  high_resolution_clock::time_point t2 = high_resolution_clock::now();
  for(std::size_t i=0; i < 1000; ++i) {
    test_multiply(m1.size(), m1.data().pointer(), m2.data().pointer(), ret.data().pointer());   
  }

  high_resolution_clock::time_point t3 = high_resolution_clock::now();  
  duration<double> time_span1 = duration_cast<duration<double>>(t2 - t1);
  duration<double> time_span2 = duration_cast<duration<double>>(t3 - t2);  
  std::cout << "Builtin method: " << time_span1.count() << " seconds." << std::endl;
  std::cout << "Manual: " << time_span2.count() << " seconds." << std::endl;  
}


int main() {
  static fetch::random::LinearCongruentialGenerator gen;
  std::size_t n = 2000, m = 2000;
  
  Matrix<data_type,container_type> m1 = RandomMatrix(n,m);
  Matrix<data_type,container_type> m2 = RandomMatrix(n,m);
  Matrix<data_type, container_type> ret(n,m);  

  benchmark_add(m1,m2,ret);
  benchmark_multiply(m1,m2,ret);  
  

/*
  ret.Add(a,b);
  ret.Multiply(a,2.0);  
  ret.Multiply(a,b);
  ret.Divide(a,b);
  ret.Subtract(a,b); 
*/
  return 0;
}
