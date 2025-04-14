#include <iostream> 

#define	THREAD_MUTEX_TEST

#ifdef THREAD_MUTEX_TEST
	#include <mutex>
	#include <thread> 

	std::mutex m1;
	std::mutex m2;

	
	size_t 	arr1_len = 10000;
	size_t  idx_w    = 0; 
	size_t  idx_r	 = arr1_len / 2; 
	int* 	arr1 	 = new int[arr1_len];
	

	void thread_func_1();
	void thread_func_2();
#endif 

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
    signal(SIGINT, 	&signal_handler_callback);
	signal(SIGILL, 	&signal_handler_callback);
	signal(SIGFPE, 	&signal_handler_callback);
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

	#ifdef THREAD_MUTEX_TEST
		std::thread t1(thread_func_1);
	    std::thread t2(thread_func_2);

		t1.join();
		t2.join();
	#endif 

    return EXIT_SUCCESS;
}

#ifdef THREAD_MUTEX_TEST
	void thread_func_1() {
		
	}

	void thread_func_2() {

	}
#endif