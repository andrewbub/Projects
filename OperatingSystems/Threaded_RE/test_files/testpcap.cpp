#include <pcap/pcap.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>

using namespace std;
int main() {
	char fname[] = "Dataset-Small.pcap"; 
	FILE *fp = fopen(fname, "r");

	fseek(fp, 0, SEEK_END); //seek to end to find full size
	long fsize = ftell(fp); //get size
	fseek(fp, 0, SEEK_SET); //rewind
	cout << "Size of File = " << fsize << endl;

	char data[2400];
	int pcount = 0;
	int totalpsize = 0;
	float avg = 0.0;

	/*
	//
	uint32_t MN, zone, sf, snap, network;
	uint16_t vmajor, vminor;
	fread(&MN, 4, 1, fp);
	fread(&vmajor, 2, 1, fp);
	fread(&vminor, 2, 1, fp);
	fread(&zone, 4, 1, fp);
	fread(&sf, 4, 1, fp);
	fread(&snap, 4, 1, fp);
	fread(&network, 4, 1, fp);
	cout << MN << endl;
	cout << vmajor << endl;
	cout << vminor << endl;
	cout << zone << endl;
	cout << sf << endl;
	cout << snap << endl;
	cout << network << endl;
	//exit(0);
	//
	*/
	
	fseek(fp, 24, SEEK_CUR); //skip past entire Global Header
	uint32_t maxlen = 0;
	while( 1 ){
		if(pcount == 3) break;

		uint32_t packet_length=0;
		fseek(fp, 8, SEEK_CUR);          // skip ts_sec, ts_usec fields
		fread(&packet_length, 4, 1, fp); // read in the packet_length field
		fseek(fp, 4, SEEK_CUR);          // skip orig_len field

		//if (packet_length > maxlen)
		//	maxlen = packet_length;

		//the while() condition used to be while(!feof(fp)) however, this was
		//not working so I had to do the check here, where it will break out
		//of the while loop if it does not read a packet length at all (because
		//the fp is at the EOF)
		if(packet_length==0)
			break;


		//print length and then just skip ahead, comment this out if 
		//we are actually data processing
		//printf("Packet Length = %d\n", packet_length);
		//fseek(fp, packet_length, SEEK_CUR);

			
		//use this code below if we actually want to read it into a 'data' buffer
 		// and then process it (hash it) this test code assumes that 2000 is the
 		// max_packet size were willing to process

		
		if(packet_length < 2400 && packet_length > 128){
			cout << pcount;
			printf("  Packet Length = %d\n", packet_length);
			fseek(fp, 52, SEEK_CUR);
			packet_length -= 52;
			fread(data, packet_length, 1, fp); //read and store in DATA
			//cout << "*" << data << "*" << endl;
			cout << "*" << endl;
			//for(int i=0; i<3; i++)
			//	cout << data[i];
		} else {
			cout << pcount;
			printf("  Packet Length ~ %d ~ is out of bounds\n", packet_length);
			fseek(fp, packet_length, SEEK_CUR); //Skip x bytes ahead
		}
		pcount +=1;
		totalpsize += packet_length;
	}

	avg = float(totalpsize) / float(pcount);

	printf("There were %d packets\n", pcount);
	printf("Average Size =  %f\n", avg);
	cout << "Max packet size = " << maxlen << endl;
	fclose(fp);
	return 0;
}
