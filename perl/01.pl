#!/usr/bin/perl

use strict;
use warnings;

# 测试执行 shell 命令

my $v1 = `date +"%Y-%m-%d %H:%M:%S %z"`;
print("当前时间: $v1");

