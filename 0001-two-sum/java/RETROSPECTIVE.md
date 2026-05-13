# 풀이 회고

## 핵심 아이디어

배열을 한 번 순회하면서, 현재 원소와 짝을 이뤄 `target`이 되는 값(보수, complement)이 이미 등장했는지를 HashMap에서 O(1)로 확인합니다. 짝이 없으면 현재 원소와 인덱스를 HashMap에 저장해 두고, 이후 원소가 이를 찾을 수 있게 합니다. 이렇게 하면 배열을 단 한 번만 훑어도 정답을 찾을 수 있습니다.

## 사용된 자료구조 / 알고리즘

- HashMap (Hash Table): 값 → 인덱스 매핑, O(1) 평균 조회
- 단일 순회 (One-pass Scan)

## 복잡도 분석

- **시간 복잡도**: O(n)
  - 배열을 한 번만 순회하며, HashMap의 조회·삽입이 평균 O(1)이므로 전체 O(n)
- **공간 복잡도**: O(n)
  - 최악의 경우 배열의 모든 원소를 HashMap에 저장해야 하므로 O(n)

## 개선된 코드

```java
import java.util.HashMap;
import java.util.Map;

class Solution {
    public int[] twoSum(int[] nums, int target) {
        // 값 → 인덱스를 저장하는 해시 맵 (이미 방문한 원소 추적용)
        Map<Integer, Integer> visitedValueToIndex = new HashMap<>();

        for (int currentIndex = 0; currentIndex < nums.length; currentIndex++) {
            int currentValue = nums[currentIndex];

            // target에서 현재 값을 뺀 보수(complement) 계산
            int complement = target - currentValue;

            // 보수가 이미 해시 맵에 존재하면 → 정답 쌍 발견
            if (visitedValueToIndex.containsKey(complement)) {
                int complementIndex = visitedValueToIndex.get(complement);
                return new int[]{complementIndex, currentIndex};
            }

            // 보수가 없으면 현재 값과 인덱스를 해시 맵에 저장 후 계속 순회
            visitedValueToIndex.put(currentValue, currentIndex);
        }

        // 문제 조건상 항상 정답이 존재하므로 이 지점에 도달하지 않음
        throw new IllegalArgumentException("유효한 정답이 존재하지 않습니다.");
    }
}
```

## 다른 접근

**브루트 포스 (Brute Force) — O(n²) / O(1)**
모든 원소 쌍 `(i, j)`를 이중 반복문으로 탐색하여 합이 `target`인 쌍을 찾습니다. 추가 공간이 전혀 필요 없다는 장점이 있지만, 배열이 클수록 시간 비용이 급격히 증가하여 `n = 10^4`에서는 약 5천만 번의 비교가 발생합니다.

**정렬 + 투 포인터 (Two Pointers) — O(n log n) / O(n)**
배열을 `(값, 원래 인덱스)` 쌍으로 복사한 뒤 값 기준으로 정렬하고, 양쪽 끝에서 포인터를 좁혀가며 합을 비교합니다. HashMap 없이 풀 수 있다는 장점이 있으나, 원래 인덱스를 보존하기 위한 복사 배열이 필요하고 정렬 비용(O(n log n))이 추가됩니다.

## 비슷한 문제

- LeetCode 167 · Two Sum II - Input Array Is Sorted
- LeetCode 15 · 3Sum
- LeetCode 653 · Two Sum IV - Input is a BST