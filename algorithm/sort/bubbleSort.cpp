#include <iostream>

#include <algorithm>
#include <vector>

using namespace std;

void bubleSort(vector<int> &vec) {
  using size_type = vector<int>::size_type;
  size_type n = vec.size();
  for (size_type i = 0; i < n; ++i) {
    for (size_type j = 0; j < n - i - 1; ++j) {
      if (vec[j] > vec[j + 1]) {
        swap(vec[j], vec[j + 1]);
      }
    }
  }
}

void bubleSort2(vector<int> &vec) {
  using size_type = vector<int>::size_type;
  size_type n = vec.size();
  for (size_type i = 0; i < n; ++i) {
    bool switched = false;
    for (size_type j = 0; j < n - i - 1; ++j) {
      if (vec[j] > vec[j + 1]) {
        swap(vec[j], vec[j + 1]);
        switched = true;
      }
    }
    if (!switched)
      break;
  }
}

int main() {
  vector<int> vec = {2, 5, 6, 7, 2};

  //   bubleSort(vec);
  bubleSort2(vec);

  for_each(vec.begin(), vec.end(), [](const int &num) { cout << num << " "; });
}

/*
冒泡排序的时间复杂度为 O(n^2)
稳定排序
优化：加入变量，在如果内部循环没有交换，说明已经有序了，直接终止循环
*/