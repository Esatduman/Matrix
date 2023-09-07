
/* -----------------------------------------
Title: Project 3 - mymatrix.h/Unit Testing 
Name: Esat Duman 
UIN:662726641
Course: Data Structures (CS251)
IDE used: VS code 
Professor: Adam Koehler
--------------------------------------------*/

#include <iostream>
#include "mymatrix.h"
#include <cassert>
using namespace std;


bool multiplication_test() {
  // Create 2 matrices to multiply
  mymatrix<double> mat1(2, 3);
  mat1(0, 0) = 1; mat1(0, 1) = 2; mat1(0, 2) = 3;
  mat1(1, 0) = 4; mat1(1, 1) = 5; mat1(1, 2) = 6;

  mymatrix<double> mat2(3, 2);
  mat2(0, 0) = 7; mat2(0, 1) = 8;
  mat2(1, 0) = 9; mat2(1, 1) = 10;
  mat2(2, 0) = 11; mat2(2, 1) = 12;

  // Multiply the matrices
  mymatrix<double> result = mat1 * mat2;

  // Check the result
  if (result.size() != 4) {
    cout << "Multiplication test failed: incorrect result size" << endl;
    return false;
  }

  if (result(0, 0) != 58 || result(0, 1) != 64) {
    cout << "Multiplication test failed: incorrect result" << endl;
    return false;
  }

  // All tests passed
  return true;
}
//-------------------------------------------------------------------------------------
bool exception_test() {
  // Create a matrix of integers
  mymatrix<string> mat(2, 2);

  // Try to set a non-integer value
  try {
    mat(0, 0) = "hello";
  }
  catch (const invalid_argument& e) {
    // Check that the correct exception was thrown
    if (string(e.what()) != "mymatrix::(): invalid argument") {
      cout << "Exception test failed: incorrect exception message" << endl;
      return false;
    }

    // All tests passed
    return true;
  }

  // If an exception was not thrown, the test failed
  cout << "Exception test failed: no exception thrown" << endl;
  return false;
}

int main()
{

  mymatrix<double> A(2, 3);
    cout << "Size of matrix A: " << A.size() << endl;  // Test to see if the size is given 

  // test case for constructor and size function
    mymatrix<double> M1(3, 4);
    if (M1.numrows() != 3 || M1.numcols() != 4) {
        std::cout << "Error in constructor or size function!" << endl;
    }

 M1(1, 2) = 5.0;
    if (M1(1, 2) != 5.0) {
        cout << "Error in indexing operator or setting values!" << endl;
    }

    // test case for copy constructor and assignment operator
    mymatrix<double> M2(M1);
    mymatrix<double> M3 = M1;
    if (M2(1, 2) != 5.0 || M3(1, 2) != 5.0) {
        cout << "Error in copy constructor or assignment operator!" << endl;
    }

mymatrix<int> Ma1(2, 3);  // declaring our matrices 
mymatrix<int> Ma2(3, 2);

Ma1(0, 0) = 1; // setting the values for the matrix multiplication 
Ma1(0, 1) = 2;
Ma1(0, 2) = 3;
Ma1(1, 0) = 4;
Ma1(1, 1) = 5;
Ma1(1, 2) = 6;

Ma2(0, 0) = 7;
Ma2(0, 1) = 8;
Ma2(1, 0) = 9;
Ma2(1, 1) = 10;
Ma2(2, 0) = 11;
Ma2(2, 1) = 12;

mymatrix<int> result = Ma1 * Ma2;

cout << "Multiplication result:\n";
result._output();
cout << "\n";
        
int passed = 0;
    int failed = 0;

    // Run size test
    if (multiplication_test()) {
        passed++;
    }
    else {
        cout << "size_test1 failed" << endl;
        failed++;
    }

    // Run exception test
    if (exception_test()) {
        passed++;
    }
    else {
        cout << "exception_test_special failed" << endl;
        failed++;
    }

    // Report results
    cout << "Tests passed: " << passed << endl;
    cout << "Tests failed: " << failed << endl;

   
        


  return 0;

}

