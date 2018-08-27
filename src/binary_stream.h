#ifndef BINARY_STREAM_H
#define BINARY_STREAM_H

#include "units.h"

namespace BattleRoom {

    /**
     * Class for writing and reading binary streams
     *
     * // TODO throw exception when reading past limit
     */
    class BinaryStream {

        public: 

            // constructor
            BinaryStream(size_t bufferSize);
            ~BinaryStream();

            // generic writing functions
            void writeInt(int val);
            void writeDouble(double val);
            void writeString(std::string str);
            void writeBool(bool val);

            // unit writing functions
            void writeSeconds(seconds val);
            void writeMeters(meters val);
            void writeRadians(radians val);
            void writeDegrees(degrees val);
            void writeKilograms(kilograms val);

            // generic reading functions
            int readInt();
            double readDouble();
            std::string readString();
            bool readBool();

            // unit reading functions
            seconds readSeconds();
            meters readMeters();
            radians readRadians();
            degrees readDegrees();
            kilograms readKilograms();

            // peeking functions
            int peekInt();
            double peekDouble();
            std::string peekString();
            bool peekBool();

            /**
             * Reset the position marker to the beginning.
             */
            void reset();

            /**
             * Set the valid data length
             */
            void setDataLength(size_t length);
            
            /**
             * Sets the location marker position
             */
            void setPosition(size_t pos);

            /**
             * Get the raw pointer to the buffer
             */
            char* getBuffer();

            /**
             * Get the current length of valid data written to the buffer
             */
            size_t getLength() const;

            /**
             * Get the current position of stream in buffer
             */
            size_t getPosition() const;

            int hash() const;

        private:

            // increment m_loc by by
            void incrementWriteLoc(size_t by);
            void incrementReadLoc(size_t by);

            size_t m_bufferSize;
            size_t m_dataLength;
            char* m_buffer;
            size_t m_loc;

    }; // BinaryStream class
} // BattleRoom namespace
#endif // BINARY_STREAM_H
