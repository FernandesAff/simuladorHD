CXX=g++
OBJDIR=./obj/
SRCDIR=./src/
OUTDIR=./out/

all: dir my_drive

my_drive:$(OBJDIR)main.o $(OBJDIR)HD.o
	$(CXX) $^ -o $@

$(OBJDIR)main.o:$(SRCDIR)main.cpp $(SRCDIR)HD.cpp $(SRCDIR)HD.h
	$(CXX) $< -c -o $(OBJDIR)main.o

$(OBJDIR)HD.o:$(SRCDIR)HD.cpp $(SRCDIR)HD.h
	$(CXX) $< -c -o $(OBJDIR)HD.o

dir:
	if test -d obj; then echo obj exists; else mkdir obj;fi
	if test -d out; then echo out exists; else mkdir out;fi

clean:
	rm $(OBJDIR)*.o $(OUTDIR)*.txt
