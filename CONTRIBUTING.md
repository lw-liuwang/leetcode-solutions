# 贡献约定

先查看已有Issue和PR，避免对同一题、同一语言重复提交。A编写Python，B编写C++17。另一账号负责Code review，检查正确性、复杂度、边界和可读性。作者不能批准自己的PR。

每个完整题解包含原题链接、输入约束的必要假设、算法与不变量、时间/额外空间复杂度、可直接提交LeetCode的`Solution`接口，以及相关样例或测试。示例用自行组织的说明，不复制整篇题面或他人的实现。

Python验证从仓库根目录运行：

```console
python -m unittest discover -s tests/python -p "test_*.py" -v
```

C++测试各自包含main，在仓库根目录按具体文件构建，例如：

```console
g++ -std=c++17 -O2 -Wall -Wextra -pedantic tests/cpp/test_p0001_two_sum.cpp -o test_two_sum
./test_two_sum
```

不要求每台机器具备两种语言的工具链。未执行、静态审查、实际运行、线上CI结果分别记录；没有LeetCode提交记录就不写“Accepted”。

PR关联实际工作Issue，说明算法、边界、验证与需要另一人补写的具体内容。提交后请求对方评审。收到分支写入交接后，原作者暂停该分支写入；其他独立工作可以继续。

接收方实际补写后，将双方真实成果整合为同一个共同署名内容提交，使用正确关联邮箱。核对完整最终diff，正式批准最终head，绑定同一head用merge commit合并并回读。若代码有问题则具体指出并修复或交回，不能无条件批准。新内容使旧批准失效，不关闭或绕过审批规则。

双方各有一个工作仓库：A的lw-liuwang/leetcode-solutions与B的ZicongHe2002/leetcode-solutions。A使用Python向B仓库提交Issue和PR；B使用C++向A仓库提交Issue和PR。跨账号交接也写入对应工作Issue/PR，Assignee表示下一行动人，不使用共享Issues。

完成Issue需有可核对实现，正式Code review需有对实际代码的检查结论。A/B达到既定官方银色目标才结束连续任务，公开操作数量不等于GitHub内部成就计数。
