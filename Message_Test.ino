#include <Packet.h>
#include <FloodMesh.h>

FloodMesh mesh(1);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Packet pkt;
  
  pkt.SRC = 2;
  pkt.DEST = 4;
  pkt.TYPE = PKT_TYPE_DATA;
  pkt.MSGID = 1;
  pkt.LEN = 0;
  pkt.TTL = 2;
  uint8_t* tx_buffer = (uint8_t *)malloc(PACKET_HEADER + pkt.LEN + 1);
  size_t len = encode_packet(pkt,tx_buffer);
  //The date is read 1 byte at a time and pkt->LEN is read and Payload is read
  uint8_t* rx_buffer = tx_buffer;
  Packet* out_pkt = new Packet();
  
  
  if(decode_packet(rx_buffer,len,out_pkt)){
    if(mesh.mesh_action(*out_pkt) == DO_FORWORD){
      Serial.println("Packet Forwording......");
    }
    Serial.println("Hello\n");
  }
  //Serial.println("Hello\n");
  delay(500);
}
