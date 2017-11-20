#ifndef BINARY_STREAM_H
#define BINARY_STREAM_H

#include <string>

namespace BattleRoom {

    /**
     * Class for writing and reading binary streams
     */
    class BinaryStream {

        public: 

            // constructor
            BinaryStream(size_t maxSize);
            ~BinaryStream();

            // writing functions
            void writeInt(int val);
            void writeDouble(double val);
            void writeString(std::string str);

            // reading functions
            int readInt();
            double readDouble();
            std::string readString();

            /**
             * Reset the position marker to the beginning.
             */
            void reset();

            /**
             * Get the raw pointer to the buffer
             */
            char* getBuffer();

            /**
             * Get the current length of data written to the buffer
             */
            size_t getLength() const;

        private:

            // increment m_loc by by
            void incrementLoc(size_t by);

            size_t m_maxSize;
            char* m_buffer;
            size_t m_loc;

    }; // BinaryStream class
} // BattleRoom namespace
#endif // BINARY_STREAM_H
