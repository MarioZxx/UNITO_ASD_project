all: merge_binary

merge_binary: main.o merge_binary.o order_array.o
	gcc -o merge_bin_ins main.o merge_binary.o order_array.o
  
%.o: %.c
	gcc -c $<
  
clean:
	rm -f *.o 
