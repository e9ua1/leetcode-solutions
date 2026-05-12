# 풀이 회고

## 핵심 아이디어

배열을 순회하면서 각 원소에 대해 "target에서 현재 값을 뺀 나머지(complement)"가 이미 등장한 적 있는지 해시 맵(Hash Map)으로 O(1)에 조회한다. 이전에 본 값과 그 인덱스를 해시 맵에 기록해두면, 단 한 번의 순회만으로 정답 쌍을 찾을 수 있다. 정답이 반드시 존재한다는 보장이 있으므로, 찾는 즉시 반환해도 안전하다.

## 사용된 자료구조 / 알고리즘

- 해시 맵 (Hash Map, `unordered_map`): 값 → 인덱스 매핑으로 O(1) 조회
- 단일 순회 (Single Pass): 배열을 한 번만 훑는 선형 탐색

## 복잡도 분석

- **시간 복잡도**: O(n)
  - 배열을 한 번 순회하며, 각 원소마다 해시 맵 삽입/조회에 평균 O(1)이 소요되므로 전체 O(n)
- **공간 복잡도**: O(n)
  - 최악의 경우 배열의 모든 원소를 해시 맵에 저장해야 하므로 O(n)의 추가 공간 필요

## 개선된 코드

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // 값 → 인덱스를 기록하는 해시 맵 (이미 방문한 원소 추적용)
        unordered_map<int, int> visitedValueToIndex;

        for (int currentIndex = 0; currentIndex < (int)nums.size(); ++currentIndex) {
            int currentValue = nums[currentIndex];

            // target을 만들기 위해 현재 값과 짝이 되어야 하는 값 계산
            int complement = target - currentValue;

            // 짝이 되는 값이 이전에 등장한 적 있는지 해시 맵에서 확인
            auto it = visitedValueToIndex.find(complement);
            if (it != visitedValueToIndex.end()) {
                // 짝을 찾았으면 두 인덱스를 반환 (순서 무관)
                int complementIndex = it->second;
                return { complementIndex, currentIndex };
            }

            // 아직 짝을 못 찾았으면 현재 값과 인덱스를 해시 맵에 기록
            visitedValueToIndex[currentValue] = currentIndex;
        }

        // 문제 조건상 반드시 정답이 존재하므로 여기엔 도달하지 않음
        return {};
    }
};
```

## 다른 접근

**① 브루트 포스 (Brute Force) — O(n²) / O(1)**
이중 for 루프로 모든 두 원소 쌍을 직접 검사한다. 추가 공간이 전혀 필요 없다는 장점이 있지만, 입력 크기가 10⁴에 달할 경우 최대 ~5천만 번의 비교가 발생해 실질적으로 느리다. 공간이 극도로 제한된 환경이 아니라면 권장되지 않는다.

**② 정렬 + 투 포인터 (Two Pointers) — O(n log n) / O(n)**
배열을 (값, 원래 인덱스) 쌍으로 복사한 뒤 값 기준으로 정렬하고, 양 끝에서 포인터를 좁혀가며 합이 target인 쌍을 찾는다. 해시 맵 없이 포인터만으로 동작한다는 점이 직관적이지만, 정렬 비용(O(n log n))과 인덱스 보존을 위한 복사 배열(O(n))이 추가로 필요하다. 해시 충돌이 전혀 없다는 보장이 필요한 상황에서 안정적인 대안이 된다.

## 비슷한 문제

- **LeetCode 167** · Two Sum II - Input Array Is Sorted
- **LeetCode 15** · 3Sum
- **LeetCode 560** · Subarray Sum Equals K