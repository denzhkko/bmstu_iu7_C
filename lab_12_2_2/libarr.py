import ctypes

LIB_PATH = "./out/libarr.so"

class Libarr:
    def __init__(self):
        self.lib = ctypes.CDLL(LIB_PATH)

        # void array_fill_fib(int *arr, int arr_len)
        self._array_fill_fib = self.lib.array_fill_fib
        self._array_fill_fib.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_int)
        self._array_fill_fib.restype = None

        # int array_cp_uniq_len(int *arr, int arr_len);
        self._array_cp_uniq_len = self.lib.array_cp_uniq_len
        self._array_cp_uniq_len.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_int)
        self._array_cp_uniq_len.restype = ctypes.c_int

        # void array_cp_uniq(int *arr, int arr_len, int *arr_uniq, int *arr_uniq_len)
        self._array_cp_uniq = self.lib.array_cp_uniq
        self._array_cp_uniq.argtypes = (
                ctypes.POINTER(ctypes.c_int),
                ctypes.c_int,
                ctypes.POINTER(ctypes.c_int),
                ctypes.POINTER(ctypes.c_int)
            )
        self._array_cp_uniq.restype = None

    # void array_fill_fib(int *arr, int arr_len)
    def array_fill_fib(self, arr_len):
        arr = (ctypes.c_int * arr_len)()
        self._array_fill_fib(arr, arr_len)
        return list(arr)

    # int array_cp_uniq_len(int *arr, int arr_len);
    def array_cp_uniq_len(self, arr):
        arr_len = len(arr)
        arr = (ctypes.c_int * arr_len)(*arr)

        return self._array_cp_uniq_len(arr, arr_len)

    # void array_cp_uniq(int *arr, int arr_len, int *arr_uniq, int *arr_uniq_len)
    def array_cp_uniq(self, arr, uniq_arr_len):
        arr_len = len(arr)
        arr = (ctypes.c_int * arr_len)(*arr)
        uniq_arr = (ctypes.c_int * uniq_arr_len)()
        uniq_arr_len = ctypes.c_int()

        self._array_cp_uniq(arr, arr_len, uniq_arr, uniq_arr_len)

        return list(uniq_arr), uniq_arr_len.value

    def array_cp_uniq_by_max(self, arr):
        return self.array_cp_uniq(arr, len(arr))

    def array_cp_uniq_by_count(self, arr):
        return self.array_cp_uniq(arr, self.array_cp_uniq_len(arr))


if __name__ == "__main__":
    print("This is package file")
