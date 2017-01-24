#include <iostream>
#include "CalculateScore.h"
float W[128][128];


int main(int argc, char** argv)
{
    int command;
    std::cout << "Score:" << std::endl;
    const int M = 5, N = 3;
    char A[M] = {'a', 'g', 't', 'a', 'c'};
    char B[N] = {'a', 'a', 'g'};
    // initialize W matrix
    
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

    std::cout << Cost(M, N, A, B, W) << std::endl;
    std::cin >> command;
    return 0;
}
