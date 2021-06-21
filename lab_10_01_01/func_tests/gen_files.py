import random

DIR = "./"

NUM_COUNT = 1000

FILENAME_BASE = "pos_06"

FILENAME_IN = DIR + FILENAME_BASE + "_in.txt"
FILENAME_OUT_F = DIR + FILENAME_BASE + "_out_f.txt"
FILENAME_OUT_S = DIR + FILENAME_BASE + "_out_s.txt"

def remove_duplicates(vector):
    vector_out = list()
    for value in vector:
        if (0 == len(vector_out) or vector_out[-1] != value):
            vector_out.append(value)
    return vector_out

def vector_to_file(filename, vector):
    # print(vector)
    with open(filename, "w") as file:
        for value in vector:
            file.write(("%d\n") % value)

def main():
    vector_in = [random.randint(-50, 50) for i in range(NUM_COUNT)]
    vector_out_f = vector_in.copy()
    vector_out_f.sort()
    vector_out_s = remove_duplicates(vector_out_f)
    vector_to_file(FILENAME_IN, vector_in)
    print(FILENAME_IN, "filled")
    vector_to_file(FILENAME_OUT_F, vector_out_f)
    print(FILENAME_OUT_F, "filled")
    vector_to_file(FILENAME_OUT_S, vector_out_s)
    print(FILENAME_OUT_S, "filled")

if __name__ == "__main__":
    main()
