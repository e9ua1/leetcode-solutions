# 풀이 회고

## 핵심 아이디어

슬라이딩 윈도우(Sliding Window) 기법을 활용하여 오른쪽 포인터(`right`)를 한 칸씩 전진시키면서 윈도우를 확장한다. 새로 추가한 문자가 중복되면, 중복이 해소될 때까지 왼쪽 포인터(`left`)를 전진시켜 윈도우를 축소한다. 이 방식으로 항상 "중복 없는 부분 문자열"이라는 불변식을 유지하면서, 매 시점의 윈도우 길이를 정답 후보와 비교해 최댓값을 갱신한다.

## 사용된 자료구조 / 알고리즘

- **슬라이딩 윈도우 (Sliding Window)**: 두 포인터로 유효한 구간을 동적으로 유지
- **빈도 배열 (Frequency Array)**: ASCII 128칸 배열로 각 문자의 등장 횟수를 O(1)에 조회/갱신
- **투 포인터 (Two Pointers)**: `left`, `right` 포인터가 각각 독립적으로 전진

## 복잡도 분석

- **시간 복잡도**: O(n)
  - `right` 포인터는 문자열을 한 번 순회하고, `left` 포인터도 전체적으로 최대 n번 전진하므로 두 포인터 합산 이동 횟수는 O(2n) = O(n)이다.
- **공간 복잡도**: O(1)
  - 빈도 배열의 크기가 ASCII 문자 수인 128로 고정되어 있어, 입력 크기 n에 무관하게 상수 공간만 사용한다.

## 개선된 코드

```cpp
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // ASCII 문자 범위 상수 정의
        const int ASCII_SIZE = 128;

        int strLen = s.size();      // 문자열 전체 길이
        int left = 0;               // 윈도우 왼쪽 경계 (포함)
        int maxLen = 0;             // 현재까지의 최장 길이

        // 각 문자의 윈도우 내 등장 횟수를 기록하는 빈도 배열
        vector<int> charCount(ASCII_SIZE, 0);

        // 오른쪽 포인터를 전진시키며 윈도우 확장
        for (int right = 0; right < strLen; ++right) {
            char newChar = s[right];

            // 새 문자를 윈도우에 포함시키고 빈도 증가
            charCount[newChar]++;

            // 새 문자가 중복이면, 중복이 해소될 때까지 왼쪽 포인터 전진
            while (charCount[newChar] > 1) {
                charCount[s[left]]--;
                left++;
            }

            // 현재 윈도우 길이로 최댓값 갱신
            maxLen = max(maxLen, right - left + 1);
        }

        return maxLen;
    }
};
```

## 다른 접근

**1. 슬라이딩 윈도우 + 해시 맵 (마지막 인덱스 기록)**
각 문자의 마지막 등장 인덱스를 `unordered_map`에 저장하고, 중복 문자 발견 시 `left`를 `max(left, lastSeen[char] + 1)`로 한 번에 점프시키는 방식이다. `while` 루프 없이 `left`를 즉시 이동할 수 있어 코드가 더 간결하지만, 해시 맵의 상수 오버헤드로 인해 실제 실행 속도는 빈도 배열 방식보다 느릴 수 있다.

**2. 브루트 포스 (Brute Force)**
가능한 모든 부분 문자열을 열거하고, 각 부분 문자열에 대해 중복 여부를 `set`으로 확인하는 방식이다. 구현이 직관적이고 이해하기 쉽지만 시간 복잡도가 O(n²) ~ O(n³)으로 n이 클 경우 제한 시간을 초과할 위험이 있다.

## 비슷한 문제

- **LeetCode 159** - Longest Substring with At Most Two Distinct Characters
- **LeetCode 340** - Longest Substring with At Most K Distinct Characters
- **LeetCode 76** - Minimum Window Substring