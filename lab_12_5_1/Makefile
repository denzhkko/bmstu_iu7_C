# No filename targets

.PHONY: all clean unit func gen_gcov


# Compiler

CC := gcc


# Flags

OBJECT_FLAGS := -std=c99 -Wall -Werror -Wpedantic -Wvla \
-Wextra -Wcast-align -Wcast-qual -Wconversion -Wenum-compare \
-Wfloat-equal -Wredundant-decls -Wsign-conversion

DEBUG_FLAGS := -g -O0

GCOV_FLAGS := $(DEBUG_FLAGS) --coverage

CHECK_LINK_FLAGS := -lcheck -lpthread -lrt


# Filenames

SRC_FILES := $(wildcard src/*.c)
SRC_LIBS := $(wildcard libs/*.c)

RELEASE_OBJECT_FILES := $(SRC_FILES:src/%.c=out/release/files/%.o)
RELEASE_OBJECT_FILES_WITHOUT_MAIN := $(filter-out out/release/files/main.o, \
	$(RELEASE_OBJECT_FILES))
RELEASE_STAT_LIBS := $(SRC_LIBS:libs/%.c=out/release/libs/%.a)
RELEASE_DEPENDENCE_FILES := $(SRC_FILES:src/%.c=out/release/files/%.d)
RELEASE_DEPENDENCE_LIBS := $(SRC_LIBS:libs/%.c=out/release/libs/%.d)

DEBUG_OBJECT_FILES := $(SRC_FILES:src/%.c=out/debug/files/%.o)
DEBUG_STAT_LIBS := $(SRC_LIBS:libs/%.c=out/debug/libs/%.a)
DEBUG_DEPENDENCE_FILES := $(SRC_FILES:src/%.c=out/debug/files/%.d)
DEBUG_DEPENDENCE_LIBS:= $(SRC_LIBS:libs/%.c=out/debug/libs/%.d)

UNIT_FILES := $(wildcard unit_tests/*.c)
UNIT_OBJECT_FILES := $(UNIT_FILES:unit_tests/%.c=out/unit/%.o)
UNIT_DEPENDENCE_FILES := $(UNIT_FILES:unit_tests/%.c=out/unit/%.d)

RELEASE_DIN_LIBS := $(SRC_LIBS:libs/%.c=out/release/dlibs/%.so)


# Targets

all: app.exe app_dlib.exe debug_app.exe unit_tests.exe

unit: unit_tests.exe
	valgrind -q --leak-check=yes --log-file=valgrind_unit_tests.txt -- \
		./unit_tests.exe

func: debug_app.exe
	rm -f out/debug/*.gcda
	cd func_tests; ./test.sh
	@mkdir -p gcov
	gcov $(SRC_FILES) --object-directory out/debug/files/
	gcov $(SRC_LIBS) --object-directory out/debug/libs/
	mv *.c.gcov gcov/

func_dlibs: app_dlib.exe
	cd func_tests; ./test_dlibs.sh


app.exe: $(RELEASE_OBJECT_FILES) $(RELEASE_STAT_LIBS)
	$(CC) -o $@ $^ -lm

debug_app.exe: $(DEBUG_OBJECT_FILES) $(DEBUG_STAT_LIBS)
	$(CC) -o $@ $^ -lm $(DEBUG_FLAGS) $(GCOV_FLAGS)

unit_tests.exe: $(RELEASE_OBJECT_FILES_WITHOUT_MAIN) $(RELEASE_STAT_LIBS) \
$(UNIT_OBJECT_FILES)
	$(CC) -o $@ $^ $(CHECK_LINK_FLAGS) -lm

app_dlib.exe: $(RELEASE_OBJECT_FILES) $(RELEASE_DIN_LIBS)
	$(CC) -o $@ $(RELEASE_OBJECT_FILES) -lm -L./out/release/dlibs/ -ldarr -ldarr_methods


out/release/files/%.o: src/%.c
	@mkdir -p out/release/files/
	$(CC) $(OBJECT_FLAGS) -o $@ -c $<

out/release/libs/%.o: libs/%.c
	@mkdir -p out/release/libs/
	$(CC) $(OBJECT_FLAGS) -o $@ -c $<

out/debug/files/%.o: src/%.c
	@mkdir -p out/debug/files/
	$(CC) $(OBJECT_FLAGS) -o $@ -c $< $(DEBUG_FLAGS) $(GCOV_FLAGS)

out/debug/libs/%.o: libs/%.c
	@mkdir -p out/debug/libs/
	$(CC) $(OBJECT_FLAGS) -o $@ -c $< $(DEBUG_FLAGS) $(GCOV_FLAGS)

out/unit/%.o: unit_tests/%.c
	@mkdir -p out/unit
	$(CC) $(OBJECT_FLAGS) $(DEBUG_FLAGS) -o $@ -c $<


out/release/dlibs/%.o: libs/%.c
	@mkdir -p out/release/dlibs/
	gcc $(OBJECT_FLAGS) -fPIC -c $< -o $@

out/release/dlibs/%.so: out/release/dlibs/%.o
	@mkdir -p out/release/dlibs/
	gcc -o $@ -shared $<


out/release/libs/%.a: out/release/libs/%.o
	@mkdir -p out/release/libs/
	ar rc $@ $<
	ranlib $@

out/debug/libs/%.a: out/debug/libs/%.o
	@mkdir -p out/debug/libs/
	ar rc $@ $<
	ranlib $@


out/release/files/%.d: src/%.c
	@mkdir -p out/release/files/
	$(CC) -MM $< | sed '1s|^|out/release/files/|' > $@

out/release/libs/%.d: libs/%.c
	@mkdir -p out/release/libs/
	$(CC) -MM $< | sed '1s|^|out/release/libs/|' > $@

out/debug/files/%.d: src/%.c
	@mkdir -p out/debug/files/
	$(CC) -MM $< | sed '1s|^|out/debug/files/|' > $@

out/debug/libs/%.d: libs/%.c
	@mkdir -p out/debug/libs/
	$(CC) -MM $< | sed '1s|^|out/debug/libs/|' > $@

out/unit/%.d: unit_tests/%.c
	@mkdir -p out/unit
	$(CC) -MM $< | sed '1s|^|out/unit/|' > $@


include $(RELEASE_DEPENDENCE_FILES)

include $(RELEASE_DEPENDENCE_LIBS)

include $(DEBUG_DEPENDENCE_FILES)

include $(DEBUG_DEPENDENCE_LIBS)

include $(UNIT_DEPENDENCE_FILES)


clean:
	rm -f app.exe app_dlib.exe debug_app.exe unit_tests.exe
	rm -rf out/
	rm -rf gcov/
	rm -rf func_tests/res/
	rm -f valgrind_unit_tests.txt
