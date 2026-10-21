#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>
#include <utility>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
void trickleUp(size_t idx);
  void heapify(size_t idx);
 
  std::vector<T> data_;   // the heap, stored level by level (root at index 0)
  int m_;                 // ary-ness: every node has up to m_ children
  PComparator comp_;      // comp_(a, b) is true if a has priority over b
 



};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c) : data_(), m_(m), comp_(c)
{
}
 
template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap()
{
}
 
template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item)
{
  // Add at the first free spot at the bottom, then promote it while it
  // has priority over its parent
  data_.push_back(item);
  trickleUp(data_.size() - 1);
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("top() called on an empty heap");

  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return data_[0];


}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("pop() called on an empty heap");

  }
  data_[0] = data_.back();
  data_.pop_back();
  if(!empty()){
    heapify(0);
  }


}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const
{
  return data_.empty();
}
 
template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const
{
  return data_.size();
}
 
// Promote the item at idx while it has priority over its parent
template <typename T, typename PComparator>
void Heap<T,PComparator>::trickleUp(size_t idx)
{
  while(idx > 0){
    size_t parent = (idx - 1) / m_;
    if(comp_(data_[idx], data_[parent])){
      std::swap(data_[idx], data_[parent]);
      idx = parent;
    }
    else {
      return;
    }
  }
}
 
// Push the item at idx down while one of its children has priority over it
template <typename T, typename PComparator>
void Heap<T,PComparator>::heapify(size_t idx)
{
  while(true){
    size_t firstChild = m_ * idx + 1;
    if(firstChild >= data_.size()){
      return;                           // no children: it is a leaf
    }
 
    // Find the child with the best priority (children are firstChild .. firstChild+m_-1)
    size_t best = firstChild;
    for(size_t k = firstChild + 1; k < firstChild + m_ && k < data_.size(); k++){
      if(comp_(data_[k], data_[best])){
        best = k;
      }
    }
 
    if(comp_(data_[best], data_[idx])){
      std::swap(data_[best], data_[idx]);
      idx = best;
    }
    else {
      return;
    }
  }
}


#endif

