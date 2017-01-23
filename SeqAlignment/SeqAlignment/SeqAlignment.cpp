// SeqAlignment.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#define NMAX 400
#define g 2
#define h 0.5f
#define DeleteSeparator "\n-\n "
#define InsertSeparator " \n-\n"
#define MatchSeparator "\n|\n"
#define DisMatchSeparator "\n*\n"
#define MinValue(a,b)\
     (a) > (b) ? (b) : (a);

float W[128][128] = {

};

float C[NMAX+1][NMAX+1];
float D[NMAX+1][NMAX+1];
float R[NMAX+1][NMAX+1];
float S[NMAX+1][NMAX+1];

//\brief    Minimum Cost in Linear Space
//param[in]  M/N                -- the length of two sequences
//param[in]  char[] A/ char[] B -- two comparable sequences
//param[in]  g/h                -- coefficient of gap function
//Out        Minimum Cost of Conversion
float Cost(int M, int N, char A[], char B[])
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

void CostOnly(int M, int N, char A[], char B[], float initT)
{
    int i, j;
    float c; // C(i, j-1)
    float e; // I(i, j-1)
    float t; // accumulate g
    float s; // C(i-1, j-1)
    C[0][0] = 0.;
    t = g;
    for (j = 1; j < N; ++j)
    {
        // initialize 1st row
        t += h;
        C[0][j] = t;
        D[0][j] = t + g;
    }
    t = initT;
    for (i = 1; i < M; ++i)
    {
        // initialize 1st column
        s = C[i][0];
        D[i][0] = C[i][0] = c = t = t + h;
        e = t +g;

        // C = min(d, e, c) if j > 0 & i > 0
        for(j = 1; j < N; ++i)
        {
            e = MinValue(e, c+g) + h; // I(i,j) = min{e, c+g} +h
            D[i][j] = MinValue(D[i-1][j], C[i-1][j] + g) + h;
            float a1 = MinValue(D[i][j], e);
            float b1 = s + W[A[i]][B[j]];
            c = MinValue(a1, b1);
            C[i][j] = s = c;
        }
    }

}
void CostOnlyReverse(int M, int N, char ReverseA[], char ReverseB[], float initT)
{
    int i, j;
    float c; // R(i, j-1)
    float e; // I(i, j-1)
    float t; // accumulate g
    float s; // R(i-1, j-1)
    R[0][0] = 0.;
    t = g;
    for (j = 1; j < N; ++j)
    {
        // initialize 1st row
        t += h;
        R[0][j] = t;
        S[0][j] = t + g;
    }
    t = initT;
    for (i = 1; i < M; ++i)
    {
        // initialize 1st column
        s = R[i][0];
        S[i][0] = R[i][0] = c = t = t + h;
        e = t +g;

        // R = min(d, e, c) if j > 0 & i > 0
        for(j = 1; j < N; ++i)
        {
            e = MinValue(e, c+g) + h; // I(i,j) = min{e, c+g} +h
            S[i][j] = MinValue(S[i-1][j], R[i-1][j] + g) + h;
            float a1 = MinValue(S[i][j], e);
            float b1 = s + W[ReverseA[i]][ReverseB[j]];
            c = MinValue(a1, b1);
            R[i][j] = s = c;
        }
    }
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
            // delete A, output:
            // gca
            // --|
            //   a
            for (int i =0; i < M; ++i)
            {
                std::cout << A[i] << DeleteSeparator;
            }
        }
    }
    else if (M == 0)
    {
        // insert B
        for (int i = 0; i < N; ++i)
        {
             std::cout << InsertSeparator <<B[i];
        }
    }
    else if (M == 1)
    {
        float gapN = g + h * N;
        float minG = MinValue(tb, te);
        float costIndel = minG + h + gapN;
        float minW = 100000.0;
        int replaceJ = 0; //Suppose there is only one replacement
        for (int j = 0; j < N; ++j)
        {
            if (minW > W[A[0]][B[j]])
            {
                minW = W[A[0]][B[j]];
                replaceJ = j;
            }
            minW = MinValue(minW, W[A[0]][B[j]]);
        }

        float cost2 = minW + 2*g + h* (N-1); // {gap(j-1) + gap(N-j)+ w(a1, bj)}

        if (costIndel < cost2)
        {
            // inserting B(j-1)
            for ( int i = 0; i < replaceJ; ++i)
            {
                std::cout << InsertSeparator << B[i];
            }

            // replacing a1 by bj
            if (minW == 0)
            {
                // positive match
                std::cout << A[0] << MatchSeparator << B[replaceJ];

            }
            else
            {
                std::cout << A[0] << DisMatchSeparator << B[replaceJ];
            }

            // inserting bjt
            for(int i = replaceJ+1; i < N; ++i)
            {
                std::cout << InsertSeparator << B[i];
            }
        }
        else
        {
            // inserting b & delete A
            std::cout << A[0] << DisMatchSeparator << B[0];
            for (int i = 1; i < N; ++i)
            {
                std::cout << InsertSeparator << B[i];
            }
        }
    }
    else
    {
        // 1. Initialize iStar as midpoint of M
        int iStar = M/2;
        int k = 0, jStar = 0, optimalJStar = 0;
        
        // 2.1 Create sequences of Ai*, Ai*T, Bj*, Bj*T, Rev(A), Rev(B)
        char AiStar[NMAX], BjStar[NMAX], AiStarT[NMAX], BjStarT[NMAX], ReverseA[NMAX], ReverseB[NMAX];

        do
        {
            AiStar[k] = A[k];
            ReverseA[k] = A[M-k];
            k++;
        }while (k < iStar + 1);

        do 
        {
            AiStarT[k] = A[k];
            ReverseA[k] = A[M-k];
            k++;
        } while (k < M + 1);

        k = 0;
        do 
        {
            ReverseB[k] = B[N-k];
            k++;
        } while (k < N + 1);

        // 3. Compute CC and DD in forward phase, replacing [*] of Fig. 1B with "t<-tb"
        CostOnly(M, N, A, B, tb);

        // 4. Compute RR and SS in a reverse phase, replacing [*] of Fig. 1B with "t<-te"
        CostOnlyReverse(M, N, ReverseA, ReverseB, te);

        // 5. Find optimal midpoint j: [0,N] minimizing min(CC(j) + RR(N-j), DD(j) + SS(N-j) - g)
        float optimalCost = 100000.0;
        bool isType1Optimal = false;
        for (jStar = 0; jStar < N; ++jStar)
        {
            float type1Cost = C[iStar][jStar] + R[iStar][N - jStar];
            float type2Cost = D[iStar][jStar] + S[iStar][N - jStar] - g;
            if (type1Cost < type2Cost)
            {
                isType1Optimal = true;
                if (optimalCost > type1Cost)
                {
                    optimalCost = type1Cost;
                    optimalJStar = jStar;
                }
            }
            else
            {
                isType1Optimal = false;
                if (optimalCost > type2Cost)
                {
                    optimalCost = type2Cost;
                    optimalJStar = jStar;
                }
            }
        }

        // 2. PART2 initialize Bj*: from left-most to optimal j*
        k = 0;
        do 
        {
            BjStar[k] = B[k];
            k++;
        } while (k < optimalJStar);

        do 
        {
            BjStarT[k] = B[k];
            k++;
        } while (k < N);

        // 6. Divide the problem into 2 sub-problem
        if (isType1Optimal)
        {
            // type 1 
            Diff(AiStar, BjStar, iStar, optimalJStar, tb, g);
            Diff(AiStarT, BjStarT, M-iStar, N-optimalJStar, g, te);
        }
        else
        {
            // type 2
            Diff(AiStar, BjStar, iStar -1, optimalJStar, tb, 0);
            std::cout << A[iStar] << "\n\n-" << A[iStar+1] << "\n\n-";
            Diff(AiStarT + 1, BjStarT, M-iStar-1, N-optimalJStar, 0, te);
        }
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
    // initialize W matrix
    float W[128][128];
    for(int i = 0; i < 128; ++i)
    {
        for (int j = 0; j < 128; ++j)
        {
            if (i == j)
            {
                W[i][j] = 0;
            }
            else
            {
                W[i][j] = 1;
            }
        }
    }
    std::cout << "Score: " << Cost(M, N, A, B) << std::endl; 
    DeliverConversion(A, B, M, N);
    std::cout << std::endl;
    std::cout << "Please press any key to exit." << std::endl;
    std::cin >> command;
	return 0;
}

