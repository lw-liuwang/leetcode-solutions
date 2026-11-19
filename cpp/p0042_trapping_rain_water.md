# 42. Trapping Rain Water · C++17

[原题](https://leetcode.com/problems/trapping-rain-water/)统计每根宽1柱子上方可积水的总量。`int Solution::trap(vector<int>& height)`不改输入。官方长度1..20000、高度0..100000，空输入作为扩展返回0。积水按每个位置的左右最高墙决定，与只选一对线的容器问题不同。

left、right围住尚未结算区间，leftMax与rightMax分别记已知两侧最高值。每轮先把当前两端高度纳入各自最大值。若leftMax<=rightMax，左端积水就是leftMax-height[left]，结算后left加一；反之结算右端并减小right。循环使用left<=right，最后一个位置也结算一次。

纳入当前端点后，leftMax恰好是[0,left]的最大高度，rightMax恰好是[right,n)的最大高度。若leftMax较小，left右侧的真实最高墙至少有rightMax那么高，因为整个[right,n)都在其右侧或包含它。于是当前位置左右最大墙的较小值必是leftMax，不需要知道中间还有多高的柱子。另一分支完全对称。最大值包含当前柱，增加量非负；每次移走一个已正确结算的位置，所有位置恰好结算一次。

空数组先返回，随后把已知至多20000的长度转成int。left和right允许越界到n或-1作为终止状态，但循环条件在下一次数组访问前检查，因此没有下溢访问。两端柱不能积水，总量上界为(20000-2)*100000=1999800000，小于INT_MAX，int累加安全。该界依赖官方非负高度与长度合同。

每个位置结算一次，时间O(n)，额外空间O(1)。独立oracle对每个位置分别遍历完整左右区间求最大墙，再计算较小值减当前高度，不使用生产的双指针或滚动最大值。四值长度1..7共21844个数组，加4个固定例子、空扩展以及3个20000长度边界：最大积水盆地、全等高和单调递增。全部检查输入保持。

A补写height=[5,1,2,1,4]的完整结算表，最大值均是本轮纳入两端高度之后的值：

| left / right | leftMax / rightMax | 结算位置 | 新增水量 | 累计 |
| --- | --- | --- | --- | --- |
| 0 / 4 | 5 / 4 | 右4 | 4-4=0 | 0 |
| 0 / 3 | 5 / 4 | 右3 | 4-1=3 | 3 |
| 0 / 2 | 5 / 4 | 右2 | 4-2=2 | 5 |
| 0 / 1 | 5 / 4 | 右1 | 4-1=3 | 8 |
| 0 / 0 | 5 / 5 | 左0 | 5-5=0 | 8 |

最后同一位置只结算一次，不是左右各结算一次。这里总积水8是逐柱水量之和，不能改用一对端点的矩形面积代替。

所有高度合法增加同一常数k后，每个非空左右区间的最高墙都增加k，因此min(左最高,右最高)-当前位置高度不变，逐柱相加也不变。A只对21844个小枚举加k=5：原高度0..3变5..8，长度1..7保持，仍满足官方合同。新增期望沿用原独立逐位置oracle，分别检查原输入与平移输入不变；高度已到100000的大边界不平移，空输入仍只按既有扩展检验。A实际编写上述账本、证明与测试，未本机编译C++，最终运行需B补充。

```console
g++ -std=c++17 -O2 -Wall -Wextra -pedantic tests/cpp/test_p0042_trapping_rain_water.cpp -o test_water
./test_water
```

B独立实现、解释与测试，OpenAI Codex辅助；占位返回0已实际触发断言失败，后续运行结果按真实日志记录。未提交LeetCode，不声称Accepted。

B对A真实补写应用后的验证：GCC 16.2，`-std=c++17 -O2 -Wall -Wextra -pedantic`，编译无诊断，执行退出0。保留原oracle，新增性质检查均实际执行。以下是这次补写后的实际输出；较早的完整分支记录只证明当时内容，最终提交的精确head另行运行并在PR交回。

```text
21844 arrays matched per-position maxima oracle; 4 fixtures, empty extension and 3 length boundaries passed; legal height translations checked
```

测试文件SHA256：`3de0f7ce0e732bcfa1dfadc349e6e20a93c6f25051943dc763e6ecf75b6382c4`。双方实际贡献共同整合后再请求A正式批准最终head，B不自批。未提交LeetCode。
