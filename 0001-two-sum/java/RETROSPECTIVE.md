# 풀이 회고

## 핵심 아이디어

배열을 한 번 순회하면서, 현재 원소의 "짝꿍(complement)"이 이미 앞에서 등장했는지를 해시 맵(HashMap)으로 O(1)에 확인한다. 짝꿍이 존재하면 즉시 두 인덱스를 반환하고, 없으면 현재 원소와 인덱스를 맵에 저장하며 계속 진행한다. 이 방식은 "지금까지 본 값들"을 맵에 누적하기 때문에, 단일 순회만으로 정답을 찾을 수 있다.

## 사용된 자료구조 / 알고리즘

- 해시 맵 (HashMap): 값 → 인덱스 매핑을 통한 O(1) 탐색
- 단일 순회 (One-pass Linear Scan)

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
        // 값 → 인덱스를 저장하는 해시 맵 (이미 방문한 원소 기록용)
        Map<Integer, Integer> valueToIndex = new HashMap<>();

        for (int currentIndex = 0; currentIndex < nums.length; currentIndex++) {
            int currentValue = nums[currentIndex];

            // target을 만들기 위해 현재 값과 더해야 하는 짝꿍 값 계산
            int complement = target - currentValue;

            // 짝꿍이 이미 앞에서 등장했는지 확인
            if (valueToIndex.containsKey(complement)) {
                int complementIndex = valueToIndex.get(complement);
                // 짝꿍의 인덱스와 현재 인덱스를 반환
                return new int[]{complementIndex, currentIndex};
            }

            // 아직 짝꿍을 못 찾았으므로, 현재 값을 맵에 기록
            valueToIndex.put(currentValue, currentIndex);
        }

        // 문제 조건상 항상 정답이 존재하므로 이 줄에 도달하지 않음
        throw new IllegalArgumentException("유효한 두 수의 합이 존재하지 않습니다.");
    }
}
```

## 다른 접근

**① 브루트 포스 (Brute Force) — O(n²) / O(1)**
모든 원소 쌍 `(i, j)`를 이중 반복문으로 검사하여 `nums[i] + nums[j] == target`인 쌍을 찾는다. 추가 공간이 필요 없다는 장점이 있지만, 시간 복잡도가 O(n²)으로 입력이 커질수록 급격히 느려지는 트레이드오프가 있다.

**② 정렬 + 투 포인터 (Two Pointer) — O(n log n) / O(n)**
배열을 `(값, 원래 인덱스)` 쌍으로 복사한 뒤 값 기준으로 정렬하고, 양 끝 포인터를 좁혀가며 합을 확인한다. 시간 복잡도는 O(n log n)으로 브루트 포스보다 낫지만, 정렬을 위한 복사본 배열과 정렬 시간 오버헤드가 발생하여 HashMap 방식보다는 느리다. 원본 인덱스 보존을 위해 복사본이 반드시 필요하다는 점도 주의해야 한다.

## 비슷한 문제

- LeetCode 167번 · Two Sum II - Input Array Is Sorted
- LeetCode 15번 · 3Sum
- LeetCode 18번 · 4Sum