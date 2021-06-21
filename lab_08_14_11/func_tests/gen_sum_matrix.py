import numpy

DIR = "../unit_tests/files/matrix_methods/"
DIR = "./"

FILENAME_BASE = "neg_42"

FILENAME_F = DIR + FILENAME_BASE + "_f.txt"
FILENAME_S = DIR + FILENAME_BASE + "_s.txt"
FILENAME_SUM = DIR + FILENAME_BASE + "_out.txt"

ROW_COUNT = 14
COL_COUNT = 7

def matrix_to_file(filename, matrix, tol=5):
    with open(filename, "w") as file:
        file.write("%d %d\n" % (matrix.shape[0], matrix.shape[1]))
        for i in range(matrix.shape[0]):
            for j in range(matrix.shape[1]):
                file.write(("%."+str(tol)+"lf ") % matrix[i][j])
            file.write("\n");

def main():
    matrix_f = numpy.random.rand(ROW_COUNT, COL_COUNT)
    matrix_s = numpy.random.rand(ROW_COUNT, COL_COUNT)

    matrix_sum = matrix_f + matrix_s

    matrix_to_file(FILENAME_F, matrix_f, tol = 15)
    matrix_to_file(FILENAME_S, matrix_s, tol = 15)
    matrix_to_file(FILENAME_SUM, matrix_sum, tol = 5)

if __name__ == "__main__":
    main()
