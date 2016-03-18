#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

int a = 0;
mutex m;

void callback(int f)
{
	for(int i=0; i<10; i++)
	{
		m.lock();
		a += f;
		cout<<"NUMBER: "<<a<<endl;
		m.unlock();
		this_thread::sleep_for(chrono::milliseconds(1));
	}
}

int main()
{
	thread t;
	t = thread(callback, 3);
	t.detach();
	this_thread::sleep_for(chrono::milliseconds(12));
	cout<<"EXIT FROM MAIN THREAD!"<<endl;
	return 0;
}

