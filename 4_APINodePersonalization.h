#ifndef __4_APINODEPERSONALIZATION__
#define __4_APINODEPERSONALIZATION__

#include "3_APINodeLink.h"

/*! \defgroup APINodePersonalization
	@{
*/
/*! \class Test_API_Node_Default
	\brief An Example with Default Configuration

	System developer would first define a common node language and api endpoints.
	Through Selection of Packet Port Type and Input/Output Interface Combinations,
	default features can be used to exchange packets and execute api endpoints.

	This test node is an example of enterprise level (system level) node definition
	intended to be designed and implemented by system developers.

	In particular, this node is an example with no customization, only default features.
	This test node defines the base cross-platform node structure to then
	be used to derive application nodes and define specific api endpoint functions.

*/
namespace IMSPacketsAPICore
{
	template<class TokenType>
	class Test_API_Node_Default : public API_NODE
	{
	public:
		Test_API_Node_Default();
	protected:

		void	CustomLoop();

		void	Handler_VERSION(pCLASS(VERSION)* inPack);
		bool	Packager_VERSION(pCLASS(VERSION)* outPack);


		bool	API_CustomShared_PrepareTx(Packet* TxPackOutPtr);
		void	API_CustomShared_HandleRx(Packet* RxPackInPtr);

	};

	// define interface functions (*link the stream)
	class Test_std_cin_Interface :public PacketInterface_ASCII
	{
	public:
		Test_std_cin_Interface(int PortIDin, std::istream* ifaceInStreamPtrIn = nullptr);
		void CustomReadFrom();
		bool DeSerializePacket();
	};

	class Test_std_cout_Interface :public PacketInterface_ASCII
	{
	public:
		Test_std_cout_Interface(int PortIDin, std::ostream* ifaceOutStreamPtrIn = nullptr);
		void CustomWriteTo();
		bool SerializePacket();
	};

}
/*! @}*/

#endif
