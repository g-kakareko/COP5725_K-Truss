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