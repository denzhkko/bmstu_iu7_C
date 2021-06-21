import numpy

DIR = "../unit_tests/files/matrix_methods/"
DIR = "./"

FILENAME_BASE = "neg_42"

FILENAME_F = DIR + FILENAME_BASE + "_f.txt"
FILENAME_S = DIR + FILENAME_BASE + "_s.txt"
FILENAME_PRODUCT = DIR + FILENAME_BASE + "_out.txt"

FM_ROW_COUNT = 10
FM_COL_COUNT = 5
SM_ROW_COUNT = FM_COL_COUNT
SM_COL_COUNT = 12

def matrix_to_file(filename, matrix, tol=5):
    with open(filename, "w") as file:
        file.write("%d %d\n" % (matrix.shape[0], matrix.shape[1]))
        for i in range(matrix.shape[0]):
            for j in range(matrix.shape[1]):
                file.write(("%."+str(tol)+"lf ") % matrix[i][j])
            file.write("\n");

def main():
    matrix_f = numpy.random.rand(FM_ROW_COUNT, FM_COL_COUNT)
    matrix_s = numpy.random.rand(SM_ROW_COUNT, SM_COL_COUNT)

    matrix_sum = numpy.dot(matrix_f, matrix_s)

    matrix_to_file(FILENAME_F, matrix_f, tol = 15)
    matrix_to_file(FILENAME_S, matrix_s, tol = 15)
    matrix_to_file(FILENAME_PRODUCT, matrix_sum, tol = 5)

if __name__ == "__main__":
    main()
