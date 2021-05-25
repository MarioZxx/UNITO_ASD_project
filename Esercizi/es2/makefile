CFLAGS 		= -g -Wall -Wextra -Wpedantic -Wconversion
COMMON_DEPS 	= src/*.h makefile

all: ./edit_distance ./edit_distance_tests

./edit_distance: src/main.o src/edit_distance.o $(COMMON_DEPS)
	gcc -o ./client src/main.o src/edit_distance.o
	
./edit_distance_tests: src/edit_distance_tests.o src/edit_distance.o src/unity.o $(COMMON_DEPS)
	gcc -o ./edit_distance_tests src/edit_distance_tests.o src/edit_distance.o src/unity.o
	 
src/%.o: src/%.c $(COMMON_DEPS)
	gcc $(CFLAGS) -c $< -o $@
  
tests: 
	./edit_distance_tests
  
clean:
	$(RM) src/*.o
	
