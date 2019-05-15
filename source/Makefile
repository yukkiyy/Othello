CXX = g++-5
CXXFLAGS = -g -std=c++14 -Wall -MMD
#CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = a4q5
OBJECTS = main.o window.o cell.o grid.o textdisplay.o graphicsdisplay.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
