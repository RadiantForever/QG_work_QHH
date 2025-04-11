#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort3.2.h"
//��װ��������͹鲢����ʹ���ܹ�������Ժ���
void QuickSortAdapter(int* arr, int length) {
	QuickSort(arr, 0, length - 1);
}
void MergeSortAdapter(int* arr, int length) {
	MergeSort(arr, 0, length - 1);
}
//���Ժ��� (�����������������飬������(��ǰΪ3))
void testSortTime(void (*sortFunction)(int[], int), int dataSize[], int numSize) {
	for (int i = 0; i < numSize; i++) {
		int size = dataSize[i];
		int* arr = (int*)malloc(size * sizeof(int));
		for (int j = 0; j < size; j++) {
			arr[j] = rand() % 10000;//�������Χ��0��9999
		}
		//��ʼ��ʱ��������������֮���¼������ʱ�䣬����֮�Ϊ������ʱ
		clock_t start = clock();
		sortFunction(arr, size);
		clock_t end = clock();
		double sortTime = (double)(end - start)/CLOCKS_PER_SEC;
		printf("��������%d����ʱ��%.6f��\n", size, sortTime);
		free(arr); 
	}
}
int main() {
	srand(time(0));
	int dataSize[3] = { 10000,50000,200000 };//���Ե�������
	printf("\n��������\n");
	testSortTime(InsertSort, dataSize, 3);
	printf("\n�鲢����\n");
	testSortTime(MergeSortAdapter, dataSize, 3);
	printf("\n��������\n");
	testSortTime(QuickSortAdapter, dataSize, 3);
	printf("\n��������\n");
	testSortTime(CountSort, dataSize, 3);
	printf("\n��������\n");
	testSortTime(RadixCountSort, dataSize, 3);
	return 0;
}