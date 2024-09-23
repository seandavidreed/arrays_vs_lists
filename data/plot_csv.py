import pandas as pd
import sys
import matplotlib.pyplot as plt

def plot_csv(src, dest, xlabel, ylabel, title):
    data = pd.read_csv(src)

    fig, ax = plt.subplots(figsize=(15,4.8))
    ax.plot(data[xlabel], data['Array'], color='c', label="Array")
    ax.plot(data[xlabel], data['List'], color='0.7', label="List")
    ax.set_title(title)
    ax.set_xlabel(xlabel)
    ax.set_ylabel(ylabel)
    ax.legend()

    fig.savefig(dest)
    plt.show()

def main():
    if sys.argv[1] == '1':
        plot_csv(
            src="data/test1_results.csv",
            dest="test1_results.png",
            xlabel="Elements",
            ylabel="Time (s)",
            title="Variable Size - Insertion Index (n / 2)"
        )
    elif sys.argv[1] == '2':
        plot_csv(
            src="data/test2_results.csv",
            dest="test2_results.png",
            xlabel="Insertion Index",
            ylabel="Time (s)",
            title="Constant Size (100000) - Variable Insertion Index"
        )
    elif sys.argv[1] == '3':
        plot_csv(
            src="data/test3_results.csv",
            dest="test3_results.png",
            xlabel="Insertion Index",
            ylabel="Time (s)",
            title="Constant Size (100000) - Variable Insertion Index (with list optimization)"
        )
    elif sys.argv[1] == '4':
        plot_csv(
            src="data/test4_results.csv",
            dest="test4_results.png",
            xlabel="Sample",
            ylabel="Time (s)",
            title="Constant Size (100000) - Insertion Index (random)"
        )
    elif sys.argv[1] == '5':
        plot_csv(
            src="data/test5_results.csv",
            dest="test5_results.png",
            xlabel="Sample",
            ylabel="Time (s)",
            title="Constant Size (100000) - Insertion Index (random - with list optimization)"
        )
    elif sys.argv[1] == '6':
        plot_csv(
            src="data/test6_results.csv",
            dest="test6_results.png",
            xlabel="Sample",
            ylabel="Time (s)",
            title="Constant Size (100000) - Random Element (with Binary Search Insert for Array)"
        )

if __name__=="__main__":
    main()  