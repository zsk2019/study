#include <iostream>

#include <algorithm>
#include <vector>

using namespace std;

void selectSort(vector<int> &vec) {
  using size_type = vector<int>::size_type;
  int n = vec.size();
  for (size_type i = n - 1; i > 0; --i) {
    for (size_type j = 0; j < i; j++) {
      if (vec[j] >= vec[i]) {
        swap(vec[j], vec[i]);
      }
    }
  }
}

int main() {
  vector<int> vec = {2, 5, 6, 7, 2};

  //   bubleSort(vec);
  selectSort(vec);

  for_each(vec.begin(), vec.end(), [](const int &num) { cout << num << " "; });
}

/*
不稳定排序
O(n^2)
*/