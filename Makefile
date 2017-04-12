CFLAGS	= -Wall -Wextra -pedantic -std=c++14 
DEBUG	= -g -ggdb
PROG	= Mazer
OBJ	= grid.o main.o cell.o edge.o svgsaver.o depthfirst.o breadthfirst.o aldousbrodergenerator.o binary-file-io.o dijkstraalgorithm.o ellersgenerator.o
%.o: %.cpp
	@echo "> Compiling........"
	g++ $(CFLAGS) $(DEBUG) -c $< -o $@

all: $(OBJ)
	
	g++ -o $(PROG) $(OBJ)

clean: 
	
	rm -f $(OBJ) $(PROG)

.PHONY:prep
prep:
	
	source /opt/rh/devtoolset-4/enable
