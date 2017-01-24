#include <iostream>
#include <fstream>
#include "CalculateScore.h"
#include "DeliverConversion.h"
float W[128][128];

int ReadFile(const char* filePath, int bufferSize, char* outputBuffer)
{
	int iBufferIndex = 0;
	char seqInfo[256];
	std::fstream referFile;
	referFile.open(filePath, std::ios::in);

	referFile.getline(seqInfo, 256, '\n');
	while (!referFile.eof())
	{
		char tempBuffer[256];
		referFile.getline(tempBuffer, 256, '\n');
		for (int i = 0; i < 256; ++i)
		{
			if (tempBuffer[i] == '\0' || iBufferIndex >= bufferSize)
			{
				break;
			}
			outputBuffer[iBufferIndex] = tempBuffer[i];
			iBufferIndex++;
		}

	}
	referFile.close();
	return iBufferIndex;
}

int main(int argc, char** argv)
{
	const int M = 400, N = 400;
	//char A[M] = {'a', 'g', 't', 'a', 'c'};
	//char B[N] = {'a', 'a', 'g'};


	char referenceBuffer[M];
	char targetBuffer[N];

	//initialize bufer
	for (int i = 0; i < M; ++i)
	{
		referenceBuffer[i] = '\0';
	}
	for (int i = 0; i < N; ++i)
	{
		targetBuffer[i] = '\0';
	}
	int referenceSize = ReadFile("../Examples/refer.FASTA", M, referenceBuffer);
	int targetSize = ReadFile("../Examples/target.FASTA", N, targetBuffer);

	// initialize W matrix
	for (int i = 0; i < 128; ++i)
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

	//std::cout << "Score:" << Cost(M, N, A, B, W) << std::endl;
	std::cout << "Score:" << Cost(referenceSize, targetSize, referenceBuffer, targetBuffer, W) << std::endl;
	//DeliverConversion(A, B, M, N, W);
	DeliverConversion(referenceBuffer, targetBuffer, referenceSize, targetSize, W);
	std::cin.get();
	return 0;
}
