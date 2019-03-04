

CC = g++
#CFLAGS=-I
FILESCPP = DirectoryCounter.cpp FileCounter.cpp FileString.cpp VecCounter.cpp main.cpp
FILESHPP = DirectoryCounter.hpp FileCounter.hpp FileString.hpp VecCounter.hpp Word.hpp
EXENAME = WordCount 
#default option
install:
	$(CC) -O1 $(FILESCPP) $(FILESHPP)
	rm -f *.gch
	mv a.out $(EXENAME)

optimized:
	$(CC) -O3 $(FILESCPP) $(FILESHPP)
	rm -f *.gch
	mv a.out $(EXENAME)

clean:
	rm -f $(EXENAME)

	
