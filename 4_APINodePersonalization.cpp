#include "3_APINodeLink.h"

using namespace IMSPacketsAPICore;

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
template<class TokenType>
class Test_API_Node_Default : public API_NODE
{
public:
	Test_API_Node_Default() :API_NODE() { ; }
protected:

	void	CustomLoop() { ; }

	void	Handler_VERSION(pCLASS(VERSION)* inPack) 
	{ 
		API_NODE::VERSION_Handler_template<TokenType>(inPack, this);
	}
	bool	Packager_VERSION(pCLASS(VERSION)* outPack)
	{ 
		return API_NODE::VERSION_Packager_template<TokenType>(outPack, this, API_NODE::ECOSYSTEM_MajorVersion, API_NODE::ECOSYSTEM_MinorVersion, API_NODE::ECOSYSTEM_BuildNumber, !ECOSYSTEM_isReleaseBuild);
	}


	bool	API_CustomShared_PrepareTx(Packet* TxPackOutPtr) { return false; }  
	void	API_CustomShared_HandleRx(Packet* RxPackInPtr) { ; }

};

// define interface functions (*link the stream)
class Test_std_cin_Interface :public PacketInterface_ASCII
{
public:
	Test_std_cin_Interface(std::istream* ifaceInStreamPtrIn = nullptr) :
		PacketInterface_ASCII(ifaceInStreamPtrIn) { 
		BufferPacket.setCharsBuffer(&(TokenBuffer.chars[0])); 
	}
	void CustomReadFrom()
	{
		ReadFromStream_ASCII(this, &std::cin);
	}
	bool DeSerializePacket() 
	{ 
		return DeSerializePacket_ASCII(this);
	}
};

class Test_std_cout_Interface :public PacketInterface_ASCII
{
public:
	Test_std_cout_Interface(std::ostream* ifaceOutStreamPtrIn = nullptr) :
		PacketInterface_ASCII(ifaceOutStreamPtrIn) {
		BufferPacket.setCharsBuffer(&(TokenBuffer.chars[0]));
	}
	void CustomWriteTo()
	{
		WriteToStream_ASCII(this, &std::cout);
	}
	bool SerializePacket() 
	{ 
		return SerializePacket_ASCII(this); 
	}
};


/*! @}*/