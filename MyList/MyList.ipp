#include "MyList.h"


template<typename T>
MyList<T>::MyList() {
	end_ptr_ = createNode();
	end_ptr_->prev = end_ptr_;
	end_ptr_->next = end_ptr_;
	end_ = iterator(end_ptr_);
	begin_ = end_;
}

template<typename T>
MyList<T>::~MyList() {
}

template<typename T>
MyListIterator<T> MyList<T>::find(const T & val) {
	iterator itr = begin();
	while (itr != end() && *itr != val) {
		++itr;
	}
	return itr;
}


template<typename T>
MyListIterator<T> MyList<T>::insert(iterator itr, const T & val) {
#if defined(DEBUG)
	if (end() != begin() && itr != end()) {
		iterator tmp = begin_;
		while (tmp != end() && tmp != itr) {
			++tmp;
		}
		assert(tmp != end());
	}
#endif

	node_pointer node = createNode(val);
	node_pointer prev_node = itr.node_->prev;
	node_pointer next_node = itr.node_;

	node->next = next_node;
	next_node->prev = node;
	node->prev = prev_node;
	prev_node->next = node;

	++size_;
	begin_ = end_;
	++begin_;
	return --itr;
}

template<typename T>
MyListIterator<T> MyList<T>::erase(iterator itr) {
#if defined(DEBUG)
	assert(itr != end());
	iterator tmp = begin();
	while (tmp != end() && tmp != itr) {
		++tmp;
	}
	assert(tmp != end());
#endif
	node_pointer node = itr.node_;
	node_pointer prev_node = node->prev;
	node_pointer next_node = node->next;
	
	prev_node->next = next_node;
	next_node->prev = prev_node;

	--size_;
	--itr;
	destroyNode(node);
	return itr;
}

template<typename T>
void MyList<T>::remove(const T & val) {
	iterator tmp = begin();
	while (tmp != end()) {
		if (*tmp == val) {
			node_pointer node = tmp.node_;
			node->prev->next = node->next;
			node->next->prev = node->prev;
			++tmp;
			--size_;
			destroyNode(node);
		}
		else {
			++tmp;
		}
	}
}


template<typename T>
void MyList<T>::sort() {
	mergeSort();
}

template<typename T>
void MyList<T>::push_back(const T & val) {
	insert(end_, val);
}

template<typename T>
void MyList<T>::push_front(const T & val) {
	insert(begin_, val);
}


template<typename T>
template<typename Compare>
MyListIterator<T> MyList<T>::mergeSort(iterator first, iterator last, size_t size, Compare cmp) {
	if (size <= 2) return first;

	size_t half_size = size / 2;
	iterator mid = next(first, half_size);

	iterator list1 = mergeSort(first, mid, half_size, cmp);
	iterator list2 = mergeSort(mid, last, size - half_size, cmp);

	list1 = merge(list1, mid, list2, end_, cmp);
	return list1;
}

template<typename T>
template<typename Compare>
MyListIterator<T> MyList<T>::merge(iterator first1, iterator last1, iterator first2, iterator last2, Compare cmp) {
	if (first1 == last1) return first2;
	if (first2 == last2) return first1;

	if (cmp(*first2, *first1)) {
		swap(first1, first2);
		swap(last1, last2);
	}
	while (first1 != last1 && first2 != last2) {
		if (cmp(*first2, *first1)) {
			iterator tmp_itr = first2++;
			node_pointer node1 = first1.getNodePtr();
			node_pointer node2 = tmp_itr.getNodePtr();
			node2->setPrev(node1->prev);
			node2->setNext(node1);
		}
		else {
			++first1;
		}
	}

	if (first2 != last2) {
		node_pointer node1 = first1.getNodePtr();
		node_pointer node2 = first2.getNodePtr();
		node2->setPrev(node1->prev);
	}
	return new_first;
}