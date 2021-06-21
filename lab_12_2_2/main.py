from application import *
from libarr import *

def main():
    lib = Libarr()
    
    root = tk.Tk()
    app = Application(root, lib)
    root.mainloop()

if __name__ == "__main__":
    main()
