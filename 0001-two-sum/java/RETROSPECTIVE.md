# 풀이 회고

## 핵심 아이디어

배열을 순회하면서 현재 숫자(`nums[i]`)의 **보수(complement)**, 즉 `target - nums[i]`를 해시 맵에서 찾는다. 이미 방문한 숫자와 그 인덱스를 해시 맵에 기록해두면, 매 원소마다 O(1)에 짝을 확인할 수 있다. 짝이 발견된 순간 바로 두 인덱스를 반환하므로, 불필요한 탐색 없이 한 번의 순회로 답을 구한다.

## 사용된 자료구조 / 알고리즘

- 해시 맵 (HashMap) — 숫자 값 → 인덱스 매핑
- 단일 순회 (One-pass Linear Scan)

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
        // 이미 방문한 숫자의 값 → 인덱스를 기록하는 해시 맵
        Map<Integer, Integer> visitedNumToIndex = new HashMap<>();

        for (int currentIndex = 0; currentIndex < nums.length; currentIndex++) {
            int currentNum = nums[currentIndex];

            // target을 만들기 위해 현재 숫자와 쌍을 이루어야 하는 보수 계산
            int complement = target - currentNum;

            // 보수가 이미 해시 맵에 존재하면 정답을 찾은 것
            if (visitedNumToIndex.containsKey(complement)) {
                int complementIndex = visitedNumToIndex.get(complement);
                return new int[]{complementIndex, currentIndex};
            }

            // 현재 숫자를 해시 맵에 기록해 이후 순회에서 보수 탐색에 활용
            visitedNumToIndex.put(currentNum, currentIndex);
        }

        // 문제 조건상 반드시 정답이 존재하므로 이 지점에 도달하지 않음
        throw new IllegalArgumentException("유효한 두 수의 합이 존재하지 않습니다.");
    }
}
```

## 다른 접근

**① 브루트 포스 (Brute Force) — O(n²) / O(1)**
모든 두 원소 쌍 `(i, j)`를 이중 반복문으로 검사해 합이 `target`이면 반환한다. 추가 공간이 전혀 필요 없다는 장점이 있지만, 배열 크기가 커질수록 시간이 급격히 늘어나 비효율적이다.

**② 정렬 + 투 포인터 (Two Pointers) — O(n log n) / O(n)**
배열을 값 기준으로 정렬한 뒤, 양 끝에서 포인터를 좁혀가며 합을 확인한다. 그러나 정렬 과정에서 원래 인덱스 정보가 사라지므로, 인덱스를 함께 저장한 별도 배열을 만들어야 한다. 정렬 비용(O(n log n))이 추가되어 해시 맵 방식보다 느리고, 구현도 더 복잡하다.

## 비슷한 문제

- LeetCode 167 · Two Sum II - Input Array Is Sorted
- LeetCode 15 · 3Sum
- LeetCode 560 · Subarray Sum Equals K