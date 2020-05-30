CXX = gcc
OPT = -O4
CXXFLAGS = -w

all: strassen_test.x

strassen_test.x: test.c main.c matrix.c strassen.c optimised_strassen.c
	$(CXX) $(OPT) -o $@ $^ $(CXXFLAGS)

clean:
	@rm *.x

.PHONY: clean all
