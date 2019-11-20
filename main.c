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

	//������������ʼ��
	/*�洢����*/
	sq* pA = (sq*)malloc(sizeof(sq));
	init(pA);
	int sortorder;//����������
	long sortnum;//��������
	int sorttime;//�������
	/*��ʱ��*/
	clock_t start, stop, starts, stops;
	double duration[5], extra_cost;
	 double time_second[5] = { 0 };
	/*�ļ�ָ��*/
	FILE  *fp;
	errno_t err;
	if ((err = fopen_s(&fp, "database.txt", "w+")) != 0) {
		printf("1�޷��򿪴��ļ�..\n");
		system("pause");
		exit(0);
	}

	//	//����һ:�������������
	//printf("������һ������Ϊ������\n");
	//scanf_s("%ld", &sortnum);
	//int i = sortnum/10;
	//for (sortorder = 1; i < 10; sortorder++) {
	//	i /= 10;
	//}

		//������:ѡ��������
	printf(">��ѡ����������\n");
	for (long i = 0; i < 6; i++)
		printf("%d��10e%d  ", i + 1, i + 1);
	printf("\n>");
	scanf_s("%d", &sortorder);
	printf("\n\n");
	sortnum = pow(10, sortorder);
	if (sortorder <= 3) 
		sorttime = 100000/sortnum;
	else
		sorttime = 1000000 / sortnum;

	/*�������� ������� ���ֵ*/
	srand(time(NULL));
	printf(">������������������Ժ�...\n");
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
	printf("  -�����������ϣ�\n");

	//���򲿷�
	long data_tmp;
	/*0Ԥ����*/
	fseek(fp, 0L, SEEK_SET);
	printf(">���ڽ���Ԥ�������Ժ�...\n");
	starts = clock();
	for (int j = 0; j < sorttime; j++) {
		for (long i = 0; i < sortnum; i++) {
			fscanf_s(fp, "%6ld", &data_tmp);
			insertElem(pA, pA->len - 1, data_tmp);
		}
	}
	stops = clock();
	extra_cost = ((double)(stops - starts)) / CLK_TCK;
	printf(" -Ԥ������ɣ�\n");

	/*1Ͱ����*/
	fseek(fp, 0L, SEEK_SET);
	printf(">�㷨1��ʼ�������Ժ�...\n");
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
	printf("  -�㷨1������ɣ�\n>�㷨2��ʼ�������Ժ�...\n");

	/*2������*/
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
	printf("  -�㷨2������ɣ�\n>�㷨3��ʼ�������Ժ�...\n");
	/*3��������*/
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
	printf("  -�㷨3������ɣ�\n>�㷨4��ʼ�������Ժ�...\n");
	
	/*4�ϲ�����*/
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
	printf("  -�㷨4������ɣ�\n>�㷨5��ʼ�������Ժ�...\n");

	/*5��������*/
	fseek(fp, 0L, SEEK_SET);
	start = clock();/*��ʼ��ʱ ����һ��������ֹͣ*/
	for (int j = 0; j < sorttime; j++) {
		for (long i = 0; i < sortnum; i++) { /*1. ������ ��ʼ������ */
			fscanf_s(fp, "%6ld", &data_tmp);
			insertElem(pA, pA->len - 1, data_tmp);
		}
		InsertionSort(pA->items, sortnum);/*2. ���� */
	}
	stop = clock();
	duration[4] = ((double)(stop - start - extra_cost)) / CLK_TCK;
	printf("  -�㷨5������ɣ�\n\n");

	//����&��ӡʵ������
	printf(">��������ÿ�δ��� %d������,������ %d�Σ�\n	���㷨ÿ������ƽ����ʱ�ֱ�Ϊ:\n", sortnum, sorttime);
	printf("ÿ��Ԥ������ʱ�䣺  %lf\n", extra_cost/sorttime);
	for (int i = 0; i < SORTKINDS; i++) {
		Sleep(500);
		time_second[i] = duration[i] /sorttime;
		printf("	-�㷨%d.  %lf�� \n", i + 1, time_second[i]);
	}
	printf("PS:1.Ͱ����2.������3.��������4.�ϲ�����5.��������\n");
	system("pause");
}