OUTDIR := bin
BINARIES := FindMaximumSubarray FindMaximumSubarrayNonRecursive ComplexNumberMultiplaction
OUT := $(patsubst %,$(OUTDIR)/%,$(BINARIES))
CXX := g++
CXXFLAGS := -Wall -Werror --std=c++17

.PHONY: all clean directories

all: directories $(OUT)

clean:
	rm -rf *.o bin

directories:
	mkdir $(OUTDIR)

%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(OUTDIR)/% : %.o
	$(CXX) $(CXXFLAGS) $< -o $@
