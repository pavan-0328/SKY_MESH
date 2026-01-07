#ifndef FLOOD_MESH_
#define FLOOD_MESH_
#include "Arduino.h"
#include <Packet.h>

typedef enum {
      DO_FORWORD = 0x01,
      DO_PROCESS = 0x02,
      DO_DISCARD = 0x03
} ActionType;

class FloodMesh
{
  public:
    FloodMesh(uint8_t id_);
    ~FloodMesh();
    uint8_t mesh_action(Packet& pkt);
  private:
    uint8_t action_(const Packet& pkt);//this will tell what to do with the packet

    void net_forword_(Packet& pkt);//this will forword if the packet is not for thid node

    void process_(Packet& pkt);
    
  
    
  public:
    uint8_t node_id;
    std::unordered_map<int,int> info_table;

};


#endif