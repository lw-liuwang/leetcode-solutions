# 11. Container With Most Water · C++17

[原题](https://leetcode.com/problems/container-with-most-water/)在不同下标的两根竖线之间选最大容积。`int Solution::maxArea(vector<int>& height)`不改输入；官方长度2..100000、高度0..10000。长度0或1作为扩展返回0，不假定有两根线可选。

left、right初始为首尾。先记录当前面积`(right-left)*min(height[left],height[right])`，再移动较短一端；等高时固定移动左端。每轮至少排除一个下标，直到两端相遇。容器宽度是下标差，而非包含端点的元素个数。

若左端不高于右端，任一保留左端且右端向内收缩的候选，其高度上界不超过height[left]，宽度小于等于当前宽度，所以面积不超过已经记录的当前面积。安全排除左端不会遗漏尚未记录的更大答案。右端较矮时对称；等高时任一端均可排除。循环保持所有已排除候选都不优于best，终止时没有剩余下标对，best为全局最大值。仅移动高端没有这个排除依据。

单调移动两端，时间O(n)，额外空间O(1)。最大面积是99999*10000=999990000，int安全；宽度在转换为int前已有官方长度保证。空和单元素先返回，避免size()-1的无符号下溢。

独立测试枚举所有下标对作为oracle，不复用双指针。四种高度上长度2..7共21840个数组；5个固定例子包含内侧最佳、等高、零高度、重复高柱，两种短长度扩展和长度100000的最大面积边界。每次检查输入保持。

A补写height=[1,8,2,7,1]的完整双指针账本，下标为0基，先算面积再移端点：

| left / right | 两端高度 | 当前面积 | best | 移动 |
| --- | --- | --- | --- | --- |
| 0 / 4 | 1 / 1 | 4 | 4 | 等高，left变1 |
| 1 / 4 | 8 / 1 | 3 | 4 | 右端较短，right变3 |
| 1 / 3 | 8 / 7 | 14 | 14 | 右端较短，right变2 |
| 1 / 2 | 8 / 2 | 2 | 14 | 右端较短，right变1，终止 |

best只记录已检查面积的最大值，不会随当前面积下降；宽度是right-left。数组反转把每个下标对i<j双射为n-1-j<n-1-i，宽度与两端最小高度都保持，所以全部候选面积的集合及最大值保持。此性质不要求生产算法以相同顺序访问对应对。

A对每次exact调用增加反序核对，涵盖21840个小枚举、5个固定例子、2个短长度扩展与1个大边界，共21848次；原全下标对oracle保留。反序不改变合法长度/高度，空和单元素仍按既有扩展检验；求解前后分别核对原数组与反序数组保持。A实际编写上述账本、证明与测试，未本机编译C++，最终运行需B补充。

```console
g++ -std=c++17 -O2 -Wall -Wextra -pedantic tests/cpp/test_p0011_container_with_most_water.cpp -o test_container
./test_container
```

B独立实现、解释与测试，OpenAI Codex辅助；实际先观察返回0占位失败，最终测试结果以运行日志为准。未提交LeetCode，不声称Accepted。

B对A真实补写应用后的验证：GCC 16.2，`-std=c++17 -O2 -Wall -Wextra -pedantic`，编译无诊断，执行退出0。保留原oracle，新增性质检查均实际执行。以下是这次补写后的实际输出；较早的完整分支记录只证明当时内容，最终提交的精确head另行运行并在PR交回。

```text
21840 arrays matched all-pairs oracle; 5 fixtures, 2 short extensions and maximum-area boundary passed; reversal invariance checked
```

测试文件SHA256：`d668cd8d25bb843f2c687f76812c7d3451ca484eb963bfd73164bb32099862bd`。双方实际贡献共同整合后再请求A正式批准最终head，B不自批。未提交LeetCode。
