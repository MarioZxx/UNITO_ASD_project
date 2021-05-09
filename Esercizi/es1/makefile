COMMON_DEPS 	= src/*.h makefile

all: bin/merge_binary bin/merge_bin_tests

bin/merge_binary: build/main.o build/merge_binary.o build/sorting_array.o $(COMMON_DEPS)
	gcc -o bin/client build/main.o build/merge_binary.o build/sorting_array.o
	
bin/merge_bin_tests: build/merge_bin_tests.o build/merge_binary.o build/sorting_array.o build/unity.o $(COMMON_DEPS)
	gcc -o bin/merge_bin_tests build/merge_bin_tests.o build/merge_binary.o build/sorting_array.o build/unity.o
  
build/%.o: src/%.c $(COMMON_DEPS)
	gcc -c $< -o $@
  
tests: 
	bin/merge_bin_tests
  
clean:
	$(RM) build/*
	$(RM) bin/*
	
