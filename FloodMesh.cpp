#include <FloodMesh.h>

FloodMesh::FloodMesh(uint8_t id_)
{
  node_id = id_;
}

uint8_t FloodMesh::mesh_action(Packet &pkt){
  uint8_t action = action_(pkt);
  Serial.println(pkt.SRC);
  switch(action){
    case DO_FORWORD:
      net_forword_(pkt);
      break;
    
    case DO_PROCESS:
      process_(pkt);
      break;
    case DO_DISCARD:
      break;
    default:
      break;
  } 

  Serial.println(action);
  return action;
}

uint8_t FloodMesh::action_(const Packet& pkt){
  if(pkt.SRC == node_id) return DO_DISCARD;
  else if(pkt.TTL == 0) return DO_DISCARD;
  else if(pkt.DEST == node_id) return DO_PROCESS;
  else
  {
    if(!info_table.empty())
    {auto it = info_table.find(pkt.SRC);
      if(it!=info_table.end()){
        if(pkt.MSGID == it->second){
          return DO_DISCARD;
        }
      }
      else
      {
        info_table[pkt.SRC] = pkt.MSGID;
        return DO_FORWORD;
      }
    }
    else{
      info_table[pkt.SRC] = pkt.MSGID;
      return DO_FORWORD;
    }

  }
  return -1;
}

void FloodMesh::net_forword_(Packet& pkt){
  pkt.TTL = pkt.TTL - 1;
}

void FloodMesh::process_(Packet& pkt){
  delay(3000);
  Serial.println("Backing off for 3 seconds");
}

FloodMesh::~FloodMesh(){
  info_table.clear();
  
}