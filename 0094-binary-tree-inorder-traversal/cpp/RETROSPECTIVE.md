# 풀이 회고

## 핵심 아이디어

중위 순회(Inorder Traversal)는 "왼쪽 서브트리 → 현재 노드 → 오른쪽 서브트리" 순서로 방문하는 탐색이다. 재귀(DFS)를 이용하면 이 순서를 함수 호출 스택에 자연스럽게 위임할 수 있어 구현이 직관적이다. 각 노드에서 왼쪽을 끝까지 탐색한 뒤 자신의 값을 기록하고, 마지막으로 오른쪽을 탐색함으로써 정렬된 방문 순서를 보장한다.

## 사용된 자료구조 / 알고리즘

- 이진 트리 (Binary Tree)
- 깊이 우선 탐색 (DFS, Depth-First Search)
- 재귀 호출 스택 (Recursive Call Stack)

## 복잡도 분석

- **시간 복잡도**: O(N)
  - 트리의 모든 노드를 정확히 한 번씩 방문하므로 노드 수 N에 비례한다.
- **공간 복잡도**: O(N)
  - 결과 배열에 N개의 값을 저장하고, 재귀 호출 스택의 깊이는 최악의 경우(편향 트리) O(N), 평균적으로 O(log N)이다.

## 개선된 코드

```cpp
class Solution {
public:
    // 중위 순회 결과를 담을 벡터를 초기화하고 탐색을 시작한다
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> visitOrder; // 방문 순서대로 값을 저장할 결과 벡터
        collectInorder(root, visitOrder);
        return visitOrder;
    }

private:
    // 재귀적으로 중위 순회를 수행하며 노드 값을 결과 벡터에 추가한다
    void collectInorder(TreeNode* currentNode, vector<int>& visitOrder) {
        // 현재 노드가 없으면(null이면) 탐색 종료
        if (!currentNode) return;

        // 1단계: 왼쪽 서브트리를 먼저 재귀 탐색
        collectInorder(currentNode->left, visitOrder);

        // 2단계: 현재 노드의 값을 결과에 기록
        visitOrder.push_back(currentNode->val);

        // 3단계: 오른쪽 서브트리를 재귀 탐색
        collectInorder(currentNode->right, visitOrder);
    }
};
```

## 다른 접근

**1. 반복문 + 명시적 스택 (Iterative with Explicit Stack)**
재귀 대신 `stack<TreeNode*>`를 직접 사용해 중위 순회를 구현한다. 현재 노드가 있는 한 왼쪽으로 계속 내려가며 스택에 push하고, 더 이상 없으면 pop하여 값을 기록한 뒤 오른쪽으로 이동한다. 재귀 호출 오버헤드가 없고 스택 오버플로우 위험이 없다는 장점이 있지만, 코드가 재귀 방식보다 다소 길고 직관성이 떨어진다.

**2. 모리스 순회 (Morris Traversal)**
스택이나 재귀 없이 O(1) 추가 공간만으로 중위 순회를 수행하는 방법이다. 현재 노드의 왼쪽 서브트리에서 가장 오른쪽 노드(중위 선행자)에 임시 링크를 걸어 돌아올 경로를 만들고, 탐색 후 링크를 원상복구한다. 공간 복잡도가 O(1)로 매우 효율적이나 트리 구조를 일시적으로 변형하기 때문에 코드 이해와 유지보수 난이도가 높다.

## 비슷한 문제

- LeetCode 144. Binary Tree Preorder Traversal
- LeetCode 145. Binary Tree Postorder Traversal
- LeetCode 230. Kth Smallest Element in a BST