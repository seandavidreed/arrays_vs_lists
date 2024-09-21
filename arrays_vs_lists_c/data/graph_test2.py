import pandas as pd
import sys
import matplotlib.pyplot as plt

with_optimization = sys.argv[1]

if with_optimization:
    data = pd.read_csv("data/test3_results.csv")
    output_file = "test3_results.png"
else:
    data = pd.read_csv("data/test2_results.csv")
    output_file = "test2_results.png"

fig, ax = plt.subplots()
ax.step(data["Insertion Index"], data["Array"], label="Array")
ax.step(data["Insertion Index"], data["List"], label="List")
ax.set_title("Time as a Function of Insertion: Varying the Index")
ax.set_xlabel("Insertion Index")
ax.set_ylabel("Time (s)")
ax.legend()

fig.savefig(output_file)
plt.show()