# 풀이 회고

## 핵심 아이디어

> ⚠️ **코드 불일치 감지**: 제출된 코드는 "Two Sum" 문제와 무관한 **Binary Tree Inorder Traversal (LeetCode #94)** 풀이입니다. Two Sum 문제에 맞는 코드로 재작성하여 회고를 진행합니다.

Two Sum의 핵심은 현재 숫자 `nums[i]`를 순회할 때, "이전까지 본 숫자 중 `target - nums[i]`가 존재하는가"를 O(1)에 확인하는 것입니다. 해시 맵(Hash Map)에 `{값 → 인덱스}`를 저장해두면, 배열을 단 한 번만 순회하면서 정답을 찾을 수 있습니다. 브루트 포스(O(n²))와 달리 각 원소를 보는 순간 즉시 보수(complement)를 조회하므로 전체 시간 복잡도가 O(n)으로 줄어듭니다.

## 사용된 자료구조 / 알고리즘

- 해시 맵 (Hash Map / `unordered_map`): 값 → 인덱스 매핑
- 단일 순회 (One-pass Scan)

## 복잡도 분석

- **시간 복잡도**: O(n)
  - 배열을 한 번만 순회하며, 각 원소에서 해시 맵 조회/삽입이 평균 O(1)이므로 전체 O(n)
- **공간 복잡도**: O(n)
  - 최악의 경우 배열의 모든 원소를 해시 맵에 저장해야 하므로 O(n)

## 개선된 코드

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // 지금까지 등장한 숫자의 값 → 인덱스를 저장하는 해시 맵
        unordered_map<int, int> valueToIndex;

        for (int currentIndex = 0; currentIndex < (int)nums.size(); ++currentIndex) {
            int currentValue  = nums[currentIndex];

            // target을 만들기 위해 현재 값과 짝이 되어야 하는 보수(complement) 계산
            int complement = target - currentValue;

            // 보수가 이미 해시 맵에 존재하면 정답 발견
            if (valueToIndex.count(complement)) {
                return { valueToIndex[complement], currentIndex };
            }

            // 아직 정답을 못 찾았으면 현재 값을 해시 맵에 기록
            valueToIndex[currentValue] = currentIndex;
        }

        // 문제 조건상 반드시 정답이 존재하므로 이 줄에는 도달하지 않음
        return {};
    }
};
```

## 다른 접근

- **브루트 포스 (Brute Force)**: 이중 반복문으로 가능한 모든 쌍 `(i, j)`를 검사합니다. 구현이 가장 단순하지만 시간 복잡도가 O(n²)으로, 입력이 커질수록 급격히 느려지는 트레이드오프가 있습니다.

- **정렬 + 투 포인터 (Two Pointers)**: 배열을 값 기준으로 정렬한 뒤 양 끝에서 포인터를 좁혀 가며 합을 확인합니다. 시간 복잡도는 O(n log n)으로 해시 맵보다 느리지만 추가 공간이 O(1)(정렬 제외)입니다. 단, 정렬 과정에서 원본 인덱스 정보가 사라지므로 인덱스를 함께 보존하는 별도 처리가 필요한 트레이드오프가 있습니다.

## 비슷한 문제

- LeetCode #167 · Two Sum II - Input Array Is Sorted
- LeetCode #15 · 3Sum
- LeetCode #560 · Subarray Sum Equals K