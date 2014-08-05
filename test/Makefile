
sources := 		$(wildcard *.cpp)
#programs := 		$(sources:.cpp=)
programs := 		tests

CXXFLAGS = 		-I../src -Wall -pedantic -march=native

all: 			$(programs)

$(programs):		$(sources)

clean:
			rm -f $(programs)
