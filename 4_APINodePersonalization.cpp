#include "4_APINodePersonalization.h"

using namespace IMSPacketsAPICore;

template class Test_API_Node_Default<SPD1>;
template class Test_API_Node_Default<SPD2>;
template class Test_API_Node_Default<SPD4>;
template class Test_API_Node_Default<SPD8>;

template<class TokenType>
Test_API_Node_Default<TokenType>::Test_API_Node_Default() :API_NODE() { ; }

template<class TokenType>
void	Test_API_Node_Default<TokenType>::CustomLoop() { ; }

template<class TokenType>
void	Test_API_Node_Default<TokenType>::Handler_VERSION(pCLASS(VERSION)* inPack)
{
	API_NODE::staticHandler_VERSION<TokenType>(inPack, this);
}

template<class TokenType>
bool	Test_API_Node_Default<TokenType>::Packager_VERSION(pCLASS(VERSION)* outPack)
{
	struct pSTRUCT(VERSION) theEcoSysVersion;
	theEcoSysVersion.Major = ECOSYSTEM_MajorVersion;
	theEcoSysVersion.Minor = ECOSYSTEM_MinorVersion;
	theEcoSysVersion.Build = ECOSYSTEM_BuildNumber;
	theEcoSysVersion.DevFlag = !ECOSYSTEM_isReleaseBuild;
	return API_NODE::staticPackager_VERSION<TokenType>(outPack, this, &theEcoSysVersion);
}
template<class TokenType>
bool	Test_API_Node_Default<TokenType>::API_CustomShared_PrepareTx(Packet* TxPackOutPtr) { return false; }

template<class TokenType>
void	Test_API_Node_Default<TokenType>::API_CustomShared_HandleRx(Packet* RxPackInPtr) { ; }

Test_std_cin_Interface::Test_std_cin_Interface(int PortIDin, std::istream* ifaceInStreamPtrIn) :
	PacketInterface_ASCII(PortIDin, ifaceInStreamPtrIn) {
	BufferPacket.setCharsBuffer(&(TokenBuffer.chars[0]));
}
void Test_std_cin_Interface::CustomReadFrom()
{
	ReadFromStream_ASCII(this, &std::cin);
}
bool Test_std_cin_Interface::DeSerializePacket()
{
	return DeSerializePacket_ASCII(this);
}

Test_std_cout_Interface::Test_std_cout_Interface(int PortIDin, std::ostream* ifaceOutStreamPtrIn) :
	PacketInterface_ASCII(PortIDin, ifaceOutStreamPtrIn) {
	BufferPacket.setCharsBuffer(&(TokenBuffer.chars[0]));
}
void Test_std_cout_Interface::CustomWriteTo()
{
	WriteToStream_ASCII(this, &std::cout);
}
bool Test_std_cout_Interface::SerializePacket()
{
	return SerializePacket_ASCII(this);
}