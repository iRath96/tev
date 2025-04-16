/*
 * tev -- the EXR viewer
 *
 * Copyright (C) 2025 Thomas Müller <contact@tom94.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <tev/Common.h>
#include <tev/VectorGraphics.h>

#include <list>
#include <vector>

namespace tev {

#ifdef _WIN32
    using socket_t = SOCKET;
#else
    using socket_t = int;
#endif

struct IpcPacketOpenImage {
    std::string imagePath;
    std::string channelSelector;
    bool grabFocus;
};

struct IpcPacketReloadImage {
    std::string imageName;
    bool grabFocus;
};

struct IpcPacketUpdateImage {
    std::string imageName;
    bool grabFocus;
    int32_t nChannels;
    std::vector<std::string> channelNames;
    std::vector<int64_t> channelOffsets;
    std::vector<int64_t> channelStrides;
    int32_t x, y, width, height;
    std::vector<std::vector<float>> imageData; // One set of data per channel
};

struct IpcPacketCloseImage {
    std::string imageName;
};

struct IpcPacketCreateImage {
    std::string imageName;
    bool grabFocus;
    int32_t width, height;
    int32_t nChannels;
    std::vector<std::string> channelNames;
};

struct IpcPacketVectorGraphics {
    std::string imageName;
    bool grabFocus;
    bool append; // If true, appends new vector instructions to existing ones rather than overwriting them
    int32_t nCommands;
    std::vector<VgCommand> commands;
};

struct IpcPacketRemoteProcedureCall {
    int32_t nBytes;
    std::vector<uint8_t> data;
};

class IpcPacket {
public:
    enum EType : char {
        OpenImage = 0,
        ReloadImage = 1,
        CloseImage = 2,
        UpdateImage = 3,
        CreateImage = 4,
        UpdateImageV2 = 5, // Adds multi-channel support
        UpdateImageV3 = 6, // Adds custom striding/offset support
        OpenImageV2 = 7,   // Explicit separation of image name and channel selector
        VectorGraphics = 8,
        RemoteProcedureCall = 9,
    };

    IpcPacket() = default;
    IpcPacket(const char* data, size_t length, socket_t socket);

    socket_t socket() const { return mSocket; }

    const char* data() const { return mPayload.data(); }

    size_t size() const { return mPayload.size(); }

    EType type() const {
        // The first 4 bytes encode the message size.
        return (EType)mPayload[4];
    }

    struct ChannelDesc {
        std::string name;
        int64_t offset;
        int64_t stride;
    };

    void setOpenImage(const std::string& imagePath, const std::string& channelSelector, bool grabFocus);
    void setReloadImage(const std::string& imageName, bool grabFocus);
    void setCloseImage(const std::string& imageName);
    void setUpdateImage(
        const std::string& imageName,
        bool grabFocus,
        const std::vector<ChannelDesc>& channelDescs,
        int32_t x,
        int32_t y,
        int32_t width,
        int32_t height,
        const std::vector<float>& stridedImageData
    );
    void setCreateImage(
        const std::string& imageName, bool grabFocus, int32_t width, int32_t height, int32_t nChannels, const std::vector<std::string>& channelNames
    );
    void setVectorGraphics(const std::string& imageName, bool grabFocus, bool append, const std::vector<VgCommand>& commands);

    IpcPacketOpenImage interpretAsOpenImage() const;
    IpcPacketReloadImage interpretAsReloadImage() const;
    IpcPacketCloseImage interpretAsCloseImage() const;
    IpcPacketUpdateImage interpretAsUpdateImage() const;
    IpcPacketCreateImage interpretAsCreateImage() const;
    IpcPacketVectorGraphics interpretAsVectorGraphics() const;
    IpcPacketRemoteProcedureCall interpretAsRemoteProcedureCall() const;

private:
    std::vector<char> mPayload;
    socket_t mSocket;

    class IStream {
    public:
        IStream(const std::vector<char>& data) : mData{data} {
            uint32_t size;
            *this >> size;
            if ((size_t)size != data.size()) {
                throw std::runtime_error{"Trying to read IPC packet with incorrect size."};
            }
        }

        IStream& operator>>(bool& var) {
            if (mData.size() < mIdx + 1) {
                throw std::runtime_error{"Trying to read bool beyond the bounds of the IPC packet payload."};
            }

            var = mData[mIdx] == 1;
            ++mIdx;
            return *this;
        }

        IStream& operator>>(std::string& var) {
            std::vector<char> buffer;
            do {
                if (mData.size() < mIdx + 1) {
                    throw std::runtime_error{"Trying to read string beyond the bounds of the IPC packet payload."};
                }

                buffer.push_back(mData[mIdx]);
            } while (mData[mIdx++] != '\0');
            var = buffer.data();
            return *this;
        }

        template <typename T> IStream& operator>>(std::vector<T>& var) {
            for (auto& elem : var) {
                *this >> elem;
            }
            return *this;
        }

        template <typename T> IStream& operator>>(T& var) {
            if (mData.size() < mIdx + sizeof(T)) {
                throw std::runtime_error{"Trying to read generic type beyond the bounds of the IPC packet payload."};
            }

            var = *(T*)&mData[mIdx];
            mIdx += sizeof(T);
            return *this;
        }

        size_t remainingBytes() const { return mData.size() - mIdx; }

        const char* get() const { return &mData[mIdx]; }

    private:
        const std::vector<char>& mData;
        size_t mIdx = 0;
    };

    class OStream {
    public:
        OStream(std::vector<char>& data) : mData{data} {
            // Reserve space for an integer denoting the size
            // of the packet.
            *this << (uint32_t)0;
        }

        template <typename T> OStream& operator<<(const std::vector<T>& var) {
            for (auto&& elem : var) {
                *this << elem;
            }

            return *this;
        }

        OStream& operator<<(const std::string& var) {
            for (auto&& character : var) {
                *this << character;
            }

            *this << '\0';
            return *this;
        }

        OStream& operator<<(bool var) {
            if (mData.size() < mIdx + 1) {
                mData.resize(mIdx + 1);
            }

            mData[mIdx] = var ? 1 : 0;
            ++mIdx;
            updateSize();
            return *this;
        }

        template <typename T> OStream& operator<<(T var) {
            if (mData.size() < mIdx + sizeof(T)) {
                mData.resize(mIdx + sizeof(T));
            }

            *(T*)&mData[mIdx] = var;
            mIdx += sizeof(T);
            updateSize();
            return *this;
        }

    private:
        void updateSize() { *((uint32_t*)mData.data()) = (uint32_t)mIdx; }

        std::vector<char>& mData;
        size_t mIdx = 0;
    };
};

class Ipc {
public:
    Ipc(const std::string& hostname = "127.0.0.1:14158");
    virtual ~Ipc();

    bool isPrimaryInstance() { return mIsPrimaryInstance; }

    bool attemptToBecomePrimaryInstance();

    void sendToPrimaryInstance(const IpcPacket& message);
    void receiveFromSecondaryInstance(std::function<void(const IpcPacket&)> callback);

private:
    bool mIsPrimaryInstance;
    socket_t mSocketFd;

#ifdef _WIN32
    HANDLE mInstanceMutex;
#else
    int mLockFileDescriptor;
    fs::path mLockFile;
#endif

    class SocketConnection {
    public:
        SocketConnection(socket_t fd, const std::string& name);

        void service(std::function<void(const IpcPacket&)> callback);

        void close();

        bool isClosed() const;

    private:
        socket_t mSocketFd;
        std::string mName;

        // Because TCP socket recv() calls return as much data as is available (which may have the partial contents of a client-side send()
        // call, we need to buffer it up in SocketConnection.
        std::vector<char> mBuffer;
        // Offset into buffer where next recv() call should start writing.
        size_t mRecvOffset = 0;
    };

    std::list<SocketConnection> mSocketConnections;

    std::string mIp;
    std::string mPort;
    std::string mLockName;
};

} // namespace tev
