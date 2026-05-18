# 7. Reverse Integer

> **Medium** · Math · [원문](https://leetcode.com/problems/reverse-integer/)

## 문제

부호 있는 32비트 정수 `x`가 주어질 때, 각 자릿수를 뒤집은 값을 반환하라. 뒤집은 결과가 부호 있는 32비트 정수 범위 `[-2³¹, 2³¹ - 1]`를 벗어난다면 `0`을 반환한다.

**환경이 64비트 정수(부호 있음/없음 모두)를 저장할 수 없다고 가정한다.**

## 입출력 예시

### Example 1
```
Input: x = 123
Output: 321
```

### Example 2
```
Input: x = -123
Output: -321
```

### Example 3
```
Input: x = 120
Output: 21
```

## 제약 조건

- `-2³¹ <= x <= 2³¹ - 1`

---