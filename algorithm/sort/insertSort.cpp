#include <iostream>

#include <algorithm>
#include <vector>

using namespace std;

void insertSort(vector<int> &vec) {
  using size_type = vector<int>::size_type;
  int n = vec.size();
  for (int i = 1; i < n; ++i) {
    int temp = vec[i];
    for (int j = i - 1; j >= 0; --j) {

      if (vec[j] > temp) {
        vec[j + 1] = vec[j];
      } else {
        vec[j + 1] = temp;
        break;
      }
    }
  }
}

int main() {
  vector<int> vec = {2, 5, 6, 7, 2, 3, 5};

  //   bubleSort(vec);
  insertSort(vec);

  for_each(vec.begin(), vec.end(), [](const int &num) { cout << num << " "; });
}

/*
稳定排序
O(n^2)
*/