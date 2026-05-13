# 풀이 회고

## 핵심 아이디어

배열을 순회하면서 각 원소에 대해 "지금까지 본 숫자 중에 `target - 현재값`이 존재하는가?"를 묻는 방식으로 동작합니다. 이를 위해 HashMap에 `(값 → 인덱스)` 형태로 기록하며, 이미 지나온 원소들을 O(1)에 조회할 수 있게 합니다. 한 번의 순회만으로 답을 찾을 수 있기 때문에 O(n) 시간에 해결됩니다. 문제 조건상 반드시 하나의 정답이 존재하므로, 순회 도중 반드시 조건을 만족하는 쌍이 발견됩니다.

## 사용된 자료구조 / 알고리즘

- 해시 맵 (HashMap): 값을 키로, 인덱스를 값으로 저장하여 O(1) 조회
- 단일 순회 (Single Pass): 배열을 한 번만 훑으며 탐색과 기록을 동시에 수행

## 복잡도 분석

- **시간 복잡도**: O(n)
  - 배열을 단 한 번 순회하며, 각 원소에서 HashMap 조회·삽입이 모두 O(1)이므로 전체 O(n)
- **공간 복잡도**: O(n)
  - 최악의 경우 배열의 모든 원소를 HashMap에 저장해야 하므로 O(n)의 추가 공간 필요

## 개선된 코드

```java
import java.util.HashMap;
import java.util.Map;

class Solution {
    public int[] twoSum(int[] nums, int target) {
        // 지금까지 순회한 원소를 기록: (원소값 → 배열 인덱스)
        Map<Integer, Integer> visitedValueToIndex = new HashMap<>();

        for (int currentIndex = 0; currentIndex < nums.length; currentIndex++) {
            int currentValue = nums[currentIndex];

            // 현재 값과 더해서 target이 되는 보완값 계산
            int complementValue = target - currentValue;

            // 보완값이 이미 순회한 원소 중에 존재하는지 확인
            if (visitedValueToIndex.containsKey(complementValue)) {
                int complementIndex = visitedValueToIndex.get(complementValue);

                // 보완값의 인덱스와 현재 인덱스를 반환 (순서 무관)
                return new int[]{complementIndex, currentIndex};
            }

            // 현재 원소를 방문 기록에 추가
            visitedValueToIndex.put(currentValue, currentIndex);
        }

        // 문제 조건상 반드시 정답이 존재하므로 이 지점에 도달하지 않음
        throw new IllegalArgumentException("유효한 두 수의 합이 존재하지 않습니다.");
    }
}
```

## 다른 접근

**① 브루트 포스 (Brute Force) — O(n²) / O(1)**
이중 for문으로 모든 쌍 `(i, j)`를 검사하여 합이 target인 경우를 찾습니다. 추가 공간이 전혀 필요 없다는 장점이 있지만, 배열 크기가 커질수록 시간이 급격히 늘어나 큰 입력에서는 비효율적입니다.

**② 정렬 + 투 포인터 (Two Pointers) — O(n log n) / O(n)**
배열을 `(값, 원래 인덱스)` 쌍으로 복사한 뒤 값 기준으로 정렬하고, 양 끝에서 포인터를 좁혀가며 합을 찾습니다. 정렬 후 탐색 자체는 O(n)이지만 정렬 비용 O(n log n)이 발생하고, 원래 인덱스를 보존하기 위한 복사 배열이 추가로 필요합니다. 현재 HashMap 풀이보다 시간·공간 모두 이점이 없으나, 정렬된 배열이 이미 주어지는 변형 문제에서는 유리합니다.

## 비슷한 문제

- LeetCode 167 · Two Sum II - Input Array Is Sorted
- LeetCode 15 · 3Sum
- LeetCode 560 · Subarray Sum Equals K