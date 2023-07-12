#include <iostream>
#include <vector>

void countingSort(std::vector<int> &arr) {
  int maxElement =
      *std::max_element(arr.begin(), arr.end()); // 找到数组中的最大值

  std::vector<int> count(maxElement + 1, 0); // 创建计数数组

  // 统计每个元素出现的次数
  for (int i = 0; i < arr.size(); ++i)
    count[arr[i]]++;

  // 计算每个元素的累积次数
  for (int i = 1; i < count.size(); ++i)
    count[i] += count[i - 1];

  std::vector<int> output(arr.size());

  // 根据计数数组将元素放入正确的位置
  for (int i = arr.size() - 1; i >= 0; --i) {
    output[count[arr[i]] - 1] = arr[i];
    count[arr[i]]--;
  }

  // 将输出数组复制回原始数组
  for (int i = 0; i < arr.size(); ++i)
    arr[i] = output[i];
}

// 打印数组
void printArray(const std::vector<int> &arr) {
  for (const int &element : arr) {
    std::cout << element << " ";
  }
  std::cout << std::endl;
}

int main() {
  std::vector<int> arr = {9, 5, 7, 2, 1, 8, 3};

  std::cout << "Original array: ";
  printArray(arr);

  countingSort(arr);

  std::cout << "Sorted array: ";
  printArray(arr);

  return 0;
}
