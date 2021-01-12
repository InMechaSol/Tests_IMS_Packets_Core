/*! \file  5_IntendedUseTesting.cpp
	\brief Examples of Intended Use Cases

	The IMS Packets Core is intended for use by developers of distributed
	computing systems.  It provides a base of code that can be used in a
	"default" configuration or modified easily to custom needs.

	TestSource.cpp defines cross platform reusable test objects that demonstrate
	the intended use cases (for developers) and provided testable objects to be
	instantiated on Console Applications, Unit Test Applications, and Node Firmware.

	As developments move from default to fully custom implementations, a hierarchy of
	developer types emerges.  System developers are responsible for understanding the
	communication partners within an ecosystem.  Application developers are responsible for
	understanding the application requirements of a particular node, or set of nodes,
	within an ecosystem.
	- System developers would first define a common node language and api enpoints.
	- Application developers would then define application nodes which rely on the definitions of common node language and api endpoints.

*/
#include "4_APINodePersonalization.cpp"
#include <thread>

using namespace IMSPacketsAPICore;
/*! \defgroup IntendedUseTesting
	@{
*/
class CoreTest_STDIOThread_SPD4Node : public Test_API_Node_Default<SPD4>
{
private:
	std::thread						ConsolePortThread;
	bool							ExitServiceThread = false;
	bool							PortAReady = false;
protected:
	virtual PolymorphicPacketPort* GetConsolePort() = 0;

public:
	CoreTest_STDIOThread_SPD4Node() :
		Test_API_Node_Default<SPD4>(),
		ConsolePortThread(CoreTest_STDIOThread_SPD4Node::ServiceConsolePort, this) {
		;
	}
	static void ServiceConsolePort(CoreTest_STDIOThread_SPD4Node* nodePtr)
	{
		while (!nodePtr->ExitServiceThread)
		{
			if (nodePtr->PortAReady)
				nodePtr->GetConsolePort()->ServicePort();
			std::this_thread::yield();
		}
	}
	void Setup()
	{
		PortAReady = true;
	}
	~CoreTest_STDIOThread_SPD4Node()
	{
		PortAReady = false;
		ExitServiceThread = true;
		ConsolePortThread.~thread();
	}
};

// define api node with custom input/output interface instances
class CoreTest_CustomConsole_Node :public CoreTest_STDIOThread_SPD4Node
{
protected:
	PolymorphicPacketPort*				GetConsolePort()		{ return &TestPortA; }
public:
	PolymorphicPacketPort*				getPacketPortat(int i)	{ return &TestPortA; };
	int									getNumPacketPorts()		{ return 1; }

	// create custom interface instances
	Test_std_cout_Interface		PortA_OutputIface;
	Test_std_cin_Interface		PortA_InputIface;
	PolymorphicPacketPort		TestPortA;
	

	CoreTest_CustomConsole_Node() :
		CoreTest_STDIOThread_SPD4Node(),
		PortA_OutputIface(),
		PortA_InputIface(),
		TestPortA(&PortA_InputIface, &PortA_OutputIface, this, true) {
		;
	}
	

};

// define api node with default ascii spd4 serialization to/from cout/cin
class CoreTest_Console_Node :public CoreTest_STDIOThread_SPD4Node
{
protected:
	PolymorphicPacketPort* GetConsolePort() { return &TestPortA; }

private:

	// create default interface instances
	PacketInterface_ASCII			PortA_OutputIface;
	PacketInterface_ASCII			PortA_InputIface;
	PolymorphicPacketPort			TestPortA;


public:
	CoreTest_Console_Node() :
		CoreTest_STDIOThread_SPD4Node(),
		TestPortA(&PortA_InputIface, &PortA_OutputIface, this, true),
		PortA_OutputIface(&std::cout),
		PortA_InputIface(&std::cin)	{
		;
	}

	PolymorphicPacketPort*				getPacketPortat(int i) { return &TestPortA; };
	int									getNumPacketPorts() { return 1; }

};

/*! @} */
