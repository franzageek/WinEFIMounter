ARGS=-Os -std=c++23 -Wall -Wextra -pedantic -v

all: release release-static

release: src/*.cxx
	g++ src/*.cxx -o bin/WinEFIMounter.exe $(ARGS)

release-static: src/*.cxx
	g++ src/*.cxx -o bin/WinEFIMounter-static.exe $(ARGS) --static 

debug: src/*.cxx
	g++ src/*.cxx -o bin/WinEFIMounter-debug.exe $(ARGS) -g

debug-static: src/*.cxx
	g++ src/*.cxx -o bin/WinEFIMounter-debug-static.exe $(ARGS) -g --static 

clean:
	rm -rf bin/*

help:
	@echo "Available targets:"
	@echo ""
	@echo "all: generate both a dynamically & a statically compiled executable."
	@echo "release: generate a dynamically compiled executable."
	@echo "release-static: generate a statically compiled executable."
	@echo "debug: generate a dynamic executable with debug symbols."
	@echo "debug-static: generate a static executable with debug symbols."
	@echo "clean: clean up old files."
	@echo "help: i think you've already figured this out."
	@echo ""
	@echo "Generated executables will be placed inside of the 'bin/' folder."