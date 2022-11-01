CC = g++ #gcc commamd to complie
CFLAGS = -Wall -g # wall is to provide all warning// -g default debug information

INCLUDES = -I ../org/ #path from which files should include

# vpath %.cpp CppWrappers 

all: time_error

%: %.cpp | createBin
	$(CC) $(CFLAGS) $(INCLUDES) -o res/$@ $^

deps.o: 
	$(CC) $(CFLAGS) $(INCLUDES) -c $< 

createBin:
	mkdir res
	
clean:
	rm *.o