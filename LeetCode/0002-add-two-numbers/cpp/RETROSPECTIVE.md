# 풀이 회고

## 핵심 아이디어

두 연결 리스트가 숫자를 **역순**으로 저장하고 있다는 점을 활용한다. 낮은 자리부터 순서대로 순회하면서 자릿수끼리 더하고, 올림수(carry)를 다음 자리로 전달하면 자연스럽게 덧셈이 완성된다. 두 리스트의 길이가 달라도 짧은 쪽이 끝난 이후에는 0으로 처리하면 되고, 마지막에 올림수가 남아 있으면 새 노드를 추가해 마무리한다.

## 사용된 자료구조 / 알고리즘

- Linked List 순회 (Iteration)
- 초등 수학의 자리올림(Carry) 덧셈 시뮬레이션
- Dummy Head 패턴 (결과 리스트의 head 관리를 단순화)

## 복잡도 분석

- **시간 복잡도**: O(max(m, n))
  - 두 리스트 중 더 긴 쪽의 길이만큼 순회하며, 각 노드를 한 번씩만 방문한다.
- **공간 복잡도**: O(max(m, n))
  - 결과 리스트의 노드 수가 최대 max(m, n) + 1개이므로, 출력용 공간을 제외하면 O(1)이다.

## 개선된 코드

```cpp
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // 결과 리스트의 시작점을 쉽게 참조하기 위한 더미 헤드 노드 생성
        ListNode dummyHead(0);
        ListNode* currentNode = &dummyHead;

        int carry = 0; // 다음 자리로 넘길 올림수

        // 두 리스트 중 하나라도 남아 있거나, 올림수가 남아 있으면 계속 처리
        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            // 노드가 없는 쪽은 0으로 간주
            int digit1 = (l1 != nullptr) ? l1->val : 0;
            int digit2 = (l2 != nullptr) ? l2->val : 0;

            // 현재 자릿수 합산 (이전 올림수 포함)
            int sum = digit1 + digit2 + carry;

            // 다음 자리로 넘길 올림수 계산
            carry = sum / 10;

            // 현재 자리의 한 자리 숫자만 새 노드에 저장
            int currentDigit = sum % 10;
            currentNode->next = new ListNode(currentDigit);
            currentNode = currentNode->next;

            // 각 리스트에서 다음 노드로 이동 (nullptr이면 그대로 유지)
            if (l1 != nullptr) l1 = l1->next;
            if (l2 != nullptr) l2 = l2->next;
        }

        // 더미 헤드의 다음 노드가 실제 결과 리스트의 첫 번째 노드
        return dummyHead.next;
    }
};
```

## 다른 접근

**재귀(Recursion) 방식**
각 자리를 재귀 호출로 처리하는 방법이다. 현재 자리의 합을 계산하고, 올림수를 인자로 넘겨 다음 자리를 재귀적으로 처리한다. 코드가 선언적이고 간결해 보이지만, 리스트 길이가 최대 100이므로 스택 오버플로우 위험은 없다. 다만 반복(Iteration) 방식보다 함수 호출 오버헤드가 있어 미세하게 느릴 수 있다.

**실제 정수 변환 후 덧셈 방식**
리스트를 역순으로 읽어 실제 정수로 변환 후 덧셈하고, 결과를 다시 리스트로 만드는 방법이다. 직관적으로 이해하기 쉽지만, 노드 수가 최대 100개이므로 일반적인 `int`나 `long long` 범위를 초과할 수 있어 큰 수(Big Integer) 처리가 필요하다. 따라서 실용적이지 않으며 코드도 오히려 복잡해진다.

## 비슷한 문제

- LeetCode 43 · Multiply Strings
- LeetCode 445 · Add Two Numbers II
- LeetCode 989 · Add to Array-Form of Integer