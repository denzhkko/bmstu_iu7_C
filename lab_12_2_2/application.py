import tkinter as tk

BUTTON_WIDTH = 3
BUTTON_HEIGHT = 1

def isinteger(a):
    try:
        int(a)
        return True
    except:
        return False

class Application:
    def __init__(self, root, lib):
        self.root = root
        self.lib = lib

        #entry

        self.entry = tk.Entry(
            self.root,
            width = 9,
            font = ("Helvetica", 24),
            borderwidth = 0,
            )
        self.entry.focus_set()
        self.entry.pack(fill = tk.BOTH)

        self.label = tk.Label(
            self.root,
            width = 9,
            font = ("Helvetica", 24),
            borderwidth = 0,
            )
        self.label.pack(fill = tk.BOTH)

        self.button_fib = tk.Button(
            bg = "white",
            width = BUTTON_WIDTH,
            height = BUTTON_HEIGHT,
            text = "Fib array",
            font = ("Helvetica", 24),
            command = self.on_button_fibs_clicked,
            borderwidth = 0
            )
        self.button_fib.pack(fill = tk.BOTH)

        self.button_arr_uniq = tk.Button(
            bg = "white",
            width = BUTTON_WIDTH,
            height = BUTTON_HEIGHT,
            text = "Array uniq",
            font = ("Helvetica", 24),
            command = self.on_button_arr_uniq_clicked,
            borderwidth = 0
            )
        self.button_arr_uniq.pack(fill = tk.BOTH)

    def on_button_fibs_clicked(self):
        entry_value = self.entry.get()
        if (isinteger(entry_value)):
            arr_len = int(entry_value)
            if (arr_len > 0):
                arr = self.lib.array_fill_fib(arr_len)
                self.label['text'] = str(arr)
            else:
                self.label['text'] = "Not positive num"
        else:
            self.label['text'] = "NaN"

    def on_button_arr_uniq_clicked(self):
        entry_value = self.entry.get()
        try:
            arr = list(map(int, entry_value.split()))
            uniq_arr = self.lib.array_cp_uniq_by_count(arr)[0]
            self.label['text'] = str(uniq_arr)
        except:
            self.label['text'] = "Incorrect input"

if __name__ == "__main__":
    print("This is package file")
