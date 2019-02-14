HEADERS = Graph.h Matrix.h
OBJECTS = Lab11.o Graph.o Matrix.o
DEMO_OBJECTS = Lab11Demo.o Graph.o Matrix.o
EXEC = Lab11
DEMO_EXEC = Lab11Demo

#build executable program
$(EXEC): $(OBJECTS)
	g++ $^ -o $@
#build testing target for demonstration
$(DEMO_EXEC): $(DEMO_OBJECTS)
	g++ $^ -o $@
#build objective files from source files
%.o: %.cpp $(HEADERS)
	g++ -c $< -o $@
#clean up the mess
clean:
	rm -i `find ./ -type f -executable`
	rm -i *.o

