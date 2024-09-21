import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("data/test2_results.csv")

fig, ax = plt.subplots()
ax.step(data["Insertion Index"], data["Array"], label="Array")
ax.step(data["Insertion Index"], data["List"], label="List")
ax.set_title("Time as a Function of Insertion: Varying the Index")
ax.set_xlabel("Insertion Index")
ax.set_ylabel("Time (s)")
ax.legend()

fig.savefig("test2_results.png")
plt.show()