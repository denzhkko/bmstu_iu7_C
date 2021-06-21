import numpy

DIR = "../unit_tests/files/matrix_methods/"
DIR = "./"

FILENAME_BASE = "neg_42"

FILENAME_IN = DIR + FILENAME_BASE + "_f.txt"
FILENAME_OUT = DIR + FILENAME_BASE + "_out.txt"

ROW_COUNT = 10
COL_COUNT = ROW_COUNT

def matrix_to_file(filename, matrix, tol=5):
    with open(filename, "w") as file:
        file.write("%d %d\n" % (matrix.shape[0], matrix.shape[1]))
        for i in range(matrix.shape[0]):
            for j in range(matrix.shape[1]):
                file.write(("%."+str(tol)+"lf ") % matrix[i][j])
            file.write("\n");

def main():
    matrix_in = numpy.random.rand(ROW_COUNT, COL_COUNT)
    matrix_out = numpy.linalg.inv(matrix_in)

    matrix_to_file(FILENAME_IN, matrix_in, tol = 15)
    matrix_to_file(FILENAME_OUT, matrix_out, tol = 5)

if __name__ == "__main__":
    main()
