import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("results2.csv")

fig, ax = plt.subplots()
ax.step(data["Insertion Index"], data["Array"], label="Array")
ax.step(data["Insertion Index"], data["List"], label="List")
ax.set_xlabel("Insertion Index")
ax.set_ylabel("Time (s)")
ax.legend()

fig.savefig("arrays_vs_lists2.png")
plt.show()