#include <iostream>
#include <vector>

using namespace std;

class Heap {
public:
  Heap(vector<int> &v);
  int top();
  void push(int num);
  int pop();
  int size() { return heap_size; }

private:
  int heap_size = 0;
  vector<int> vec;
  void heapify(int index);
};

int Heap::top() { return vec[0]; }
void Heap::push(int num) {
  heap_size++;
  vec.push_back(num);
  int id = vec.size() - 1;
  while (id != 0) {
    int fid = (id - 1) / 2;
    if (vec[fid] < vec[id]) {
      swap(vec[fid], vec[id]);
      id = fid;
    } else
      break;
  }
}

Heap::Heap(vector<int> &v) {
  for (auto &e : v) {
    push(e);
  }
}

int Heap::pop() {
  int temp = vec[0];
  swap(vec[0], vec[heap_size - 1]);
  heap_size--;
  heapify(0);
  return temp;
}

void Heap::heapify(int index) {
  int left_id = index * 2 + 1;
  int right_id = left_id + 1;
  if (left_id >= heap_size)
    return;

  int larget = right_id < heap_size
                   ? (vec[left_id] < vec[right_id] ? right_id : left_id)
                   : left_id;
  if (vec[larget] > vec[index]) {
    swap(vec[index], vec[larget]);
    heapify(larget);
  }
}

int main() {
  vector<int> vec = {2, 4, 5, 2, 1};
  Heap heap(vec);
  while (heap.size() != 0) {
    cout << heap.pop() << endl;
  }
}