CC = gcc

TARGET=pi

CFLAGS=-Wall -Werror
LIBS=-lgmp

all: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) -o ./bin/$(TARGET) ./src/$(TARGET).c $(LIBS)

clean:
	@rm -f ./bin/$(TARGET) 
