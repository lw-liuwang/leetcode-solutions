# 33. Search in Rotated Sorted Array · C++17

[原题](https://leetcode.com/problems/search-in-rotated-sorted-array/)要求在可能左旋的严格递增数组里返回target所在下标，不存在返回−1。官方长度1..5000，元素互不相同，元素和target在[-10000,10000]。`int Solution::search(vector<int>& nums, int target)`保持输入。空数组返回−1是额外扩展；不承诺处理重复值的旋转数组。

维护闭区间[left,right]。若中点已命中则直接返回。否则至少一半有序：当nums[left]<=nums[middle]时左半有序，target落在[nums[left],nums[middle])才保留左半，否则保留右半；若左半无序，则右半有序，target落在(nums[middle],nums[right]]才保留右半，否则保留左半。排除中点时用middle−1或middle+1，避免相邻位置停滞。

严格递增数组经过一次旋转后，除旋转连接处外相邻值都递增。任何连续候选子区间至多有一处下降；若左半跨过下降，右半便不跨过。互异性保证端点比较能识别有序半区，left=middle时单元素半区也有序。已先排除中点相等，才能在target范围中使用对应严格边界。

循环不变量是：若target存在且未返回，其唯一位置仍在候选区间。有序半区的端点界恰好界定该半区能够包含的目标值；不在此界内可以排除整个半区，在界内则另一半不可能有相同值。每轮保留中点一侧，候选长度至少减半，所以非空输入时间O(log n)、额外空间O(1)。下标长度至多5000，使用int且先把size转成有符号数，空输入right=−1不会被访问。

例如[4,5,6,7,0,1,2]找0：初始middle=3、左半有序但0不在[4,7)，移到[4,6]；middle=5、左半[0,1]有序且0在[0,1)，保留[4,4]，随后命中4。不能对旋转数组直接使用全局递增二分，也不能把本算法无条件用于重复值，例如[1,0,1,1,1]会破坏有序半区识别。

测试的oracle逐个线性扫描，完全不依赖半区判断。对七个不同值−3..3的每个非空子集枚举所有左旋：共有448个旋转数组，每个查询−4..4，共4032次。8个固定例子覆盖缺失、单元素、两元素、旋转点和值域两端。空数组另测9个target；长度5000数组左旋1234后，查询全部5000个值及两侧缺失值，共5002次。所有调用均检查输入保持。

```console
g++ -std=c++17 -O2 -Wall -Wextra -pedantic tests/cpp/test_p0033_rotated_search.cpp -o test_rotated
./test_rotated
```

B独立编写实现、解释及测试，OpenAI Codex辅助。返回−1的占位实现已真实触发已存在目标的断言失败，最终运行结果按实际日志补充。未向LeetCode提交，不声称Accepted。

最终本机验证：GCC16.2、C++17、`-O2 -Wall -Wextra -pedantic`，上述目标测试及完整分支25个程序均编译无诊断、运行退出0。独立完整内容评审无阻塞。实际目标输出：

```text
448 rotations / 4032 linear-oracle queries; 8 fixtures, 9 empty extensions and 5002 maximum-length queries passed; input unchanged
```

未提交LeetCode。A后续真实补写将另行核验并记录，不提前共同署名。
