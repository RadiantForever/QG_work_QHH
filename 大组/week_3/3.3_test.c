#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sort3.3.h"
//包装快速排序和归并排序，使其能够适配测试函数
void QuickSortAdapter(int* arr, int length) {
	QuickSort(arr, 0, length - 1);
}
void MergeSortAdapter(int* arr, int length) {
	MergeSort(arr, 0, length - 1);
}
//测试函数 (排序函数，数据量，迭代次数)
void testSortSmallDataTime(void (*sortFunction)(int[], int), int dataSize, int iterations) {
	int* arr = (int*)malloc(dataSize * sizeof(int));
	for (int i = 0; i < dataSize; i++) {
		arr[i] = rand() % 100;//随机数范围在0到99
	}
	double totolTime = 0.0;//记录迭代总时长
	for (int i = 0; i < iterations; i++) {
		int* copy = (int*)malloc(dataSize * sizeof(int));
		//将arr的值复制到copy，复制排序后的arr值被修改
		memcpy(copy, arr, dataSize * sizeof(int));
		//计时
		clock_t start = clock();
		sortFunction(copy, dataSize);
		clock_t end = clock();
		totolTime += (double)(end - start)/CLOCKS_PER_SEC;
		free(copy);
	}
	double averageTime = totolTime / iterations;
	printf("数据量：%d，迭代次数：%d，排序平均用时%.6f秒\n", dataSize, iterations, averageTime);
	free(arr);
}
int main() {
	srand(time(0));
	int dataSize = 100, iteration = 100000;
	printf("\n插入排序\n");
	testSortSmallDataTime(InsertSort, dataSize, iteration);
	printf("\n归并排序\n");
	testSortSmallDataTime(MergeSortAdapter, dataSize, iteration);
	printf("\n快速排序\n");
	testSortSmallDataTime(QuickSortAdapter, dataSize, iteration);
	printf("\n计数排序\n");
	testSortSmallDataTime(CountSort, dataSize, iteration);
	printf("\n基数排序\n");
	testSortSmallDataTime(RadixCountSort, dataSize, iteration);
	return 0;
}