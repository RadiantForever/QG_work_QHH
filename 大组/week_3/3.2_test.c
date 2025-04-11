#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort3.2.h"
//包装快速排序和归并排序，使其能够适配测试函数
void QuickSortAdapter(int* arr, int length) {
	QuickSort(arr, 0, length - 1);
}
void MergeSortAdapter(int* arr, int length) {
	MergeSort(arr, 0, length - 1);
}
//测试函数 (排序函数，数据量数组，测试量(当前为3))
void testSortTime(void (*sortFunction)(int[], int), int dataSize[], int numSize) {
	for (int i = 0; i < numSize; i++) {
		int size = dataSize[i];
		int* arr = (int*)malloc(size * sizeof(int));
		for (int j = 0; j < size; j++) {
			arr[j] = rand() % 10000;//随机数范围在0到9999
		}
		//开始计时，运行完排序函数之后记录结束的时间，两者之差即为测试用时
		clock_t start = clock();
		sortFunction(arr, size);
		clock_t end = clock();
		double sortTime = (double)(end - start)/CLOCKS_PER_SEC;
		printf("数据量：%d，用时：%.6f秒\n", size, sortTime);
		free(arr); 
	}
}
int main() {
	srand(time(0));
	int dataSize[3] = { 10000,50000,200000 };//测试的数据量
	printf("\n插入排序\n");
	testSortTime(InsertSort, dataSize, 3);
	printf("\n归并排序\n");
	testSortTime(MergeSortAdapter, dataSize, 3);
	printf("\n快速排序\n");
	testSortTime(QuickSortAdapter, dataSize, 3);
	printf("\n计数排序\n");
	testSortTime(CountSort, dataSize, 3);
	printf("\n基数排序\n");
	testSortTime(RadixCountSort, dataSize, 3);
	return 0;
}