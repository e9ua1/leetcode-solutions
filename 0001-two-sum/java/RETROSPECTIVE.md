# 풀이 회고

## 핵심 아이디어

배열을 순회하면서 각 원소에 대해 "지금까지 본 숫자 중 나와 합해서 target이 되는 숫자가 있는가?"를 묻는 방식이다. 이를 위해 HashMap에 `(숫자 → 인덱스)` 쌍을 저장해두고, 현재 숫자의 보수(`target - nums[i]`)가 맵에 존재하면 즉시 두 인덱스를 반환한다. 배열을 한 번만 순회하면서 탐색과 저장을 동시에 수행하기 때문에 O(n) 시간에 문제를 해결할 수 있다.

## 사용된 자료구조 / 알고리즘

- 해시 맵 (HashMap): 숫자 값을 키, 배열 인덱스를 값으로 저장하여 O(1) 평균 탐색
- 단일 순회 (Single Pass): 배열을 한 번만 훑으며 탐색과 등록을 동시에 처리

## 복잡도 분석

- **시간 복잡도**: O(n)
  - 배열을 한 번 순회하며, 각 원소에서 HashMap 조회/삽입은 평균 O(1)이므로 전체 O(n)
- **공간 복잡도**: O(n)
  - 최악의 경우 배열의 모든 원소를 HashMap에 저장해야 하므로 O(n)

## 개선된 코드

```java
import java.util.HashMap;
import java.util.Map;

class Solution {
    public int[] twoSum(int[] nums, int target) {
        // 숫자 값 → 배열 인덱스 를 저장하는 해시 맵
        Map<Integer, Integer> valueToIndex = new HashMap<>();

        for (int currentIndex = 0; currentIndex < nums.length; currentIndex++) {
            int currentValue = nums[currentIndex];

            // 현재 값과 합산하여 target이 되는 보수(complement) 계산
            int complement = target - currentValue;

            // 보수가 이미 맵에 존재하면 정답 인덱스 쌍을 반환
            if (valueToIndex.containsKey(complement)) {
                int complementIndex = valueToIndex.get(complement);
                return new int[]{complementIndex, currentIndex};
            }

            // 현재 값을 맵에 등록 (이후 순회에서 보수 탐색에 활용)
            valueToIndex.put(currentValue, currentIndex);
        }

        // 문제 조건상 항상 정답이 존재하므로 이 지점에 도달하지 않음
        throw new IllegalArgumentException("유효한 두 수의 합이 존재하지 않습니다.");
    }
}
```

## 다른 접근

**① 브루트 포스 (Brute Force) — O(n²) / O(1)**
이중 for 루프로 모든 원소 쌍을 직접 비교하여 합이 target인 쌍을 찾는다. 별도의 자료구조가 필요 없어 공간은 절약되지만, 배열 크기가 커질수록 시간이 급격히 증가한다. 입력 크기가 작거나 메모리가 극도로 제한된 환경에서만 고려할 만하다.

**② 정렬 + 투 포인터 (Sort + Two Pointer) — O(n log n) / O(n)**
배열을 정렬한 뒤 양 끝에 포인터를 두고 합이 target보다 크면 오른쪽 포인터를 줄이고, 작으면 왼쪽 포인터를 늘리는 방식이다. 단, 정렬 과정에서 원래 인덱스 정보가 사라지므로 `(값, 원래인덱스)` 쌍을 따로 보존해야 한다는 번거로움이 있다. 시간 복잡도도 O(n log n)으로 HashMap 방식보다 열등하다.

## 비슷한 문제

- LeetCode 167 · Two Sum II - Input Array Is Sorted
- LeetCode 15 · 3Sum
- LeetCode 560 · Subarray Sum Equals K