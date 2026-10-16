# FIGHT DA STARZ

## Build Dependencies

- gcc
- make

## Development Build

```bash
make
```
or
```bash
make dev
```

Run the dev build: `./dist/dev/game`

Or run the object editor: `./dist/dev/object_editor`

## Production Build

```bash
make prod
```

Run the prod build: `./dist/prod/game`

Or run the object editor: `./dist/prod/object_editor`


## Debugging

Basic debugging can be done with `gdb`.

Profile physical and virtual memory with `pmap`.

```bash
pmap -X <pid>
```

Trace memory allocations with `valgrind`.

```bash
valgrind --tool=massif ./dist/dev

ms_print massif.out.<pid>
```