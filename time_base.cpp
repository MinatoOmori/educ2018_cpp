#include <iostream>
#include <random>
#include <string.h>

using namespace std;

int numberofServers = 2;
double now = 0.0;

class Server
{
	private:
		char name[2];
		double minTime = 0.5;
		double maxTime = 1.0;
	public:
		Server(const char* inname);
		double endTime = 0;	
		double getEndTime(const char* inlabel);
};

Server::Server(const char* inname)
{
	strcpy(name, inname);
};

class Request
{
	public:
		Request();
		char label[2];
		double arrivalInterval;
		bool isRejected;
};

Request::Request()
{
	random_device seed_gen;
	mt19937 engine1(seed_gen());

	uniform_int_distribution<> dice(0, numberofServers);
	
	//request labels are random.
	
	switch (dice(engine1))
	{
		case 0:
			strcpy(label, "A");
			break;
		case 1:
			strcpy(label, "B");
			break;
	}

	// requests arrive in exponential distribution.
	//
	mt19937 engine2(seed_gen());

	exponential_distribution<> exp (1.0);
	arrivalInterval = exp(engine2);

};

double Server::getEndTime(const char* inlabel)
{
	if(strcasecmp(name, inlabel) != 0)
	{
		return now + maxTime;
	}
	else
	{
		return now + minTime;
	}
};

int main()
{
	//initialize servers and requests.
	Server serverA("a");
	Server serverB("b");
	
	int numberofRequests = 10000;
	
	Request *request = new Request[numberofRequests];

	int counter = 0;
	int reject = 0;

	while (counter < numberofRequests)
	{
		Server* selectedServer;
		switch (counter % numberofServers)
		{
			case 0:
				selectedServer = &serverA;
				break;
			case 1:
				selectedServer = &serverB;
				break;
		}

		if (now >= selectedServer->endTime)
		{
			request[counter].isRejected = false;
			now += request[counter].arrivalInterval;
			selectedServer->endTime = selectedServer->getEndTime(request[counter].label);
		}
		else
		{
			request[counter].isRejected = true;
			now += request[counter].arrivalInterval;
			reject++;
		}

		counter++;
	}

	cout<<"Rejected Request Rate: "<<(double)reject/numberofRequests<<endl;

	delete[] request;

	return 0;

}
