#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
//插入排序
void InsertSort(int* arr,int length)
{
	int key;
	for (int i = 1; i < length; i++)//从第1位抽离一个元素，和以前的元素比较
	{
		key =arr[i];
		int j = i - 1;
		for(;j >= 0 && arr[j] > key;j--) //key值小则插在前面
		{								 //以前的数已排好序，则大于key退出，或j=-1退出
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = key;
	}

}
//归并排序
void merge(int* arr, int left,int mid,int right)  
{//计算左右部分的长度
	int n1 = mid - left + 1;
	int n2 = right - mid;

	int* L = (int*)malloc(n1 * sizeof(int));
	int* R = (int*)malloc(n2 * sizeof(int));

	if (L == NULL||R==NULL) {
		printf("内存分配失败\n");
		free(L); free(R);
		return;
	}
	for (int i = 0; i < n1; i++)
	{
		L[i] = arr[left + i];
	}
	for (int j = 0; j < n2; j++) 
		R[j] = arr[mid + 1 + j];

		int i = 0, j = 0, k = left;

		while (i < n1 && j < n2) {//比较两个数组，将较小的元素放到原数组中
			if (L[i] <= R[j]) {
				arr[k] = L[i];
				i++;
			}
			else {
				arr[k] = R[j];
				j++;
			}
			k++;
		}
		while (i<n1)//L剩余的元素
		{
			arr[k] = L[i];
			i++;
			k++;
		}
		while (j < n2) {//R剩余元素
			arr[k] = R[j];
			j++;
			k++;
		}
		free(L);
		free(R);
}

void MergeSort(int* arr, int left,int right)
{
	if (left < right) {//继续递归
		int mid = left + (right - left) / 2;//中间位置
		MergeSort(arr, left, mid);
		MergeSort(arr, mid + 1, right);
		merge(arr,left,mid,right);
	}
}
//快速排序
int partition(int* arr, int low, int high) 
{
	int pivot = arr[high];//将最后的元素作为基准值，将小于基准值的元素移向左边
	int i = low - 1;
	for (int j = low; j < high; j++) {
		if (arr[j] < pivot) {
			i++;

			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}
	//将基准值放到正确的位置
	int temp = arr[i + 1];
	arr[i + 1]=arr[high];
	arr[high] = temp;

	return i + 1;//基准值的位置
}
void QuickSort(int* arr,int low ,int high) 
{
	if (low < high) {//继续递归
		int pivot= partition(arr, low, high);
		QuickSort(arr, low, pivot - 1);
		QuickSort(arr, pivot + 1, high);
	}
}

//计数排序

int getMax(int* arr, int length) //获取最大值，用于计数排序和基数计数排序
{
	int max = arr[0];
	for (int i = 0; i < length; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
	}
	return max;
}

void CountSort(int* arr, int length)
{
	int max = getMax(arr,length);
	//计数数组，初始化为0
	int* count = (int*)calloc(max + 1, sizeof(int));
	//统计元素出现的个数
	for (int i = 0; i < length; i++)
		count[arr[i]]++;
	//对计数数组累加，确定每个元素的输出位置
	for (int i = 1; i <= max; i++)
		count[i] += count[i - 1];
	//输出数组
	int* output = (int*)malloc(length * sizeof(int));
	if (output == NULL) {
		printf("内存分配失败\n"); free(output);
		return;
	}
	for (int i = length - 1; i >= 0; i--) {
		output[count[arr[i]] - 1] = arr[i];
		count[arr[i]]--;
	}

	for (int i = 0; i < length; i++) {
		arr[i] = output[i];
	}
	free(count); free(output);
}
//基数计数排序? 基数排序?
void RadixCountSort(int* arr,int length) {
	int max = getMax(arr,length);

	int maxDigit = 0;
	//计算最大值的位数
	for (; max > 0; maxDigit++, max /= 10);

	int count[10];
	int* output = (int*)malloc(length * sizeof(int));
	if (output == NULL) {
		printf("内存分配失败\n"); free(output);
		return;
	}
	//按每一位进行计数排序
	for(int exp=1;maxDigit>0;exp*=10,maxDigit--){
		for (int i = 0; i < 10; i++) {
				count[i] = 0;
			}
		//当前位的数字排布
		for (int i = 0; i < length; i++) {
				int digit = (arr[i] / exp) % 10;
				count[digit]++;
			}
		for (int i = 1; i < 10; i++) {
				count[i] += count[i - 1];//增加计数，确定元素输出位置
			}
		//输出数组
		for (int i = length - 1; i >= 0; i--) {
				int digit = (arr[i] / exp) % 10;
				output[count[digit]-1] = arr[i];
				count[digit]--;
			}
		for (int i = 0; i < length; i++) {
				arr[i] = output[i];
			}
		}
	free(output);
}
//打印数组
void printArr(int* arr, int length) 
{
	for (int i = 0; i < length; i++) {
		printf("%d  ", arr[i]);
	}
}
int main() {
	int length,choice;
	printf("请输入数组长度\n");
	scanf("%d", &length);
	int* arr = (int*)malloc(length * sizeof(int));
	if (arr == NULL) {
		printf("内存分配失败\n"); free(arr);
		return 1;
	}
	printf("请输入数组元素\n");
	for (int i = 0; i < length; i++)
	{
		scanf("%d", &arr[i]);
	}
	printf("数组元素为\n");
	printArr(arr, length);
	printf("\n请选择排序算法\n插入排序（1）\t归并排序（2）\t快速排序（3）\t计数排序（4）\t基数计数排序（5）\n");
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:
		InsertSort(arr,length);
		printf("插入排序\n");
		printArr(arr, length);
		break;
	case 2:
		MergeSort(arr, 0, length - 1);
		printf("归并排序\n");
		printArr(arr, length);
		break; 
	case 3:
		QuickSort(arr, 0, length - 1);
		printf("快速排序\n");
		printArr(arr, length);
		break;
	case 4:
		CountSort(arr,length);
		printf("计数排序\n");
		printArr(arr, length);
		break;
	case 5:
		RadixCountSort(arr, length);
		printf("基数计数排序\n");
		printArr(arr, length);
		break;
	default:
		break;
	}

	free(arr);
	return 0;
}