CC=gcc
CFLAGS=-I$(INC_DIR)
TARGET=program
# Directories
INC_DIR = ./include
SRC_DIR = ./src
OBJ_DIR = ./build

LIBS = -lm

_DEPS= load-data.h sin-amplitude.h
DEPS = $(patsubst %,$(INC_DIR)/%,$(_DEPS))

_OBJ = load-data.o test.o sin-amplitude.o
OBJ= $(patsubst %, $(OBJ_DIR)/%,$(_OBJ))


#OBJ_DIR=$(patsubst %prefix, $(OBJ_DIR)/, $(OBJ))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(OBJ_DIR)/*.o *~ core $(INC_DIR)/*~