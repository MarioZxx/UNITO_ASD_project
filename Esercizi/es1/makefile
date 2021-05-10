COMMON_DEPS 	= src/*.h makefile

all: ./merge_binary ./merge_bin_tests

./merge_binary: src/main.o src/merge_binary.o src/sorting_array.o $(COMMON_DEPS)
	gcc -o ./client src/main.o src/merge_binary.o src/sorting_array.o
	
./merge_bin_tests: src/merge_bin_tests.o src/merge_binary.o src/sorting_array.o src/unity.o $(COMMON_DEPS)
	gcc -o ./merge_bin_tests src/merge_bin_tests.o src/merge_binary.o src/sorting_array.o src/unity.o
  
src/%.o: src/%.c $(COMMON_DEPS)
	gcc -c $< -o $@
  
tests: 
	./merge_bin_tests
  
clean:
	$(RM) src/*.o
	
