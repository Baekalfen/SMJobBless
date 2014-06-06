//
//  SMJobBless.h
//

#ifndef SMJobBless_SMJobBless_h
#define SMJobBless_SMJobBless_h

#define kSocketPath "/var/run/com.apple.SMJobBlessHelper.socket"
#define kHelperIdentifier "com.apple.bsd.SMJobBlessHelper"
#define kVersionPart1 1
#define kVersionPart2 0
#define kVersionPart3 52

enum SMJobBlessCommand {
    SMJobBless_Error    = 0,
    SMJobBless_Version  = 1,
    SMJobBless_CMD      = 2,
};

// This needs to change if the following structure changes
#define kMessageVersion 1

struct SMJobBlessMessage {
    unsigned char version;      // kMessageVersion
    unsigned char command;      // SMJobBlessCommand
    unsigned char dataSizeLo;     // 0 to 255
    unsigned char dataSizeHi;     // 256 to 65535
    unsigned char data[8191];    // command-specific data
};

#define getDataSize(message_p) ((message_p)->dataSizeHi*0xff + (message_p)->dataSizeLo)
#define setDataSize(message_p, newSize) {(message_p)->dataSizeHi = newSize/0xff; (message_p)->dataSizeLo = newSize-((message_p)->dataSizeHi*0xff);}
#define messageSize(message_p) sizeof(*message_p) - sizeof((message_p)->data) + getDataSize(message_p)
#define initMessage(m, c) { m.version = kMessageVersion; m.command = c; m.dataSizeLo = 0;m.dataSizeHi = 0; }

int readMessage(int fd, struct SMJobBlessMessage * message);

#endif