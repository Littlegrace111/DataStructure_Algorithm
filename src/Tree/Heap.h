#ifndef _HEAP_H
#define _HEAP_H

template <class T>
class MinHeap{
private:
	T* heapArray; // ��Ŷ����ݵ�����
	int CurrentSize; // ��ǰ����Ԫ����Ŀ
	int MaxSize; //���������ɵ����Ԫ����Ŀ
	void BuildHeap(); //����
public:
	MinHeap(const int n); //���캯���� n��ʾ��ʼ���ѵ����Ԫ����Ŀ
	virtual ~MinHeap(){ delete []heapArray; }

	bool isLeaf(int pos) const; //Ҷ�ӽ�㣬����ture
	int leftChild(int pos) const; //�������ӵ�λ��
	int rightChild(int pos) const; //�����Һ��ӵ�λ��
	int parent(int pos) const; //���ظ�����λ��
	bool Remove(int pos, T& node); // ɾ�������±��Ԫ��
	bool Insert(const T& newnode); //����в�����Ԫ��
	T& RemoveMin();// �ӶѶ�ɾ����СԪ��
	void SiftUp(int position); //��position���Ͽ�ʼ������ʹ���г�Ϊ��
	void SiftDown(int position); // ɸѡ������������left��ʾ��ʼ����������±�
};

//����
//�Ӷѵĵ�һ����֧���heapArray[CurrentSize/2-1]
//��ʼ���Ե������𲽰�һ������֧���Ϊ�������������ɶ�
template <class T>
inline void MinHeap<T>::BuildHeap()
{
	//��������ɸѡ����
	
}

//ɸѡ��
template <class T>
inline void MinHeap<T>::SiftDown( int position )
{
	int i = position; // ��ʶ�����
	int j = 2*i+1; // ��ʶ�ؼ�ֵ��С���ӽ��
	T temp = heapArray[i]; //���游���
	//��ɸ
	while(j<CurrentSize){
		if((j<CurrentSize-1)&&(heapArray[j]>heapArray[j+1]))
			j++; //jָ����ֵ��С���ӽ��
		if(temp>heapArray[j]){
			heapArray[i] = heapArray[j];
			i = j;
			j = 2*j+1;//���¼���
		}// end if
		else 
			break;
	}
	heapArray[i] = temp;
}

template <class T>
inline int MinHeap<T>::parent( int pos ) const
{
	return (pos-1)/2; //���ظ����λ��
}

template <class T>
inline int MinHeap<T>::rightChild( int pos ) const
{
	return 2*pos+2; // �����Һ��ӵ�λ��
}

template <class T>
inline int MinHeap<T>::leftChild( int pos ) const
{
	return 2*pos+1;//�������ӵ�λ��
}

template <class T>
inline bool MinHeap<T>::isLeaf( int pos ) const
{
	return (pos>=CurrentSize/2)&&(pos<CurrentSize);
}

template <class T>
inline MinHeap<T>::MinHeap( const int n )
{
	if(n<=0) return;
	CurrentSize = 0;
	MaxSize = n; //��ʼ���ѵ�����Ϊn
	heapArray = new T[MaxSize]; // �����ѿռ�
	BuildHeap(); //�˴����ж�Ԫ�صĸ�ֵ����
}

#endif