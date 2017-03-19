CC = gcc -std=c99
SRCS = ./*.c
OBS = ./*.o

single_cycle: SRC
	$(CC) -o $@ $(OBS)

SRC: $(SRCS)
	$(CC) -c $(SRCS)

clean: $(OBS)
	rm -f $(OBS)  