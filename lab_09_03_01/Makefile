# No filename targets

.PHONY: all clean unit func gen_gcov


# Compiler

CC := gcc


# Flags

OBJECT_FLAGS := -std=gnu99 -Wall -Werror -Wpedantic -Wvla \
-Wextra -Wcast-align -Wcast-qual -Wconversion -Wenum-compare \
-Wfloat-equal -Wredundant-decls -Wsign-conversion

DEBUG_FLAGS := -g -O0

GCOV_FLAGS := $(DEBUG_FLAGS) --coverage

CHECK_LINK_FLAGS := -lcheck -lpthread -lrt


# Filenames

SRC_FILES := $(wildcard src/*.c)

RELEASE_OBJECT_FILES := $(SRC_FILES:src/%.c=out/release/%.o)
RELEASE_OBJECT_FILES_WITHOUT_MAIN := $(filter-out out/release/main.o, \
	$(RELEASE_OBJECT_FILES))
RELEASE_DEPENDENCE_FILES := $(SRC_FILES:src/%.c=out/release/%.d)

DEBUG_OBJECT_FILES := $(SRC_FILES:src/%.c=out/debug/%.o)
DEBUG_DEPENDENCE_FILES := $(SRC_FILES:src/%.c=out/debug/%.d)

UNIT_FILES := $(wildcard unit_tests/*.c)
UNIT_OBJECT_FILES := $(UNIT_FILES:unit_tests/%.c=out/unit/%.o)
UNIT_DEPENDENCE_FILES := $(UNIT_FILES:unit_tests/%.c=out/unit/%.d)


# Targets

all: app.exe debug_app.exe unit_tests.exe

unit: unit_tests.exe
	valgrind -q --leak-check=yes --log-file=valgrind_unit_tests.txt -- \
		./unit_tests.exe

func: debug_app.exe
	rm -f out/debug/*.gcda
	cd func_tests; ./test.sh
	@mkdir -p gcov
	gcov $(SRC_FILES) --object-directory out/debug/
	mv *.c.gcov gcov/


app.exe: $(RELEASE_OBJECT_FILES)
	$(CC) -o $@ $^ -lm

debug_app.exe: $(DEBUG_OBJECT_FILES)
	$(CC) -o $@ $^ -lm $(DEBUG_FLAGS) $(GCOV_FLAGS)

unit_tests.exe: $(RELEASE_OBJECT_FILES_WITHOUT_MAIN) $(UNIT_OBJECT_FILES)
	$(CC) -o $@ $^ $(CHECK_LINK_FLAGS) -lm


out/release/%.o: src/%.c
	@mkdir -p out/release
	$(CC) $(OBJECT_FLAGS) -o $@ -c $<

out/debug/%.o: src/%.c
	@mkdir -p out/debug/
	$(CC) $(OBJECT_FLAGS) -o $@ -c $< $(DEBUG_FLAGS) $(GCOV_FLAGS)

out/unit/%.o: unit_tests/%.c
	@mkdir -p out/unit
	$(CC) $(OBJECT_FLAGS) $(DEBUG_FLAGS) -o $@ -c $<


out/release/%.d: src/%.c
	@mkdir -p out/release
	$(CC) -MM $< | sed '1s|^|out/release/|' > $@

out/debug/%.d: src/%.c
	@mkdir -p out/debug/
	$(CC) -MM $< | sed '1s|^|out/debug/|' > $@

out/unit/%.d: unit_tests/%.c
	@mkdir -p out/unit
	$(CC) -MM $< | sed '1s|^|out/unit/|' > $@


include $(RELEASE_DEPENDENCE_FILES)

include $(DEBUG_DEPENDENCE_FILES)

include $(UNIT_DEPENDENCE_FILES)


clean:
	rm -f app.exe debug_app.exe unit_tests.exe
	rm -rf out/
	rm -rf gcov/
	rm -rf func_tests/res/
	rm -f valgrind_unit_tests.txt
