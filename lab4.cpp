#include <iostream>
#include <unistd.h>
#include <pthread.h>

void* my_foo(void * d) {
	sleep(1);
	std::cout << "READY" << std::endl;
	pthread_exit(0);
}

int main(int argv, char* argc[]) {
	void* data = NULL;
	pthread_t thread;
	
	pthread_create(&thread, NULL, my_foo, data);
	pthread_join(thread, NULL);
	return 0;
}
