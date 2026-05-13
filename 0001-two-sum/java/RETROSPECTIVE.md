# 풀이 회고

## 핵심 아이디어

배열을 한 번 순회하면서, 현재 숫자의 "짝꿍 값(complement = target - nums[i])"이 이전에 등장했는지 해시 맵에서 O(1)로 확인한다. 짝꿍이 이미 맵에 존재하면 두 인덱스를 즉시 반환하고, 없으면 현재 숫자와 인덱스를 맵에 저장해 다음 순회에서 활용한다. 이 방식은 "찾아야 할 값을 미리 계산해 저장"하는 전형적인 해시 테이블 활용 패턴으로, 이중 루프 없이 단일 순회로 정답을 찾을 수 있다.

## 사용된 자료구조 / 알고리즘

- 해시 맵 (Hash Map) — 값 → 인덱스 매핑
- 단일 패스 순회 (One-pass Linear Scan)

## 복잡도 분석

- **시간 복잡도**: O(n)
  - 배열을 딱 한 번만 순회하며, 각 원소에서 해시 맵 조회·삽입이 평균 O(1)이므로 전체 O(n)
- **공간 복잡도**: O(n)
  - 최악의 경우(정답이 배열 끝에 위치) 배열 원소 거의 전부를 해시 맵에 저장해야 하므로 O(n)

## 개선된 코드

```java
import java.util.HashMap;
import java.util.Map;

class Solution {
    public int[] twoSum(int[] nums, int target) {
        // 값(value) → 인덱스(index) 를 저장하는 해시 맵
        Map<Integer, Integer> valueToIndex = new HashMap<>();

        for (int currentIndex = 0; currentIndex < nums.length; currentIndex++) {
            int currentValue = nums[currentIndex];

            // target 을 만들기 위해 현재 값과 쌍을 이뤄야 하는 짝꿍 값 계산
            int complement = target - currentValue;

            // 짝꿍 값이 이미 맵에 존재하면 → 두 인덱스를 반환
            if (valueToIndex.containsKey(complement)) {
                int complementIndex = valueToIndex.get(complement);
                return new int[]{complementIndex, currentIndex};
            }

            // 짝꿍이 없으면 현재 값과 인덱스를 맵에 저장 후 계속 순회
            valueToIndex.put(currentValue, currentIndex);
        }

        // 문제 조건상 항상 정답이 존재하므로 여기에 도달하지 않음
        throw new IllegalArgumentException("유효한 두 수의 합이 존재하지 않습니다.");
    }
}
```

## 다른 접근

**① 브루트 포스 (Brute Force) — O(n²) / O(1)**
모든 원소 쌍 `(i, j)`를 이중 루프로 검사해 합이 `target`인 쌍을 찾는다. 별도 자료구조가 필요 없어 공간 복잡도가 O(1)이지만, 시간 복잡도가 O(n²)으로 입력이 커질수록 급격히 느려진다. 배열이 매우 작거나 메모리가 극도로 제한될 때만 고려할 만하다.

**② 정렬 + 투 포인터 (Two Pointer) — O(n log n) / O(n)**
`(값, 원래 인덱스)` 쌍을 값 기준으로 정렬한 뒤, 양 끝 포인터를 좁혀 가며 합을 확인한다. 시간 복잡도는 정렬로 인해 O(n log n)이고, 원본 인덱스를 보존하기 위한 추가 배열로 O(n) 공간이 필요하다. 해시 맵 방식보다 상수 계수가 클 수 있으나, 해시 충돌이 없어 최악 케이스 성능이 보장된다는 트레이드오프가 있다.

## 비슷한 문제

- LeetCode 167 · Two Sum II - Input Array Is Sorted
- LeetCode 15 · 3Sum
- LeetCode 560 · Subarray Sum Equals K