#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void insertSort(vector<int> &vec, int gap) {

  for (int i = gap; i < vec.size(); ++i) {
    int temp = vec[i];
    int j = i - gap;
    while (j >= 0 && vec[j] > temp) {
      vec[j + gap] = vec[j];
      j -= gap;
    }
    vec[j + gap] = temp;
  }
}

void shellSort(vector<int> &vec) {
  int gap = vec.size();
  while (gap = gap / 2 > 0) {
    insertSort(vec, gap);
  }
}

int main() {
  vector<int> vec = {2, 5, 6, 7, 2};

  //   bubleSort(vec);
  shellSort(vec);

  for_each(vec.begin(), vec.end(), [](const int &num) { cout << num << " "; });
}

/*

时间复杂度介于

nlog~ n^2间

原地排序不需要额外的排序空间

*/