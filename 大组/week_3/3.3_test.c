#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sort3.3.h"
//��װ��������͹鲢����ʹ���ܹ�������Ժ���
void QuickSortAdapter(int* arr, int length) {
	QuickSort(arr, 0, length - 1);
}
void MergeSortAdapter(int* arr, int length) {
	MergeSort(arr, 0, length - 1);
}
//���Ժ��� (������������������������)
void testSortSmallDataTime(void (*sortFunction)(int[], int), int dataSize, int iterations) {
	int* arr = (int*)malloc(dataSize * sizeof(int));
	for (int i = 0; i < dataSize; i++) {
		arr[i] = rand() % 100;//�������Χ��0��99
	}
	double totolTime = 0.0;//��¼������ʱ��
	for (int i = 0; i < iterations; i++) {
		int* copy = (int*)malloc(dataSize * sizeof(int));
		//��arr��ֵ���Ƶ�copy������������arrֵ���޸�
		memcpy(copy, arr, dataSize * sizeof(int));
		//��ʱ
		clock_t start = clock();
		sortFunction(copy, dataSize);
		clock_t end = clock();
		totolTime += (double)(end - start)/CLOCKS_PER_SEC;
		free(copy);
	}
	double averageTime = totolTime / iterations;
	printf("��������%d������������%d������ƽ����ʱ%.6f��\n", dataSize, iterations, averageTime);
	free(arr);
}
int main() {
	srand(time(0));
	int dataSize = 100, iteration = 100000;
	printf("\n��������\n");
	testSortSmallDataTime(InsertSort, dataSize, iteration);
	printf("\n�鲢����\n");
	testSortSmallDataTime(MergeSortAdapter, dataSize, iteration);
	printf("\n��������\n");
	testSortSmallDataTime(QuickSortAdapter, dataSize, iteration);
	printf("\n��������\n");
	testSortSmallDataTime(CountSort, dataSize, iteration);
	printf("\n��������\n");
	testSortSmallDataTime(RadixCountSort, dataSize, iteration);
	return 0;
}