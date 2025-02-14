#include "client.h"
#include <enet/enet.h>
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>

ENetHost* client = nullptr;
ENetPeer* peerClient = nullptr;

void sendInput(const std::string& input) {
	
    ENetPacket* packet = enet_packet_create(input.c_str(), input.length() + 1, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peerClient, 0, packet);
    enet_host_flush(client);
}

void initClient() {
    if (enet_initialize() != 0) {
        std::cerr << "Failed to initialize ENet!" << std::endl;
        exit(EXIT_FAILURE);
    }
    client = enet_host_create(nullptr, 1, 2, 0, 0);
    if (!client) {
        std::cerr << "Failed to create ENet client!" << std::endl;
        exit(EXIT_FAILURE);
    }
    ENetAddress address;
    enet_address_set_host(&address, "127.0.0.1");
    address.port = 1234;
    peerClient = enet_host_connect(client, &address, 2, 0);
    if (!peerClient) {
        std::cerr << "Failed to create connection!" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "Client initialized and attempting to connect..." << std::endl;
}

void handleServerResponses() {
	std::cout<<"handleServerResponse"<<std::endl;
    ENetEvent event;
    while (enet_host_service(client, &event, 100) > 0) {
        if (event.type == ENET_EVENT_TYPE_RECEIVE) {
            std::string response = (char*)event.packet->data;
            std::istringstream stream(response);
            std::string type;
            stream >> type;
            if (type == "pos") {
                float x, y;
                stream >> x >> y;
                std::cout << "Updated position: (" << x << ", " << y << ")\n";
            }
            enet_packet_destroy(event.packet);
        }
    }
}
