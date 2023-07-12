#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void mergeSort(vector<int> &vec, int low, int high);
void merge(vector<int> &vec, int low, int mid, int high);

int main() {
  vector<int> vec = {2, 5, 3};
  int n = vec.size();
  mergeSort(vec, 0, n - 1);
  for_each(vec.begin(), vec.end(), [](const int &num) { cout << num << " "; });
}

void mergeSort(vector<int> &vec, int low, int high) {
  if (low >= high)
    return;
  int mid = low + (high - low) / 2;
  mergeSort(vec, low, mid);
  mergeSort(vec, mid + 1, high);
  merge(vec, low, mid, high);
}
void merge(vector<int> &vec, int low, int mid, int high) {
  int sz = high - low + 1;
  vector<int> mer_res(sz);
  int z = 0;
  int i = low;
  int j = mid + 1;
  while (i <= mid || j <= high) {
    if (i > mid) {
      mer_res[z] = vec[j++];
      continue;
    }
    if (j > high) {
      mer_res[z] = vec[i++];
      continue;
    }

    if (vec[i] < vec[j]) {
      mer_res[z] = vec[i++];
    } else {
      mer_res[z] = vec[j++];
    }
    ++z;
  }
  copy(mer_res.begin(), mer_res.end(), vec.begin() + low);
}

/*
时间复杂度 O(nlog)
稳定排序
非原地排序，需要额外的空间
*/