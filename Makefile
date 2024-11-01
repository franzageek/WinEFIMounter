ARGS=-Os -std=c++23 -Wall -Wextra -pedantic -v

all: default static

default: bin/WinEFIMounter.exe

static: bin/WinEFIMounter-static.exe

debug: src/*.cxx
	g++ src/*.cxx -o bin/WinEFIMounter.exe $(ARGS) -g -ggdb

bin/WinEFIMounter.exe: src/*.cxx
	g++ src/*.cxx -o bin/WinEFIMounter.exe $(ARGS)

bin/WinEFIMounter-static.exe: src/*.cxx
	g++ src/*.cxx -o bin/WinEFIMounter-static.exe $(ARGS) --static 

clean:
	rm -rf bin/*

help:
	@echo "Available targets:"
	@echo ""
	@echo "all: generate both a dynamically & a statically compiled executable."
	@echo "default: generate a dynamically compiled executable only."
	@echo "static: generate a statically compiled executable only."
	@echo "debug: include debug symbols for GDB (dyn exec only)."
	@echo "clean: clean up old files."
	@echo "help: i think you've already figured this out."
	@echo ""
	@echo "Generated executables will be placed inside of the 'bin/' folder."