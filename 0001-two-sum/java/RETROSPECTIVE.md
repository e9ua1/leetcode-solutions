# 풀이 회고

## 핵심 아이디어

배열을 순회하면서 각 원소 `nums[i]`에 대해 `target - nums[i]`(이하 `complement`)가 이미 등장한 적 있는지를 해시 맵(HashMap)에서 O(1)로 조회한다. 등장한 적 없으면 현재 원소를 맵에 저장하고, 등장한 적 있으면 맵에 저장된 인덱스와 현재 인덱스를 바로 반환한다. 이처럼 "지금까지 본 값"을 맵에 누적하면서 단 한 번의 순회만으로 정답을 찾을 수 있다는 것이 이 풀이의 본질이다.

## 사용된 자료구조 / 알고리즘

- 해시 맵 (HashMap) — 값(value) → 인덱스(index) 매핑
- 단일 선형 순회 (Single-pass Linear Scan)

## 복잡도 분석

- **시간 복잡도**: O(n)
  - 배열을 딱 한 번 순회하며, 각 원소마다 HashMap의 `get`/`put`이 평균 O(1)이므로 전체 O(n)
- **공간 복잡도**: O(n)
  - 최악의 경우 배열의 모든 원소를 HashMap에 저장해야 하므로 O(n)

## 개선된 코드

```java
import java.util.HashMap;
import java.util.Map;

class Solution {
    public int[] twoSum(int[] nums, int target) {
        // (값 → 인덱스) 형태로 이미 방문한 원소를 저장하는 해시 맵
        Map<Integer, Integer> visitedValueToIndex = new HashMap<>();

        for (int currentIndex = 0; currentIndex < nums.length; currentIndex++) {
            int currentValue = nums[currentIndex];

            // 현재 값과 더해서 target이 되는 보완 값(complement) 계산
            int complement = target - currentValue;

            // 보완 값이 이미 맵에 존재하면 정답을 찾은 것
            if (visitedValueToIndex.containsKey(complement)) {
                int complementIndex = visitedValueToIndex.get(complement);
                return new int[]{complementIndex, currentIndex};
            }

            // 아직 정답을 찾지 못했으므로 현재 값과 인덱스를 맵에 기록
            visitedValueToIndex.put(currentValue, currentIndex);
        }

        // 문제 조건상 항상 정답이 존재하므로 이 지점에는 도달하지 않음
        throw new IllegalArgumentException("유효한 정답이 존재하지 않습니다.");
    }
}
```

## 다른 접근

**① 브루트 포스 (Brute Force) — O(n²) / O(1)**
이중 반복문으로 모든 쌍 `(i, j)`를 검사해 `nums[i] + nums[j] == target`인 경우를 찾는다. 추가 공간이 전혀 필요 없다는 장점이 있지만, 배열 길이가 커질수록 성능이 급격히 떨어져 실무에서는 사용하기 어렵다.

**② 정렬 + 투 포인터 (Two Pointers) — O(n log n) / O(n)**
배열을 `(값, 원래 인덱스)` 쌍으로 복사한 뒤 값 기준으로 정렬하고, 양 끝에서 포인터를 좁혀가며 합을 확인한다. 정렬 비용(O(n log n))이 추가되고 원본 인덱스를 보존하기 위해 별도 공간이 필요하다. 그러나 배열이 이미 정렬돼 있거나 여러 쌍을 찾는 변형 문제에서는 유리한 접근이다.

## 비슷한 문제

- LeetCode 15 · 3Sum
- LeetCode 18 · 4Sum
- LeetCode 167 · Two Sum II – Input Array Is Sorted