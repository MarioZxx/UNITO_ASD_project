all: bin/merge_binary

bin/merge_binary: build/main.o build/merge_binary.o build/sorting_array.o
	gcc -o bin/client build/main.o build/merge_binary.o build/sorting_array.o
  
build/%.o: src/%.c
	gcc -c $< -o $@
  
clean:
	$(RM) build/*
	$(RM) bin/*
	
