#define Cutoff (3)    /*3.���ŷָ���Ҫ*/
#define LENGTH(array) ( (sizeof(array)) / (sizeof(array[0])) )  /*4.������Ҫ*/
#define swap(a,b) (a^=b,b^=a,a^=b)
//1.��������
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

//2.�ϲ�����
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

//3.����
void Quicksort(int a[], int left, int right) {
	if (left > right)
		return;
	//��Ŧ��Ԫ��ѡȡΪ����ߡ����м䡢���ұ�����������λ��,ʹ�����ҷֲ���������
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
	//��key��ֵ���ڵ�һλ
	int temp = a[left];
	a[left] = a[index];
	a[index] = temp;

	//ʵ�ִ����ұ�С�����
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
	//�ݹ�ش�����ߣ��ݹ�ش����ұ�
	Quicksort(a, left, i - 1);
	Quicksort(a, i + 1, right);
}

//4.������
void minheap_down(int A[], int start, int end) {
	int c = start;            // ��ǰ(current)�ڵ��λ��
	int l = 2 * c + 1;        // ��(left)���ӵ�λ��
	int tmp = A[c];            // ��ǰ(current)�ڵ�Ĵ�С
	for (; l <= end; c = l, l = 2 * l + 1) {
		// "l"�����ӣ�"l+1"���Һ���
		if (l < end && A[l] > A[l + 1])
			l++;        // ������������ѡ���С��
		if (tmp <= A[l])
			break;        // ��������
		else {           // ����ֵ
			A[c] = A[l];
			A[l] = tmp;
		}
	}
}
void heap_sort_desc(int A[], int n) {
	int i;
	// ��(n/2-1) --> 0��α���ÿ������֮�󣬵õ�������ʵ������һ����С�ѡ�
	for (i = n / 2 - 1; i >= 0; i--)
		minheap_down(A, i, n - 1);
	// �����һ��Ԫ�ؿ�ʼ�����н��е��������ϵ���С�����ķ�Χֱ����һ��Ԫ��
	for (i = n - 1; i > 0; i--)
	{
		// ����A[0]��A[i]��������A[i]��A[0...i]����С�ġ�
		swap(A[0], A[i]);
		// ����A[0...i-1]��ʹ��A[0...i-1]��Ȼ��һ����С�ѡ�
		// ������֤A[i-1]��A[0...i-1]�е���Сֵ��
		minheap_down(A, 0, i - 1);
	}
}

//5.Ͱ����
typedef struct node {
	int key;
	struct node* next;
}KeyNode;
void bucket_sort(int A[], int size){
	int bucket_size = 1;
	
	KeyNode **bucket_table = (KeyNode**)malloc(bucket_size * sizeof(KeyNode*));
	
	for (int i = 0; i < bucket_size; i++) {    //��ʼ��Ͱ 
		bucket_table[i] = (KeyNode*)malloc(sizeof(KeyNode));
		bucket_table[i]->key = 0;
		bucket_table[i]->next = NULL;
	}

	for (int i = 0; i < size; i++) {
		KeyNode* node = (KeyNode*)malloc(sizeof(KeyNode));
		node->key = A[i];
		node->next = NULL;

		int index = A[i] % bucket_size ;//�����ݷ���ķ�������ϵ�������ٶȣ�����Ҫ��
		KeyNode *p = bucket_table[index];
		if (p->key == 0) {
			p->next = node;
			p->key++;
		}
		else {
			while (p->next != NULL && p->next->key <= node->key) {//=��ʱ�������Ԫ�ػ����ں��� 
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