# 풀이 회고

## 핵심 아이디어

배열을 한 번 순회하면서, 현재 숫자의 "짝꿍 숫자(complement = target - nums[i])"가 이미 앞에서 등장했는지를 HashMap으로 O(1)에 확인합니다. 짝꿍이 존재하면 즉시 두 인덱스를 반환하고, 없으면 현재 숫자를 맵에 저장하며 계속 진행합니다. 이 방식 덕분에 배열을 두 번 중첩 순회할 필요 없이 단 한 번의 선형 탐색으로 답을 찾을 수 있습니다.

## 사용된 자료구조 / 알고리즘

- **HashMap** (값 → 인덱스 매핑, 평균 O(1) 조회)
- **One-pass Linear Scan** (단일 순회)

## 복잡도 분석

- **시간 복잡도**: O(n)
  - 배열을 정확히 한 번 순회하며, 각 원소에서 HashMap 조회/삽입 모두 평균 O(1)이므로 전체 O(n)
- **공간 복잡도**: O(n)
  - 최악의 경우 배열의 모든 원소를 HashMap에 저장해야 하므로 O(n)의 추가 공간 필요

## 개선된 코드

```java
import java.util.HashMap;
import java.util.Map;

class Solution {
    public int[] twoSum(int[] nums, int target) {
        // 숫자(값) → 해당 인덱스를 저장하는 해시 맵
        Map<Integer, Integer> valueToIndex = new HashMap<>();

        for (int currentIndex = 0; currentIndex < nums.length; currentIndex++) {
            int currentValue = nums[currentIndex];

            // target을 만들기 위해 현재 숫자와 짝을 이뤄야 하는 보완 값 계산
            int complement = target - currentValue;

            // 보완 값이 이미 앞에서 등장한 적 있는지 확인
            if (valueToIndex.containsKey(complement)) {
                // 짝꿍 인덱스와 현재 인덱스를 반환
                int complementIndex = valueToIndex.get(complement);
                return new int[]{complementIndex, currentIndex};
            }

            // 아직 짝꿍을 못 찾았으므로 현재 값과 인덱스를 맵에 기록
            valueToIndex.put(currentValue, currentIndex);
        }

        // 문제 조건상 반드시 정답이 존재하므로 이 줄에는 도달하지 않음
        throw new IllegalArgumentException("유효한 두 수의 합이 존재하지 않습니다.");
    }
}
```

## 다른 접근

**① 브루트 포스 (Brute Force) — O(n²) / O(1)**
이중 for 루프로 모든 쌍(i, j)을 검사해 합이 target인 쌍을 찾습니다. 추가 공간이 전혀 필요 없다는 장점이 있지만, 배열 크기가 커질수록 시간 비용이 급격히 증가합니다. 심화 문제에서 요구하는 O(n²) 미만 조건을 만족하지 못합니다.

**② 정렬 + 투 포인터 (Sorting + Two Pointer) — O(n log n) / O(n)**
배열을 정렬한 뒤 양 끝에 포인터를 두고 합에 따라 좁혀가는 방식입니다. 시간 복잡도가 O(n log n)으로 HashMap 풀이보다 느리고, 정렬 후 원래 인덱스 추적을 위해 인덱스 정보를 별도로 보존해야 하는 번거로움이 생깁니다. 원본 인덱스를 반환해야 하는 이 문제에서는 구현 복잡도 대비 이점이 없습니다.

## 비슷한 문제

- **LeetCode 167** · Two Sum II - Input Array Is Sorted
- **LeetCode 15** · 3Sum
- **LeetCode 560** · Subarray Sum Equals K