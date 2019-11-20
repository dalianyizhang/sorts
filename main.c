#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<Windows.h>
#include"ArrayList.h"
#include"sorts.h"
#define SORTKINDS (5)

//void initRandData(FILE *fp, int sortnum);
//void getData(sq *l, FILE* fp, int N);

void main() {

	//变量声明及初始化
	/*存储数据*/
	sq* pA = (sq*)malloc(sizeof(sq));
	init(pA);
	int sortorder;//排序数量级
	long sortnum;//排序数量
	int sorttime;//排序次数
	/*计时器*/
	clock_t start, stop, starts, stops;
	double duration[5], extra_cost;
	 double time_second[5] = { 0 };
	/*文件指针*/
	FILE  *fp;
	errno_t err;
	if ((err = fopen_s(&fp, "database.txt", "w+")) != 0) {
		printf("1无法打开此文件..\n");
		system("pause");
		exit(0);
	}

	//	//方案一:输入随机数数量
	//printf("请输入一个数作为总数：\n");
	//scanf_s("%ld", &sortnum);
	//int i = sortnum/10;
	//for (sortorder = 1; i < 10; sortorder++) {
	//	i /= 10;
	//}

		//方案二:选择数量级
	printf(">请选择数量级：\n");
	for (long i = 0; i < 6; i++)
		printf("%d：10e%d  ", i + 1, i + 1);
	printf("\n>");
	scanf_s("%d", &sortorder);
	printf("\n\n");
	sortnum = pow(10, sortorder);
	if (sortorder <= 3) 
		sorttime = 100000/sortnum;
	else
		sorttime = 1000000 / sortnum;

	/*生成数表 多次排序 求均值*/
	srand(time(NULL));
	printf(">正在生成随机数，请稍候...\n");
	int kk = 0;
	while(++kk <= sorttime*sortnum + 1){
		fprintf(fp, "%6ld", (rand()*rand()) % 1000000);
		fprintf(fp, "%6ld", (rand()*rand()) % 1000000);
		fprintf(fp, "%6ld", (rand()*rand()) % 1000000);
		fprintf(fp, "%6ld", (rand()*rand()) % 1000000);
		fprintf(fp, "%6ld", (rand()*rand()) % 1000000);
		fprintf(fp, "%6ld", (rand()*rand()) % 1000000);
		fprintf(fp, "%6ld", (rand()*rand()) % 1000000);
		fprintf(fp, "%6ld", (rand()*rand()) % 1000000);
		fprintf(fp, "%6ld", (rand()*rand()) % 1000000);
		fprintf(fp, "%6ld", (rand()*rand()) % 1000000);
	}
	printf("  -随机数生成完毕！\n");

	//排序部分
	long data_tmp;
	/*0预处理*/
	fseek(fp, 0L, SEEK_SET);
	printf(">正在进行预处理，请稍候...\n");
	starts = clock();
	for (int j = 0; j < sorttime; j++) {
		for (long i = 0; i < sortnum; i++) {
			fscanf_s(fp, "%6ld", &data_tmp);
			insertElem(pA, pA->len - 1, data_tmp);
		}
	}
	stops = clock();
	extra_cost = ((double)(stops - starts)) / CLK_TCK;
	printf(" -预处理完成！\n");

	/*1桶排序*/
	fseek(fp, 0L, SEEK_SET);
	printf(">算法1开始排序，请稍候...\n");
	start = clock();
	for (int j = 0; j < sorttime; j++) {
		for (long i = 0; i < sortnum; i++) {
			fscanf_s(fp, "%6ld", &data_tmp);
			insertElem(pA, pA->len - 1, data_tmp);
		}
		bucket_sort(pA->items, sortnum);
	}
	stop = clock();
	duration[0] = ((double)(stop - start - extra_cost)) / CLK_TCK;
	printf("  -算法1排序完成！\n>算法2开始排序，请稍候...\n");

	/*2堆排序*/
	fseek(fp, 0L, SEEK_SET);
	start = clock();
	for (int j = 0; j < sorttime; j++) {
		for (long i = 0; i < sortnum; i++) {
			fscanf_s(fp, "%6ld", &data_tmp);
			insertElem(pA, pA->len - 1, data_tmp);
		}
		heap_sort_desc(pA->items, sortnum);
	}
	stop = clock();
	duration[1] = ((double)(stop - start - extra_cost)) / CLK_TCK;
	printf("  -算法2排序完成！\n>算法3开始排序，请稍候...\n");
	/*3快速排序*/
	fseek(fp, 0L, SEEK_SET);
	start = clock();
	for (int j = 0; j < sorttime; j++) {
		for (long i = 0; i < sortnum; i++) {
			fscanf_s(fp, "%6ld", &data_tmp);
			insertElem(pA, pA->len - 1, data_tmp);
		}
		Quicksort(pA->items, 0, sortnum - 1);
	}
	stop = clock();
	duration[2] = ((double)(stop - start - extra_cost)) / CLK_TCK;
	printf("  -算法3排序完成！\n>算法4开始排序，请稍候...\n");
	
	/*4合并排序*/
	fseek(fp, 0L, SEEK_SET);
	start = clock();
	for (int j = 0; j < sorttime; j++) {
		for (long i = 0; i < sortnum; i++) {
			fscanf_s(fp, "%6ld", &data_tmp);
			insertElem(pA, pA->len - 1, data_tmp);
		}
		Mergesort(pA->items, sortnum);
	}
	stop = clock();
	duration[3] = ((double)(stop - start - extra_cost)) / CLK_TCK;
	printf("  -算法4排序完成！\n>算法5开始排序，请稍候...\n");

	/*5插入排序*/
	fseek(fp, 0L, SEEK_SET);
	start = clock();/*开始计时 处理一百万数据停止*/
	for (int j = 0; j < sorttime; j++) {
		for (long i = 0; i < sortnum; i++) { /*1. 读数据 初始化数组 */
			fscanf_s(fp, "%6ld", &data_tmp);
			insertElem(pA, pA->len - 1, data_tmp);
		}
		InsertionSort(pA->items, sortnum);/*2. 排序 */
	}
	stop = clock();
	duration[4] = ((double)(stop - start - extra_cost)) / CLK_TCK;
	printf("  -算法5排序完成！\n\n");

	//处理&打印实验数据
	printf(">本次排序每次处理 %d个数据,共处理 %d次，\n	各算法每次排序平均用时分别为:\n", sortnum, sorttime);
	printf("每次预处理花费时间：  %lf\n", extra_cost/sorttime);
	for (int i = 0; i < SORTKINDS; i++) {
		Sleep(500);
		time_second[i] = duration[i] /sorttime;
		printf("	-算法%d.  %lf秒 \n", i + 1, time_second[i]);
	}
	printf("PS:1.桶排序；2.堆排序；3.快速排序；4.合并排序；5.插入排序\n");
	system("pause");
}