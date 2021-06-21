.PHONY: build run clean

APP := app.exe

CFLAGS := -std=c99 -Wall -Werror -pedantic

build: $(APP)

$(APP): main.o matrix_method.o
	gcc -o $@ $^

%.o: %.c *.h
	gcc $(CFLAGS) -c $<

run: build
	./$(APP)

clean:
	rm -f $(APP) *.o
