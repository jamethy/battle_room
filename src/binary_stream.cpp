#include "binary_stream.h"
#include "Logger.h"

#include <cstring>
#include <stdexcept>
#include <sstream>

namespace BattleRoom {

    BinaryStream::BinaryStream(size_t bufferSize) :
        m_bufferSize(bufferSize),
        m_dataLength(0),
        m_buffer(new char[m_bufferSize]()),
        m_loc(0) { }

    BinaryStream::~BinaryStream() { 
        delete[] m_buffer; 
    }

    void BinaryStream::reset() { 
        m_loc = 0; 
        m_dataLength = 0;
    }

    void BinaryStream::setDataLength(size_t length) {

        if (length > m_bufferSize) {

            std::stringstream ss;
            ss << "Increasing buffer size from " << m_bufferSize << " to " << length;
            Log::debug(ss.str());

            char* old = m_buffer;
            m_bufferSize = length;
            m_buffer = new char[m_bufferSize]();
            if (m_dataLength > 0) {
                memcpy(m_buffer, old, m_dataLength);
            }
            delete[] old;
        }
        m_dataLength = length;
    }

    void BinaryStream::setPosition(size_t pos) {
        m_loc = pos;
    }

    char* BinaryStream::getBuffer() { 
        return m_buffer; 
    }

    size_t BinaryStream::getLength() const { 
        return m_dataLength; 
    } 

    size_t BinaryStream::getPosition() const { 
        return m_loc; 
    } 

    void BinaryStream::writeInt(int val) {
        incrementWriteLoc(sizeof(int));
        memcpy(m_buffer + m_loc - sizeof(int), &val, sizeof(int));
    }

    void BinaryStream::writeDouble(double val) {
        incrementWriteLoc(sizeof(double));
        memcpy(m_buffer + m_loc - sizeof(double), &val, sizeof(double));
    }

    void BinaryStream::writeString(std::string str) {
        writeInt(str.length());
        incrementWriteLoc(str.length());
        memcpy(m_buffer + m_loc - str.length(), str.data(), str.length());
    }

    void BinaryStream::writeBool(bool val) {
        incrementWriteLoc(sizeof(bool));
        memcpy(m_buffer + m_loc - sizeof(bool), &val, sizeof(bool));
    }

    int BinaryStream::readInt() {
        int retVal = 0;
        incrementReadLoc(sizeof(int));
        memcpy(&retVal, m_buffer + m_loc - sizeof(int), sizeof(int));
        return retVal;
    }

    double BinaryStream::readDouble() {
        double retVal = 0;
        incrementReadLoc(sizeof(double));
        memcpy(&retVal, m_buffer + m_loc - sizeof(double), sizeof(double));
        return retVal;
    }

    std::string BinaryStream::readString() {
        int size = readInt();
        incrementReadLoc(size);
        std::string retVal(size, '\0');
        memcpy((void*)retVal.data(), m_buffer + m_loc - size, size);
        return retVal;
    }

    bool BinaryStream::readBool() {
        bool retVal = 0;
        incrementReadLoc(sizeof(bool));
        memcpy(&retVal, m_buffer + m_loc - sizeof(bool), sizeof(bool));
        return retVal;
    }

    int BinaryStream::peekInt() {
        int retVal = 0;
        memcpy(&retVal, m_buffer + m_loc, sizeof(int));
        return retVal;
    }

    double BinaryStream::peekDouble() {
        double retVal = 0;
        memcpy(&retVal, m_buffer + m_loc, sizeof(double));
        return retVal;
    }

    std::string BinaryStream::peekString() {
        int size = peekInt();
        std::string retVal(size, '\0');
        memcpy((void*)retVal.data() , m_buffer + m_loc + sizeof(int), size);
        return retVal;
    }

    bool BinaryStream::peekBool() {
        bool retVal = 0;
        memcpy(&retVal, m_buffer + m_loc, sizeof(bool));
        return retVal;
    }

    void BinaryStream::incrementWriteLoc(size_t by) {
        if (m_loc + by > m_bufferSize) {

            std::stringstream ss;
            ss << "Doubling buffer size from " << m_bufferSize << " to " << 2*m_bufferSize;
            Log::debug(ss.str());

            char* old = m_buffer;
            m_bufferSize = 2*m_bufferSize;
            m_buffer = new char[m_bufferSize]();
            if (m_dataLength > 0) {
                memcpy(m_buffer, old, m_dataLength);
            }
            delete[] old;
        }
        m_loc += by;
        m_dataLength += by;
    }

    void BinaryStream::incrementReadLoc(size_t by) {
        if (m_loc + by > m_dataLength) {
            throw std::runtime_error("Reading out of bounds of binary stream");
        }
        m_loc += by;
    }

    int BinaryStream::hash() const {
        int val = 0;
        for (size_t i = 0; i < m_dataLength; ++i) {
            val += m_buffer[i];
        }
        return val;
    }

    // unit versions

    void BinaryStream::writeSeconds(seconds val) { writeDouble(val); }
    void BinaryStream::writeMeters(meters val) { writeDouble(val); }
    void BinaryStream::writeRadians(radians val) { writeDouble(val); }
    void BinaryStream::writeDegrees(degrees val) { writeDouble(val); }
    void BinaryStream::writeKilograms(kilograms val) { writeDouble(val); }
    seconds BinaryStream::readSeconds() { return readDouble(); }
    meters BinaryStream::readMeters() { return readDouble(); }
    radians BinaryStream::readRadians() { return readDouble(); }
    degrees BinaryStream::readDegrees() { return readDouble(); }
    kilograms BinaryStream::readKilograms() { return readDouble(); }

} // BattleRoom namespace
