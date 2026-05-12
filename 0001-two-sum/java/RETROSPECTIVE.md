# 풀이 회고

## 핵심 아이디어

배열을 순회하면서 현재 숫자의 "보수(complement)"—즉 `target - nums[i]`—가 이전에 등장한 적 있는지를 해시 맵(Hash Map)으로 O(1)에 조회합니다. 보수가 맵에 존재하면 두 인덱스를 즉시 반환하고, 없으면 현재 숫자와 인덱스를 맵에 저장한 뒤 계속 진행합니다. 이 방식은 배열을 단 한 번만 순회하므로 중첩 루프 없이도 정답을 찾을 수 있습니다.

## 사용된 자료구조 / 알고리즘

- 해시 맵 (Hash Map): 숫자 → 인덱스 매핑, O(1) 평균 조회
- 단일 순회 (Single Pass)

## 복잡도 분석

- **시간 복잡도**: O(n)
  - 배열을 한 번만 순회하며, 각 원소에서 해시 맵 조회/삽입이 평균 O(1)이므로 전체 O(n)
- **공간 복잡도**: O(n)
  - 최악의 경우 배열의 모든 원소를 해시 맵에 저장해야 하므로 O(n)

## 개선된 코드

```java
import java.util.HashMap;
import java.util.Map;

class Solution {
    public int[] twoSum(int[] nums, int target) {
        // 숫자 값 → 해당 인덱스를 저장하는 해시 맵
        Map<Integer, Integer> valueToIndex = new HashMap<>();

        for (int currentIndex = 0; currentIndex < nums.length; currentIndex++) {
            int currentValue = nums[currentIndex];
            // 현재 숫자와 더해서 target이 되는 보수 계산
            int complement = target - currentValue;

            // 보수가 이미 맵에 존재하면 정답을 찾은 것
            if (valueToIndex.containsKey(complement)) {
                int complementIndex = valueToIndex.get(complement);
                return new int[]{complementIndex, currentIndex};
            }

            // 보수가 없으면 현재 숫자를 맵에 저장하고 다음으로 진행
            valueToIndex.put(currentValue, currentIndex);
        }

        // 문제 조건상 항상 정답이 존재하므로 이 줄에는 도달하지 않음
        throw new IllegalArgumentException("유효한 두 수의 합이 존재하지 않습니다.");
    }
}
```

## 다른 접근

**① 브루트 포스 (Brute Force) — O(n²) / O(1)**
모든 쌍 `(i, j)`를 이중 루프로 검사해 `nums[i] + nums[j] == target`인 경우를 찾습니다. 구현이 단순하고 추가 공간이 필요 없지만, 배열 크기가 커질수록 시간이 급격히 늘어나는 단점이 있습니다.

**② 정렬 + 투 포인터 (Two Pointers) — O(n log n) / O(n)**
배열을 `(값, 원래 인덱스)` 쌍으로 정렬한 뒤, 양 끝에서 포인터를 좁혀가며 합을 계산합니다. 시간 복잡도는 정렬 비용 O(n log n)으로 해시 맵보다 살짝 느리고, 원래 인덱스를 보존하기 위한 추가 공간도 필요합니다. 단, 해시 충돌 걱정 없이 결정론적으로 동작한다는 장점이 있습니다.

## 비슷한 문제

- LeetCode 167 · Two Sum II - Input Array Is Sorted
- LeetCode 15 · 3Sum
- LeetCode 560 · Subarray Sum Equals K