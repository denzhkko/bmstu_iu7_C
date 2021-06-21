.PHONY: all, run

OBJECT_FLAGS := -std=c99 -Wall -Werror -Wpedantic -Wvla \
-Wextra -Wcast-align -Wcast-qual -Wconversion -Wenum-compare \
-Wfloat-equal -Wredundant-decls -Wsign-conversion

all: run

out/libarr.so: out/libarr.o inc/libarr.h
	@mkdir -p out/
	gcc -o $@ -shared $<

out/libarr.o: src/libarr.c
	@mkdir -p out/
	gcc $(OBJECT_FLAGS) -fPIC -c $< -o $@

run: out/libarr.so
	python3 main.py

clean:
	rm -rf out
	rm -rf __pycache__
