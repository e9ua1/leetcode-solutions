# 2. Add Two Numbers

> **Medium** · Linked List, Math, Recursion · [원문](https://leetcode.com/problems/add-two-numbers/)

## 문제

두 개의 **비어 있지 않은** linked list가 주어지며, 각각 음이 아닌 정수를 나타낸다. 숫자는 **역순**으로 저장되어 있고, 각 노드에는 한 자리 숫자가 담겨 있다. 두 수를 더한 결과를 linked list로 반환하라.

두 수는 숫자 0을 제외하고 앞자리가 0으로 시작하지 않는다고 가정해도 된다.

## 입출력 예시

### Example 1

![예시 1 다이어그램](https://assets.leetcode.com/uploads/2020/10/02/addtwonumber1.jpg)

```
Input: l1 = [2,4,3], l2 = [5,6,4]
Output: [7,0,8]
```
**설명**: 342 + 465 = 807.

### Example 2

```
Input: l1 = [0], l2 = [0]
Output: [0]
```

### Example 3

```
Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
Output: [8,9,9,9,0,0,0,1]
```

## 제약 조건

- 각 linked list의 노드 수는 `[1, 100]` 범위 내에 있다.
- `0 <= Node.val <= 9`
- 각 linked list가 나타내는 수는 앞자리가 0으로 시작하지 않음이 보장된다.

---