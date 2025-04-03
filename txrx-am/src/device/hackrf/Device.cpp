#include <iostream>
#include "device/hackrf/Device.hpp"

using hackrf = device::hackrf; 

int hackrf::API_INIT = 0;

hackrf::hackrf() {}

hackrf::~hackrf() {
    if (m_dev != nullptr) { 
        if ( hackrf_close(m_dev) != HACKRF_SUCCESS ) { 
            std::cerr << "hackrf_close() != HACKRF_SUCCESS\n"; 
        } 
    }
}

hackrf* hackrf::make(const char* serialPortID, enum device::MODE mode) { 
    if (API_INIT == 0) { 
        API_INIT = hackrf_init();
    }

    if (API_INIT != HACKRF_SUCCESS) {   
        std::cerr << "hackrf_init() != HACKRF_SUCCESS\n";
        return nullptr; 
    }

    hackrf* dev = new hackrf;

    dev->m_device_init = hackrf_open_by_serial(serialPortID, &dev->m_dev);  
    
    if (dev->m_device_init != HACKRF_SUCCESS) { 
        std::cerr << "hackrf_open_by_serial() != HACKRF_SUCCESS\n";
        dev->m_dev = nullptr;
        return nullptr;
    }
    
    dev->m_dev_direction = mode; 

    /**
     * DANGER: Устройство сдохнуть может!! Тольлко 0
     */
    hackrf_set_amp_enable(dev->m_dev, 0);

    return dev;
}

void hackrf::PrintDevInfo() { 
    uint8_t board_id; 

    if (hackrf_board_id_read(m_dev, &board_id) != HACKRF_SUCCESS) { 

    }

    std::cout << "Device:\n" \
        << "\tBoardID: \t" << hackrf_board_id_name(static_cast<hackrf_board_id>(board_id)) << "\n" \
        << "\tDirect: \t" << ((m_dev_direction == TX) ? "TX" : "RX") << "\n" \
        << "\n"; 
}