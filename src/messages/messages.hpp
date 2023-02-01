#pragma once

struct Message {
  int varName;
  int varValue;
};

void sendMessage(int varName, int varValue);
Message receiveMessage(void);
