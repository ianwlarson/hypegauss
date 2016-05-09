#!/usr/bin/env python3

from math import sqrt, pi

consts = [1]

for i in range(1, 50):
	sum = 0
	for j in range(0, i):
		sum += consts[j] * consts[i - 1 - j] / ((j + 1) * (2*j + 1))
	consts.append(sum)

for i in range(0, len(consts)):
	consts[i] = consts[i] / (2*i + 1) * (sqrt(pi)/2)**(2*i + 1)

print(consts)
