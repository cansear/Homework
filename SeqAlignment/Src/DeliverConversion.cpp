#include "DeliverConversion.h"
#include <iostream>
#include "define.h"


float CC[NMAX + 1][NMAX + 1];
float DD[NMAX + 1][NMAX + 1];
float R[NMAX + 1][NMAX + 1];
float S[NMAX + 1][NMAX + 1];
char ArrayReferenceSeq[50];
char ArrayTargetSeq[50];
char ArraySeparator[50];
int iArrayIndicator = 0;

#define FlushOutput() {\
std::cout << ArrayReferenceSeq << std::endl;\
std::cout << ArraySeparator << std::endl;\
std::cout << ArrayTargetSeq << std::endl; \
};
#define ClearOutput(){\
	iArrayIndicator = 0;\
};
void DeliverConversion(char A[], char B[], int M, int N, float W[][128])
{
	Diff(A, B, M, N, g, g, W);
	FlushOutput();
	ClearOutput();
}

void CostOnlyForward(int M, int N, char A[], char B[], float W[][128], float initT)
{
	int i, j;
	float c; // C(i, j-1)
	float e; // I(i, j-1)
	float t; // accumulate g
	float s; // C(i-1, j-1)
	CC[0][0] = 0.;
	t = g;
	for (j = 1; j <= N; ++j)
	{
		// initialize 1st row
		t += h;
		CC[0][j] = t;
		DD[0][j] = t + g;
	}
	t = initT;
	for (i = 1; i <= M; ++i)
	{
		// initialize 1st column
		s = CC[i][0];
		DD[i][0] = CC[i][0] = c = t = t + h;
		e = t + g;

		// C = min(d, e, c) if j > 0 & i > 0
		for (j = 1; j <= N; ++j)
		{
			e = MinValue(e, c + g); // I(i,j) = min{e, c+g} +h
			e += h;
			float tempMinValue = MinValue(DD[i - 1][j], CC[i - 1][j] + g);
			DD[i][j] = tempMinValue + h;
			float a1 = MinValue(DD[i][j], e);
			float b1 = CC[i - 1][j - 1] + W[A[i - 1]][B[j - 1]];
			c = MinValue(a1, b1);
			CC[i][j] = c;
		}
	}

}
void CostOnlyReverse(int M, int N, char ReverseA[], char ReverseB[], float W[][128], float initT)
{
	int i, j;
	float c; // R(i, j-1)
	float e; // I(i, j-1)
	float t; // accumulate g
	float s; // R(i-1, j-1)
	R[0][0] = 0.;
	t = g;
	for (j = 1; j <= N; ++j)
	{
		// initialize 1st row
		t += h;
		R[0][j] = t;
		S[0][j] = t + g;
	}
	t = initT;
	for (i = 1; i <= M; ++i)
	{
		// initialize 1st column
		s = R[i][0];
		S[i][0] = R[i][0] = c = t = t + h;
		e = t + g;

		// R = min(d, e, c) if j > 0 & i > 0
		for (j = 1; j <= N; ++j)
		{
			e = MinValue(e, c + g); // I(i,j) = min{e, c+g} +h
			e += h;
			float tempMinValue = MinValue(S[i - 1][j], R[i - 1][j] + g);
			S[i][j] = tempMinValue + h;
			float a1 = MinValue(S[i][j], e);
			float b1 = R[i - 1][j - 1] + W[ReverseA[i - 1]][ReverseB[j - 1]];
			c = MinValue(a1, b1);
			R[i][j] = c;
		}
	}
}

void Diff(char A[], char B[], int M, int N, float tb, float te, float W[][128])
{
	//flush outstream when total char number reach 50
	if (iArrayIndicator == 49)
	{
		FlushOutput();
		ClearOutput();
	}
	if (N == 0)
	{
		if (M > 0)
		{
			// delete A, output:
			// gca
			// --|
			//   a
			for (int i = 0; i < M; ++i)
			{
				ArrayReferenceSeq[iArrayIndicator] = A[i];
				ArraySeparator[iArrayIndicator] = '-';
				ArrayTargetSeq[iArrayIndicator] = ' ';
				iArrayIndicator++;
			}
		}
	}
	else if (M == 0)
	{
		// insert B
		for (int i = 0; i < N; ++i)
		{
			ArrayReferenceSeq[iArrayIndicator] = ' ';
			ArraySeparator[iArrayIndicator] = '-';
			ArrayTargetSeq[iArrayIndicator] = B[i];
			iArrayIndicator++;
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
		}

		float cost2 = minW /*+ 2*g*/ + h* (N - 1); // {gap(j-1) + gap(N-j)+ w(a1, bj)}

		if (costIndel > cost2)
		{
			// inserting B(j-1)
			for (int i = 0; i < replaceJ; ++i)
			{
				ArrayReferenceSeq[iArrayIndicator] = ' ';
				ArraySeparator[iArrayIndicator] = '-';
				ArrayTargetSeq[iArrayIndicator] = B[i];
				iArrayIndicator++;
			}

			// replacing a1 by bj
			if (minW == 0)
			{
				// positive match
				ArrayReferenceSeq[iArrayIndicator] = A[0];
				ArraySeparator[iArrayIndicator] = '|';
				ArrayTargetSeq[iArrayIndicator] = B[replaceJ];
				iArrayIndicator++;
			}
			else
			{
				ArrayReferenceSeq[iArrayIndicator] = A[0];
				ArraySeparator[iArrayIndicator] = '*';
				ArrayTargetSeq[iArrayIndicator] = B[replaceJ];
				iArrayIndicator++;
			}

			// inserting bjt
			for (int i = replaceJ + 1; i < N; ++i)
			{
				ArrayReferenceSeq[iArrayIndicator] = ' ';
				ArraySeparator[iArrayIndicator] = '-';
				ArrayTargetSeq[iArrayIndicator] = B[i];
				iArrayIndicator++;
			}
		}
		else
		{
			// inserting b & delete A0
			for (int i = 0; i < N; ++i)
			{
				ArrayReferenceSeq[iArrayIndicator] = ' ';
				ArraySeparator[iArrayIndicator] = '-';
				ArrayTargetSeq[iArrayIndicator] = B[i];
				iArrayIndicator++;
			}
			ArrayReferenceSeq[iArrayIndicator] = A[0];
			ArraySeparator[iArrayIndicator] = '-';
			ArrayTargetSeq[iArrayIndicator] = ' ';
			iArrayIndicator++;
		}
	}
	else
	{
		// 1. Initialize iStar as midpoint of M
		int iStar = M / 2;
		int k = 0, jStar = 0, optimalJStar = 0;

		// 2.1 Create sequences of Ai*, Ai*T, Bj*, Bj*T, Rev(A), Rev(B)
		char AiStar[NMAX], BjStar[NMAX], AiStarT[NMAX], BjStarT[NMAX], ReverseA[NMAX], ReverseB[NMAX];

		do
		{
			AiStar[k] = A[k];
			ReverseA[k] = A[M - k - 1];
			k++;
		} while (k < iStar);

		do
		{
			AiStarT[k - iStar] = A[k];
			ReverseA[k] = A[M - k - 1];
			k++;
		} while (k < M);

		k = 0;
		do
		{
			ReverseB[k] = B[N - k - 1];
			k++;
		} while (k < N);

		// 3. Compute CC and DD in forward phase, replacing [*] of Fig. 1B with "t<-tb"
		CostOnlyForward(M, N, A, B, W, tb);

		// 4. Compute RR and SS in a reverse phase, replacing [*] of Fig. 1B with "t<-te"
		CostOnlyReverse(M, N, ReverseA, ReverseB, W, te);

		// 5. Find optimal midpoint j: [0,N] minimizing min(CC(j) + RR(N-j), DD(j) + SS(N-j) - g)
		float optimalCost = 100000.0;
		bool isType1Optimal = false;
		for (jStar = 0; jStar < N; ++jStar)
		{
			float type1Cost = CC[iStar][jStar] + R[M - iStar][N - jStar];
			float type2Cost = DD[iStar][jStar] + S[M - iStar][N - jStar] - g;
			if (type1Cost < type2Cost)
			{
				if (optimalCost > type1Cost)
				{
					isType1Optimal = true;
					optimalCost = type1Cost;
					optimalJStar = jStar;
				}
			}
			else
			{
				if (optimalCost > type2Cost)
				{
					isType1Optimal = false;
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
			BjStarT[k - optimalJStar] = B[k];
			k++;
		} while (k < N);

		// 6. Divide the problem into 2 sub-problem
		if (isType1Optimal)
		{
			// type 1 
			Diff(AiStar, BjStar, iStar, optimalJStar, tb, g, W);
			Diff(AiStarT, BjStarT, M - iStar, N - optimalJStar, g, te, W);
		}
		else
		{
			// type 2
			Diff(AiStar, BjStar, iStar - 1, optimalJStar, tb, 0, W);

			// ends with a delete
			ArrayReferenceSeq[iArrayIndicator] = AiStar[iStar - 1];
			ArraySeparator[iArrayIndicator] = '-';
			ArrayTargetSeq[iArrayIndicator] = ' ';
			iArrayIndicator++;

			//begin with a delete
			ArrayReferenceSeq[iArrayIndicator] = AiStarT[0];
			ArraySeparator[iArrayIndicator] = '-';
			ArrayTargetSeq[iArrayIndicator] = ' ';
			iArrayIndicator++;

			Diff(AiStarT + 1, BjStarT, M - iStar - 1, N - optimalJStar, 0, te, W);

		}
	}
}
