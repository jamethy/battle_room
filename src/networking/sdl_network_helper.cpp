#include "common/logger.h"
#include "networking/sdl_network_helper.h"

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

    int sdlSendTCPMessage(Message &message, BinaryStream &messageStream, BinaryStream &body, TCPsocket socket) {

        message.setDataSize(body.getLength());
        message.setBodyHash(body.hash());

        messageStream.reset();
        message.serialize(messageStream);

        int bytesWritten = SDLNet_TCP_Send(socket, messageStream.getBuffer(), messageStream.getLength());

        if (bytesWritten == 0) {
            Log::error("Wrote zero bytes in header");
            return 0;
        }

        if (bytesWritten < (int)Message::Size) {
            //freak out
            Log::error("Did not send full header");
            return -1;
        }

        if (message.hasBody()) {
            bytesWritten = SDLNet_TCP_Send(socket, body.getBuffer(), body.getLength());

            if (bytesWritten == 0) {
                Log::error("Wrote zero bytes in body");
                return 0;
            }
            if (bytesWritten < (int)body.getLength()) {
                //freak out
                Log::error("Did not send full body");
                return -1;
            }
        }

        return 1;
    }

    int sdlReceiveTCPMessage(Message &message, BinaryStream &messageStream, BinaryStream &dataStream, TCPsocket socket) {

        messageStream.reset();
        dataStream.reset();

        messageStream.setDataLength(Message::Size);
        int bytesRead = sdlReceive(socket, messageStream, Message::Size);

        if (bytesRead == 0) {
            Log::error("Read zero bytes in header");
            return 0;
        }

        if (bytesRead < (int)Message::Size) {
            Log::error("Did not receive full header: ", bytesRead);
            return -1;
        }

        message = Message::deserialize(messageStream);

        if (message.getHeaderHash() != message.hash()) {
            Log::error("Header hash did not meet calculations");
            return -1;
        }

        if (message.hasBody()) {
            dataStream.setDataLength(message.getDataSize());
            bytesRead = sdlReceive(socket, dataStream, message.getDataSize());

            if (bytesRead == 0) {
                Log::error("Read zero bytes in body");
                return 0;
            }

            if (bytesRead < (int)message.getDataSize()) {
                Log::error("Did not receive full body");
                return -1;
            }

            if (message.getBodyHash() != dataStream.hash()) {
                Log::error("Body hash did not meet calculations: header: ", message.getBodyHash(), " bs: ", dataStream.hash());
                return -1;
            }
        }

        return 1;
    }
} // BattleRoom namespace
