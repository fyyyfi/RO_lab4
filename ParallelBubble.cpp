#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <mpi.h>

#include "ParallelBubbleSort.h"

using namespace std;

const double RandomDataMultiplier = 1000.0;
int ProcNum = 0; // Number of available processes
int ProcRank = -1; // Rank of current process

// Function for allocating the memory and setting the initial values
void ProcessInitialization(double *&pData, int& DataSize, double
*&pProcData, int& BlockSize) {
    setvbuf(stdout, 0, _IONBF, 0);

    if(ProcRank == 0) {
        do {
            printf("Enter the size of data to be sorted: ");
            scanf("%d", &DataSize);

            if(DataSize < ProcNum)
                printf("Data size should be greater than number of processes\n");
        } while(DataSize < ProcNum);
            printf("Sorting %d data items\n", DataSize);
    }

    // Broadcasting the data size
    MPI_Bcast(&DataSize, 1, MPI_INT, 0, MPI_COMM_WORLD);
    int RestData = DataSize;
    
    for(int i = 0; i < ProcRank; i++)
        RestData -= RestData / (ProcNum - i);
    BlockSize = RestData / (ProcNum - ProcRank);
    pProcData = new double[BlockSize];
    
    if(ProcRank == 0) {
        pData = new double[DataSize];
        // Data initalization
        //RandomDataInitialization(pData, DataSize);
        DummyDataInitialization(pData, DataSize);
    }
}

// Function for computational process termination
void ProcessTermination(double *pData, double *pProcData) {
    if(ProcRank == 0)
        delete []pData;
        delete []pProcData;
}

// Function for simple setting the data to be sorted
void DummyDataInitialization(double*& pData, int& DataSize) {
    for(int i = 0; i < DataSize; i++)
        pData[i] = DataSize - i;
}

// Function for initializing the data by the random generator
void RandomDataInitialization(double *&pData, int& DataSize) {
    srand( (unsigned)time(0) );

    for(int i = 0; i < DataSize; i++)
        pData[i] = double(rand()) / RAND_MAX * RandomDataMultiplier;
}

// Data distribution among the processes
void DataDistribution(double *pData, int DataSize, double *pProcData, int
BlockSize) {
    // Allocate memory for temporary objects
    int *pSendInd = new int[ProcNum];
    int *pSendNum = new int[ProcNum];
    int RestData = DataSize;
    int CurrentSize = DataSize / ProcNum;

    pSendNum[0] = CurrentSize ;
    pSendInd[0] = 0;

    for(int i = 1; i < ProcNum; i++) {
        RestData -= CurrentSize;
        CurrentSize = RestData / (ProcNum - i);
        pSendNum[i] = CurrentSize;
        pSendInd[i] = pSendInd[i - 1] + pSendNum[i - 1];
    }

    MPI_Scatterv(pData, pSendNum, pSendInd, MPI_DOUBLE, pProcData,
    pSendNum[ProcRank], MPI_DOUBLE, 0, MPI_COMM_WORLD);
    
    // Free the memory
    delete [] pSendNum;
    delete [] pSendInd;
}
