#pragma once

#include "hackrf.h" 

namespace device { 
    enum MODE { 
        TX,
        RX 
    };

    class hackrf { 
        public:
            explicit hackrf(); 
            ~hackrf(); 

            static hackrf* make(const char* serialPortID, enum MODE=RX);
            
            MODE GetDirection(); 

            void PrintDevInfo(); 
        protected: 
            static int API_INIT;
        
        private:
            /**
             * TODO: doc
             */
            int m_device_init;

            /**
             * TODO: doc
             */
            hackrf_device* m_dev;
            
            /**
             * TODO: doc
             */
            MODE           m_dev_direction; 

            /**
             * TODO: doc
             */
            bool           m_rstream_rx;

            /**
             * TODO: doc 
             */
            bool           m_rstream_tx;
    };

    class tx_streamer {
        private: 
            //tx_buff
    };

    class rx_streamer {
        private: 
            //rx_buff
    };
};

