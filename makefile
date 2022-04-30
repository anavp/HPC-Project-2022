CFLAGS=-g -ggdb -O2 -Werror=implicit-function-declaration -Wl,-z,now -fstack-protector -Wall
CC=g++
EXECUTABLE=serial_wfc
${EXECUTABLE}: ${EXECUTABLE}.cpp
		$(CC) $(CFLAGS) $^ -o $(EXECUTABLE) -lm
clean: 
	rm -rf *.o *.gch $(EXECUTABLE)
leaks:
	valgrind --leak-check=full --show-reachable=yes --track-origins=yes ./mswfc firstmap.txt