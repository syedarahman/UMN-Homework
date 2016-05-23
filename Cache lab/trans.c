/* Syeda Rahman
 * 4524416
 *
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N]) 
{

  if(M == 61 && N == 67) 
  {
    //declare local variables
     int bs = 20;  //block size is 20. 
                   //so the beginning of the 1st block is at index 0, the beginning of the 2nd block is at index 20...

     int row;      //block row 
     int column;   //block column
     int i = 0;    //row index 
     int j = 0;    //column index
   
     for (row = 0; row < N; row += bs) 
       //row index from 0 to 20 = 1st block. So 0 + 20 = index 20.
       //row index 21-31 = 2nd block. So 20 + 20 = index 40. 
       {
	 for (column = 0; column < M; column += bs) 
	   //each block is of 20x20, so block size + column
	   {
	     for (i = row; i < row + bs; i++) 
	       //now you want to go through each 20x20 block, with i x j.
	       {
		 for (j = column; j < column + bs; j++)  
		   {
		     if (i > 66 || j > 60)
		       //checking if we are at the last spot, aka at 61x67. 
		       continue;
		     //if we are, then we are done. 
		       else
			 B[j][i] = A[i][j]; 
		     //if not on the last spot yet, replace matrix B's jxi spot by putting in A's ixj element there.
		     //so actually transposing here.
		   }
	       }
	   }
       }
  }



  else if (M == 64 && N == 64) 
    {
      //declare local variables.
      int row;
      int column;

      int i;
      int j;

      int diagonalspot = 0;
      int temporaryspot = 0;
      int blocksize = 4; 
      //btw, tried other blocksizes of powers of 2, but not getting better results.. 

      //starting with similar format as my 61x67 one. 
      for (column = 0; column < N; column += blocksize) 
	//row index from 0 to 4 = 1st block. So 0 + 4 = index 4.
	//row index 5-9 = 2nd block. So 4 + 4 = index 8... and so on.
	{
	  for (row = 0; row < N; row += blocksize) 
	    {		
      	      for (i = row; i < row + blocksize; i ++) 
		//now go thru each 4x4 block with i x j.
		{
		  for (j = column; j < column + blocksize; j ++)
		    {
		      if (i != j) 
			//if i and j are not equal, that means that spot isn't on the diagonal.
			{
			  B[j][i] = A[i][j];
			  //so transpose here
			}
		      else 
			//if i and j are equal, that means you're at a diagonal spot.
			 {
			    temporaryspot = A[i][j];
			    // if you are at a diagonal spot (where i == j), then temp = that spot on the diagonal.
			    // go thru the entire column except the diagonal one (where i == j), then put that ixj into B.
			    // doing diagonal last bc don't need to "transpose"

	               	    //so to get to A[0][0], brings over entire first row of matrix B.
			    //then to get to the next spot in the row, still brings over the entire first row of matrix B. 

			    diagonalspot = i;
			    //  reset diagonal to your current spot (current i and/or j index).
			}
		    }
		  
		  //inside i loop (not j yet)
		  if (row == column)
		    //in terms of the block you are in
		    {
		      B[diagonalspot][diagonalspot] = temporaryspot;
		      //since the diagonal spot (where i == j) was not transposed since it's the same anyways, take care of it here.
		    }
		}	 
	    }
	}
    }
}





/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
  registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

