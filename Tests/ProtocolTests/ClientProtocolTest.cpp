#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../src/Client/Protocol/protocol.h"
#include "socket.h"

class SocketMock: public Socket {
public:
    explicit SocketMock(const std::string& port) : Socket(port.c_str()) {};
    MOCK_METHOD(int, recvall, (void* buffer, unsigned int len, bool* wasClosed), (override));
};

class ClientProtocolTest : public ::testing::Test {
protected:
    std::shared_ptr<SocketMock> mockSocket;
    std::atomic<bool> wasClosed;
    ClientProtocol clientProtocol;

    ClientProtocolTest() :
            mockSocket(std::make_shared<SocketMock>("8080")),
            wasClosed(false),
            clientProtocol(mockSocket, wasClosed) {}
};

TEST_F(ClientProtocolTest, ReceivePlayerIdReturnsCorrectValue) {
    uint8_t expectedValue = 123;
    EXPECT_CALL(*mockSocket, recvall(testing::_, testing::_, testing::_))
            .WillOnce(testing::Invoke([&](void* buffer, size_t len, bool* wasClosed) -> int {
                *(static_cast<uint8_t*>(buffer)) = expectedValue;
                return len;
            }));

    uint8_t receivedValue;
    clientProtocol.receivePlayerId(receivedValue);

    EXPECT_EQ(receivedValue, expectedValue);
}

TEST_F(ClientProtocolTest, ReceiveDTOTypeReturnsCorrectValue) {
    char expectedValue = 'a';
    EXPECT_CALL(*mockSocket, recvall(testing::_, testing::_, testing::_))
            .WillOnce(testing::Invoke([&](void* buffer, size_t len, bool* wasClosed) -> int {
                *(static_cast<char*>(buffer)) = expectedValue;
                return len;
            }));

    char receivedValue;
    clientProtocol.receiveDTOType(receivedValue);

    EXPECT_EQ(receivedValue, expectedValue);
}

TEST_F(ClientProtocolTest, ReceiveMapsListReturnsCorrectValue) {
    std::unordered_map<uint8_t, std::string> expectedMaps;
    expectedMaps[1] = "Map1";
    expectedMaps[2] = "Map2";

    EXPECT_CALL(*mockSocket, recvall(testing::_, testing::_, testing::_))
            .WillOnce(testing::Invoke([&](void* buffer, size_t len, bool* wasClosed) -> int {
                *(static_cast<uint8_t*>(buffer)) = expectedMaps.size();
                return len;
            }))
            .WillRepeatedly(testing::Invoke([&](void* buffer, size_t len, bool* wasClosed) -> int {
                static int callCount = 0;
                if (callCount < expectedMaps.size() * 3) {
                    uint8_t value = callCount / 3 + 1;
                    if (callCount % 3 == 0) {
                        *(static_cast<uint8_t*>(buffer)) = value;
                    } else if (callCount % 3 == 1) {
                        *(static_cast<uint8_t*>(buffer)) = expectedMaps[value].size();
                    } else if (callCount % 3 == 2) {
                        std::copy(expectedMaps[value].begin(), expectedMaps[value].end(), static_cast<char*>(buffer));
                    }
                    callCount++;
                }
                return len;
            }));

    std::unique_ptr<DTO> dto;
    clientProtocol.receiveMapsList(dto);

    auto* mapsListDTO = dynamic_cast<MapsListDTO*>(dto.get());
    ASSERT_NE(mapsListDTO, nullptr);
    ASSERT_FALSE(mapsListDTO->getMaps().empty());
}
