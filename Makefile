PROJECT = cpy
SRC = $(PROJECT).c

# prefer no edits below
TARGET = bin/$(PROJECT)
CFLAGS = -Wall -Wextra -g

all: $(TARGET)

$(TARGET): $(SRC)
	mkdir -p bin
	gcc $(CFLAGS) $^ -o $@

clean:
	rm -rf bin
