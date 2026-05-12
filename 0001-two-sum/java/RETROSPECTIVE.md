# 풀이 회고

## 핵심 아이디어

배열을 순회하면서 각 원소에 대해 "지금까지 본 숫자 중 `target - 현재값`이 존재하는가?"를 묻는다. 이 보완값(complement)을 HashMap에 미리 저장해두면, 매 원소마다 O(1)로 확인할 수 있다. 즉, 배열을 한 번만 순회하면서 동시에 "지금 이 숫자가 이전 어떤 숫자의 보완값인가"를 체크하고 저장하는 방식이다. 정답이 반드시 하나 존재한다는 보장이 있으므로, 조건을 만족하는 순간 즉시 반환한다.

## 사용된 자료구조 / 알고리즘

- 해시 맵 (HashMap): 값 → 인덱스 매핑을 O(1) 조회로 수행
- 단일 순회 (One-pass): 배열을 딱 한 번만 탐색

## 복잡도 분석

- **시간 복잡도**: O(n)
  - 배열을 한 번 순회하며, 각 원소에서 HashMap 조회·삽입이 평균 O(1)이므로 전체 O(n)
- **공간 복잡도**: O(n)
  - 최악의 경우 배열의 모든 원소를 HashMap에 저장해야 하므로 O(n)

## 개선된 코드

```java
import java.util.HashMap;
import java.util.Map;

class Solution {
    public int[] twoSum(int[] nums, int target) {
        // 숫자값 → 해당 인덱스를 저장하는 해시 맵
        Map<Integer, Integer> valueToIndex = new HashMap<>();

        for (int currentIndex = 0; currentIndex < nums.length; currentIndex++) {
            int currentValue = nums[currentIndex];

            // 현재 값과 더했을 때 target이 되는 보완값 계산
            int complement = target - currentValue;

            // 보완값이 이미 해시 맵에 존재하면 정답을 찾은 것
            if (valueToIndex.containsKey(complement)) {
                int complementIndex = valueToIndex.get(complement);
                return new int[]{complementIndex, currentIndex};
            }

            // 아직 정답을 못 찾았으면 현재 값과 인덱스를 해시 맵에 저장
            valueToIndex.put(currentValue, currentIndex);
        }

        // 문제 조건상 항상 정답이 존재하므로 여기에 도달하지 않음
        throw new IllegalArgumentException("유효한 두 수의 합이 존재하지 않습니다.");
    }
}
```

## 다른 접근

**① 브루트 포스 (Brute Force) — O(n²) / O(1)**
모든 두 원소 쌍 `(i, j)`를 이중 반복문으로 확인한다. 구현이 가장 단순하지만, 배열 크기가 커질수록 급격히 느려진다. 공간은 추가로 쓰지 않는다는 장점이 있다.

**② 정렬 + 투 포인터 (Two Pointers) — O(n log n) / O(n)**
`(값, 원래 인덱스)` 쌍으로 복사한 배열을 정렬한 뒤, 양 끝에서 포인터를 좁혀가며 합을 찾는다. 원래 인덱스 복원을 위해 별도 공간이 필요하고, 정렬 비용이 추가된다. 단일 순회 HashMap 방식보다 빠르지 않으므로 이 문제에서는 최선이 아니지만, 인덱스가 아닌 값 자체를 반환해도 되는 변형 문제에선 유용하다.

## 비슷한 문제

- LeetCode 167 · Two Sum II - Input Array Is Sorted
- LeetCode 15 · 3Sum
- LeetCode 560 · Subarray Sum Equals K