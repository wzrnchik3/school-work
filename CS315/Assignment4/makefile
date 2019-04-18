GOAL = assign4
OBJECTS = main.o famTree.o
HEADERS = famTree.h

$(GOAL): $(OBJECTS)
	g++ -g -Wall $^ -o $@

%o: %.cpp $(HEADERS)
	g++ -c $< -o $@

clean:
	rm -i `find ./ -type f -executable`
	rm -i *.o 

run: $(GOAL)
	./$(GOAL)