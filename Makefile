# Usage:
# make        # compile all binary
# make clean  # remove ALL binaries and objects
# make run	  # runs the application

.PHONY = all clean

CC = gcc                        # compiler to use

all: create_bin_dir compile_binaries

create_bin_dir:
	@mkdir -p bin

compile_binaries:
	@echo "Compiling"
	@${CC} `pkg-config --cflags gtk+-3.0` main.c -o ./bin/eqns `pkg-config --libs gtk+-3.0`

clean:
	@rm -r ./bin

run:
	@./bin/eqns > log
