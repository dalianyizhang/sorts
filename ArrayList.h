#include<stdlib.h>
#define MAX_SIZE 100

typedef long Element;
typedef struct squence {
	Element *items;
	int listlen;/*当前数组总长度*/
	int len;/*1~listlen 当前数组有效长度*/
} sq;

//初始化表
void init(sq *l) {
	//分配内存空间
	l->items = (Element *)malloc(MAX_SIZE * sizeof(Element));
	if (!l->items) exit(0);
	l->len = 1;
	l->listlen = MAX_SIZE;
}

//插入元素(往l的指定位置i/*下标*/插入元素e)
void insertElem(sq *l, int i, Element e) {
	Element *base, *insertPtr, *p;
	if (i < 0 || i > (l->len-1)) {
		exit(0);
	}

	if (l->len >= l->listlen) {
		//扩展空间
		base = (Element *)realloc(l->items, (l->listlen + 100) * sizeof(Element));
		l->items = base;
		l->listlen = l->listlen + 100;
	}

	insertPtr = &(l->items[i]);
	for (p = &(l->items[l->len]); p >= insertPtr; p--) {
		*(p + 1) = *p;
	}

	*insertPtr = e;
	l->len++;
}

//删除元素
void delElem(sq *l, int i) { 
	Element *delElem, *q;
	if (i<1 || i>l->len)exit(0);
	delElem = &(l->items[i - 1]);
	q = l->items + l->len - 1;
	//往前推移
	for (++delElem; delElem <= q; ++delElem) {
		*(delElem - 1) = *delElem;
	}
	l->len--;
}