#ifndef AX25_h
#define AX25_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Arduino.h"

//Magic Constants
#define AX25_FLAG				0x7E
//#define AX25_SSID_SOURCE		0x61
//#define AX25_SSID_DESTINATION	0x60
#define AX25_CONTROL			0x03
#define AX25_PROTOCOL			0xF0

//Maximum payload size of an AX.25 packet in bytes (determined by RF22 library)
// DIFFERENT
#define AX25_MAX_PAYLOAD_SIZE   160
#define CRC_POLYGEN     	    0x1021

#define MAX_LENGTH 				280
#define MAX_LENGTH_FINAL 		450

class AX25 {
public:
	//Default Constructor
	// AX25(char* fromCallsign, char* fromSSID);
	AX25(char *source_callsign, byte source_ssid);

	byte* modulatePacket(char* payload, uint16_t size); // void transmit(char* payload, unsigned int len)
  void AX25::setDestination(char *dest_callsign, byte dest_ssid);
	bool receive(uint8_t* buf, uint8_t* len);
	char* demod(byte *Buffer, uint8_t bytelength);

  byte finalSequence[MAX_LENGTH_FINAL];

private:
	char SrcCallsign[7];
	char DestCallsign[7];

	byte ssid_source;
	byte ssid_destination;

  //These are buffer unsigned char arrays
	byte bitSequence[MAX_LENGTH*8];
	char message_buffer[256];

  // Index runs through the message as bits are being added to keep track of last bit position
	int Index = 0;

	unsigned int FCS = 0;

	void setSSIDsource(byte ssid_src);
	void setSSIDdest(byte ssid_dest);
	void setFromCallsign(char *fromcallsign);
	void setToCallsign(char *tocallsign);

	void addHeader( byte *Buffer);

	void bitProcessing(byte *Buffer, uint8_t bytelength);


	boolean logicXOR(boolean a, boolean b);

	//Calculate the 2-byte CRC on the data
	// void crcCcitt(char* crc, char* data, unsigned int len);
	uint16_t crcCcitt (byte *Buffer,uint8_t bytelength);

	//Flips the order of bytes from MSB first to LSB first
	byte MSB_LSB_swap_8bit(byte v);

	uint16_t MSB_LSB_swap_16bit(uint16_t v);

	// Initializes arrays with zeros
	void arrayInit();

	//Perform bit stuffing on the input array (add an extra 0 after 5 sequential 1's)
	// unsigned int bitStuff(char* out, char* in, unsigned int inLen);
	void formatPacket(uint16_t size);
};

#endif //AX25_h