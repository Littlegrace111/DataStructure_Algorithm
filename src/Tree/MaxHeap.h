#ifndef _MINHEAP_H


template<class T>
class MaxHeap{
 
private:
	T* heapArray;    // ��Ŷ����ݵ�����
	int CurrentSize; // ��ǰ����Ԫ����Ŀ
	int MaxSize;     // ���������ɵ����Ԫ����Ŀ
	void BuildHeap(); // ����
public:
	//���캯������ʼ���ѵ����Ԫ����Ŀ
	MaxHeap(const int MaxSize);
	//��������
	virtual ~MaxHeap(){ delete []heapArray;};
	//�����Ҷ��㣬����TRUE
	bool isLeaf(int pos)const;
	//��������λ��
	int leftchild(int pos)const;
	//�����Һ���λ��
	int rightchild(int pos)const;
	//���ظ����λ��
	int parent(int pos)const;
	//ɾ�������±��Ԫ��
	bool Remove(int pos, T& node);
	//����в�����Ԫ��newnode
	bool Insert(const T& newNode);
	//�ӶѶ�ɾ����Сֵ
	T& RemoveMax();

};
#endif