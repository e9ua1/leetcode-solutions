# 풀이 회고

## 핵심 아이디어

매 반복마다 `x % 10`으로 현재 1의 자리를 뽑아내고, `result * 10 + digit`으로 결과에 누적한다. `x /= 10`으로 자릿수를 하나씩 줄여가면 자연스럽게 숫자가 뒤집힌다. 오버플로우 감지는 숫자를 누적하기 **직전**에 현재 `result`가 `Integer.MAX_VALUE / 10`보다 크거나 같은지 비교하여 수행한다. 64비트 정수를 사용하지 않고도 32비트 범위 초과를 사전에 탐지할 수 있는 것이 이 풀이의 핵심이다.

## 사용된 자료구조 / 알고리즘

- 수학적 자릿수 분리 (Digit Extraction via Modulo)
- 오버플로우 사전 탐지 (Pre-multiplication Overflow Guard)

## 복잡도 분석

- **시간 복잡도**: O(log₁₀ n)
  - 입력 정수 `x`의 자릿수만큼 반복하므로, 자릿수는 log₁₀(x)에 비례한다.
- **공간 복잡도**: O(1)
  - 결과값과 현재 자리 숫자를 저장하는 고정 크기 변수만 사용한다.

## 개선된 코드

```java
class Solution {

    // 부호 있는 32비트 정수의 최댓값 / 10 (오버플로우 사전 탐지 기준값)
    private static final int OVERFLOW_THRESHOLD = Integer.MAX_VALUE / 10;

    public int reverse(int x) {
        int result = 0;

        // x의 모든 자릿수를 처리할 때까지 반복
        while (x != 0) {
            // 현재 x의 1의 자리 숫자 추출
            int digit = x % 10;

            // 다음 자리 누적 전 오버플로우 여부 사전 검사
            if (isOverflow(result, digit)) {
                return 0;
            }

            // 기존 결과를 한 자리 올리고 새 자릿수를 추가
            result = result * 10 + digit;

            // 처리한 1의 자리를 제거
            x /= 10;
        }

        return result;
    }

    /**
     * result * 10 + digit 연산이 32비트 정수 범위를 벗어나는지 사전에 판별한다.
     * 64비트 자료형 없이 오버플로우를 감지하기 위해 곱셈 이전 단계에서 비교한다.
     *
     * @param result 현재까지 누적된 뒤집힌 숫자
     * @param digit  새로 추가할 1의 자리 숫자
     * @return 오버플로우가 발생하면 true, 그렇지 않으면 false
     */
    private boolean isOverflow(int result, int digit) {
        // 절댓값 기준으로 OVERFLOW_THRESHOLD 초과 시 무조건 오버플로우
        if (Math.abs(result) > OVERFLOW_THRESHOLD) {
            return true;
        }

        // result가 정확히 경계값일 때, digit이 허용 범위를 넘는지 확인
        // 양수 방향: result == THRESHOLD이고 digit > 7 이면 MAX_VALUE(2147483647) 초과
        // 음수 방향: result == -THRESHOLD이고 digit < -8 이면 MIN_VALUE(-2147483648) 미만
        if (Math.abs(result) == OVERFLOW_THRESHOLD) {
            if (result > 0 && digit > 7) return true;
            if (result < 0 && digit < -8) return true;
        }

        return false;
    }
}
```

## 다른 접근

**문자열 변환 후 뒤집기**
`Integer.toString(x)`로 문자열로 변환한 뒤 `StringBuilder.reverse()`를 사용해 뒤집고 다시 정수로 파싱하는 방법이다. 구현이 직관적이고 코드가 짧지만, 문자열 객체 생성으로 인한 추가 힙 메모리 사용이 발생하며, 부호 처리와 파싱 예외(`NumberFormatException`) 처리를 별도로 해야 한다는 트레이드오프가 있다.

**long 타입 활용**
64비트 환경이 허용된다면 `long`으로 결과를 누적한 뒤 마지막에 `Integer.MAX_VALUE`/`Integer.MIN_VALUE`와 비교하는 방법이다. 오버플로우 사전 탐지 로직이 필요 없어 코드가 단순해지지만, 이 문제는 명시적으로 64비트 사용을 금지하고 있으므로 제약 조건을 위반한다.

## 비슷한 문제

- LeetCode 9 · Palindrome Number
- LeetCode 8 · String to Integer (atoi)
- LeetCode 190 · Reverse Bits