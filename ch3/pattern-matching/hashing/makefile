CXX = g++
# put -D <name> to define preprocessor macros
CXXFLAGS = -g -Wall -std=c++11 -MMD 
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}
# put your objects here 
OBJS = main.o
DEPENDS = ${OBJS:.o=.d}
EXEC = a.out

.PHONY : clean

${EXEC}: ${OBJS}
	${CXX} ${CXXFLAGS} $^ -o ${EXEC}

${OBJS} : ${MAKEFILE_NAME}

-include ${DEPENDS}

clean:
	${RM} ${EXEC} ${OBJS} ${DEPENDS}
