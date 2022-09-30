#!/bin/bash
set -u          # 使用未初始化的变量报错
set -e          # 只要发生错误就退出
set -o pipefail # 只要管道发生错误就退出
set -E          # 即使意外退出, 也会执行 trap 命令

rm -rf test
mkdir -p test && cd test

git init

echo a > 1.txt
git add 1.txt
git commit -m "A"

echo b > 1.txt
git add 1.txt
git commit -m "B"

echo c > 1.txt
git add 1.txt
git commit -m "C"

echo d > 1.txt
git add 1.txt
git commit -m "D"

