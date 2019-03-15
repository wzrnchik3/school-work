GOAL = assign3
OBJECTS = main.o hashTable.o
HEADERS = hashTable.h

$(GOAL): $(OBJECTS)
	g++ -g -Wall $^ -o $@

%o: %.cpp $(HEADERS)
	g++ -c $< -o $@

clean:
	rm -i `find ./ -type f -executable`
	rm -i *.o 

run: $(GOAL)
	./$(GOAL)
