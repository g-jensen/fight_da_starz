BUILD_PATH=build
DIST_PATH=dist
LIB_PATH=lib

EXEC_NAME=main
EXEC_PATH=$(DIST_PATH)/$(EXEC_NAME)

CC=gcc
CFLAGS=-Wall -I.

HEADERS=$(shell find . -maxdepth 1 -type f -name '*.h')
SRC=$(shell find . -maxdepth 1 -type f -name '*.c')
OBJ=$(patsubst %.c,$(BUILD_PATH)/%.o,$(SRC))

.PHONY: all
all: $(EXEC_PATH)

$(EXEC_PATH): $(LIB_PATH) $(OBJ) | $(DIST_PATH)
	$(CC) -o $@ $(OBJ) $(CFLAGS)

$(BUILD_PATH):
	mkdir -p $@

$(BUILD_PATH)/%.o: %.c $(HEADERS) | $(BUILD_PATH)
	$(CC) -c -o $@ $< $(CFLAGS)

$(DIST_PATH):
	mkdir -p $@

.PHONY: clean
clean:
	rm -rf $(BUILD_PATH)

.PHONY: clean-dist
clean-dist:
	rm -rf $(DIST_PATH)

.PHONY: clean-lib
clean-lib:
	rm -rf $(LIB_PATH)

.PHONY: clean-all
clean-all: clean clean-dist clean-lib