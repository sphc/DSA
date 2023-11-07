CC = g++
include_dir = include
src_dir = src
src_files = $(wildcard $(src_dir)/*.cpp)
obj_dir = obj
obj_files = $(patsubst %.cpp, $(obj_dir)/%.o, $(notdir $(src_files)))
exe_dir = exe
exe_files = $(patsubst %.cpp, $(exe_dir)/%, $(notdir $(src_files)))
boost_include = /home/sphc/cpp_soft/boost_1_81_0
boost_lib = /home/sphc/cpp_soft/boost_1_81_0/stage/lib
CXXFLAGS = -Wall -std=c++17 -I$(include_dir) -I$(boost_include) -L$(boost_lib)
.PRECIOUS: $(obj_dir)/%.o

release: all
.PHONY: release

debug: CXXFLAGS += -DDEBUG -g -fsanitize=address
debug: all
.PHONY: debug

all: $(exe_files)
.PHONY: all


$(exe_dir)/%: $(obj_dir)/%.o $(exe_dir)
	$(CC) $(CXXFLAGS) $< -o $@

$(obj_dir)/%.o: $(src_dir)/%.cpp $(obj_dir)
	$(CC) $(CXXFLAGS) -c $< -o $@

$(exe_dir):
	mkdir -p $@

$(obj_dir):
	mkdir -p $@

clean:
	rm -rf $(exe_dir) $(obj_dir)
.PHONY: clean