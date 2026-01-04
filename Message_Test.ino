#include <Packet.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Packet pkt;
  
  pkt.SRC = 1;
  pkt.DEST = 2;
  pkt.TYPE = PKT_TYPE_DATA;
  pkt.LEN = 0;
  pkt.TTL = 1;
  uint8_t* tx_buffer = (uint8_t *)malloc(PACKET_HEADER + pkt.LEN + 1);
  size_t len = encode_packet(pkt,tx_buffer);
  //The date is read 1 byte at a time and pkt->LEN is read and Payload is read
  uint8_t* rx_buffer = tx_buffer;
  Packet* out_pkt = new Packet();

  Serial.println(sizeof(*rx_buffer));
  Serial.println(len);
  if(decode_packet(rx_buffer,len,out_pkt)){
    Serial.println(out_pkt->SRC);
    Serial.println("Entered");
  }
  Serial.println("Hello\n");
  delay(500);
}
