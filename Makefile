SRC_PATH=src
BUILD_PATH=build
DIST_PATH=dist

DEV_BUILD_PATH=$(BUILD_PATH)/dev
PROD_BUILD_PATH=$(BUILD_PATH)/prod

DEV_EXEC=$(DIST_PATH)/dev
PROD_EXEC=$(DIST_PATH)/prod

CC=gcc
CFLAGS=-Wall -Wextra -I.
DEV_FLAGS=-D_DEV
PROD_FLAGS=-O3

HEADERS := $(wildcard $(SRC_PATH)/*.h)
RAW_SRC := $(notdir $(wildcard $(SRC_PATH)/*.c))

ifeq ($(OS),Windows_NT)
    SRC = $(filter-out %_posix.c, $(RAW_SRC))
    MKDIR = if not exist "$(1)" mkdir "$(1)"
else
	SRC = $(filter-out %_windows.c, $(RAW_SRC))
    MKDIR = mkdir -p "$(1)"
endif

OBJ=$(patsubst %.c,%.o,$(SRC))
DEV_OBJ=$(patsubst %,$(DEV_BUILD_PATH)/%,$(OBJ))
PROD_OBJ=$(patsubst %,$(PROD_BUILD_PATH)/%,$(OBJ))

.PHONY: dev
dev: $(DEV_EXEC)

.PHONY: prod
prod: $(PROD_EXEC)

$(DEV_EXEC): $(DEV_OBJ) | $(DIST_PATH)
	$(CC) $(DEV_FLAGS) -o $@ $(DEV_OBJ) $(CFLAGS)

$(PROD_EXEC): $(PROD_OBJ) | $(DIST_PATH)
	$(CC) $(PROD_FLAGS) -o $@ $(PROD_OBJ) $(CFLAGS)

$(DIST_PATH):
	$(call MKDIR,$@)

$(DEV_BUILD_PATH)/%.o: $(SRC_PATH)/%.c $(HEADERS) | $(DEV_BUILD_PATH)
	$(CC) $(DEV_FLAGS) -c -o $@ $< $(CFLAGS)

$(DEV_BUILD_PATH):
	$(call MKDIR,$@)

$(PROD_BUILD_PATH)/%.o: $(SRC_PATH)/%.c $(HEADERS) | $(PROD_BUILD_PATH)
	$(CC) $(PROD_FLAGS) -c -o $@ $< $(CFLAGS)

$(PROD_BUILD_PATH):
	$(call MKDIR,$@)

.PHONY: clean
clean:
	rm -rf $(BUILD_PATH)