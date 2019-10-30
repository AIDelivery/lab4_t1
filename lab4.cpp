#include <iostream>
#include <unistd.h>
#include <pthread.h>

void* my_foo(void * d) {
	sleep(1);
	std::cout << "READY" << std::endl;
	pthread_exit(0);
}

int main(int argv, char* argc[]) {
	int n = 10;
	void* data = NULL;
	pthread_t* thread = new pthread_t[n];
	
	for(int i = 0; i < n; ++i) {
		pthread_create(&thread[i], NULL, my_foo, data);
		pthread_join(thread[i], NULL);
	}
	
	return 0;
}
