CXXFLAGS = -O0 -g -std=c++17 -Wall -Wextra -Wpedantic

sort: sort.o unit.o student.o
	$(CXX) $(CXXFLAGS) -o $@ $^

sort.o: sort.cpp student.h
	$(CXX) $(CXXFLAGS) -c $<

student.o: student.cpp student.h
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f student.o sort.o sort

.PHONY: clean
