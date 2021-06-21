.PHONY: build run clean

CFLAGS := -std=c99 -Wall -Werror

build: app.exe

run: app.exe
	./app.exe

app.exe: out/main.o out/list_methods.o
	gcc $^ -o $@

out/main.o: src/main.c inc/*
	@mkdir -p out
	gcc $(CFLAGS) -c $< -o $@

out/list_methods.o: src/list_methods.c inc/*
	@mkdir -p out
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -f *.exe
	rm -rf out/
