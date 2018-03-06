#include <iostream>
#include <random>
#include <string.h>

using namespace std;

int numberofServers = 2;
double now = 0.0;

class Server
{
	private:
		char name[];
		double minTime = 0.5;
		double maxTime = 1.0;
	public:
		Server(const char* inname);
		double endTime = 0;	
		double getEndTime(const char* inlabel);
};

Server::Server(const char* inname)
{
	//initialize Server.
	//
	strcpy(name, inname);
};

class Request
{
	public:
		Request();
		char label[];
		double arrivalInterval;
		bool isRejected;
};

Request::Request()
{
	//label Request with A or B using uniform init distribution class in std::random library.
	//generate arrivalinterval of each request using exponential distribution class in std::random library.
	//
	random_device seed_gen;
	mt19937 engine1(seed_gen());

	uniform_int_distribution<> dice(0, numberofServers - 1);
	
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

	exponential_distribution<> exp (1.0);

	//requests arrive in exponential distribution.
	
	arrivalInterval = exp(engine1);

};

double Server::getEndTime(const char* inlabel)
{
	//get completion time of the Server.
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
	//conttruct servers.
	Server serverA("a");
	Server serverB("b");
	
	int numberofRequests = 10000;
	
	//construct requests.
	Request *request = new Request[numberofRequests];

	int counter = 0;//request counter.
	int reject = 0;//rejected request counter.

	while (counter < numberofRequests)
	{
		Server* selectedServer;
		switch (counter % numberofServers)
		{
			//select the next server by round robin.
			case 0:
				selectedServer = &serverA;
				break;
			case 1:
				selectedServer = &serverB;
				break;
		}

		now += request[counter].arrivalInterval;

		if (now >= selectedServer->endTime)
		{
			//the request has arrived before the completion time.
			request[counter].isRejected = false;
			selectedServer->endTime = selectedServer->getEndTime(request[counter].label);
		}
		else
		{
			request[counter].isRejected = true;
			reject++;
		}

		counter++;
	}

	cout<<"Rejected Request Rate: "<<(double)reject/numberofRequests<<endl;

	delete[] request;

	return 0;

}
