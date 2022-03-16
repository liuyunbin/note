## 如何理解 git reset?

### 不带路径的 git reset
假设: 目前的提交记录是 A --> B --> C --> D, 此时 HEAD 指向 D, C --> D 时 README 有修改

此时 git reset 会有以下行为

1.     如果 此时运行 git reset --soft C


