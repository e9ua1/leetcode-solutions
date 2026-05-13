# 풀이 회고

## 핵심 아이디어

배열을 한 번 순회하면서, 현재 값의 "보완값(complement = target - nums[i])"이 이미 등장한 적 있는지 HashMap에서 O(1)로 조회한다. 보완값이 존재하면 즉시 두 인덱스를 반환하고, 없으면 현재 값과 인덱스를 HashMap에 기록한다. 이 방식은 "지금까지 본 숫자들"을 HashMap에 축적하며 앞으로 필요한 짝을 즉시 찾을 수 있다는 점에서 단일 순회로 문제를 해결한다.

## 사용된 자료구조 / 알고리즘

- HashMap (해시 맵): 값 → 인덱스 매핑, O(1) 조회/삽입
- 단일 순회 (Single Pass): 배열을 한 번만 탐색

## 복잡도 분석

- **시간 복잡도**: O(n)
  - 배열을 한 번만 순회하며, 각 원소에서 HashMap 조회/삽입이 평균 O(1)이므로 전체 O(n)
- **공간 복잡도**: O(n)
  - 최악의 경우 배열의 모든 원소를 HashMap에 저장해야 하므로 O(n)

## 개선된 코드

```java
import java.util.HashMap;
import java.util.Map;

class Solution {
    public int[] twoSum(int[] nums, int target) {
        // 값 → 인덱스를 저장하는 해시 맵 (지금까지 순회한 원소 누적)
        Map<Integer, Integer> valueToIndex = new HashMap<>();

        for (int currentIndex = 0; currentIndex < nums.length; currentIndex++) {
            int currentValue = nums[currentIndex];

            // target이 되려면 현재 값의 짝(보완값)이 얼마인지 계산
            int complement = target - currentValue;

            // 보완값이 이미 HashMap에 존재하면 → 정답 쌍 발견
            if (valueToIndex.containsKey(complement)) {
                int complementIndex = valueToIndex.get(complement);
                return new int[]{complementIndex, currentIndex};
            }

            // 아직 짝을 못 찾은 경우, 현재 값과 인덱스를 HashMap에 기록
            valueToIndex.put(currentValue, currentIndex);
        }

        // 문제 조건상 반드시 정답이 존재하므로 여기에는 도달하지 않음
        throw new IllegalArgumentException("유효한 정답이 존재하지 않습니다.");
    }
}
```

## 다른 접근

**1. 브루트 포스 (Brute Force) — O(n²) / O(1)**
모든 두 원소 쌍을 이중 반복문으로 검사해 합이 target인 쌍을 찾는다. 추가 공간이 불필요하지만 시간 복잡도가 O(n²)로 느리다. 배열 크기가 작을 때는 단순하고 직관적이라는 장점이 있다.

**2. 정렬 + 투 포인터 (Two Pointer) — O(n log n) / O(n)**
배열을 (값, 원래 인덱스) 쌍으로 정렬한 뒤, 양 끝에서 포인터를 좁혀가며 합을 맞춘다. 시간 복잡도는 HashMap 방식과 비슷한 수준이지만 정렬 비용(O(n log n))이 추가된다. 원래 인덱스를 보존하기 위한 별도 자료구조가 필요해 구현이 다소 복잡하다.

## 비슷한 문제

- **LeetCode 167** · Two Sum II - Input Array Is Sorted
- **LeetCode 15** · 3Sum
- **LeetCode 560** · Subarray Sum Equals K