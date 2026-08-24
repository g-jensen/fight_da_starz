BUILD_PATH=build
DIST_PATH=dist
LIB_PATH=lib
EXEC_NAME=main
CC=gcc
CFLAGS=-Wall -I.
HEADERS=$(shell find . -maxdepth 1 -type f -name '*.h')
SRC=$(shell find . -maxdepth 1 -type f -name '*.c')
OBJ=$(patsubst %.c,$(BUILD_PATH)/%.o,$(SRC))
LIBUIOHOOK_PATH=$(LIB_PATH)/libuiohook/dist/lib
LIBS_PATH=-L$(LIBUIOHOOK_PATH) -Wl,-rpath=$(LIBUIOHOOK_PATH)
LIBS=-luiohook

build: lib $(OBJ) dist-dir
	$(CC) $(LIBS_PATH) -o $(DIST_PATH)/$(EXEC_NAME) $(OBJ) $(CFLAGS) $(LIBS)

dist-dir:
	mkdir -p $(DIST_PATH)

build-dir:
	mkdir -p $(BUILD_PATH)

lib-dir:
	mkdir -p $(LIB_PATH)

$(BUILD_PATH)/%.o: %.c $(HEADERS) build-dir
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: lib
lib: lib-dir $(LIB_PATH)/libuiohook

$(LIB_PATH)/libuiohook:
	git clone https://github.com/kwhat/libuiohook.git lib/libuiohook; \
	cd lib/libuiohook; \
	mkdir build && cd build; \
	cmake -S .. -D BUILD_SHARED_LIBS=ON -D BUILD_DEMO=ON -DCMAKE_INSTALL_PREFIX=../dist; \
	cmake --build . --parallel 2 --target install

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