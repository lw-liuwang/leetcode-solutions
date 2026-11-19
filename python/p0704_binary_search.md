# 704. Binary Search · Python

[原题](https://leetcode.com/problems/binary-search/)在严格升序的整数数组中查找target，找到返回下标，否则返回−1。`Solution.search`保留原数组，不先排序或复制数据。

候选区间用半开[left,right)表示。初始为[0,n)；若中点值小于target，则中点及左侧都可排除，left改为middle+1；若中点值大于target，则中点及右侧排除，right改为middle。相等时直接返回。区间每次严格缩小，left==right时无候选位置，返回−1。

右端不包含在候选区间内，所以大于分支使用right=middle，不能混入闭区间写法而无条件减1；另一方面，小于分支必须跳过已排除的中点，否则两元素区间可能停滞。时间O(log n)，额外空间O(1)。实现也自然支持空数组，返回−1。

测试覆盖首尾命中、单元素、缺失及空数组，并对−3至3的全部128个有序子集和−4至4的9个target进行1152次独立线性查找比较。实际执行情况写入PR；没有LeetCode Accepted记录。A实现，OpenAI Codex辅助整理。
