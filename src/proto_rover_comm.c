#include <ProtoRover.h>
#include <proto_rover_comm.h>

#define MAX_MESSAGE_LENGTH 100
#define ROVER_SPEED 1.0

char msg[MAX_MESSAGE_LENGTH];
char cmdMsg[MAX_MESSAGE_LENGTH];
int counter = 0;
Rover hal9000;

int main()
{
  setup();
  int msgLen;

  bool thirmanSux = true;  //Suck it thirman.
  while(thirmanSux)
  {
    msgLen = readCmd(msg, 25, '!', '\n');
    if(isValidCommand(msg, msgLen))
    {
      multiAct(msg);
    }
  }
}

void setup()
{
  NU32_Startup();
  sprintf(msg, "Starting in Start Command \n");
  NU32_WriteUART1(msg);
  hal9000.reset( //placeholder inputs
    -1,  // left phase 
    -1,  // left enable
    -1,  // right phase
    -1   // right enable
  );
}

unsigned int getTime()
{
  unsigned int time = NU32_ReadCoreTimer()/40000;
  NU32_WriteCoreTimer(unsigned int 0);
  return time;
}


char readByte(unsigned int timeout)
{
  char data;

  if (waitForData(timeout)) 
  {
    data = U1RXREG; 
  }

  return data;
}

int readCmd(char *cmdBuffer, int maxLen, unsigned int timeout, char startDelim, char endDelim)
{
  int count;
  char charIn;

  charIn = readByte(timeout);
  count = 0;

  while(charIn != startDelim)
  {
    charIn = readByte(timeout);
  }
  SERIAL_STATE = WAIT_COMMAND;
  while(count < maxLen || charIn == endDelim)
  {
    cmdBuffer[count] = charIn;
    count++;
    charIn = readByte(timeout);
  }

  return count;
}

bool isValidCommand(char *cmdBuffer, int len)
{
  int i;

  for(i = 0; i < len; i++)
  {
    if(!isCommand(cmdBuffer[i]))
    {
      return false;
    }
  }
  return true;
}

bool isCommand(char c)
{
  return c == 'f' || c == 'b' || c == 'l' || c == 'r';
}

void multiAct(char *cmdMsg, int cmdLen)
{
  int i;

  for(i = 0; i < cmdLen; i++)
  {
    //act(cmdMsg[i]);
    printAct(cmdMsg[i]);
  }

}

void act(char cmd)
{
  if(cmd == 'f') {
    hal9000.driveForward();
    hal9000.setSpeed(ROVER_SPEED);
  }
  else if(cmd == 'b') {
    hal9000.driveBackward();
    hal9000.setSpeed(ROVER_SPEED);
  }
  else if(cmd == 'l') {
    hal9000.turnLeft();
    hal9000.setSpeed(ROVER_SPEED);
  }
  else if(cmd == 'r') {
    hal9000.turnRight();
    hal9000.setSpeed(ROVER_SPEED);
  }
  else {
    // Halt
    hal9000.setSpeed(0.);
  }  
}

void printAct(char cmd)
{
  char printMsg[100];

  if(cmd == 'f') {
    sprintf(printMsg, "Forward Command \n");
    NU32_WriteUART1(printMsg);
  }
  else if(cmd == 'b') {
    sprintf(printMsg, "Backwards Command \n");
    NU32_WriteUART1(printMsg);
  }
  else if(cmd == 'l') {
    sprintf(printMsg, "Left Command \n");
    NU32_WriteUART1(printMsg);
  }
  else if(cmd == 'r') {
    sprintf(printMsg, "Right Command \n");
    NU32_WriteUART1(printMsg);
  }
  else {
    sprintf(printMsg, "Invalid Command \n");
    NU32_WriteUART1(printMsg);
  }  
}

bool waitForData(int ms)
{
  int current_time = getTime();
  int time_diff = 0;
  while(U1STAbits.URXDA == 0 && ((time_diff = getTime()-current_time) < ms)); 
  if(time_diff > ms) return false;
  return true;
}
