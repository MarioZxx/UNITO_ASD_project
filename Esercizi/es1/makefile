CFLAGS 		= -g -O1 -Wall -Wextra -Wpedantic -Wconversion
COMMON_DEPS 	= src/mergebinary/*.h src/unity/*.h makefile

all: mkdir bin/merge_binary bin/merge_bin_tests

mkdir:
	mkdir build
	mkdir bin

bin/merge_binary: build/main.o build/merge_binary.o build/sorting_array.o $(COMMON_DEPS)
	gcc -o bin/client build/main.o build/merge_binary.o build/sorting_array.o
	
bin/merge_bin_tests: build/merge_bin_tests.o build/merge_binary.o build/sorting_array.o build/unity.o $(COMMON_DEPS)
	gcc -o bin/merge_bin_tests build/merge_bin_tests.o build/merge_binary.o build/sorting_array.o build/unity.o
  
build/main.o: src/mains/main.c $(COMMON_DEPS)
	gcc $(CFLAGS) -c $< -o $@
	
build/merge_binary.o: src/mergebinary/merge_binary.c $(COMMON_DEPS)
	gcc $(CFLAGS) -c $< -o $@
	
build/sorting_array.o: src/mergebinary/sorting_array.c $(COMMON_DEPS)
	gcc $(CFLAGS) -c $< -o $@
	
build/merge_bin_tests.o: src/mains/merge_bin_tests.c $(COMMON_DEPS)
	gcc $(CFLAGS) -c $< -o $@
	
build/unity.o: src/unity/unity.c $(COMMON_DEPS)
	gcc $(CFLAGS) -c $< -o $@
  
tests: 
	bin/merge_bin_tests
  
clean:
	$(RM) build/*
	$(RM) bin/*
	rmdir build
	rmdir bin
	
