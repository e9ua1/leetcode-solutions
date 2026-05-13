# 풀이 회고

## 핵심 아이디어

배열을 순회하면서 각 원소 `nums[i]`에 대해 "현재 값과 더해서 `target`이 되는 보완값(complement)"이 이미 등장했는지를 해시 맵에서 O(1)로 조회한다. 아직 등장하지 않았다면 현재 값과 인덱스를 해시 맵에 저장해두고, 이후 순회에서 보완값이 나타나는 순간 즉시 두 인덱스를 반환한다. 이 방법이 작동하는 이유는 해시 맵이 "지금까지 본 값 → 그 인덱스" 매핑을 O(1) 조회 비용으로 유지하기 때문이며, 덕분에 중첩 반복문 없이 단일 순회만으로 정답을 찾을 수 있다.

## 사용된 자료구조 / 알고리즘

- 해시 맵 (Hash Map) — 값(key)과 인덱스(value)를 저장해 보완값의 존재 여부를 O(1)에 조회
- 단일 순회 (One-pass Linear Scan) — 배열을 한 번만 훑으며 저장과 조회를 동시에 수행

## 복잡도 분석

- **시간 복잡도**: O(n)
  - 배열을 한 번만 순회하며, 각 원소에서 해시 맵 조회/삽입이 평균 O(1)이므로 전체 O(n)
- **공간 복잡도**: O(n)
  - 최악의 경우 배열의 모든 원소를 해시 맵에 저장해야 하므로 O(n)의 추가 공간 필요

## 개선된 코드

```java
class Solution {
    public int[] twoSum(int[] nums, int target) {
        // 지금까지 순회한 값(key)과 해당 인덱스(value)를 저장하는 해시 맵
        Map<Integer, Integer> visitedValueToIndex = new HashMap<>();

        for (int currentIndex = 0; currentIndex < nums.length; currentIndex++) {
            int currentValue = nums[currentIndex];

            // target에서 현재 값을 뺀 "보완값" 계산
            int complement = target - currentValue;

            // 보완값이 이미 해시 맵에 존재하면 정답을 즉시 반환
            if (visitedValueToIndex.containsKey(complement)) {
                int complementIndex = visitedValueToIndex.get(complement);
                return new int[] { complementIndex, currentIndex };
            }

            // 아직 정답을 찾지 못했으므로 현재 값과 인덱스를 해시 맵에 저장
            visitedValueToIndex.put(currentValue, currentIndex);
        }

        // 문제 조건상 항상 정답이 존재하므로 이 줄에 도달하지 않음
        throw new IllegalArgumentException("유효한 두 수의 합이 존재하지 않습니다.");
    }
}
```

## 다른 접근

**① 브루트 포스 (Brute Force) — O(n²) / O(1)**
두 개의 중첩 반복문으로 모든 쌍 `(i, j)`를 검사해 합이 `target`인 쌍을 찾는다. 추가 공간이 전혀 필요 없다는 장점이 있지만, 시간 복잡도가 O(n²)으로 입력이 커질수록 급격히 느려진다. Follow-up에서 요구하는 O(n²) 미만 조건을 만족하지 못한다.

**② 정렬 + 투 포인터 (Sort + Two Pointer) — O(n log n) / O(n)**
배열을 정렬한 뒤 왼쪽·오른쪽 포인터를 좁혀가며 합이 `target`인 쌍을 찾는다. 시간 복잡도는 O(n log n)으로 해시 맵보다 느리고, 정렬로 인해 원래 인덱스 정보가 사라지므로 `(값, 원래 인덱스)` 쌍을 별도로 저장해야 하는 번거로움이 있다. 해시 충돌이 전혀 없다는 점은 장점이다.

## 비슷한 문제

- **LeetCode 167** · Two Sum II - Input Array Is Sorted
- **LeetCode 15** · 3Sum
- **LeetCode 560** · Subarray Sum Equals K