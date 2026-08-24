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

LIBUIOHOOK_PATH=$(LIB_PATH)/libuiohook/dist/lib
LIBS_PATH=-L$(LIBUIOHOOK_PATH) -Wl,-rpath=$(LIBUIOHOOK_PATH)
LIBS=-luiohook

.PHONY: all
all: $(EXEC_PATH)

$(EXEC_PATH): $(LIB_PATH) $(OBJ) | $(DIST_PATH)
	$(CC) $(LIBS_PATH) -o $@ $(OBJ) $(CFLAGS) $(LIBS)

$(LIB_PATH): $(LIB_PATH)/libuiohook

$(LIB_PATH)/libuiohook:
	git clone https://github.com/kwhat/libuiohook.git $@; \
	cd $@; \
	mkdir build && cd build; \
	cmake -S .. -D BUILD_SHARED_LIBS=ON -D BUILD_DEMO=ON -DCMAKE_INSTALL_PREFIX=../dist; \
	cmake --build . --parallel 2 --target install

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