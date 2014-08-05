
sources := 		$(wildcard *.cpp)
programs := 		$(sources:.cpp=)

CXXFLAGS = 		-DUSE_MAIN -Wall -pedantic -march=native

all: 			$(programs)

clean:
			rm -f $(programs)
