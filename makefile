executable = a.exe
src_dir =
include_dir =
exclude =
std = c++11


filter := $(foreach file, $(exclude), $(src_dir)$(file))
src_files := $(filter-out $(filter), $(wildcard $(src_dir)*.cpp))

all:
	$(CXX) -std=$(std) -Wall -I./$(include_dir) $(src_files) -o $(executable) -static

run:
	./$(executable)
