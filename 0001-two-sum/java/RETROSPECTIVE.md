# 풀이 회고

## 핵심 아이디어

배열을 한 번 순회하면서, 현재 원소와 짝을 이루어 `target`이 되는 **보완값(complement)** 이 이전에 등장했는지를 해시 맵으로 O(1)에 조회한다. 이미 등장한 숫자와 그 인덱스를 해시 맵에 저장해두기 때문에, 별도의 이중 반복 없이 단일 순회만으로 정답을 찾을 수 있다. 현재 원소를 보기 전에 보완값을 먼저 조회하므로, 같은 인덱스를 두 번 사용하는 경우도 자연스럽게 방지된다.

## 사용된 자료구조 / 알고리즘

- 해시 맵 (Hash Map): 숫자 → 인덱스 매핑, O(1) 평균 조회
- 단일 순회 (One-pass Linear Scan)

## 복잡도 분석

- **시간 복잡도**: O(n)
  - 배열을 단 한 번만 순회하며, 각 원소에서 해시 맵 조회/삽입은 평균 O(1)이므로 전체 O(n)
- **공간 복잡도**: O(n)
  - 최악의 경우 배열의 모든 원소를 해시 맵에 저장해야 하므로 O(n)

## 개선된 코드

```java
import java.util.HashMap;
import java.util.Map;

class Solution {
    public int[] twoSum(int[] nums, int target) {
        // 지금까지 등장한 숫자와 해당 인덱스를 기록하는 해시 맵
        // key: 숫자 값, value: 해당 숫자의 인덱스
        Map<Integer, Integer> visitedNumToIndex = new HashMap<>();

        for (int currentIndex = 0; currentIndex < nums.length; currentIndex++) {
            int currentNum = nums[currentIndex];

            // 현재 숫자와 더했을 때 target이 되는 보완값 계산
            int complement = target - currentNum;

            // 보완값이 이전에 등장한 적 있는지 해시 맵에서 조회
            if (visitedNumToIndex.containsKey(complement)) {
                // 보완값의 인덱스와 현재 인덱스를 정답으로 반환
                int complementIndex = visitedNumToIndex.get(complement);
                return new int[]{complementIndex, currentIndex};
            }

            // 아직 짝을 못 찾은 경우, 현재 숫자를 해시 맵에 기록
            visitedNumToIndex.put(currentNum, currentIndex);
        }

        // 문제 조건상 항상 정답이 존재하므로 이 지점에 도달하지 않음
        throw new IllegalArgumentException("유효한 두 수의 합이 존재하지 않습니다.");
    }
}
```

## 다른 접근

**① 브루트 포스 (Brute Force) — O(n²) / O(1)**
모든 원소 쌍 `(i, j)`를 이중 반복으로 검사해 합이 `target`인 쌍을 찾는다. 구현이 가장 단순하고 추가 공간이 전혀 필요 없지만, 배열 크기가 커질수록 급격히 느려지는 단점이 있다.

**② 정렬 + 투 포인터 (Two Pointers) — O(n log n) / O(n)**
배열을 `(값, 원래인덱스)` 쌍으로 정렬한 뒤, 양 끝에서 포인터를 좁혀가며 합을 확인한다. 시간 복잡도가 해시 맵보다 다소 높지만(정렬 비용), 해시 충돌이 없어 최악 케이스가 안정적이다. 다만 원래 인덱스를 별도로 보존해야 하는 번거로움이 있다.

## 비슷한 문제

- LeetCode 167 · Two Sum II - Input Array Is Sorted
- LeetCode 15 · 3Sum
- LeetCode 18 · 4Sum