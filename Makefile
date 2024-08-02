bin/WinEFIMounter.exe: src/*.cxx
	g++ src/*.cxx -o bin/WinEFIMounter.exe -Os -std=c++23 --static -Wall -Wextra -pedantic
