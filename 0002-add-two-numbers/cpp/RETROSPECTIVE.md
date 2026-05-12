# 풀이 회고

## 핵심 아이디어

두 linked list가 이미 역순으로 저장되어 있으므로, 앞에서부터 노드를 하나씩 읽으면 자연스럽게 낮은 자리부터 더할 수 있다. 각 자리의 합과 올림수(carry)를 함께 관리하면서 새 노드를 순서대로 이어붙이면, 별도의 역순 변환 없이 결과 linked list를 직접 구성할 수 있다. 두 리스트 중 하나가 먼저 끝나거나, 마지막 덧셈 후에도 올림수가 남는 경우를 모두 처리해야 완전한 풀이가 된다.

## 사용된 자료구조 / 알고리즘

- **Linked List 순회**: 두 리스트를 동시에 앞에서부터 순회
- **Dummy Head 패턴**: 결과 리스트의 head 처리를 단순화하기 위한 더미 노드
- **자리올림(Carry) 전파**: 초등 덧셈과 동일한 방식으로 올림수를 다음 자리로 전달

## 복잡도 분석

- **시간 복잡도**: O(max(m, n))
  - m, n이 각 리스트의 길이일 때, 더 긴 리스트를 한 번 순회하는 것이 전체 연산을 지배한다.
- **공간 복잡도**: O(max(m, n))
  - 결과 리스트의 노드 수가 최대 max(m, n) + 1개이므로 (올림수가 남을 경우 +1), 출력 공간을 제외하면 O(1)이다.

## 개선된 코드

```cpp
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // 결과 리스트 구성을 단순화하기 위한 더미 헤드 노드 생성
        ListNode dummyHead(0);
        ListNode* currentNode = &dummyHead;

        int carry = 0; // 자리올림수 (0 또는 1)

        // 두 리스트 중 하나라도 남아 있거나, 올림수가 남아 있으면 계속 처리
        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            // 현재 자리의 각 피연산자 값 추출 (리스트가 끝났으면 0으로 처리)
            int digit1 = (l1 != nullptr) ? l1->val : 0;
            int digit2 = (l2 != nullptr) ? l2->val : 0;

            // 두 자릿값과 올림수를 합산
            int digitSum = digit1 + digit2 + carry;

            // 다음 자리로 전달할 올림수 계산
            carry = digitSum / 10;

            // 현재 자리의 결과값(1의 자리)으로 새 노드 생성 후 결과 리스트에 연결
            currentNode->next = new ListNode(digitSum % 10);
            currentNode = currentNode->next;

            // 각 리스트 포인터를 다음 노드로 이동 (nullptr이면 그대로 유지)
            if (l1 != nullptr) l1 = l1->next;
            if (l2 != nullptr) l2 = l2->next;
        }

        // 더미 헤드의 다음 노드가 실제 결과 리스트의 시작
        return dummyHead.next;
    }
};
```

## 다른 접근

**재귀(Recursion) 방식**
현재 자리의 합과 올림수를 계산한 뒤, 나머지 리스트와 올림수를 인자로 재귀 호출하는 방식이다. 코드가 선언적으로 읽히는 장점이 있지만, 리스트 길이 최대 100인 제약 조건에서는 큰 차이가 없어도, 재귀 깊이만큼 콜 스택이 쌓이므로 반복문 방식보다 공간 비용이 미세하게 높다.

**실제 정수로 변환 후 덧셈**
두 리스트를 각각 정수로 변환하고, 더한 뒤 결과를 다시 linked list로 변환하는 방식이다. 직관적이지만 노드가 100개일 경우 수가 100자리에 달해 `long long` 범위를 초과하므로 별도의 big integer 처리가 필요하다. 범용성이 낮아 실제로는 권장되지 않는 접근이다.

## 비슷한 문제

- **LeetCode 43 · Multiply Strings**: 문자열로 표현된 두 수의 곱셈을 자릿수 단위로 처리
- **LeetCode 445 · Add Two Numbers II**: 같은 문제이나 숫자가 정순(앞자리가 먼저)으로 저장되어 역순 처리가 필요
- **LeetCode 67 · Add Binary**: 이진수 문자열 두 개의 덧셈을 carry를 이용해 처리