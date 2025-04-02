#include <iostream> 
/*** 
 * Hardware definitions
 */

#include "device/hackrf/Device.hpp"
#include "buffer/DoubleBuffer.hpp"

/**
 * 
 */
DoubleBuffer<int> hack1_buff;
DoubleBuffer<int> hack2_buff;

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

	hack1_buff.Make(10); 
	hack2_buff.Make(10); 



	// device::hackrf* dev1 = device::hackrf::make("0000000000000000909864c8296a21cf");
	// device::hackrf* dev2 = device::hackrf::make("0000000000000000081c69dc327b591b");

	// dev1->PrintDevInfo(); 
	// dev2->PrintDevInfo();

	//dev1->SetSRate(); 
	
	// KeyHandler key_tx; 
	// KeyHandler key_rx; 

    return EXIT_SUCCESS;
}