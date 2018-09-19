# encoding: utf-8

import sys

data = list(map(int, sys.stdin.readline.split()))

bytes = 10
import os
data = list(map(int, os.read(0, 10).split()))  # 读取10个字节

