CXX = g++
CXXFLAGS = -std=c++20
OBJ = ProgramArgs.o ipkcpc_main.o tcp.o udp.o connection.o

.PHONY: clean zip

ipkcpc: ${OBJ}
	${CXX} ${CXXFLAGS} -o $@ ${OBJ}

ipkcpc_main.o: ipkcpc_main.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

ProgramArgs.o: ProgramArgs.cpp ProgramArgs.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

connection.o: connection.cpp connection.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tcp.o: tcp.cpp tcp.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

udp.o: udp.cpp udp.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

zip: *.cpp *.h Makefile LICENSE README.md CHANGELOG.md images/*
	zip xstast38 $^

clean:
	rm -f ipkcpc *.o
