CXX = g++
CXXFLAGS = -g -Wall -std=c++11 -MMD # -D NDEBUG
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}
OBJS = main.o alist.o
DEPENDS = ${OBJS:.o=.d}
EXEC = a.out

.PHONY : clean

${EXEC}: ${OBJS}
	${CXX} ${CXXFLAGS} $^ -o ${EXEC}

${OBJS} : ${MAKEFILE_NAME}

-include ${DEPENDS}

clean:
	${RM} ${EXEC} ${OBJS} ${DEPENDS}
