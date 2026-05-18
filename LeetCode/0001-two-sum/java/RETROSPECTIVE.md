# 풀이 회고

## 핵심 아이디어

배열을 순회하면서 각 원소에 대해 "지금 이 수와 더해서 target이 되는 수(complement)를 이전에 본 적 있는가?"를 해시 맵으로 O(1)에 확인합니다. 이미 본 수라면 그 수의 인덱스와 현재 인덱스가 정답이 됩니다. 배열을 한 번만 순회하면서 탐색과 저장을 동시에 수행하기 때문에, 브루트 포스의 이중 루프 없이도 정답을 찾을 수 있습니다.

## 사용된 자료구조 / 알고리즘

- 해시 맵 (HashMap): 값 → 인덱스 매핑을 위한 O(1) 조회
- 단일 순회 (One-pass Traversal)

## 복잡도 분석이양
- **시간 복잡도**: O(n)
  - 배열을 한 번만 순회하며, 해시 맵 삽입/조회가 각 원소마다 O(1)이므로 전체 O(n)
- **공간 복잡도**: O(n)
  - 최악의 경우 배열의 모든 원소를 해시 맵에 저장해야 하므로 O(n)

## 개선된 코드

```java
import java.util.HashMap;
import java.util.Map;

class Solution {
    public int[] twoSum(int[] nums, int target) {
        // 값 → 인덱스를 저장하는 해시 맵 (이미 방문한 원소 기록용)
        Map<Integer, Integer> visitedValueToIndex = new HashMap<>();

        for (int currentIndex = 0; currentIndex < nums.length; currentIndex++) {
            int currentValue = nums[currentIndex];

            // target에서 현재 값을 뺀 나머지(complement)가 이전에 등장했는지 확인
            int complement = target - currentValue;

            if (visitedValueToIndex.containsKey(complement)) {
                // complement를 발견한 경우: 두 인덱스를 반환
                int complementIndex = visitedValueToIndex.get(complement);
                return new int[]{complementIndex, currentIndex};
            }

            // 아직 정답을 찾지 못했으면 현재 값과 인덱스를 맵에 기록
            visitedValueToIndex.put(currentValue, currentIndex);
        }

        // 문제 조건에 따라 정답은 반드시 존재하므로 이 줄에 도달하지 않음
        return new int[]{};
    }
}
```

## 다른 접근

- **브루트 포스 (Brute Force)**: 이중 for 루프로 모든 쌍 `(i, j)`를 확인해 `nums[i] + nums[j] == target`인 경우를 찾습니다. 추가 공간이 필요 없어 공간 복잡도가 O(1)이지만, 시간 복잡도가 O(n²)으로 입력이 커질수록 급격히 느려집니다.

- **정렬 + 투 포인터 (Two Pointers)**: 배열을 값 기준으로 정렬한 뒤 양 끝 포인터를 좁혀가며 합을 확인합니다. 시간 복잡도는 O(n log n)이지만, **정렬 과정에서 원래 인덱스 정보가 사라지기 때문에** 인덱스를 함께 저장하는 별도 처리가 필요하고 코드가 복잡해집니다. 인덱스가 아닌 값 자체를 반환해도 되는 변형 문제라면 가장 직관적인 방법입니다.

## 비슷한 문제

- LeetCode 167 · Two Sum II - Input Array Is Sorted
- LeetCode 15 · 3Sum
- LeetCode 560 · Subarray Sum Equals K