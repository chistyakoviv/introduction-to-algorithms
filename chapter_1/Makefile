OUTDIR := bin
BINARIES := InsertionSort
OUT := $(patsubst %,$(OUTDIR)/%,$(BINARIES))
FLAGS := -Wall -Werror

.PHONY: all clean directories

all: directories $(OUT)

clean:
	rm -rf *.o bin

directories:
	mkdir $(OUTDIR)

%.o : %.cpp
	g++ -c $(FLAGS) $< -o $@

$(OUTDIR)/% : %.o
	g++ $(FLAGS) $< -o $@