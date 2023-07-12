#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void quickSort(vector<int> &vec, int low, int high);
int partation(vector<int> &vec, int low, int high);

int main() {
  vector<int> vec = {2, 5, 6, 7, 2, 3, 5};
  int n = vec.size();
  quickSort(vec, 0, n - 1);
  for_each(vec.begin(), vec.end(), [](const int &num) { cout << num << " "; });
}

void quickSort(vector<int> &vec, int low, int high) {
  if (low >= high)
    return;
  int id = partation(vec, low, high);
  quickSort(vec, low, id - 1);
  quickSort(vec, id + 1, high);
}
int partation(vector<int> &vec, int low, int high) {
  int temp = vec[high];
  int i = low - 1;

  for (int j = low; j < high; ++j) {
    if (vec[j] < temp) {
      ++i;
      swap(vec[i], vec[j]);
    }
  }
  swap(vec[i + 1], vec[high]);
  return i + 1;
}