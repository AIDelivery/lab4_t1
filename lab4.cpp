#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

using namespace std;

void* my_foo(void * d) {
	sleep(1);
	std::cout << "READY" << std::endl;
	pthread_exit(0);
}

int main(int argv, char* argc[]) {
	pid_t pid = getpid();
	void* data = NULL;
	pthread_t* thread = new pthread_t[5];
	
	sched_setparam(99);
	
	switch(sched_getscheduler(pid)) {
		case 0: cout << "FIFO" << endl; break;
		case 1: cout << "RR" << endl; break;
		case 2: cout << "OTHER (dynamic scheduler)" << endl; break;
	}
	cout << "MAX PRIORITY: " << sched_get_priority_max(sched_getscheduler(pid)) << endl;
	cout << "MIN PRIORITY: " << sched_get_priority_min(sched_getscheduler(pid)) << endl;
	
	return 0;
}
