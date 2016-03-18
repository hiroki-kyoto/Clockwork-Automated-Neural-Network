#ifndef NET_H
#define NET_H

#include <thread>
#include <mutex>
#include <vector>

const int INI_CAP = 100;
const int ADD_CAP = 100;

// mode of net
enum NetMode
{
	NetModeStatic = 0, // FIXED NETWORK
	NetModeSemiDynamic = 1, // FIXED STRUCTURE WITH TRAINNABLE PARAMETER
	NetModeDynamic = 2, // TRAINNABLE STRUCTURE WITH TRIANNABLE PARAMETER
};

enum ThreadState
{
	ThreadStateActive = 0, // training state
	ThreadStateDead = 1, // dead state, to be recycled
	ThreadStateSleep = 2, // sleeping state, to be activated
};

// node of net
struct Node
{
	double lv; // last value
	double cv; // current value
	double le; // last error
	double ce; // current error
};

// directional link data structure
struct Link
{
	int nid; // node index
	int wid; // weight index
	Link * next; // link followed
};

// list of link
struct List
{
	Link * head; // list first node
	Link * tail; // list last node
	int length; // list length
};

class Net
{
private:
	static int uid;
	int id;

	NetMode mode;
	ThreadState current;
	ThreadState expected;
	
	int cap; // capcity of node
	int num; // number of node
	
	Node * nodes; // nodes of net
	List * lists; // connection list of net

	int freecap; // capcity for free node
	int freenum; // number of free node

	int * freeindex; // available index of node list
	
	thread t; // thread to control net updating process
	mutex m; // mutex lock to control net updating process

public:
	Net();
	~Net();
	void setmode(NetMode mode);
	void kill(); // kill thread
	void pause(); // make thread sleep
	void wakeup(); // wake up thread
	void addNode(int &index); // index : index of node created
	void addLink(int a, int b, int &index); // link from a to b, return index
	void setWeit(int a, int b, double w); // link weight of conn from a to b
	void tickOnce(double x); // input signal x and update whole net
	void tickLoop(double x); // tick in loop til weight stable
	void driveOnce(double *x, int n); // input array signal x and update net
	void driveLoop(double *x, int n); // drive in loop til weight stable
};

#endif

