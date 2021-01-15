"""
10000.000000 100000.000000 200000.000000 500000.000000 1000000.000000 2000000.000000 5000000.000000 10000000.000000
27.000000 31.000000 38.000000 40.000000 63.000000 103.000000 129.000000 144.000000


100000.000000 111111.111111 125000.000000 142857.142857 200000.000000 250000.000000 333333.333333 500000.000000 1000000.000000 1111111.111111 1250000.000000 1428571.428571 2000000.000000 2500000.000000 3333333.333333 5000000.000000 10000000.000000
15.000000 18.000000 17.000000 17.000000 18.000000 18.000000 19.000000 20.000000 29.000000 31.000000 35.000000 38.000000 50.000000 53.000000 62.000000 68.000000 70.000000
"""

from matplotlib import pyplot as plt

Ns = list(map(float, input().split()))
times = list(map(float, input().split()))

plt.gca().set_xscale('log')
plt.gca().set_yscale('log')


plt.plot(Ns, times)
plt.show()