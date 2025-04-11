#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
//��������
void InsertSort(int* arr, int length)
{
	int key;
	for (int i = 1; i < length; i++)//�ӵ�1λ����һ��Ԫ�أ�����ǰ��Ԫ�رȽ�
	{
		key = arr[i];
		int j = i - 1;
		for (; j >= 0 && arr[j] > key; j--) //keyֵС�����ǰ��
		{								 //��ǰ�������ź��������key�˳�����j=-1�˳�
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = key;
	}

}
//�鲢����
void merge(int* arr, int left, int mid, int right)
{//�������Ҳ��ֵĳ���
	int n1 = mid - left + 1;
	int n2 = right - mid;

	int* L = (int*)malloc(n1 * sizeof(int));
	int* R = (int*)malloc(n2 * sizeof(int));

	if (L == NULL || R == NULL) {
		printf("�ڴ����ʧ��\n");
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

	while (i < n1 && j < n2) {//�Ƚ��������飬����С��Ԫ�طŵ�ԭ������
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
	while (i < n1)//Lʣ���Ԫ��
	{
		arr[k] = L[i];
		i++;
		k++;
	}
	while (j < n2) {//Rʣ��Ԫ��
		arr[k] = R[j];
		j++;
		k++;
	}
	free(L);
	free(R);
}

void MergeSort(int* arr, int left, int right)
{
	if (left < right) {//�����ݹ�
		int mid = left + (right - left) / 2;//�м�λ��
		MergeSort(arr, left, mid);
		MergeSort(arr, mid + 1, right);
		merge(arr, left, mid, right);
	}
}
//��������
int partition(int* arr, int low, int high)
{
	int pivot = arr[high];//������Ԫ����Ϊ��׼ֵ����С�ڻ�׼ֵ��Ԫ���������
	int i = low - 1;
	for (int j = low; j < high; j++) {
		if (arr[j] < pivot) {
			i++;

			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}
	//����׼ֵ�ŵ���ȷ��λ��
	int temp = arr[i + 1];
	arr[i + 1] = arr[high];
	arr[high] = temp;

	return i + 1;//��׼ֵ��λ��
}
void QuickSort(int* arr, int low, int high)
{
	if (low < high) {//�����ݹ�
		int pivot = partition(arr, low, high);
		QuickSort(arr, low, pivot - 1);
		QuickSort(arr, pivot + 1, high);
	}
}

//��������

int getMax(int* arr, int length) //��ȡ���ֵ�����ڼ�������ͻ�����������
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
	int max = getMax(arr, length);
	//�������飬��ʼ��Ϊ0
	int* count = (int*)calloc(max + 1, sizeof(int));
	//ͳ��Ԫ�س��ֵĸ���
	for (int i = 0; i < length; i++)
		count[arr[i]]++;
	//�Լ��������ۼӣ�ȷ��ÿ��Ԫ�ص����λ��
	for (int i = 1; i <= max; i++)
		count[i] += count[i - 1];
	//�������
	int* output = (int*)malloc(length * sizeof(int));
	if (output == NULL) {
		printf("�ڴ����ʧ��\n"); free(output);
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
//������������? ��������?
void RadixCountSort(int* arr, int length) {
	int max = getMax(arr, length);

	int maxDigit = 0;
	//�������ֵ��λ��
	for (; max > 0; maxDigit++, max /= 10);

	int count[10];
	int* output = (int*)malloc(length * sizeof(int));
	if (output == NULL) {
		printf("�ڴ����ʧ��\n"); free(output);
		return;
	}
	//��ÿһλ���м�������
	for (int exp = 1; maxDigit > 0; exp *= 10, maxDigit--) {
		for (int i = 0; i < 10; i++) {
			count[i] = 0;
		}
		//��ǰλ�������Ų�
		for (int i = 0; i < length; i++) {
			int digit = (arr[i] / exp) % 10;
			count[digit]++;
		}
		for (int i = 1; i < 10; i++) {
			count[i] += count[i - 1];//���Ӽ�����ȷ��Ԫ�����λ��
		}
		//�������
		for (int i = length - 1; i >= 0; i--) {
			int digit = (arr[i] / exp) % 10;
			output[count[digit] - 1] = arr[i];
			count[digit]--;
		}
		for (int i = 0; i < length; i++) {
			arr[i] = output[i];
		}
	}
	free(output);
}
//��������
int readData(const char* filename, int** data, int* n) {
	FILE* file = fopen(filename, "r");//ֻ��ģʽ
	if (!file) {
		printf("�޷����ļ�\n");
		return 0;
	}
	int count = 0,temp;
	while (fscanf(file, "%d", &temp) != EOF) {//�����ļ�ĩβ
		count++;
	}

	*n = count;
	rewind(file);
	*data = (int*)malloc(count * sizeof(int));
	for (int i = 0; i < count; i++) {
		fscanf(file, "%d", &(*data)[i]);
	}
	fclose(file);
	printf("�Ѵ��ļ�%s�ж�ȡ��%d������\n",filename,count);
	return 1;
}
//��ӡ����
void printArr(int* arr, int length)
{
	for (int i = 0; i < length; i++) {
		printf("%d  ", arr[i]);
	}
}
int main() {
	int* data = NULL;
	int n = 0;
	char filename[100];	
	printf("��������ҵ��ļ���(��.txt��β)\n");
	getchar();
	if (!fgets(filename, sizeof(filename), stdin)) {
		printf("��ȡ�ļ���ʧ��\n");
		return 1;
	}
	//����ֹ��������з�����ֹ��������
	filename[strcspn(filename, "\n")] = '\0';

	if (readData(filename, &data, &n)) {
		printf("��ȡ������\n");
		printArr(data,n);
		printf("��������\n");
		//�Բ�������Ϊ��
		InsertSort(data, n);
		printArr(data, n);

		free(data);
	}
	return 0;
}