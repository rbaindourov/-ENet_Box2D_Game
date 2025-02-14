#include "network.h"
#include "physics.h"
#include <iostream>
#include <sstream>
#include <cstdlib>

ENetHost* server = nullptr;
ENetPeer* peer = nullptr;

void sendPlayerPosition(ENetPeer* peer) {
    if (!peer) return;
    b2Vec2 pos = playerBody->GetPosition();
    std::ostringstream stream;
    stream << "pos " << pos.x << " " << pos.y;
    std::string message = stream.str();
    ENetPacket* packet = enet_packet_create(message.c_str(), message.size() + 1, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer, 0, packet);
    enet_host_flush(server);
}

void initNetwork() {
	std::cout<<"INIT NETWORK"<<std::endl;
    if (enet_initialize() != 0) {
        std::cerr << "Failed to initialize ENet!" << std::endl;
        exit(EXIT_FAILURE);
    }
    ENetAddress address;
    address.host = ENET_HOST_ANY;
    address.port = 1234;
    server = enet_host_create(&address, 32, 2, 0, 0);
    if (!server) {
        std::cerr << "Failed to create ENet server!" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    std::cout<<"SERVER started"<<std::endl;
}

void handleNetwork() {
	
    ENetEvent event;
    while (enet_host_service(server, &event, 0) > 0) {
		std::cout<<"handleNetwork:"<<event.type<<std::endl;
        if (event.type == ENET_EVENT_TYPE_RECEIVE) {
            std::string command = (char*)event.packet->data;
            std::cout << "Client: " << command << std::endl;
            movePlayer(command);
            sendPlayerPosition(event.peer);
            enet_packet_destroy(event.packet);
        }
    }
}
