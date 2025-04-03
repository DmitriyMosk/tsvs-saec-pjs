#include <iostream> 
/*** 
 * Hardware definitions
 */

#include "device/hackrf/Device.hpp"
#include "buffer/DoubleBuffer.hpp"

/**
 * 
 */

/**
 * @brief Signal handler for SIGINT, SIGILL, SIGFPE, SIGSEGV, SIGTERM, and SIGABRT.
 */
void signal_handler_callback(int signal) { 
    std::cout << "Signal received: " << signal << std::endl; 
}

int main() { 
	// startup
    signal(SIGINT, &signal_handler_callback);
	signal(SIGILL, &signal_handler_callback);
	signal(SIGFPE, &signal_handler_callback);
	signal(SIGSEGV, &signal_handler_callback);
	signal(SIGTERM, &signal_handler_callback);
	signal(SIGABRT, &signal_handler_callback);

	auto rf_1 = DoubleBuffer<int>::Create(10);
	auto rf_2 = DoubleBuffer<int>::Create(10);

	// device::hackrf* dev1 = device::hackrf::Make("0000000000000000909864c8296a21cf");
	// device::hackrf* dev2 = device::hackrf::Make("0000000000000000081c69dc327b591b");


	// dev1->PrintDevInfo(); 
	// dev2->PrintDevInfo();

	//dev1->SetSRate(); 
	
	// KeyHandler key_tx; 
	// KeyHandler key_rx; 

    return EXIT_SUCCESS;
}