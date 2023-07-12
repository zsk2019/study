#include <algorithm>
#include <iostream>
#include <vector>

// 获取数字的某一位上的值
int getDigit(int num, int digit) {
  int divisor = 1;
  for (int i = 0; i < digit; ++i)
    divisor *= 10;
  return (num / divisor) % 10;
}

// 对数组进行基数排序
void radixSort(std::vector<int> &arr) {
  int maxElement =
      *std::max_element(arr.begin(), arr.end()); // 找到数组中的最大值

  int digitCount = 0;
  while (maxElement > 0) {
    maxElement /= 10;
    ++digitCount;
  }

  std::vector<int> output(arr.size());
  std::vector<int> count(10, 0);

  for (int digit = 0; digit < digitCount; ++digit) {
    // 统计当前位上的数字出现的次数
    for (int i = 0; i < arr.size(); ++i)
      count[getDigit(arr[i], digit)]++;

    // 将统计数组转换为前缀和数组
    for (int i = 1; i < 10; ++i)
      count[i] += count[i - 1];

    // 根据当前位上的数字将元素放入正确的位置
    for (int i = arr.size() - 1; i >= 0; --i) {
      int digitValue = getDigit(arr[i], digit);
      output[count[digitValue] - 1] = arr[i];
      count[digitValue]--;
    }

    // 将输出数组复制回原始数组
    for (int i = 0; i < arr.size(); ++i)
      arr[i] = output[i];

    // 清空统计数组
    std::fill(count.begin(), count.end(), 0);
  }
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

  radixSort(arr);

  std::cout << "Sorted array: ";
  printArray(arr);

  return 0;
}
