/*mymatrix.h*/

/* -----------------------------------------
Title: Project 3 - mymatrix.h/Unit Testing 
Name: Esat Duman 
UIN:662726641
Course: Data Structures (CS251)
IDE used: VS code 
Professor: Adam Koehler
--------------------------------------------*/
/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Spring 2023


//
// mymatrix
//
// The mymatrix class provides a matrix (2D array) abstraction.
// The size can grow dynamically in both directions (rows and 
// cols).  Also, rows can be "jagged" --- i.e. rows can have 
// different column sizes, and thus the matrix is not necessarily 
// rectangular.  All elements are initialized to the default value
// for the given type T.  Example:
//
//   mymatrix<int>  M;  // 4x4 matrix, initialized to 0
//   
//   M(0, 0) = 123;
//   M(1, 1) = 456;
//   M(2, 2) = 789;
//   M(3, 3) = -99;
//
//   M.growcols(1, 8);  // increase # of cols in row 1 to 8
//
//   for (int r = 0; r < M.numrows(); ++r)
//   {
//      for (int c = 0; c < M.numcols(r); ++c)
//         cout << M(r, c) << " ";
//      cout << endl;
//   }
//
// Output:
//   123 0 0 0
//   0 456 0 0 0 0 0 0
//   0 0 789 0
//   0 0 0 -99
//

#pragma once

#include <iostream>
#include <exception>
#include <stdexcept>
#include <vector>

using namespace std;

template<typename T>
class mymatrix
{
private:
  struct ROW
  {

    T*  Cols;     // dynamic array of column elements
    int NumCols;  // total # of columns (0..NumCols-1)
  };

  ROW* Rows;     // dynamic array of ROWs
  int  NumRows;  // total # of rows (0..NumRows-1)

public:
  //
  // default constructor:
  //
  // Called automatically by C++ to construct a 4x4 matrix.  All 
  // elements are initialized to the default value of T.
  //
  mymatrix() 
  {
    Rows = new ROW[4];  // an array with 4 ROW structs:
    NumRows = 4;

    // initialize each row to have 4 columns:
    for (int r = 0; r < NumRows; ++r) {
      Rows[r].Cols = new T[4];  // an array with 4 elements of type T:
      Rows[r].NumCols = 4;

      // initialize the elements to their default value:
      for (int c = 0; c < Rows[r].NumCols; ++c)
      {
        Rows[r].Cols[c] = T{};  // default value for type T which we need as said in prompt 
      }
    }
  }

  //
  // parameterized constructor:
  //
  // Called automatically by C++ to construct a matrix with R rows, 
  // where each row has C columns. All elements are initialized to 
  // the default value of T.
  //
  mymatrix(int R, int C)
  {
    if (R < 1)
      throw invalid_argument("mymatrix::constructor: # of rows");
    if (C < 1)
      throw invalid_argument("mymatrix::constructor: # of cols");

     NumRows = R;
    Rows = new ROW[R];  // an array with R ROW structs:

    // initialize each row to have C columns:
    for (int r = 0; r < NumRows; ++r)
    {
      Rows[r].Cols = new T[C];  // an array with C elements of type T:
      Rows[r].NumCols = C;

      // initialize the elements to their default value:
      for (int j = 0; j < Rows[r].NumCols; ++j)
      {
        Rows[r].Cols[j] = T{};  
        // default value for type T:
      }
    }
    //rows = R;
    //cols = C;
    // Allocating memory for the matrix 
   
    //mat = new T*[R];
    //for (int i = 0; i < R; i++) {
      //mat[i] = new T[C];
    //}
    //initilize to the value of T
    //for(int i = 0; i < R; i++) {
      //for(int i = 0; i < C; j++) {

        //mat[i][j] = T();
     // }
    //}
    
  }


  //
  // copy constructor:
  //
  // Called automatically by C++ to construct a matrix that contains a 
  // copy of an existing matrix.  Example: this occurs when passing 
  // mymatrix as a parameter by value
  //
  //   void somefunction(mymatrix<int> M2)  <--- M2 is a copy:
  //   { ... }
  //
  mymatrix(const mymatrix<T>& other)
  {
   NumRows = other.NumRows;
    Rows = new ROW[NumRows];

    for (int i = 0; i < NumRows; ++i)
    {
        Rows[i].NumCols = other.Rows[i].NumCols;
        Rows[i].Cols = new T[Rows[i].NumCols];
        for (int j = 0; j < Rows[i].NumCols; ++j)
        {
            Rows[i].Cols[j] = other.Rows[i].Cols[j];
        }
    }
  }


  //
  // numrows
  //
  // Returns the # of rows in the matrix.  The indices for these rows
  // are 0..numrows-1.
  //
  int numrows() const
  {
  
   return NumRows; // return rows

  }
  

  //
  // numcols
  //
  // Returns the # of columns in row r.  The indices for these columns
  // are 0..numcols-1.  Note that the # of columns can be different 
  // row-by-row since "jagged" rows are supported --- matrices are not
  // necessarily rectangular.
  //

    
int numcols(int r = -1) const {  // correctly return the numcols changed the condition 
  if (r >= 0 && r < NumRows) {
    return Rows[r].NumCols;
  } else if (r == -1 && NumRows > 0) {
    return Rows[0].NumCols;
  } else {
    throw invalid_argument("mymatrix::numcols: invalid row");
  }
}

  /*int numcols(int r) const
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::numcols: row");

     return Rows[r].NumCols;

  }
*/

  //
  // growcols
  //
  // Grows the # of columns in row r to at least C.  If row r contains 
  // fewer than C columns, then columns are added; the existing elements
  // are retained and new locations are initialized to the default value 
  // for T.  If row r has C or more columns, then all existing columns
  // are retained -- we never reduce the # of columns.
  //
  // Jagged rows are supported, i.e. different rows may have different
  // column capacities -- matrices are not necessarily rectangular.
  //
  void growcols(int R, int C)
  {
    if (R < 0 || R >= NumRows)
      throw invalid_argument("mymatrix::growcols: row");
    if (C < 1)
      throw invalid_argument("mymatrix::growcols: columns");

     if (Rows[R].NumCols >= C) {  // checks if row has atleast C columns 
        return;
    }
    // allocate new row with capacity C
    T* newrow = new T[C];
    for(int j = 0; j < Rows[R].NumCols; j++) {
        newrow[j] = Rows[R].Cols[j];
    }
    for(int j = Rows[R].NumCols; j < C; j++) {
        newrow[j] = T();
    }
    // free old row update new row
    delete[] Rows[R].Cols;
    Rows[R].Cols = newrow;
    Rows[R].NumCols = C;
  }


  //
  // grow
  //
  // Grows the size of the matrix so that it contains at least R rows,
  // and every row contains at least C columns.
  // 
  // If the matrix contains fewer than R rows, then rows are added
  // to the matrix; each new row will have C columns initialized to 
  // the default value of T.  If R <= numrows(), then all existing
  // rows are retained -- we never reduce the # of rows.
  //
  // If any row contains fewer than C columns, then columns are added
  // to increase the # of columns to C; existing values are retained
  // and additional columns are initialized to the default value of T.
  // If C <= numcols(r) for any row r, then all existing columns are
  // retained -- we never reduce the # of columns.
  // 
  void grow(int R, int C)
  {
    if (R < 1)
      throw invalid_argument("mymatrix::grow: # of rows");
    if (C < 1)
      throw invalid_argument("mymatrix::grow: # of cols");

    // Grows the rows.
    if (R <= NumRows && C <= Rows[0].NumCols) {
        // If the new dimensions are smaller than or equal to the current dimensions, do nothing.
        return;
    }

    // Create a new array of ROWs with the new number of rows:
    ROW* newRowsArray = new ROW[R];

    // Copy the existing ROWs to the new array:
    for (int r = 0; r < NumRows; ++r) {
        // Copy the Cols array to the new ROW:
        newRowsArray[r].Cols = new T[C];
        for (int c = 0; c < Rows[r].NumCols; ++c) {
            newRowsArray[r].Cols[c] = Rows[r].Cols[c];
        }

        // Set the NumCols value for the new ROW:
        newRowsArray[r].NumCols = C;
    }

    // Initialize any new ROWs with default values:
    for (int r = NumRows; r < R; ++r) {
        newRowsArray[r].Cols = new T[C];
        for (int c = 0; c < C; ++c) {
            newRowsArray[r].Cols[c] = T{};
        }
        newRowsArray[r].NumCols = C;
    }

    // Delete the existing ROWs and replace the Rows pointer with the new array:
    for (int r = 0; r < NumRows; ++r) {
        delete[] Rows[r].Cols;
    }
    delete[] Rows;
    Rows = newRowsArray;
    NumRows = R;
}
  

  //
  // size
  //
  // Returns the total # of elements in the matrix.
  //

  
  int size() const
{
  int count = 0;
  for (int r = 0; r < NumRows; r++) 
  {
    count += Rows[r].NumCols;
  }
  return count;
}



  //
  // at
  //
  // Returns a reference to the element at location (r, c); this
  // allows you to access the element or change it:
  //
  //    M.at(r, c) = ...
  //    cout << M.at(r, c) << endl;
  //
  T& at(int r, int c) const
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::at: row");
    if (c < 0 || c >= Rows[r].NumCols)
      throw invalid_argument("mymatrix::at: col");

    return Rows[r].Cols[c];

    //T temp = {};  // we need to return something, so a temp for now:

    //return temp;
  }


  //
  // ()
  //
  // Returns a reference to the element at location (r, c); this
  // allows you to access the element or change it:
  //
  //    M(r, c) = ...
  //    cout << M(r, c) << endl;
  //
  T& operator()(int r, int c) const
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::(): row");
    if (c < 0 || c >= Rows[r].NumCols)
      throw invalid_argument("mymatrix::(): col");

     return Rows[r].Cols[c];

   // T temp = {};  // we need to return something, so a temp for now:

    //return temp;
  }

  //
  // scalar multiplication
  //
  // Multiplies every element of this matrix by the given scalar value,
  // producing a new matrix that is returned.  "This" matrix is not
  // changed.
  //
  // Example:  M2 = M1 * 2;
  //
  mymatrix<T> operator*(T scalar)
  {
    mymatrix<T> result(NumRows, Rows[0].NumCols);

  for (int i = 0; i < NumRows; i++) {
    for (int j = 0; j < Rows[i].NumCols; j++) {
      result.Rows[i].Cols[j] = Rows[i].Cols[j] * scalar;
    }
  }

  return result;
  }


  //
  // matrix multiplication
  //
  // Performs matrix multiplication M1 * M2, where M1 is "this" matrix and
  // M2 is the "other" matrix.  This produces a new matrix, which is returned.
  // "This" matrix is not changed, and neither is the "other" matrix.
  //
  // Example:  M3 = M1 * M2;
  //
  // NOTE: M1 and M2 must be rectangular, if not an exception is thrown.  In
  // addition, the sizes of M1 and M2 must be compatible in the following sense:
  // M1 must be of size RxN and M2 must be of size NxC.  In this case, matrix
  // multiplication can be performed, and the resulting matrix is of size RxC.
  //
  mymatrix<T> operator*(const mymatrix<T>& other)
  {
    mymatrix<T> result;

    //
    // both matrices must be rectangular for this to work:
    //

    for (int i = 1; i < NumRows; i++) {
  if (Rows[i].NumCols != Rows[0].NumCols) {
    throw runtime_error("mymatrix::*: this not rectangular"); // errors for the checking if rectangular 
  }
}

// Check if other matrix is rectangular
for (int i = 1; i < other.NumRows; i++) {
  if (other.Rows[i].NumCols != other.Rows[0].NumCols) {
    throw runtime_error("mymatrix::*: other not rectangular");
  }
}
    // if (this matrix is not rectangular)
    //   throw runtime_error("mymatrix::*: this not rectangular");
    //
    // if (other matrix is not rectangular)
    //   throw runtime_error("mymatrix::*: other not rectangular");

    //
    // Okay, both matrices are rectangular.  Can we multiply?  Only
    // if M1 is R1xN and M2 is NxC2.  This yields a result that is
    // R1xC2.
    // 
    // Example: 3x4 * 4x2 => 3x2
    //
 if (Rows[0].NumCols != other.NumRows) {
    throw runtime_error("mymatrix::*: size mismatch");
  }

  result.grow(NumRows, other.Rows[0].NumCols);

  // Perform matrix multiplication
  for (int i = 0; i < NumRows; i++) {
    for (int j = 0; j < other.Rows[0].NumCols; j++) {
      T sum = 0;
      for (int k = 0; k < Rows[i].NumCols; k++) {
        sum += Rows[i].Cols[k] * other.Rows[k].Cols[j];
      }
      result(i, j) = sum;
    }
  }

  return result;
}






  


  //
  // _output
  //
  // Outputs the contents of the matrix; for debugging purposes.
  //
  void _output()
  {
    for (int r = 0; r < this->NumRows; ++r)
    {
      for (int c = 0; c < this->Rows[r].NumCols; ++c)
      {
        cout << this->Rows[r].Cols[c] << " ";
      }
      cout << endl;
    }
  }

};
