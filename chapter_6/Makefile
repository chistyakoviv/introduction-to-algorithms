OUTDIR := bin
BINARIES := $(shell find -name "*.cpp")
OUT := $(patsubst ./%.cpp, $(OUTDIR)/%, $(BINARIES))
CXX := g++
CXXFLAGS := -Wall -Werror --std=c++17

.PHONY: all clean

all: $(OUT)

clean:
	rm -rf *.o $(OUTDIR)

%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(OUTDIR)/% : %.o
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $< -o $@
