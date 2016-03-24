#include "net.hpp"
#include <thread>
#include <mutex>
#include <chrono>
#include <iostream>

using namespace std;

// initialize static member
int Net::uid = 0;

Net::Net()
{
	// construct a net
	id = uid++;
	cout<<"Net Constructed #"<<id<<endl;
	// add input and output signal
	m.lock(); // in case some process try to modify the net
	mode = NetModeStatic;
	expected = current = ThreadStateDead;
	nodecap = INI_CAP;
	nodenum = 0;
	weitcap = INI_CAP;
	weitnum = 0;
	nodes = new Node[nodecap];
	lists = new List[nodecap];
	weits = new double[weitcap];
	addNode(2); // add input and output node
	nodefreenum = 0;
	weitfreenum = 0;
	nodefreecap = INI_CAP;
	weitfreecap = INI_CAP;
	nodefreeid = new int[nodefreecap];
	weitfreeid = new int[weitfreecap];
	m.unlock(); // release control right
}

Net::~Net()
{
	// destroy a net
	// kill inner working thread
	kill();
	// recycle memory
	delete [] nodes;
	delete [] lists;
	delete [] weits;
	delete [] nodefreeid;
	delete [] weitfreeid;
	// wait until thread over
	cout<<"Net Destroyed #"<<id<<endl;
}

void Net::setMode(NetMode mode)
{
	if(state!=ThreadStateDead)
	{
		cout<<"Error: mode switch not allowed when thread running"<<endl;
		return;
	}
	m.lock();
	this->mode = mode;
	m.unlock();
}

void Net::kill()
{
	m.lock();
	expected = ThreadStateDead;
	m.unlock();
	while(current!=expected)
		this_thread::sleep_for(chrono::milliseconds(10));
}

void Net::pause()
{
	m.lock();
	expected = ThreadStateSleep;
	m.unlock();
	while(current!=expected)
		this_thread::sleep_for(chrono::milliseconds(10));
}

void Net::wakeup()
{
	m.lock();
	expected = ThreadStateActive;
	m.unlock();
	while(current!=expected)
		this_thread::sleep_for(chrono::milliseconds(10));
}

void Net::addNode(int &index)
{
	if(numfreenode>0)
		index = freenodes[--numfreenode];
	else
	{
		index = numnode++;
		if(capnode<numnode)
		{
			capnode += ADD_CAP;
			int * ptr = new int[capnode];
			memcpy((char*)ptr, (char*)nodes, 
					sizeof(int)*(capnode-ADD_CAP));
			delete [] nodes;
			nodes = ptr;
		}
	}
}

void Net::addLink(int a, int b, int &index)
{
	// search 
}


