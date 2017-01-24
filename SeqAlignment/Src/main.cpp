#include <iostream>
#include "CalculateScore.h"
#include "DeliverConversion.h"
float W[128][128];


int main(int argc, char** argv)
{
    int command;
    
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

    std::cout << "Score:" << Cost(M, N, A, B, W) << std::endl;
    DeliverConversion(A, B, M, N, W);
    std::cout << std::endl;
    std::cout << "Please press any key to exit." << std::endl;
    std::cin >> command;
    return 0;
}
