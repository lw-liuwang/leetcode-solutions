# 125. Valid Palindrome · C++17

[原题](https://leetcode.com/problems/valid-palindrome/)要求仅保留英文字母与数字、忽略字母大小写后判断回文。接口`bool Solution::isPalindrome(const std::string& s)`保持输入。官方长度1..200000，字符为可打印ASCII；这里明确处理ASCII，不把Unicode字符或区域设置相关的大小写折叠算入合同。空串返回true是额外扩展。

双指针分别位于两端，遇非字母数字就跳过。`normalized`把大写字母映射到小写、保留小写与数字、其他字符返回−1。两个端点都有效时比较：不同即可判false，相同则同时向内。数值字符必须参与比较，例如`0P`不满足回文；标点不能成为有效字符。显式ASCII归一化使生产代码不依赖C库的当前locale。

循环开始时，已越过的有效字符在两侧按镜像配对且相等，跳过的字符均不参与题目定义的序列。因此跳过标点不改变剩余问题；比较最外层有效字符后，要么有确定反例，要么把原问题缩小为内部区间。指针相遇或越过时，剩余最多一个原字符，归一化后也最多一个，所以答案为true。全标点会不断缩小到这个终止条件，符合归一化空串是回文的约定。

下标使用int，因为长度最多200000；空串的right为−1且不进入循环。每轮至少移动一个端点，总时间O(n)，仅存两个下标和两个归一化值，额外空间O(1)，不建立处理后的字符串。

测试oracle独立建立经过过滤、转小写的字符串，再与其反序副本比较，使用程序默认C locale的字符分类函数并传unsigned char，和生产双指针不同。枚举8字符集合上长度0..6的299593个字符串，覆盖大小写、数字、空格和逗号；另枚举全部95个可打印ASCII字符的9025对，覆盖各分类边界。8个固定案例检查典型正确/错误答案；长度200000分别为全逗号、全A、末项替换为b。每次检查输入保持。

B独立编写实现、解释与测试，OpenAI Codex辅助。已实际观察false占位实现的断言失败，再以GCC16.2、C++17、`-O2 -Wall -Wextra -pedantic`运行上述测试通过，无编译诊断、退出0。完整分支验证见PR记录。未向LeetCode提交，不声称Accepted。

A补写ASCII输入"0,P!0"的完整端点账本，归一化有效字符的序列是"0p0"：

| left / right | 原字符 | 归一化 | 动作 |
| --- | --- | --- | --- |
| 0 / 4 | 0 / 0 | 48 / 48 | 相等，同时内移到1 / 3 |
| 1 / 3 | 逗号 / ! | -1 / -1 | 先跳左侧无效字符，left变2 |
| 2 / 3 | P / ! | 112 / -1 | 跳右侧无效字符，right变2 |

指针相遇后结束，中心P不需要配对，返回true。数字0参与比较；"0P"仍必须为false，不能把数字当作标点跳过。归一化数值仅按ASCII合同解释。

在任意位置插入可打印且非字母数字的ASCII标点，不改变过滤/小写后的有效序列，因而不改变回文判定。A对299593个小枚举和9025个ASCII字符对增加性质检查：前面放一个'!'，每个原字符后再放一个'!'，共308618次。变换后长度1..13，仍在官方范围，原空串扩展变为合法单标点；200000长度边界不扩张。期望来自原独立归一化oracle，原文与变换文本均保留输入不变检查，未扩展为Unicode或任意locale规则。A实际编写上述账本、证明与测试，未本机编译C++，最终运行需B补充。

```console
g++ -std=c++17 -O2 -Wall -Wextra -pedantic tests/cpp/test_p0125_valid_palindrome.cpp -o test_palindrome
./test_palindrome
```

B对A真实补写应用后的验证：GCC 16.2，`-std=c++17 -O2 -Wall -Wextra -pedantic`，编译无诊断，执行退出0。保留原oracle，新增性质检查均实际执行。以下是这次补写后的实际输出；较早的完整分支记录只证明当时内容，最终提交的精确head另行运行并在PR交回。

```text
299593 strings and 9025 printable-ASCII pairs matched normalization oracle; 8 fixtures and 3 length boundaries passed; 308618 punctuation-insertion checks
```

测试文件SHA256：`04629c5f120332ebf62a7ee9debc42dc01a0ddf16ba92789cd5dca1325eb982c`。双方实际贡献共同整合后再请求A正式批准最终head，B不自批。未提交LeetCode。
