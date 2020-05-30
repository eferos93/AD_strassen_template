import pandas as pd
import matplotlib.pyplot as plt

all_times = pd.read_csv("benchmark.txt", sep ="\t", header=None, skiprows=1)
strassen_times = pd.read_csv("benchmark_strassen.txt", sep="\t", header=None, skiprows=1)

all_times.columns = ["n","Naive", "Strassen", "Optimised Strassen", "Same result (true or false)"]
strassen_times.columns = ["n", "Strassen", "Optimised Strassen", "Same result (true or false)"]

fig = plt.figure()
plt.ylabel("Elapsed Time")
plt.xlabel("Size")

ax = plt.subplot(111)

ax.plot(all_times["n"], all_times["Naive"], label = "Naive")
ax.plot(all_times["n"], all_times["Strassen"], label = "Strassen")
ax.plot(all_times["n"], all_times["Optimised Strassen"], label = "Optimised Strassen")

ax.legend()

plt.savefig("benchmark_all.png")
plt.show("benchmark_all.png")

fig = plt.figure()
plt.ylabel("Elapsed Time")
plt.xlabel("Size")

ax = plt.subplot(111)

ax.plot(strassen_times["n"], strassen_times["Strassen"], label = "Strassen")
ax.plot(strassen_times["n"], strassen_times["Optimised Strassen"], label = "Optimised Strassen")

ax.legend()

plt.savefig("benchmark_strassen.png")
plt.show("benchmark_strassen.png")
