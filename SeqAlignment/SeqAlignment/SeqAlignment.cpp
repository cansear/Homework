// SeqAlignment.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#define NMAX 400
float C[NMAX+1][NMAX+1];

//\brief    Minimum Cost in Linear Space
//param[in]  M/N                -- the length of two sequences
//param[in]  char[] A/ char[] B -- two comparable sequences
//param[in]  g/h                -- coefficient of gap function
//Out        Minimum Cost of Conversion
float Cost(int M, int N, char A[], char B[], float W[][128], float g, float h)
{
    int i, j;
    float c, d, e;
    C[0][0] = 0.;
    for (j = 1; j < N + 1; ++j)
    {
        // initialize 1st row
        C[0][j] = C[0][j - 1] + h;
    }
    for (i = 1; i < M + 1; ++i)
    {
        // initialize 1st column
        C[i][0] = C[0][j-1] + h;

        // C = min(d, e, c) if j > 0 & i > 0
        for(j = 1; j < N + 1; ++i)
        {
            c = C[i-1][j-1] + W[A[i]][B[j]];
            d = C[i-1][j] + h;
            e = C[i][j-1] + h;

            if (d < c)
            {
                c = d;
            }
            else if(e < c)
            {
                c = e;
            }
            C[i][j] = c;
        }
    }

    return C[M][N];
}

//\brief    Delivering a Conversion in Linear Space
//param[in]  
//param[in]  
//Out        
void Diff(char A[], char B[], int M, int N, float tb, float te)
{
    if (N = 0)
    {
        if (M > 0)
        {
            std::cout << "delete A" << std::endl;
        }
        else if (M == 0)
        {
            std::cout << "insert B" << std::endl;
        }
        else if (M == 1)
        {

        }
    }
    else
    {
        int iStar = M/2;
    }
}

void DeliverConversion(char A[], char B[], int M, int N)
{
    Diff(A, B, M, N, g, g);
}

int _tmain(int argc, _TCHAR* argv[])
{
    int command;
    const int M = 5, N = 3;
    char A[M] = {'a', 'g', 't', 'a', 'c'};
    char B[N] = {'a', 'a', 'g'};

    std::cout << Diff(M, N, A, B, w, 2, 0.5) << std::endl;
    std::cout << "Please press any key to exit." << std::endl;
    std::cin >> command;
	return 0;
}

