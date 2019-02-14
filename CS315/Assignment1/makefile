HEADERS = linkedList.h
OBJECTS = main.o linkedList.o
EXEC = prog1

#build executable program
$(EXEC): $(OBJECTS)
	g++ -Wall $^ -o $@
#build objective files from source files
%.o: %.cpp $(HEADERS)
	g++ -c $< -o $@
#clean up the mess
clean:
	rm -i `find ./ -type f -executable`
	rm -i *.o
#run the file
run: $(EXEC)
	./$(EXEC)