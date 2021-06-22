CFLAGS 		= -g -Wall -Wextra -Wpedantic -Wconversion
COMMON_DEPS 	= src/editdistance/*.h src/unity/*.h makefile

all: mkdir bin/edit_distance bin/edit_distance_tests

mkdir:
	mkdir build
	mkdir bin

bin/edit_distance: build/main.o build/edit_distance.o $(COMMON_DEPS)
	gcc -o bin/client build/main.o build/edit_distance.o
	
bin/edit_distance_tests: build/edit_distance_tests.o build/edit_distance.o build/unity.o $(COMMON_DEPS)
	gcc -o bin/edit_distance_tests build/edit_distance_tests.o build/edit_distance.o build/unity.o
	 
build/main.o: src/mains/main.c $(COMMON_DEPS)
	gcc $(CFLAGS) -c $< -o $@
	
build/edit_distance.o: src/editdistance/edit_distance.c $(COMMON_DEPS)
	gcc $(CFLAGS) -c $< -o $@
	
build/edit_distance_tests.o: src/mains/edit_distance_tests.c $(COMMON_DEPS)
	gcc $(CFLAGS) -c $< -o $@
	
build/unity.o: src/unity/unity.c $(COMMON_DEPS)
	gcc $(CFLAGS) -c $< -o $@
  
tests: 
	bin/edit_distance_tests
  
clean:
	$(RM) build/*
	$(RM) bin/*
	rmdir build
	rmdir bin
	$(RM) list_of_all_words.csv
	
