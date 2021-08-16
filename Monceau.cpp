#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>
#include <sstream> //stringstream

#include "Monceau.h"

using namespace std;
typedef vector<int>::iterator vecIter;
typedef vector<int>::const_iterator vecCiter;

// Add a dud first elem
Monceau::Monceau() : queue_(1,0), size_(0) {}

bool Monceau::isEmpty() const {
  return (size_ == 0);
}

int Monceau::size() const {
  return size_;
}

void Monceau::clear() {
  queue_.clear();
  queue_.push_back(0); //first item is a dud
}

int Monceau::getItem(unsigned int idx) const {
  return queue_[idx];
}

int Monceau::parent(unsigned int idx) const {
  if (size_ <= 1) return -1; //empty or root has no parent
  return ((int) idx / 2); //floor (idx/2)
}

int Monceau::child(unsigned int idx) const {
  if (size_ <= 1 || 2 * idx > size_ ) return -1; //empty or root has no child
  return (2 * idx);
}

int Monceau::find(unsigned int idx, int val) const { //O(log n)
  if (idx > size_) return -1; //base case: idx out of bounds
  if (val < queue_[idx]) return -1;   //base case: val not in min-Monceau
  if (queue_[idx] == val) return idx; //Found the val, return its index

  int childIdx = child(idx), i = -1;

  if (childIdx != -1) { //find in left and right children
    i = max(find(childIdx, val), find(childIdx + 1, val));
  }

  return i;
} 

void Monceau::bubbleUp(int idx) { //O(log n)
  int parentIdx = parent(idx);
  if (parentIdx == -1) return; //base case: root of Monceau

  if (queue_[parentIdx] > queue_[idx]) {
    swap(queue_[parentIdx], queue_[idx]);
    bubbleUp(parentIdx);
  } 
}

void Monceau::insert(int val) {
  queue_.push_back(val);
  size_++;
  bubbleUp(size_);
}

// @Precondition: index aIdx and bIdx exist in the array
int Monceau::getMinIdx(int aIdx, int bIdx, int cIdx) {
  bool isLeftSmaller = (queue_[aIdx] < queue_[bIdx]);

  if (cIdx > (int) size_) { //the last right child doesnt exist
    return isLeftSmaller ? aIdx : bIdx;
  } else if (isLeftSmaller) {
    return (queue_[aIdx] < queue_[cIdx]) ? aIdx : cIdx;
  } else {
    return (queue_[bIdx] < queue_[cIdx]) ? bIdx : cIdx;
  }
}

void Monceau::bubbleDown(int idx) { //O(log n)
  int childIdx = child(idx);
  if (childIdx == -1) return; //base case: no children left
  int minIdx = getMinIdx(idx, childIdx, childIdx + 1);
  
  if (minIdx != idx) {
    swap(queue_[minIdx], queue_[idx]);
    bubbleDown(minIdx);
  }
}

void Monceau::remove(int val) { //O(2 * log n)
  int idx = find(1, val);
  if (idx == -1) return;

  queue_[idx] = queue_[size_--]; // swap current with last item
  queue_.resize(size_ + 1); //idx 0 is a dud item
  bubbleDown(idx);
  bubbleUp(idx);
}

int Monceau::extractMin() { //Special case of remove: O(2 * log n)
  if (isEmpty()) throw "Empty Monceau!";
  
  int min = queue_[1];
  remove(min);
  return min;
}

vector<int> Monceau::MonceauSort() { //O(n log n)
  vector<int> sortedItems;
  sortedItems.reserve(size_);
  while(!isEmpty()) {
    sortedItems.push_back(extractMin());
  }

  return sortedItems;
}

// Create the Monceau given an unsorted array
void Monceau::makeMonceau(int array[], int n) { //O(n log n)?
  size_ = n;
  int i = 0;

  for (; i < n; i++) { // O(n)
    queue_.push_back(array[i]);
  }
  for (int i = n; i > 0; i--) {
    bubbleDown(i); //O(log n)
  }
}

// Create the Monceau given an unsorted vector
void Monceau::makeMonceau(std::vector<int> &input) { //O(n log n)?
  size_ = input.size();
  vecCiter citer = input.begin();

  for (; citer != input.end(); citer++) { // O(n)
    queue_.push_back(*citer);
  }
  for (int i = size_; i > 0; i--) {
    bubbleDown(i); //O(log n)
  }
}

string Monceau::toString() const {
  if (isEmpty()) return "";

  ostringstream sstream;
  copy(queue_.begin() + 1, queue_.end() - 1, ostream_iterator<int>(sstream, " "));
  sstream << *(queue_.end() - 1);
  
  return sstream.str();
}