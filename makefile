# main: main.cpp k_truss.cpp
# 	g++ main.cpp -c -o main.exe
# clean:
# 	rm -f ./*.exe ./*.o

# CC = g++
# main: main.o k_truss.o
# 	$(CC) -o main.x main.o k_truss.o
# main.o: main.cpp
# 	$(CC) -c main.cpp
# k_truss.o: k_truss.cpp k_truss.h:
# 	$(CC) -c –Wall k_truss.cpp k_truss.h
# clean:
# 	rm -f core *.o 

# main: main.o k_truss.o
# 	g++ -o main main.o k_truss.o
# k_truss.o: k_truss.h k_truss.cpp
# 	g++ -c k_truss.cpp k_truss.hs
# main.o: main.cpp 
# 	g++ -c main.cpp
# clean:
# 	rm *.o main

CC = g++
CFLAGS = -g -Wall -std=c++11
LDFLAGS =
OBJFILES = main.o k_truss.o
TARGET = k_truss_dec
all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)
clean:
	rm -f $(OBJFILES) $(TARGET) *~