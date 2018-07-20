
virtmem: main.o page_table.o disk.o program.o
	@gcc main.o page_table.o disk.o program.o -o virtmem
	@echo "Making virtmem..."

main.o: main.c
	@gcc -Wall -g -c main.c -o main.o
	@echo "Compiling main..."

page_table.o: page_table.c
	@gcc -Wall -g -c page_table.c -o page_table.o
	@echo "Compiling page table..."

disk.o: disk.c
	@gcc -Wall -g -c disk.c -o disk.o
	@echo "Compiling disc..."

program.o: program.c
	@gcc -Wall -g -c program.c -o program.o
	@echo "Compiling program..."


clean:
	@rm -f *.o virtmem
	@echo "Cleaning..."
