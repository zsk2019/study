// 全排列算法

#include <iostream>
#include <vector>

using namespace std;

void permutations_process(vector<int> &vec, int id, vector<vector<int>> &res) {
  if (id == vec.size()) {
    res.push_back(vec);
  }
  for (int i = id; i < vec.size(); ++i) {
    swap(vec[id], vec[i]);
    permutations_process(vec, id + 1, res);
    swap(vec[id], vec[i]);
  }
}

vector<vector<int>> permutations(vector<int> &vec) {
  vector<vector<int>> res;
  permutations_process(vec, 0, res);
  return res;
}

int main() {
  vector<int> vec = {1, 2, 3, 6};
  vector<vector<int>> res = permutations(vec);

  for (auto &vec : res) {
    for (auto &e : vec) {
      cout << e << " ";
    }
    cout << endl;
  }
}