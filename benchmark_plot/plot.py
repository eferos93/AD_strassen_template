import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

strassen_times = pd.read_csv("benchmark_results.txt", sep ="\t", header=None, skiprows=1)

strassen_times.columns = ["n","Naive", "Strassen", "Optimised Strassen", "Same result (true or false)"]

fig = plt.figure()
plt.ylabel("Elapsed Time")
plt.xlabel("Size")

ax = plt.subplot(111)

ax.plot(data["n"], data["Naive Alg."], label = "Naive Alg.")
ax.plot(data["n"], data["Strassen Alg."], label = "Strassen Alg.")
ax.plot(data["n"], data["Improved Strassen"], label = "Improved Strassen")

ax.legend()

plt.savefig("Benchmark.png")
plt.show("Benchmark.png")