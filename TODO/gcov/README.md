
### 安装

### 使用

#### 1. 设置环境变量
* 修改 `*.gcda` 的输出路径, 将 路径中的前 `GCOV_PREFIX_STRIP` 层删掉
* 并用 `GCOV_PREFIX` 作为前缀补充

```
export GCOV_PREFIX=$(pwd)
export GCOV_PREFIX_STRIP=6
```

#### 2. 编译
	g++ -fprofile-arcs -ftest-coverage -o test_gcov -lgcov main.cc

此步, 将生成 `*.gcno`

#### 3. 重置统计数据
    lcov --zerocounters

#### 4. 执行可执行文件
此步, 将生成 `*.gcda`

#### 5. 生成 info 文件
	lcov --directory . --capture --output-file gcov.info

#### 6. 生成 html 文件
	genhtml -o html gcov.info

### lcov 常见命令
* -c, --capture     收集统计信息
* -d, --directory . 指定工作目录
* -o, --output-file gcov.info 指定目标文件
* -z, --zerocounters 重置统计信息
* -r, --remove gcov.info "*/usr/*" "*/local/*" 移除指定统计文件

### genhtml 常见命令
* -o, --output-directory . 指定输出目录

### 官方项目
* lcov: https://github.com/linux-test-project/lcov

