# 풀이 회고

## 핵심 아이디어

슬라이딩 윈도우(Sliding Window) 기법을 사용하여 오른쪽 포인터(`rightIdx`)를 한 칸씩 전진시키면서 윈도우를 확장한다. 새로 추가된 문자가 중복되면 왼쪽 포인터(`leftIdx`)를 중복이 해소될 때까지 전진시켜 윈도우를 축소한다. 이 방식은 매 순간 윈도우 내부가 항상 "중복 없는 상태"를 유지하도록 보장하기 때문에, 각 시점에서 `rightIdx - leftIdx + 1`이 곧 현재 유효한 부분 문자열의 길이가 된다.

## 사용된 자료구조 / 알고리즘

- **슬라이딩 윈도우 (Sliding Window)**: 투 포인터로 윈도우 범위를 동적으로 조절
- **빈도 배열 (Frequency Array)**: ASCII 128 크기의 정수 배열로 각 문자의 등장 횟수를 O(1)에 관리

## 복잡도 분석

- **시간 복잡도**: O(n)
  - 오른쪽 포인터는 항상 앞으로만 이동하고, 왼쪽 포인터도 전체 수행에서 최대 n번만 이동하므로 두 포인터 합산 이동 횟수가 2n을 넘지 않는다.
- **공간 복잡도**: O(1)
  - 빈도 배열의 크기가 ASCII 범위인 128로 고정되어 있어, 입력 크기 n에 무관하게 상수 공간을 사용한다.

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

        int strLen = s.size();         // 문자열 전체 길이
        int leftIdx = 0;               // 슬라이딩 윈도우의 왼쪽 경계
        int maxLen = 0;                // 지금까지 찾은 최대 부분 문자열 길이

        // 각 문자의 현재 윈도우 내 등장 횟수를 추적하는 빈도 배열
        vector<int> charFreq(ASCII_SIZE, 0);

        for (int rightIdx = 0; rightIdx < strLen; ++rightIdx) {
            char newChar = s[rightIdx];

            // 오른쪽 끝에 새 문자를 윈도우에 추가
            charFreq[newChar]++;

            // 새 문자가 중복이면 왼쪽 경계를 중복이 해소될 때까지 축소
            while (charFreq[newChar] > 1) {
                charFreq[s[leftIdx]]--;
                leftIdx++;
            }

            // 현재 윈도우 길이로 최댓값 갱신
            maxLen = max(maxLen, rightIdx - leftIdx + 1);
        }

        return maxLen;
    }
};
```

## 다른 접근

**1. 해시 맵으로 마지막 인덱스 저장 (HashMap + Sliding Window)**
각 문자의 마지막 등장 인덱스를 `unordered_map`에 저장하고, 중복 발견 시 왼쪽 포인터를 해당 인덱스 바로 다음으로 점프시키는 방식이다. 현재 풀이처럼 `while`로 한 칸씩 이동하는 대신 한 번에 건너뛰므로 포인터 이동 횟수 자체는 줄어든다. 다만 `unordered_map`의 해시 연산 오버헤드로 인해 실제 벤치마크에서는 현재 배열 기반 풀이보다 느릴 수 있다.

**2. 비트마스크 (Bitmask)**
입력이 소문자 알파벳 26자로 제한된다면 `int` 하나의 비트를 활용해 등장 여부를 표현할 수 있다. 공간을 극단적으로 줄일 수 있지만, 이 문제처럼 입력 범위가 ASCII 전체(영문자·숫자·기호·공백)인 경우엔 128비트가 필요해 `bitset`이나 두 개의 `long long`을 써야 하므로 오히려 코드가 복잡해지는 트레이드오프가 있다.

## 비슷한 문제

- **LeetCode 76** - Minimum Window Substring
- **LeetCode 159** - Longest Substring with At Most Two Distinct Characters
- **LeetCode 424** - Longest Repeating Character Replacement