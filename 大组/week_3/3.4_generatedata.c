#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
//���������ļ��ĺ��������������ļ����֣���Χ��
void generateTestData(int n, const char* filename,int range) {
	//д������
	FILE* file = fopen(filename, "w");

	if (!file) {
		printf("�޷����ļ�\n");
		return;
	}
	srand(time(NULL));

	for (int i = 0; i < n; i++) {
		int num = rand() % range;
		fprintf(file, "%d\t", num);//�����д���ļ�
	}
	fclose(file);
	printf("������%d������������浽�ļ�%s��\n", n, filename);
}
int main() {
	//����n�����ݲ����浽�ļ�, ��Χ�Ǵ�0��range-1
	int n, range;
	char filename[100];
	printf("�������ɵ�������������������Χ���������ļ���(��.txt��β)\n");
	scanf_s("%d", &n); 
	scanf_s("%d", &range);
	getchar();//������з�
	if (!fgets(filename, sizeof(filename), stdin)) {
		printf("��ȡ�ļ���ʧ��\n");
		return 1;
	}
	//����ֹ��������з�����ֹ��������
	filename[strcspn(filename, "\n")] = '\0';

	generateTestData(n, filename, range);
	return 0;
}