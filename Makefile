CXX=g++
TXTDIR=./txt/
OBJDIR=./obj/
SRCDIR=./src/

all:my_drive clean

my_drive:$(OBJDIR)main.o $(OBJDIR)HD.o
	$(CXX) $^ -o $@

$(OBJDIR)main.o:$(SRCDIR)main.cpp $(SRCDIR)HD.cpp $(SRCDIR)HD.h
	$(CXX) $< -c -o $(OBJDIR)main.o

$(OBJDIR)HD.o:$(SRCDIR)HD.cpp $(SRCDIR)HD.h
	$(CXX) $< -c -o $(OBJDIR)HD.o

clean:
	rm $(OBJDIR)*.o
