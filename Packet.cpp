#include "Packet.h"

uint8_t crc8_compute(const uint8_t* data, size_t len)
{
    const uint8_t poly = 0x1D;
    uint8_t crc = 0x00;

    for (size_t i = 0; i < len; i++) {
        crc ^= data[i];
        for (uint8_t b = 0; b < 8; b++) {
            if (crc & 0x80)
                crc = (crc << 1) ^ poly;
            else
                crc <<= 1;
        }
    }
    return crc;
}


size_t encode_packet(const Packet& pkt, uint8_t* out_buffer){
  //TODO
  out_buffer[0] = PACKET_SOF;
  out_buffer[1] = pkt.SRC;
  out_buffer[2] = pkt.DEST;
  out_buffer[3] = pkt.TYPE;
  out_buffer[4] = pkt.MSGID;
  out_buffer[5] = pkt.TTL;
  out_buffer[6] = pkt.LEN;
  for(size_t i=7;i<pkt.LEN + 7;i++){
    out_buffer[i] = pkt.payload[i -7];
  }
  out_buffer[7 + pkt.LEN ] =  crc8_compute(&out_buffer[1],6 + pkt.LEN); 
  return pkt.LEN + PACKET_HEADER + 1 ;// for SOF;
}

bool decode_packet(const uint8_t* in_buffer, size_t in_len,Packet* out_pkt){
  //TODO
  if(in_buffer[0] != PACKET_SOF || in_len < PACKET_HEADER){
    return false;
  }

  size_t curr{1};
  out_pkt->SRC = in_buffer[curr++];
  out_pkt->DEST = in_buffer[curr++];
  out_pkt->TYPE = in_buffer[curr++];
  out_pkt->MSGID = in_buffer[curr++];
  out_pkt->TTL = in_buffer[curr++];
  out_pkt->LEN = in_buffer[curr++];
  
  if(out_pkt->LEN > 32) return false;

  for(size_t i=0;i<out_pkt->LEN;i++){
    out_pkt->payload[i] = in_buffer[curr++];
  }

  out_pkt->CHECK_SUM = in_buffer[curr++];
  uint8_t rx_crc = crc8_compute(&in_buffer[1],6+out_pkt->LEN);
  return (rx_crc == out_pkt->CHECK_SUM); 
}