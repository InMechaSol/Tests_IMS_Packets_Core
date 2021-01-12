// ConsoleTest_IMS_Packets_Core.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "5_IntendedUseTesting.cpp"
CoreTest_Console_Node theTestNode;
int main()
{
    theTestNode.Setup();

    while (true)
    {
        theTestNode.Loop();
        std::this_thread::yield();
    }
    
}
