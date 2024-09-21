import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("results.csv")

fig, ax = plt.subplots()
ax.step(data["Elements"], data["Array"], label="Array")
ax.step(data["Elements"], data["List"], label="List")
ax.set_xlabel("Elements")
ax.set_ylabel("Time (s)")
ax.legend()

fig.savefig("arrays_vs_lists.png")
plt.show()