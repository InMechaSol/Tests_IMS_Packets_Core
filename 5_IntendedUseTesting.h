#ifndef __5_INTENDEDUSETESTING__
#define __5_INTENDEDUSETESTING__

#include "4_APINodePersonalization.h"
#include <thread>


namespace IMSPacketsAPICore
{
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
		CoreTest_STDIOThread_SPD4Node();
		static void ServiceConsolePort(CoreTest_STDIOThread_SPD4Node* nodePtr);
		void Setup();
		~CoreTest_STDIOThread_SPD4Node();
	};

	// define api node with custom input/output interface instances
	class CoreTest_CustomConsole_Node :public CoreTest_STDIOThread_SPD4Node
	{
	private:
		// create custom interface instances
		Test_std_cout_Interface		PortA_OutputIface;
		Test_std_cin_Interface		PortA_InputIface;
		PolymorphicPacketPort		TestPortA;
	protected:
		PolymorphicPacketPort*	GetConsolePort();
	public:
		PolymorphicPacketPort*	getPacketPortat(int i);
		int						getNumPacketPorts();
		CoreTest_CustomConsole_Node();
	};

	// define api node with default ascii spd4 serialization to/from cout/cin
	class CoreTest_Console_Node :public CoreTest_STDIOThread_SPD4Node
	{
	private:
		// create default interface instances
		PacketInterface_ASCII			PortA_OutputIface;
		PacketInterface_ASCII			PortA_InputIface;
		PolymorphicPacketPort			TestPortA;
	protected:
		PolymorphicPacketPort* GetConsolePort();
	public:
		PolymorphicPacketPort* getPacketPortat(int i);
		int						getNumPacketPorts();
		CoreTest_Console_Node();

		

	};

	/*! @} */

}



#endif // !__5_INTENDEDUSETESTING__
