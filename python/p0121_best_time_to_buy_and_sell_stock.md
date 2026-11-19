# 121. Best Time to Buy and Sell Stock · Python

[原题](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/)最多进行一次先买后卖的交易，允许不交易，求最大收益。`Solution.maxProfit`扫描价格，维护此前最低买入价minimum和已知最佳收益best。

在处理当前卖出价时，最好的合法买入价一定是更早价格的最小值，故先用`price−minimum`更新best，再把当前价格纳入minimum。循环首轮使用首日自身得到0，对答案无影响；后续候选都有正确的时间顺序。`[2,4,1]`的答案是2，不能拿未来最低价1与过去最高价4拼出3。

best初始为0，因此一路下跌时选择不交易。空数组和单日返回0；不改变原数组。一次扫描时间O(n)，只保存两个数，额外空间O(1)，没有切片副本。Python整数不产生固定宽度溢出。

测试除样例和边界外，用独立的所有合法买卖下标对作为oracle，覆盖长度0至5、价格取0至3的全部1365个数组。运行结果另在PR中记录；这不是LeetCode线上Accepted记录。A实现，OpenAI Codex辅助整理。
