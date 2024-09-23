gcc src/main.c -o src/avl
./src/avl $1
python3 data/plot_csv.py $1