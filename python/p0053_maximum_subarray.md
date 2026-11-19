# 53. Maximum Subarray · Python

[原题](https://leetcode.com/problems/maximum-subarray/)要求选取一个非空连续子数组，使元素和最大。`Solution.maxSubArray`保存ending_here与best，分别表示必须在当前位置结束的最佳非空和，以及所有已处理位置中的最佳和。

加入当前value时，任何以它结束的连续子数组，要么只包含它，要么延长此前某个以相邻位置结束的子数组。取两者较大值，即`max(value, ending_here+value)`。再用新的ending_here更新best。若此前最佳结束和为负，从当前位置重新开始优于携带负贡献；若为正，扩展能保留收益。

两个状态都从首元素初始化，保证全负数组`[-3,-1,-2]`返回−1，而不是错误地选择空数组得到0。空输入不属于原题约定，本地接口显式抛ValueError。单次扫描O(n)时间、O(1)额外空间，不修改输入，不复制nums[1:]。

测试独立枚举所有非空切片求和，覆盖长度1至6、取值−2至2的全部19530个数组，另含样例、全负、零、输入不变及空输入约定。实际运行情况另见PR；没有LeetCode Accepted记录。A实现，OpenAI Codex辅助整理。
