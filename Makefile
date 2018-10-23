#
all: main


main : main.cpp
	@g++ -o main -std=c++11 main.cpp 

run : main
	@echo "Running the program:"
	@./main

edit:
	@vim main.cpp

debug:
	@gdb ./main

clean :
	@rm main
