#ifndef NETWORK_H
#define NETWORK_H

#include <enet/enet.h>
#include <string>




void initNetwork();
void handleNetwork();
void sendPlayerPosition(ENetPeer* peer);
void sendInput(const std::string& input); // For client use

#endif
