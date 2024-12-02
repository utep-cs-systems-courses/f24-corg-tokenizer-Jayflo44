# List of object files
OBJS= history.o tokenizer.o uimain.o

# Compiler flags: -g for debugging symbols, -O3 for optimization
CFLAGS=-g -O3

# Default target to build the main program
all: uimain

# Rule to link the object files and create the executable 'uimain'
uimain: $(OBJS)
		cc -o uimain $(CFLAGS) $(OBJS)

# Separate target for running tests
test: history.o tokenizer.o tester.o
		cc -o test $(CFLAGS) history.o tokenizer.o tester.o

# Declare dependencies on the header files
history.o tokenizer.o uimain.o tester.o: tokenizer.h history.h

# Clean rule to remove generated files
clean:
		rm -f *.o uimain test

# Run the main program
run: uimain
		./uimain

# Run the tests
runtests: test
		./test
