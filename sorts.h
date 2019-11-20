#define Cutoff (3)    /*3.快排分割需要*/
#define LENGTH(array) ( (sizeof(array)) / (sizeof(array[0])) )  /*4.堆排需要*/
#define swap(a,b) (a^=b,b^=a,a^=b)
//1.插入排序
void InsertionSort(int A[], int N) {
	int j, p;
	int Tmp;
	for (p = 1; p < N; p++) {
		Tmp = A[p];
		for (j = p; j > 0 && A[j - 1] > Tmp; j--) {
			A[j] = A[j - 1];
		}
		A[j] = Tmp;
	}
}

//2.合并排序
void Merge(int A[], int TmpArray[], int Lpos, int Rpos, int RightEnd) {
	int i, LeftEnd, NumInt,TmpPos;
	LeftEnd = Rpos - 1;
	TmpPos = Lpos;
	NumInt = RightEnd - Lpos + 1;

	while (Lpos <= LeftEnd && Rpos <= RightEnd){
		if (A[Lpos] <= A[Rpos])
			TmpArray[TmpPos++] = A[Lpos++];
		else
			TmpArray[TmpPos++] = A[Rpos++];
	}
	while (Lpos <= LeftEnd) {
		TmpArray[TmpPos++] = A[Lpos++];
	}
	while (Rpos <= RightEnd) {
		TmpArray[TmpPos++] = A[Rpos++];
	}
	for (i = 0; i < NumInt; i++, RightEnd--) {
		A[RightEnd] = TmpArray[RightEnd];
	}
}
void MSort(int A[], int TmpArray[], int Left, int Right) {
	int Center;

	if (Left < Right) {
		Center = (Left + Right) / 2;
		MSort(A, TmpArray, Left, Center);
		MSort(A, TmpArray, Center+1, Right);
		Merge(A, TmpArray, Left, Center + 1, Right);
	}
}
void  Mergesort(int A[],int N) {
	int *TmpArray;

	TmpArray = malloc(N * sizeof (int));
	if (TmpArray != NULL) {
		MSort(A, TmpArray, 0, N - 1);
		free(TmpArray);
	}
	else
		printf("No space for tmp array!");
}

//3.快排
void Quicksort(int a[], int left, int right) {
	if (left > right)
		return;
	//枢纽单元的选取为最左边、最中间、最右边三个数的中位数,使得左右分布尽量均匀
	int key;
	int index = 0;
	if (a[left] > a[right] && a[left] < a[(left + right) / 2] || a[left]<a[right] && a[left] > a[(left + right) / 2]) {
		key = a[left];
		index = left;
	}
	else if (a[right] > a[left] && a[right] < a[(left + right) / 2] || a[right]<a[left] && a[right] > a[(left + right) / 2]) {
		key = a[right];
		index = right;
	}
	else {
		key = a[(left + right) / 2];
		index = (left + right) / 2;
	}
	//将key的值放在第一位
	int temp = a[left];
	a[left] = a[index];
	a[index] = temp;

	//实现大数右边小数左边
	int i = left, j = right;
	while (i < j) {
		while (i<j&&a[j]>key) { j--; }
		if (i < j) {
			a[i++] = a[j];
		}
		while (i < j&&a[i] < key) { i++; }
		if (i < j) {
			a[j--] = a[i];
		}
	}
	a[i] = key;
	//递归地处理左边，递归地处理右边
	Quicksort(a, left, i - 1);
	Quicksort(a, i + 1, right);
}

//4.堆排序
void minheap_down(int A[], int start, int end) {
	int c = start;            // 当前(current)节点的位置
	int l = 2 * c + 1;        // 左(left)孩子的位置
	int tmp = A[c];            // 当前(current)节点的大小
	for (; l <= end; c = l, l = 2 * l + 1) {
		// "l"是左孩子，"l+1"是右孩子
		if (l < end && A[l] > A[l + 1])
			l++;        // 左右两孩子中选择较小者
		if (tmp <= A[l])
			break;        // 调整结束
		else {           // 交换值
			A[c] = A[l];
			A[l] = tmp;
		}
	}
}
void heap_sort_desc(int A[], int n) {
	int i;
	// 从(n/2-1) --> 0逐次遍历每。遍历之后，得到的数组实际上是一个最小堆。
	for (i = n / 2 - 1; i >= 0; i--)
		minheap_down(A, i, n - 1);
	// 从最后一个元素开始对序列进行调整，不断的缩小调整的范围直到第一个元素
	for (i = n - 1; i > 0; i--)
	{
		// 交换A[0]和A[i]。交换后，A[i]是A[0...i]中最小的。
		swap(A[0], A[i]);
		// 调整A[0...i-1]，使得A[0...i-1]仍然是一个最小堆。
		// 即，保证A[i-1]是A[0...i-1]中的最小值。
		minheap_down(A, 0, i - 1);
	}
}

//5.桶排序
typedef struct node {
	int key;
	struct node* next;
}KeyNode;
void bucket_sort(int A[], int size){
	int bucket_size = 1;
	
	KeyNode **bucket_table = (KeyNode**)malloc(bucket_size * sizeof(KeyNode*));
	
	for (int i = 0; i < bucket_size; i++) {    //初始化桶 
		bucket_table[i] = (KeyNode*)malloc(sizeof(KeyNode));
		bucket_table[i]->key = 0;
		bucket_table[i]->next = NULL;
	}

	for (int i = 0; i < size; i++) {
		KeyNode* node = (KeyNode*)malloc(sizeof(KeyNode));
		node->key = A[i];
		node->next = NULL;

		int index = A[i] % bucket_size ;//给数据分类的方法（关系到排序速度，很重要）
		KeyNode *p = bucket_table[index];
		if (p->key == 0) {
			p->next = node;
			p->key++;
		}
		else {
			while (p->next != NULL && p->next->key <= node->key) {//=的时候后来的元素会排在后面 
				p = p->next;
			}
			node->next = p->next;
			p->next = node;
			(bucket_table[index]->key)++;
		}
	}
	KeyNode* k = NULL;
	int num = 0;
	for (int i = 0; i < bucket_size; i++) {
		k = bucket_table[i]->next;
		while (k != NULL) {
			A[num++] = k->key;
			k = k->next;
		}
	}
}