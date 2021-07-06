CC = g++
OBJ = SystemCal.o
NIX = rm -f

SystemCal: $(OBJ) 
	$(CC) $(OBJ) -o SystemCal -pthread -lpthread

SystemCal.o: SystemCal.cpp
	$(CC) -c $< -lpthread -pthread

.PHONY: clean

clean:
	$(NIX)  $(OBJ)



