COMMON_DEPS 	= src/*.h makefile

all: ./edit_distance

./edit_distance: src/main.o src/edit_distance.o $(COMMON_DEPS)
	gcc -o ./client src/main.o src/edit_distance.o
	 
src/%.o: src/%.c $(COMMON_DEPS)
	gcc -c $< -o $@
  
  
clean:
	$(RM) src/*.o
	
