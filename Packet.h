#ifndef PACKET_H
#define PACKET_H
#include "Arduino.h"

#define PACKET_SOF 0xAA//Start of the message for easy deframing
#define PACKET_MAX_PAYLOAD 32 // 32 Bytes
#define PACKET_HEADER 6
typedef struct __attribute__((packed)) {
  uint8_t SRC; // Source node addr 
  uint8_t DEST; // Destination node addr
  uint8_t TYPE; //Message type
  uint8_t TTL;
  uint8_t LEN; //Payload Length
  uint8_t payload[PACKET_MAX_PAYLOAD];//actual payload 
  uint8_t CHECK_SUM; // CRC8
} Packet;


typedef enum {
  PKT_TYPE_DATA = 0x01,
  PKT_TYPE_PING = 0x02,
  PKT_TYPE_ERROR = 0x03,
  PKT_TYPE_ACK = 0x04
} PacketTypes;

//Encode and Decode packet
uint8_t crc_compute(const uint8_t* data ,size_t len);
size_t encode_packet(const Packet& pkt, uint8_t* out_buffer);
bool decode_packet(const uint8_t* in_buffer,size_t in_len,Packet* out_pkt);
#endif