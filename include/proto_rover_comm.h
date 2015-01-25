#ifndef PROTOROVERCOMM_H
#define PROTOROVERCOMM_H

void act(char cmd);
boolean isCommand(char c);
void setup()
unsigned int getTime()
char readByte(unsigned int timeout)
int readCmd(char *cmdBuffer, int maxLen, unsigned int timeout, char startDelim, char endDelim)
bool isValidCommand(char *cmdBuffer, int len)
bool isCommand(char c)
void act(char cmd)
void printAct(char cmd)
bool waitForData(int ms)

#endif