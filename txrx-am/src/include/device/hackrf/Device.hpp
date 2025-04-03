#pragma once

#include "hackrf.h" 
#include <thread>

namespace device { 
    enum MODE { 
        TX,
        RX 
    };

    class hackrf { 
        public:
            explicit hackrf(); 
            ~hackrf(); 

            static hackrf* Make(const char* serialPortID, enum MODE=RX);
            
            /**
             * 
             */
            bool IsConnected(); 

            /**
             * 
             */
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

    /**
     * 
     */
    class streamer { 
        public: 
            explicit streamer(); 
            ~streamer(); 


    }; 
    /**
     * 
     */
    class tx_streamer {
        public: 
            void IBuff(void* buff, size_t buff_len);

        private:
            std::thread tx_t; 
    };

    /**
     * 
     */
    class rx_streamer {
        public: 
            void OBuff(void* buff, size_t buff_len); 

        private: 
            std::thread rx_t; 
    };
};

