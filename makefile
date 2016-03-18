CC = g++ -std=c++11 -pthread
TARGETS = t_net.a t_thread.a
t_net.a:t_net.o net.o
	$(CC) -o t_net.a t_net.o net.o
t_net.o:t_net.cpp
	$(CC) -c -o t_net.o t_net.cpp
net.o:net.hpp net.cpp
	$(CC) -c -o net.o net.cpp

# test thread 
t_thread.a:t_thread.o
	$(CC) -o t_thread.a t_thread.o
t_thread.o:t_thread.cpp
	$(CC) -c -o t_thread.o t_thread.cpp

clean:
	-rm $(TARGETS)
	-rm *.o

run:
	./t_net.a
test:
	./t_thread.a

