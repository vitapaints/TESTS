SRC=main.cpp

INCLUDES=-I.
FLAGS=-g

GCC=g++

TEST=test

all : $(TEST) 

$(TEST):
	$(GCC) $(FLAGS) $(SRC) $(INCLUDES) -o $@

clean:
	rm -f $(TEST)
