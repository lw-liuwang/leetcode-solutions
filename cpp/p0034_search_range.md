# 34. Find First and Last Position · C++17

[原题](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/)要求在非递减数组中找target首尾下标，缺失时返回[-1,-1]。`vector<int> Solution::searchRange(vector<int>& nums, int target)`保持输入。官方允许空数组，长度最多100000，数值与target在[-10^9,10^9]；相同值可以连续重复。

第一次二分找首个不小于target的位置first。候选元素半开区间为[left,right)，右侧哨兵size允许作为答案：nums[middle]<target时left=middle+1，否则right=middle。若first=size或该位置不等于target，即不存在目标；短路检查保证不会访问nums[size]。

目标存在时，再在[first,size)找首个严格大于target的位置。此时nums[middle]<=target才推进left，否则收缩right；得到的边界减一就是最后一个target。没有计算target+1，也没有从首个命中处向左右线性扫描，所以大量重复元素仍保持对数时间。

第一次搜索把已经排除的前缀全部证明为<target，后缀全部证明为>=target，答案边界始终在闭区间[left,right]。mid始终位于当前非空元素区间，两个更新都保持分区且严格缩小。终止left=right时即唯一分界。第二次同理，前缀判定改为<=target、后缀改为>target；第一次已经证明first之前全小于目标，故可以从first开始。已确认nums[first]=target，最终上边界必大于first，减一不会产生越界答案。

例如[1,2,2,2,4]查2，下边界是1，上边界是4，因此返回[1,3]；若只找到任意一个2就返回两次该位置，会漏掉重复范围。两个搜索各O(log n)，总时间O(log n)，空数组常数时间；除固定两个返回下标外只用O(1)额外空间。官方长度允许int下标，中点写作left+(right-left)/2。

测试oracle从头到尾线性记录首个和最后一个相等位置，不使用二分或标准库边界算法。穷举五个值−2..2上长度0..8的全部非递减数组，共1287个，每个查询−3..3，共9009次。8个固定例子包含重复段、缺失、单元素、空输入和两个值域端点。另有5次长度100000检查，覆盖全相等、全缺失和每值重复10次数组的首段、中段、尾段。每次检查输入未变。

```console
g++ -std=c++17 -O2 -Wall -Wextra -pedantic tests/cpp/test_p0034_search_range.cpp -o test_range
./test_range
```

B独立编写实现、解释及测试，OpenAI Codex辅助。总返回[-1,-1]的占位实现已实际触发存在目标的断言失败，最终运行结果按实际日志补充。未向LeetCode提交，不声称Accepted。

最终本机验证：GCC16.2、C++17、`-O2 -Wall -Wextra -pedantic`，上述目标测试及完整分支25个程序均编译无诊断、运行退出0。独立完整内容评审无阻塞。实际目标输出：

```text
1287 sorted arrays / 9009 linear-oracle queries; 8 fixtures and 5 maximum-length checks passed; input unchanged
```

未提交LeetCode。A后续真实补写将另行核验并记录，不提前共同署名。
