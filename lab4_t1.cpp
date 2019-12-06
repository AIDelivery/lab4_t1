#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <fstream>

using namespace std;

ifstream out_file;
char* filename;

void* divided_foo(void* f) {
	pid_t pid = getpid();
	char buff[50];

	sleep(1);
	cout << "File " << filename << " content:\n<<" << endl;

	while (out_file.read(buff, 50))
		cout << buff;

	cout << endl << ">>" << endl;

	if(rand() % 100 < 50) {
		out_file.close();
		cout << "Closing file..." << endl;
	}


	cout << endl << endl << "Scheduler type: ";
	switch(sched_getscheduler(pid)) {
		case 0: cout << "FIFO" << endl; break;
		case 1: cout << "RR" << endl; break;
		case 2: cout << "OTHER (dynamic scheduler)" << endl; break;
		default: cout << "Unknown" << endl; break;
	}

	cout << endl << "Current thread sched-policy MAX priority: " << sched_get_priority_max(sched_getscheduler(pid)) << endl;
	cout << "Current thread sched-policy MIN priority: " << sched_get_priority_min(sched_getscheduler(pid)) << endl;

	pthread_exit(0);
}


int main(int argv, char* argc[]) {
	srand(time(NULL));

	void* data = NULL;
	pthread_t* thread = new pthread_t();
	pthread_attr_t attr;

	filename = (char*) "INFO.txt";
	out_file.open(filename);

	pthread_attr_init(&attr);
	pthread_create(thread, &attr , divided_foo, &out_file);
	pthread_join(*thread , NULL);

	cout << "Current process sched-policy MAX priority: " << sched_get_priority_max(sched_getscheduler(getpid())) << endl;
	cout << "Current process sched-policy MIN priority: " << sched_get_priority_min(sched_getscheduler(getpid())) << endl;

	if(out_file.is_open()) {
		cout << "\nFile wasn't closed in thread. Closing...";
		out_file.close();
		sleep(1);
		cout << " Ready!" << endl;
	}

	return 0;
}
