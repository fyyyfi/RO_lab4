void ProcessInitialization(double *&pData, int& DataSize, double
*&pProcData, int& BlockSize);
void ProcessTermination(double *pData, double *pProcData);
void DummyDataInitialization(double*& pData, int& DataSize);
void RandomDataInitialization(double *&pData, int& DataSize);
void DataDistribution(double *pData, int DataSize, double *pProcData, int
BlockSize);
void DataCollection(double *pData, int DataSize, double *pProcData, int
BlockSize);
void ParallelBubble(double *pProcData, int BlockSize);
void ExchangeData(double *pProcData, int BlockSize, int DualRank,
double *pDualData, int DualBlockSize);
void TestDistribution(double *pData, int DataSize, double *pProcData, int
BlockSize);
void ParallelPrintData(double *pProcData, int BlockSize);
void TestResult(double *pData, double *pSerialData, int DataSize);
void CopyData(double *pData, int DataSize, double *pDataCopy);
bool CompareData(double *pData1, double *pData2, int DataSize);
void SerialBubbleSort(double *pData, int DataSize);
void SerialStdSort(double *pData, int DataSize);
void PrintData(double *pData, int DataSize);