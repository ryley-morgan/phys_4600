CC=gcc
CFLAGS=-I$(INC_DIR)
TARGET1=max-amplitude
# Directories
INC_DIR = ./include
SRC_DIR = ./src
OBJ_DIR = ./build

LIBS = -lm

_DEPS1= data-io.h sin-amplitude.h add-noise.h filters.h
DEPS1 = $(patsubst %,$(INC_DIR)/%,$(_DEPS1))

_OBJ1 = data-io.o test.o sin-amplitude.o add-noise.o filters.o
OBJ1= $(patsubst %, $(OBJ_DIR)/%,$(_OBJ1))


#OBJ_DIR=$(patsubst %prefix, $(OBJ_DIR)/, $(OBJ))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS1)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET1): $(OBJ1)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(OBJ_DIR)/*.o *~ core $(INC_DIR)/*~