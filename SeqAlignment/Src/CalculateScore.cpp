#include "CalculateScore.h"
#include "define.h"

float C[NMAX+1][NMAX+1];
float D[NMAX+1][NMAX+1];
//float R[NMAX+1][NMAX+1];
//float S[NMAX+1][NMAX+1];

//\brief    Minimum Cost in Linear Space
//param[in]  M/N                -- the length of two sequences
//param[in]  char[] A/ char[] B -- two comparable sequences
//Out        Minimum Cost of Conversion
float Cost(int M, int N, char A[], char B[], float W[][128])
{
    int i, j;
    float c, d, e;
    C[0][0] = 0.;
    
    for (j = 1; j < N; ++j)
    {
        // initialize 1st row
        C[0][j] = C[0][j - 1] + h;
    }
    for (i = 1; i < M; ++i)
    {
        // initialize 1st column
        C[i][0] = C[i-1][0] + h;

        // C = min(d, e, c) if j > 0 & i > 0
        for(j = 1; j < N; ++i)
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
