.PHONY: all clean unit func gen_gcov

# Compiler
CC := gcc

# Compilation flags
CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wvla \
-Wextra -Wcast-align -Wcast-qual \
-Wconversion -Wenum-compare -Wfloat-equal -Wredundant-decls -Wsign-conversion

# Check util flags
CHECK_FLAGS := -lcheck -lpthread -lrt

# Files
SRCS := $(wildcard src/*.c)
UNITS := $(wildcard unit_tests/*.c)

DEBUG_FLAGS := -g -O0

GCOV_FLAGS := $(DEBUG_FLAGS) --coverage

ADD_0BJECT_FLAGS :=
ADD_LINK_FLAGS :=

ifeq ($(debug), yes)
	# Debug flags
	ADD_LINK_FLAGS += $(DEBUG_FLAGS)
endif

#only for unit
ifeq ($(valgrind), yes)
	ADD_0BJECT_FLAGS += $(DEBUG_FLAGS)
	# Debug flags
	ADD_LINK_FLAGS += $(DEBUG_FLAGS)

	# Valgrind flags
	VALGRIND_CALL := valgrind --leak-check=yes --log-file=valgrind_log.txt
endif

ifeq ($(gcov), yes)
	# Debug flags
	ADD_LINK_FLAGS += $(DEBUG_FLAGS)
	ADD_LINK_FLAGS += $(GCOV_FLAGS)

	ADD_0BJECT_FLAGS += $(GCOV_FLAGS)
endif

all: app.exe unit_tests.exe

app.exe: $(SRCS:%.c=out/%.o)
	$(CC) -o $@ $^ $(DEBUG_FLAGS) $(ADD_LINK_FLAGS)

unit_tests.exe: $(filter-out out/src/main.o,$(SRCS:%.c=out/%.o)) \
	$(UNITS:%.c=out/%.o)
	$(CC) -o $@ $^ $(CHECK_FLAGS) $(ADD_LINK_FLAGS)

out/src/%.o: src/%.c
	@mkdir -p out/src
	$(CC) $(CFLAGS) -o $@ -c $< $(ADD_0BJECT_FLAGS)

out/unit_tests/%.o: unit_tests/%.c
	@mkdir -p out/unit_tests
	$(CC) $(CFLAGS) -o $@ -c $< $(ADD_0BJECT_FLAGS)

out/src/%.d: src/%.c
	@mkdir -p out/src
	$(CC) -MM $< | sed '1s/^/out\/src\//' > $@

out/unit_tests/%.d: unit_tests/%.c
	@mkdir -p out/unit_tests
	$(CC) -MM $< | sed '1s/^/out\/unit_tests\//' > $@

unit: unit_tests.exe
	$(VALGRIND_CALL) ./unit_tests.exe

func: app.exe
	cd func_tests; ./test.sh

gen_gcov:
	gcov $(addprefix out/src/, $(notdir $(SRCS)))
	@mkdir -p gcov
	mv *.c.gcov gcov/

include $(SRCS:%.c=out/%.d)

include $(UNITS:%.c=out/%.d)

clean:
	rm -rf out/
	rm -f app.exe unit_tests.exe
	rm -rf func_tests/res/
	rm -rf gcov/
