CC = g++
CFLAGS = -g
DEPS = Value.h Operator.h Plus.h Sub.h Multiply.h Constant.h
OBJ = main.o Operator.o
%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	g++ -o $@ $^ $(CFLAGS)

clean:
	rm main *.o 
