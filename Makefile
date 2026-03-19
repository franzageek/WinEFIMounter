ARGS=-Os -m64 -std=c++23 -Wall -Wextra -pedantic -v

everything: 	clean all debug debug-static
all: 			release release-static

release: 		bin/WinEFIMounter.exe
release-static: bin/WinEFIMounter-static.exe
debug: 			bin/WinEFIMounter-debug.exe
debug-static: 	bin/WinEFIMounter-debug-static.exe

bin/WinEFIMounter.exe: src/*.cxx
	g++ src/*.cxx -o bin/WinEFIMounter.exe $(ARGS)

bin/WinEFIMounter-static.exe: src/*.cxx
	g++ src/*.cxx -o bin/WinEFIMounter-static.exe $(ARGS) --static 

bin/WinEFIMounter-debug.exe: src/*.cxx
	g++ src/*.cxx -o bin/WinEFIMounter-debug.exe $(ARGS) -g

bin/WinEFIMounter-debug-static.exe: src/*.cxx
	g++ src/*.cxx -o bin/WinEFIMounter-debug-static.exe $(ARGS) -g --static 

clean:
	rm -rf bin/*

help:
	@echo "Available targets:"
	@echo ""
	@echo "everything: generate release & debug static & dynamic executables"
	@echo "all: generate both a dynamically & a statically compiled release executable."
	@echo "release: generate a dynamically compiled executable."
	@echo "release-static: generate a statically compiled executable."
	@echo "debug: generate a dynamic executable with debug symbols."
	@echo "debug-static: generate a static executable with debug symbols."
	@echo "clean: clean up old files."
	@echo "help: i think you've already figured this out."
	@echo ""
	@echo "Generated executables will be placed inside of the 'bin/' folder."