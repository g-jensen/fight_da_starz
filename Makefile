SRC_PATH=src
BUILD_PATH=build
DIST_PATH=dist

DEV_BUILD_PATH=$(BUILD_PATH)/dev
PROD_BUILD_PATH=$(BUILD_PATH)/prod

DEV_EXEC=$(DIST_PATH)/dev
PROD_EXEC=$(DIST_PATH)/prod

CC=gcc
CFLAGS=-lm -Wall -Wextra -I.
DEV_FLAGS=-O0 -D_DEV -ggdb3
PROD_FLAGS=-O3

HEADERS := $(wildcard $(SRC_PATH)/*/*.h)
RAW_SRC := $(patsubst src/%, %, $(wildcard $(SRC_PATH)/*/*.c))

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
dev: $(DEV_EXEC)_game $(DEV_EXEC)_object_editor

.PHONY: prod
prod: $(PROD_EXEC)_game $(PROD_EXEC)_object_editor

$(DEV_EXEC)_game: $(DEV_OBJ) | $(DIST_PATH)
	$(CC) $(DEV_FLAGS) -o $@ $(filter-out $(DEV_BUILD_PATH)/object_editor/%, $(DEV_OBJ)) $(CFLAGS)

$(DEV_EXEC)_object_editor: $(DEV_OBJ) | $(DIST_PATH)
	$(CC) $(DEV_FLAGS) -o $@ $(filter-out $(DEV_BUILD_PATH)/game/%, $(DEV_OBJ)) $(CFLAGS)

$(PROD_EXEC)_game: $(PROD_OBJ) | $(DIST_PATH)
	$(CC) $(PROD_FLAGS) -o $@ $(filter-out $(PROD_BUILD_PATH)/object_editor/%, $(PROD_OBJ)) $(CFLAGS)

$(PROD_EXEC)_object_editor: $(PROD_OBJ) | $(DIST_PATH)
	$(CC) $(PROD_FLAGS) -o $@ $(filter-out $(PROD_BUILD_PATH)/game/%, $(PROD_OBJ)) $(CFLAGS)

$(DIST_PATH):
	$(call MKDIR,$@)

$(DEV_BUILD_PATH)/%.o: $(SRC_PATH)/%.c $(HEADERS) | $(DEV_BUILD_PATH)
	$(CC) $(DEV_FLAGS) -c -o $@ $< $(CFLAGS)

$(DEV_BUILD_PATH):
	$(call MKDIR,$@)
	$(call MKDIR,$@/game)
	$(call MKDIR,$@/object_editor)
	$(call MKDIR,$@/shared)

$(PROD_BUILD_PATH)/%.o: $(SRC_PATH)/%.c $(HEADERS) | $(PROD_BUILD_PATH)
	$(CC) $(PROD_FLAGS) -c -o $@ $< $(CFLAGS)

$(PROD_BUILD_PATH):
	$(call MKDIR,$@)
	$(call MKDIR,$@/game)
	$(call MKDIR,$@/object_editor)
	$(call MKDIR,$@/shared)

.PHONY: clean
clean:
	rm -rf $(BUILD_PATH)