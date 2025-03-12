CC=gcc
CFLAGS=-Wall -Wextra
LDFLAGS=-lpthread -g -lm
SRC_FILES=src/main.c \
		  src/physics/physics.c \
		  src/rocket/rocket.c \
		  src/mathlib/src/mathlib/vec2.c

.PHONY: all clean

all: cobete cobete-tsan

cobete: $(SRC_FILES)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

cobete-tsan: $(SRC_FILES)
	clang $(CFLAGS) -o $@ $^ $(LDFLAGS) -fsanitize=thread

run:
	./cobete

run-tsan:
	./cobete-tsan

clean:
	rm -f cobete
	rm -f cobete-tsan
