CC = g++
include_dir = include
src_dir = src
src_files = $(wildcard $(src_dir)/*.cpp)
obj_dir = obj
obj_files = $(patsubst %.cpp, $(obj_dir)/%.o, $(notdir $(src_files)))
exe_dir = exe
exe_files = $(patsubst %.cpp, $(exe_dir)/%, $(notdir $(src_files)))
CXXFLAGS = -Wall -std=c++17 -I$(include_dir)
.PRECIOUS: $(obj_dir)/%.o

release: all
.PHONY: release

debug: CXXFLAGS += -DDEBUG -g
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