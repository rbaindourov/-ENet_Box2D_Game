#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <enet/enet.h>

void initClient();
void sendInput(const std::string& input);
void handleServerResponses();

#endif
