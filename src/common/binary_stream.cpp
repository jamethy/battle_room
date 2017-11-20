#include "battle_room/common/binary_stream.h"

#include <cstring>
#include <stdexcept>

namespace BattleRoom {

    BinaryStream::BinaryStream(size_t maxSize) :
        m_maxSize(maxSize),
        m_buffer(new char[m_maxSize]()),
        m_loc(0) { }

    BinaryStream::~BinaryStream() { 
        delete[] m_buffer; 
    }

    void BinaryStream::reset() { 
        m_loc = 0; 
    }

    char* BinaryStream::getBuffer() { 
        return m_buffer; 
    }

    size_t BinaryStream::getLength() const { 
        return m_loc; 
    } 

    void BinaryStream::writeInt(int val) {
        incrementLoc(sizeof(int));
        memcpy(m_buffer + m_loc - sizeof(int), &val, sizeof(int));
    }

    void BinaryStream::writeDouble(double val) {
        incrementLoc(sizeof(double));
        memcpy(m_buffer + m_loc - sizeof(double), &val, sizeof(double));
    }

    void BinaryStream::writeString(std::string str) {
        writeInt(str.length());
        incrementLoc(str.length());
        memcpy(m_buffer + m_loc - str.length(), str.data(), str.length());
    }

    int BinaryStream::readInt() {
        int retVal = 0;
        incrementLoc(sizeof(int));
        memcpy(&retVal, m_buffer + m_loc - sizeof(int), sizeof(int));
        return retVal;
    }

    double BinaryStream::readDouble() {
        double retVal = 0;
        incrementLoc(sizeof(double));
        memcpy(&retVal, m_buffer + m_loc - sizeof(double), sizeof(double));
        return retVal;
    }

    std::string BinaryStream::readString() {
        int size = readInt();
        incrementLoc(size);
        std::string retVal(size, '\0');
        memcpy((void*)retVal.data(), m_buffer + m_loc - size, size);
        return retVal;
    }

    void BinaryStream::incrementLoc(size_t by) {
        m_loc += by;
        if (m_loc > m_maxSize) {
            throw std::runtime_error("you've gone too far.\n");
        }
    }

}; // BattleRoom namespace
