GOAL = assign2
OBJECTS = main.o tern.o
HEADERS = tern.h

$(GOAL): $(OBJECTS)
	g++ -g -Wall $^ -o $@

%o: %.cpp $(HEADERS)
	g++ -c $< -o $@

clean:
	rm -i `find ./ -type f -executable`
	rm -i *.o 

run: $(GOAL)
	./$(GOAL)

search: $(GOAL)
	./$(GOAL) 1