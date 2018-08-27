#include "./sdl_network_helper.h"

#include <iostream>

namespace BattleRoom {

    int sdlReceiveInternal(TCPsocket socket, BinaryStream& bs, int read, int maxLength) {
        int bytesToRead = maxLength - read;
        int bytesRead = SDLNet_TCP_Recv(socket, bs.getBuffer() + read, bytesToRead);
        if (bytesRead <= 0) {
            return -1;
        } else if (bytesRead < bytesToRead) { 
            return sdlReceiveInternal(socket, bs, read + bytesRead, maxLength);
        } else {
            return maxLength;
        }
    }

    int sdlReceive(TCPsocket socket, BinaryStream& bs, int maxLength) {

        bs.reset();
        bs.setDataLength(maxLength);
        return sdlReceiveInternal(socket, bs, 0, maxLength);
    }

    int sdlWriteInternal(TCPsocket socket, BinaryStream& bs, int written, int maxLength) {
        int bytesToWrite = maxLength - written;
        int bytesWritten = SDLNet_TCP_Send(socket, bs.getBuffer() + written, bytesToWrite);
        if (bytesWritten <= 0) {
            return -1;
        } else if (bytesWritten < bytesToWrite) { 
            return sdlWriteInternal(socket, bs, written + bytesWritten, maxLength);
        } else {
            return maxLength;
        }
    }

    int sdlWrite(TCPsocket socket, BinaryStream& bs) {
        return sdlWriteInternal(socket, bs, 0, bs.getLength());
    }

    int sdlSendMessage(Message& message, BinaryStream& messageStream, BinaryStream& body, TCPsocket socket) {

        message.setDataSize(body.getLength());
        message.setBodyHash(body.hash());

        messageStream.reset();
        message.serialize(messageStream);

        int bytesWritten = SDLNet_TCP_Send(socket, messageStream.getBuffer(), messageStream.getLength());

        if (bytesWritten == 0) {
            std::cerr << "Wrote zero bytes in header\n";
            return 0;
        }

        if (bytesWritten < (int)Message::Size) {
            //freak out
            std::cerr << "Did not send full header\n";
            return -1;
        }

        if (message.hasBody()) {
            bytesWritten = SDLNet_TCP_Send(socket, body.getBuffer(), body.getLength());

            if (bytesWritten == 0) {
                std::cerr << "Wrote zero bytes in body\n";
                return 0;
            }
            if (bytesWritten < (int)body.getLength()) {
                //freak out
                std::cerr << "Did not send full body\n";
                return -1;
            }
        }

        return 1;
    }

    int sdlReceiveMessage(Message& message, BinaryStream& messageStream, BinaryStream& dataStream, TCPsocket socket) {

        messageStream.reset();
        dataStream.reset();

        messageStream.setDataLength(Message::Size);
        int bytesRead = sdlReceive(socket, messageStream, Message::Size);

        if (bytesRead == 0) {
            std::cerr << "Read zero bytes in header\n";
            return 0;
        }

        if (bytesRead < (int)Message::Size) {
            std::cerr << "Did not receive full header: " << bytesRead << "\n";
            return -1;
        }

        message = Message::deserialize(messageStream);

        if (message.getHeaderHash() != message.hash()) {
            std::cerr << "Header hash did not meet calculations\n";
            return -1;
        }

        if (message.hasBody()) {
            dataStream.setDataLength(message.getDataSize());
            bytesRead = sdlReceive(socket, dataStream, message.getDataSize());

            if (bytesRead == 0) {
                std::cerr << "Read zero bytes in body\n";
                return 0;
            }

            if (bytesRead < (int)message.getDataSize()) {
                std::cerr << "Did not receive full body\n";
                return -1;
            }

            if (message.getBodyHash() != dataStream.hash()) {
                std::cerr << "Body hash did not meet calculations\n";
                std::cerr << "header: " << message.getBodyHash() << " bs: " << dataStream.hash() << std::endl;
                return -1;
            }
        }

        return 1;
    }
} // BattleRoom namespace
