#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

using namespace std;

char* filename;
bool file_is_open = true;

void* divided_foo(void* f) {
	pid_t pid = getpid();

	sleep(1);
	char buff[50];
	cout << "File " << filename << " content:\n<<" << endl;

	while (fgets(buff, 50, (FILE *) f))
		cout << buff;

	cout << endl << ">>" << endl;

	if(rand() % 100 < 50) {
		//
		cout << "Luck up!" << endl;
		// FILE* f = fopen(filename, "r");
		fclose((FILE *) f);
		file_is_open = false;
	}


	cout << endl << endl << "Scheduler type: ";
	switch(sched_getscheduler(pid)) {
		case 0: cout << "FIFO" << endl; break;
		case 1: cout << "RR" << endl; break;
		case 2: cout << "OTHER (dynamic scheduler)" << endl; break;
		default: cout << "Unknown" << endl; break;
	}

	cout << endl << "Current thread MAX priority: " << sched_get_priority_max(sched_getscheduler(pid)) << endl;
	cout << "Current thread MIN priority: " << sched_get_priority_min(sched_getscheduler(pid)) << endl;

	pthread_exit(0);
}


int main(int argv, char* argc[]) {
	srand(time(NULL));

	void* data = NULL;
	pthread_t* thread = new pthread_t();
	pthread_attr_t attr;

	filename = (char*) "INFO.txt";
	FILE* f = fopen(filename, "r");
	if(f == NULL) {
			cout << "ERROR" << endl;
			return 0;
	}

	pthread_attr_init(&attr);
	pthread_create(thread, &attr , divided_foo, f);
	pthread_join(*thread , NULL);

	cout << "Current process MAX priority: " << sched_get_priority_max(sched_getscheduler(getpid())) << endl;
	cout << "Current process MIN priority: " << sched_get_priority_min(sched_getscheduler(getpid())) << endl;

	if(file_is_open) {
		cout << "File wasn't closed in thread. Closing...";
		fclose(f);
		cout << " Ready!" << endl;
	}

	return 0;
}
