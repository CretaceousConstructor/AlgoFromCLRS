#pragma once
#include "Debug.h"
#include <functional>
#include <vector>
#include <cassert>
#include <iostream>
template <typename T>
class Heap {
public:

	Heap() = delete;
	Heap(std::vector<T> v)
	{
		v.insert(v.begin(), (T)0);
		length = v.size();
		heap = std::move(v);
	}
	//the elements in the subarray A[(n/2)+1 ... n]are all leaves of the tree, 
	void buid_head() {
		heapified = true;
		heapSize = length - 1;
		//除了叶子节点（最后一层,最底一层）之外的所有节点都遍历heapify一遍
		for (int i = parent(length); i > 0; --i) {
			heapify(heap, i);
		}
	}
	void heapSort() {
		if (!heapified) {
			buid_head();
		}
		for (int i = length; i > 1; i--) {
			std::swap(heap[1], heap[i]);
			heapSize -= 1;//表明一个元素已经排好（这里是最大的元素已经到最后一个位置上了）
			heapify(heap, 1);
		}
		heapSize = length;
	}
	static void TestHeap() {
		std::vector<int> arr{ 2,3,4,5,6,7,8,9,10,11 };
		Heap<int> pq(std::move(arr));
		pq.buid_head();
		//h.heapSort();
		//PriorityQueue<int> pq(h);
		pq.print();/*
		int a  = pq.heapMaxmum();
		int b = pq.heapExtractMax();*/
		pq.maxHeapInsert(50);
		pq.print();
	}



private:  //TO DO how to make this one private????!!
	std::function<void(std::vector<T>&, int)> heapify = [this](std::vector<T>& A, int i)->void {
		int l = left(i);
		int r = right(i);
		int largest;
		if (l <= heapSize && A[l] > A[i]) {
			largest = l;
		}
		else {
			largest = i;
		}
		if (r <= heapSize && A[r] > A[largest]) {
			largest = r;
		}

		if (largest != i) {
			std::swap(A[i], A[largest]);
			heapify(A, largest);
		}
	};
	int heapSize = 0; //dynamic
	int length; //basically is just vector size,const
	std::vector<T> heap;
	static inline int left(int current) {
		//#ifdef DEBUG
		//		assert(current >= 0);
		//		assert(current <= heapSize);
		//#endif
		return  current * 2;
	}
	static inline int right(int current) {
		return (current * 2 + 1);
	}
	static inline int parent(int current) {
		return current / 2;
	}
	bool heapified = false;
public:
	void print() {
		for (int i = 1; i <= heapSize; i++)
		{
			std::cout << heap[i] << " ";
		}
		std::cout << std::endl;
	}
	T heapMaxmum() {
		return  heap[1];
	}
	T heapExtractMax() {
		if (heapSize < 1) {
			///erro(); error handling
			return 0;
		}
		int max = heap[1];
		heap[1] = heap[heapSize];//把最后一个元素拷贝第一个元素的位置上
		heapSize -= 1;                 //然后消除重复,因为拷贝了最后一个元素
		heapify(heap, 1);
		return max;
	}
	void heapIncreaceKey(int i, int key) {
		if (key < heap[i]) {
			//need error handling
			return;
		}
		heap[i] = key;
		while (i > 1 && heap[Heap<T>::parent(i)] < heap[i]) {
			std::swap(heap[Heap<T>::parent(i)], heap[i]);
			i = Heap<T>::parent(i);
		}
	}
	void maxHeapInsert(int key) {

		++heapSize;
		if (heapSize >= length)
		{
			heap.resize(length + 1);
			length++;
		}
		heap[heapSize] = std::numeric_limits<T>::min();
		heapIncreaceKey(heapSize, key);
	}
};

template <typename T>
using PriorityQueue = Heap<T>;