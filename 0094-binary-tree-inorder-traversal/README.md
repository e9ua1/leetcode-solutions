# 94. Binary Tree Inorder Traversal

> **Easy** · Stack, Tree, Depth-First Search, Binary Tree · [원문](https://leetcode.com/problems/binary-tree-inorder-traversal/)

## 문제

이진 트리의 `root`가 주어질 때, 노드 값들의 중위 순회(inorder traversal) 결과를 반환하라.

## 입출력 예시

### Example 1
```
Input: root = [1,null,2,3]
Output: [1,3,2]
```
**설명**:

![예시 1 다이어그램](https://assets.leetcode.com/uploads/2024/08/29/screenshot-2024-08-29-202743.png)

### Example 2
```
Input: root = [1,2,3,4,5,null,8,null,null,6,7,9]
Output: [4,2,6,5,7,1,3,9,8]
```
**설명**:

![예시 2 다이어그램](https://assets.leetcode.com/uploads/2024/08/29/tree_2.png)

### Example 3
```
Input: root = []
Output: []
```

### Example 4
```
Input: root = [1]
Output: [1]
```

## 제약 조건

- 트리의 노드 수는 `[0, 100]` 범위에 있다.
- `-100 <= Node.val <= 100`

---

**심화 과제**: 재귀적 풀이는 간단하다. 반복문(iterative)으로도 풀 수 있겠는가?