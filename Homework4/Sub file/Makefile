DFLAGS   = -DPACKAGE=\"threadsystem\" -DVERSION=\"1.0\" -DPTHREAD=1 -DUNIX_MSG_Q=1 -DSTDC_HEADERS=1
IFLAGS   = -I/local/eit-linux/apps/ThreadMentor/include
TMLIB    = /local/eit-linux/apps/ThreadMentor/NoVisual/libthreadclass.a

WARNINGS = -Wno-deprecated -Wwrite-strings

all: thread.o thread-main.o thread-support.o
	g++ ${WARNINGS} -g -o prog4 thread.o thread-main.o thread-support.o ${TMLIB} -lpthread

thread.o:
	g++ ${WARNINGS} ${DFLAGS} ${IFLAGS} -g -c thread.cpp

thread-main.o:
	g++ ${WARNINGS} ${DFLAGS} ${IFLAGS} -g -c thread-main.cpp
thread-support.o:
	g++ ${WARNINGS} ${DFLAGS} ${IFLAGS} -g -c thread-support.cpp
noVisual:thread.o thread-main.o thread-support.o 
	g++ ${WARNINGS} -g -o prog4 thread.o thread-main.o thread-support.o ${TMLIB} -lpthread
clean:
	rm thread.o thread-support.o thread-main.o prog4