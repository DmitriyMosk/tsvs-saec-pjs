#include <iostream> 

/*** 
 * Hardware definitions
 */

#include "device/hackrf/Device.hpp"
#include "buffer/double_buffer.hpp"

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

	auto rf_1 = double_buffer<int>::create(1'000'000);
	auto rf_2 = double_buffer<int>::create(1'000'000);

	if (!rf_1 || !rf_2) { 
		std::cerr << "Error Initialization buffer";
		return EXIT_FAILURE;
	}

	std::cout << "Init buffer[1]: " << rf_1->capacity() << "\n"; 
	std::cout << "Init buffer[2]: " << rf_2->capacity() << "\n";

	
	// device::hackrf* dev1 = dev::hackrf::make("0000000000000000909864c8296a21cf");
	// device::hackrf* dev2 = dev::hackrf::make("0000000000000000081c69dc327b591b");

	// dev1->PrintDevInfo(); 
	// dev2->PrintDevInfo();

	// dev1->SetSRate(); 
	
	// KeyHandler key_tx; 
	// KeyHandler key_rx; 

    return EXIT_SUCCESS;
}