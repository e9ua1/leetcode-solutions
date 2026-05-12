# 풀이 회고

## 핵심 아이디어

배열을 한 번 순회하면서, 현재 숫자 `nums[i]`와 짝을 이뤄 `target`이 되는 **보완값(complement)** `target - nums[i]`을 계산합니다. 이 보완값을 해시 맵에서 즉시 조회함으로써, 이미 지나쳐온 숫자 중에 정답 쌍이 있는지 O(1)에 확인할 수 있습니다. 보완값이 없으면 현재 숫자와 인덱스를 해시 맵에 기록해두고 다음 숫자로 넘어갑니다. 이 방식 덕분에 이중 루프 없이 단일 순회만으로 정답을 찾을 수 있습니다.

## 사용된 자료구조 / 알고리즘

- 해시 맵 (Hash Map / `unordered_map`): 숫자 값 → 인덱스 매핑을 위한 O(1) 조회
- 단일 순회 (One-pass Linear Scan)

## 복잡도 분석

- **시간 복잡도**: O(n)
  - 배열을 한 번만 순회하며, 각 원소에서 해시 맵 조회와 삽입이 모두 평균 O(1)이므로 전체 O(n)
- **공간 복잡도**: O(n)
  - 최악의 경우 배열의 모든 원소를 해시 맵에 저장해야 하므로 O(n) 추가 공간 필요

## 개선된 코드

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // 숫자 값 → 해당 인덱스를 저장하는 해시 맵
        unordered_map<int, int> valueToIndex;

        for (int i = 0; i < (int)nums.size(); i++) {
            // target이 되려면 현재 숫자와 짝을 이뤄야 하는 보완값 계산
            int complement = target - nums[i];

            // 보완값이 이미 해시 맵에 존재하면 정답 쌍을 찾은 것
            if (valueToIndex.count(complement)) {
                return { valueToIndex[complement], i };
            }

            // 아직 정답을 못 찾았으므로 현재 숫자와 인덱스를 해시 맵에 기록
            valueToIndex[nums[i]] = i;
        }

        // 문제 조건상 반드시 정답이 존재하므로 이 지점에는 도달하지 않음
        return {};
    }
};
```

## 다른 접근

**① 브루트 포스 (Brute Force) — O(n²) / O(1)**
모든 숫자 쌍 `(i, j)`를 이중 루프로 확인해 합이 `target`인 쌍을 찾습니다. 구현이 가장 단순하지만, 배열 길이가 커질수록 성능이 급격히 저하됩니다. 추가 공간을 전혀 쓰지 않아도 된다는 점이 유일한 장점입니다.

**② 정렬 + 투 포인터 (Sort + Two Pointer) — O(n log n) / O(n)**
배열을 값 기준으로 정렬한 뒤, 양 끝에서 포인터를 좁혀가며 합을 확인합니다. 정렬 후에는 원래 인덱스 정보가 사라지므로, 정렬 전에 `(값, 원래 인덱스)` 쌍을 별도로 저장해야 합니다. 해시 맵보다 공간 활용이 예측 가능하고 최악의 경우 성능이 안정적이지만, 시간 복잡도가 해시 맵 풀이보다 높습니다.

## 비슷한 문제

- LeetCode 167번 · Two Sum II - Input Array Is Sorted
- LeetCode 15번 · 3Sum
- LeetCode 18번 · 4Sum