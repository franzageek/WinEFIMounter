bin/WinEFIMounter.exe: src/*.cxx
	g++ src/*.cxx -o bin/WinEFIMounter.exe -Os -std=c++23 -Wall -Wextra -pedantic