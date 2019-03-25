HEADERS = Graph.h Matrix.h
OBJECTS = PA3.o Graph.o Matrix.o
EXEC = CS216PA3

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