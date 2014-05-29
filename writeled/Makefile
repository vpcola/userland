OBJ = writeled.o
TARGET = writeled
LIBS=-lm


%.o: %.c 
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf $(OBJ) $(TARGET)
