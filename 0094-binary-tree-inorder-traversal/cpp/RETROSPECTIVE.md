# 풀이 회고

## 핵심 아이디어

중위 순회(Inorder Traversal)는 "왼쪽 → 현재 → 오른쪽" 순서로 노드를 방문하는 방식이다. 재귀 호출을 통해 각 노드에서 자연스럽게 이 순서를 구현할 수 있는데, 함수 호출 스택이 트리의 깊이 방향으로 쌓이면서 자동으로 방문 순서를 보장한다. 노드가 `null`일 때 재귀를 종료(기저 조건)함으로써 모든 노드를 정확히 한 번씩 방문하고 결과 벡터에 값을 추가한다.

## 사용된 자료구조 / 알고리즘

- 이진 트리 (Binary Tree)
- 깊이 우선 탐색 (DFS, Depth-First Search)
- 재귀 (Recursion) — 콜 스택이 암묵적인 스택(Stack) 역할을 수행

## 복잡도 분석

- **시간 복잡도**: O(N)
  - 트리의 모든 노드를 정확히 한 번씩 방문하므로 노드 수 N에 비례한다.
- **공간 복잡도**: O(N)
  - 결과 벡터에 N개의 값을 저장하므로 O(N)이다. 추가로 재귀 호출 스택이 트리의 높이 H만큼 쌓이는데, 최악(편향 트리)의 경우 H = N이 되어 전체 공간 복잡도는 O(N)이다.

## 개선된 코드

```cpp
class Solution {
public:
    // 중위 순회 결과를 담을 벡터를 초기화하고 재귀 탐색을 시작한다
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> traversalResult;
        collectInorder(root, traversalResult);
        return traversalResult;
    }

private:
    // 중위 순회(왼쪽 → 현재 → 오른쪽)를 재귀적으로 수행한다
    void collectInorder(TreeNode* currentNode, vector<int>& traversalResult) {
        // 기저 조건: 현재 노드가 null이면 탐색을 종료한다
        if (!currentNode) return;

        // 1단계: 왼쪽 서브트리를 먼저 재귀 탐색한다
        collectInorder(currentNode->left, traversalResult);

        // 2단계: 현재 노드의 값을 결과에 추가한다
        traversalResult.push_back(currentNode->val);

        // 3단계: 오른쪽 서브트리를 재귀 탐색한다
        collectInorder(currentNode->right, traversalResult);
    }
};
```

## 다른 접근

**① 반복문 + 명시적 스택 (Iterative + Explicit Stack)**
재귀 대신 `stack<TreeNode*>`를 직접 관리하여 동일한 중위 순회를 구현한다. 현재 노드를 스택에 push하며 왼쪽으로 계속 내려가다가, 더 이상 내려갈 수 없으면 스택에서 pop하여 값을 기록하고 오른쪽으로 이동하는 방식이다. 재귀 스택 오버플로우(Stack Overflow) 위험이 없어 매우 깊은 트리에서 안전하지만, 코드가 재귀 방식보다 다소 복잡하다.

**② Morris 순회 (Morris Traversal)**
추가 스택이나 재귀 없이 O(1) 공간복잡도로 중위 순회를 달성하는 방법이다. 현재 노드의 왼쪽 서브트리에서 중위 순회 상의 직전 노드(predecessor)를 찾아 임시 링크를 만들고, 이를 이용해 부모 노드로 되돌아오는 경로를 확보한다. 공간 효율이 뛰어나지만 트리의 구조를 일시적으로 변형하는 과정이 수반되어 코드 이해 난이도가 높고, 링크 복원 중 예외 처리에 주의가 필요하다.

## 비슷한 문제

- LeetCode 144. Binary Tree Preorder Traversal
- LeetCode 145. Binary Tree Postorder Traversal
- LeetCode 230. Kth Smallest Element in a BST