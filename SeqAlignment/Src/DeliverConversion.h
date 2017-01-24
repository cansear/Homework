// Recusive solution of delivering concersion
#include "define.h"

void DeliverConversion(char A[], char B[], int M, int N, float W[][128]);

//\brief    Delivering a Conversion in Linear Space
//param[in]  
//param[in]  
//Out        
void Diff(char A[], char B[], int M, int N, float tb, float te, float W[][128]);

void CostOnlyForward(int M, int N, char A[], char B[], float W[][128], float initT);

void CostOnlyReverse(int M, int N, char ReverseA[], char ReverseB[],float W[][128], float initT);
