
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */
 #include <cmath>

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    return 2*currentIdx;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    return 2*currentIdx+1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    return floor(currentIdx/2);
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    return ((currentIdx*2) <= (_elems.size()));
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
  //NOTE: MAY HAVE TO CHECK IF ONLY ONE NODE
  if (!(hasAChild(currentIdx))) return -1;

  if ((currentIdx*2)+1 > (_elems.size()-1)) return leftChild(currentIdx); //no right child
  // Dont need to check if no left child, because there will either be no children
  // or a left child (complete tree characteristic)

    size_t leftidx = leftChild(currentIdx);
    size_t rightidx = rightChild(currentIdx);

    return (higherPriority(_elems[leftidx], _elems[rightidx])) ? leftidx : rightidx;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    if (!hasAChild(currentIdx)) return; //if leaf node, already a min-heap
    size_t maxPriorityChildIdx = maxPriorityChild(currentIdx); //get the child we may swap
    if (higherPriority(_elems[maxPriorityChildIdx], _elems[currentIdx])) { //if child is smaller
      std::swap(_elems[currentIdx], _elems[maxPriorityChildIdx]); //swap
      heapifyDown(maxPriorityChildIdx); //rescursively check chilren subtree
    }

}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
    _elems.push_back(T());
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
  // @TODO Construct a heap using the buildHeap algorithm
    _elems.push_back(T());
    for (size_t i = 0; i < elems.size(); i++) {
      _elems.push_back(elems[i]);
    }
    size_t firstparent = (_elems.size()-1) / 2; //all elements after this are leaf nodes
    for (size_t i = firstparent; i >= root(); i-- ) {
      heapifyDown(i);
    }
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    if (this->empty()) return T();

    T ret = _elems[root()]; //store root node (highest priority)
    _elems[root()] = _elems[_elems.size()-1]; //swap with last
    _elems.pop_back(); //delete root, now stored at last elem
    heapifyDown(root()); //recursively fix heap
    return ret;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    return _elems[root()];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{/*
    _elems.push_back(elem);
    heapifyUp(_elems.size()-1); */
    _elems.push_back(elem);
    size_t size = _elems.size();
    heapifyUp(size - 1);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
/*
    T curr = _elems[idx]; //store current value
    _elems[idx] = elem; //replace
    if (elem > curr) heapifyDown(idx); //if the new value is greater wil need to check lower
    else heapifyUp(idx); //if new value is smaller, it may be smaller than parents, so heapify up
    */
    _elems[idx + 1] = elem;
    heapifyDown(root());
}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    return (_elems.size() <= 1) ? true : false;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
