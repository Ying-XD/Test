#pragma once
#include <assert.h>
#include <functional>
template<typename T>
struct MyListNode {
	typedef MyListNode<T>* pointer_type;
	pointer_type prev;
	pointer_type next;
	T	data;

	MyListNode(const T& val): prev(nullptr), next(nullptr), data(val) { }
	MyListNode() : prev(nullptr), next(nullptr) { }

	void setNext(pointer_type next_ptr) {
		this->next = next_ptr;
		next_ptr->prev = this;
	}
	void setPrev(pointer_type prev_ptr) {
		this->prev = prev_ptr;
		prev_ptr->next = this;
	}
};

template<typename T>
class MyListIterator {
public:
	typedef MyListNode<T>*		node_pointer;
	typedef MyListIterator<T>	iterator;

	node_pointer node_;

	MyListIterator(const node_pointer& node) : node_(node) { }
	MyListIterator() :node_(nullptr) {}
	MyListIterator(const iterator& other) : node_(other.node_) {}

	node_pointer getNodePtr() const {	return node_;}

	bool operator == (const iterator& other) const { return node_ == other.node_; }
	bool operator != (const iterator& other) const { return node_ != other.node_; }

	T& operator *()  const { return node_->data;  }
	T* operator ->() const { return &node_->data; }

	iterator& operator++() {
		node_ = node_->next;
		return *this;
	}
	iterator operator++(int) {
		iterator tmp = *this;
		++*this;
		return tmp;
	}

	iterator operator--() {
		node_ = node_->prev;
		return *this;
	}
	iterator operator--(int) {
		iterator tmp = *this;
		--*this;
		return tmp;
	}
	
};



template<typename T>
class MyList {
public:
	typedef MyListIterator<T>	iterator;
	typedef MyListNode<T>		node_type;
	typedef MyListNode<T>*		node_pointer;

private:
	iterator begin_;
	iterator end_;
	node_pointer end_ptr_;
	size_t	 size_;

protected:
	node_pointer createNode(const T& val) {
		node_pointer tmp = new node_type(val);
		return tmp;
	}

	node_pointer createNode() {
		node_pointer tmp = new node_type();
		return tmp;
	}
	
	void destroyNode(node_pointer node_ptr) {
		delete node_ptr;
	}

	iterator next(iterator itr, size_t offset) {
		if (offset == 0) return itr;
		while (offset) {
			assert(itr != end());
			++itr;
			--offset;
		}
		return itr;
	}

	template<typename Compare = std::less<T>>
	iterator mergeSort(iterator first, iterator last, size_t size, Compare cmp);

	template<typename Compare = std::less<T>>
	iterator merge(iterator first1, iterator last1, iterator first2, iterator last2, Compare cmp);

public:
	MyList();
	~MyList();
	
	size_t	 size() const { return size_; }
	iterator begin() const	{ return begin_;}
	iterator end() const	{ return end_; }

	iterator find(const T& val);
	iterator insert(iterator itr, const T& val);
	iterator erase(iterator itr);
	void remove(const T& val);

	
	void sort();
	
	void push_back(const T& val);
	void push_front(const T& val);
};


#include "Mylist.ipp"
