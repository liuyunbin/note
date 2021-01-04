
### 说明
本文主要讨论对于有序数组进行折半查找的方法，为求统一，都采用 作闭右开 的方法

### 正文

题目：
* 对于有序数组 a，查找是否包含元素 target，
* 如果包含，返回对应的索引，否则，返回 -1

说明：
* a 不包含重复元素

要求：
* 时间复杂度为 logn
  
```
int binary_search(const int* a, int n, int target) {
  int left = 0;
  int right = n;

  for (;;) {
    if (left >= right)
      return -1;
    int mid = left + (right - left) / 2; // 避免溢出
    if (a[mid] == target)
      return mid;
    else if (a[mid] < target)
      left = mid + 1;
    else if (a[mid] > target)
      right = mid;
  }
}
```

题目：
* 对于有序数组 a，返回第一个大于等于 target 的索引

说明：
* a 可能包含重复元素

要求：
* 时间复杂度为 logn
  
```
int lower_bound(const int* a, int n, int target) {
  int left = 0;
  int right = n;

  for (;;) {
    if (left >= right)
      return left;
    int mid = left + (right - left) / 2; // 避免溢出
    if (a[mid] == target)
      right = mid;
    else if (a[mid] < target)
      left = mid + 1;
    else if (a[mid] > target)
      right = mid;
  }
}
```

题目：
* 对于有序数组 a，返回第一个大于 target 的索引

说明：
* a 可能包含重复元素

要求：
* 时间复杂度为 logn
  
```
int upper_bound(const int* a, int n, int target) {
  int left = 0;
  int right = n;

  for (;;) {
    if (left >= right)
      return left;
    int mid = left + (right - left) / 2; // 避免溢出
    if (a[mid] == target)
      left = mid + 1;
    else if (a[mid] < target)
      left = mid + 1;
    else if (a[mid] > target)
      right = mid;
  }
}
```
