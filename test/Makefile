
sources := 		$(wildcard *.cpp)
#programs := 		$(sources:.cpp=)
programs := 		tests

CXXFLAGS = 		-I../src -Wall -pedantic -march=native -std=c++11 

all: 			$(programs)

$(programs):		$(sources)

clean:
			rm -f $(programs)
