proj6: proj6Base.o Island.o
	   g++ -o proj6 proj6Base.o Island.o
	   
proj6Base.o: proj6Base.cpp Island.h
		g++ -c proj6Base.cpp
		
Island.o: Island.cpp Island.h
		g++ -c Island.cpp
		
clean:
	rm proj6*.o proj6
	
