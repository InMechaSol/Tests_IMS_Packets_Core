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
#include "5_IntendedUseTesting.h"


using namespace IMSPacketsAPICore;
#include "5_IntendedUseTesting.h"
using namespace IMSPacketsAPICore;

CoreTest_STDIOThread_SPD4Node::CoreTest_STDIOThread_SPD4Node() :
	Test_API_Node_Default<SPD4>(),
	ConsolePortThread(CoreTest_STDIOThread_SPD4Node::ServiceConsolePort, this) {
	;
}
void CoreTest_STDIOThread_SPD4Node::ServiceConsolePort(CoreTest_STDIOThread_SPD4Node* nodePtr)
{
	while (!nodePtr->ExitServiceThread)
	{
		if (nodePtr->PortAReady)
			nodePtr->GetConsolePort()->ServicePort();
		std::this_thread::yield();
	}
}
void CoreTest_STDIOThread_SPD4Node::Setup()
{
	PortAReady = true;
}
CoreTest_STDIOThread_SPD4Node::~CoreTest_STDIOThread_SPD4Node()
{
	PortAReady = false;
	ExitServiceThread = true;
	ConsolePortThread.~thread();
}

PolymorphicPacketPort*	CoreTest_CustomConsole_Node::GetConsolePort() { return &TestPortA; }
PolymorphicPacketPort*	CoreTest_CustomConsole_Node::getPacketPortat(int i) { return &TestPortA; };
int						CoreTest_CustomConsole_Node::getNumPacketPorts() { return 1; }

CoreTest_CustomConsole_Node::CoreTest_CustomConsole_Node() :
	CoreTest_STDIOThread_SPD4Node(),
	PortA_OutputIface(0),
	PortA_InputIface(0),
	TestPortA(0, &PortA_InputIface, &PortA_OutputIface, this, true) {
	;
}


PolymorphicPacketPort* CoreTest_Console_Node::GetConsolePort() { return &TestPortA; }
PolymorphicPacketPort* CoreTest_Console_Node::getPacketPortat(int i) { return &TestPortA; };
int						CoreTest_Console_Node::getNumPacketPorts() { return 1; }
CoreTest_Console_Node::CoreTest_Console_Node() :
	CoreTest_STDIOThread_SPD4Node(),
	TestPortA(0,&PortA_InputIface, &PortA_OutputIface, this, true),
	PortA_OutputIface(0,&std::cout),
	PortA_InputIface(0,&std::cin) {
	;
}
