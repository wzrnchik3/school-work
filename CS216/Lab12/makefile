HEADERS = Graph.h Matrix.h
OBJECTS = Lab12.o Graph.o Matrix.o
DEMO_OBJECTS = Lab12Demo.o Graph.o Matrix.o
EXEC = Lab12

#build executable program
$(EXEC): $(OBJECTS)
	g++ $^ -o $@
#build objective files from source files
%.o: %.cpp $(HEADERS)
	g++ -c $< -o $@
#clean up the mess
clean:
	rm -i `find ./ -type f -executable`
	rm -i *.o