#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
//生成数据文件的函数（数据数，文件名字，范围）
void generateTestData(int n, const char* filename,int range) {
	//写入数据
	FILE* file = fopen(filename, "w");

	if (!file) {
		printf("无法打开文件\n");
		return;
	}
	srand(time(NULL));

	for (int i = 0; i < n; i++) {
		int num = rand() % range;
		fprintf(file, "%d\t", num);//随机数写入文件
	}
	fclose(file);
	printf("已生成%d个随机数并保存到文件%s中\n", n, filename);
}
int main() {
	//生成n个数据并保存到文件, 范围是从0到range-1
	int n, range;
	char filename[100];
	printf("输入生成的随机数个数和随机数范围，并输入文件名(以.txt结尾)\n");
	scanf_s("%d", &n); 
	scanf_s("%d", &range);
	getchar();//清除换行符
	if (!fgets(filename, sizeof(filename), stdin)) {
		printf("读取文件名失败\n");
		return 1;
	}
	//用终止符替代换行符，防止出现乱码
	filename[strcspn(filename, "\n")] = '\0';

	generateTestData(n, filename, range);
	return 0;
}