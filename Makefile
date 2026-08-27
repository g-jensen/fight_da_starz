BUILD_PATH=build
DIST_PATH=dist

DEV_BUILD_PATH=$(BUILD_PATH)/dev
PROD_BUILD_PATH=$(BUILD_PATH)/prod

DEV_EXEC=$(DIST_PATH)/dev
PROD_EXEC=$(DIST_PATH)/prod

CC=gcc
CFLAGS=-Wall -I.
PROD_FLAGS=-O3

HEADERS=$(shell find . -maxdepth 1 -type f -name '*.h')
SRC=$(shell find . -maxdepth 1 -type f -name '*.c')
OBJ=$(patsubst %.c,%.o,$(SRC))
DEV_OBJ=$(patsubst %,$(DEV_BUILD_PATH)/%,$(OBJ))
PROD_OBJ=$(patsubst %,$(PROD_BUILD_PATH)/%,$(OBJ))

.PHONY: dev
dev: $(DEV_EXEC)

.PHONY: prod
prod: $(PROD_EXEC)

$(DEV_EXEC): $(DEV_OBJ) | $(DIST_PATH)
	$(CC) -o $@ $(DEV_OBJ) $(CFLAGS)

$(PROD_EXEC): $(PROD_OBJ) | $(DIST_PATH)
	$(CC) $(PROD_FLAGS) -o $@ $(PROD_OBJ) $(CFLAGS)

$(DIST_PATH):
	mkdir -p $@

$(DEV_BUILD_PATH)/%.o: %.c $(HEADERS) | $(DEV_BUILD_PATH)
	$(CC) -c -o $@ $< $(CFLAGS)

$(DEV_BUILD_PATH):
	mkdir -p $@

$(PROD_BUILD_PATH)/%.o: %.c $(HEADERS) | $(PROD_BUILD_PATH)
	$(CC) $(PROD_FLAGS) -c -o $@ $< $(CFLAGS)

$(PROD_BUILD_PATH):
	mkdir -p $@

.PHONY: clean
clean:
	rm -rf $(BUILD_PATH)