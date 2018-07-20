// Project 4
// Group Members: Erica Boyd, John Villaflor, Molly Pierce, Andrew Bub
// Group Name: JAME
// Source Code

#include <pcap/pcap.h>
#include <iostream>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <csignal>
#include <fstream>
#include <cerrno>
#include <vector>
#include <string>
#include <map>
#include <tuple>
#include <pthread.h>
#include <cmath>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <time.h>
typedef  unsigned long  int  ub4;   /* unsigned 4-byte quantities */
typedef  unsigned       char ub1;   /* unsigned 1-byte quantities */
#define hashsize(n) ((ub4)1<<(n))
#define hashmask(n) (hashsize(n)-1)

using namespace std;

#define mix(a,b,c) \
{ \
  a -= b; a -= c; a ^= (c>>13); \
  b -= c; b -= a; b ^= (a<<8); \
  c -= a; c -= b; c ^= (b>>13); \
  a -= b; a -= c; a ^= (c>>12);  \
  b -= c; b -= a; b ^= (a<<16); \
  c -= a; c -= b; c ^= (b>>5); \
  a -= b; a -= c; a ^= (c>>3);  \
  b -= c; b -= a; b ^= (a<<10); \
  c -= a; c -= b; c ^= (b>>15); \
}

// Instantiate structs
struct Producer_Threads {
	int vector_start;
	int vector_end;
	char *filename;
};

struct PacketHolder {	
	char packetdata[2400];  
	uint32_t length;
};

struct Reference {
	int start_byte;
	int end_byte;
	int packet_reference;
};

// Instantaite global counters
unsigned int TOTALSIZE = 0;
unsigned int TOTALREDUNDANCY = 0;
unsigned int TOTALHITS = 0;
unsigned int TOTALPACKETS = 0;
unsigned int PROCESSEDPACKETS=0;

// Instantiate mutexes and condition variable
pthread_mutex_t data_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lookup_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t filled = PTHREAD_COND_INITIALIZER;

// Instantiate data structures
//tuple[0]=packet starting point, tuple[1]=packet size
vector<tuple<uint32_t, uint32_t>> PacketsInfo;
queue<PacketHolder> DATA_Q;

//this will be our "best guess" at the current size of our data structures tracking redundancy
//since we don't want to iterate through them every time to get the new sizes. We use this as sort
//of a counter/indicator
unsigned long STRUCTURE_SIZE = 0; 

//level1 Global
map<ub4, vector<PacketHolder> > LOOKUP; 
vector<ub4> KEYS; //separate vetor used to keep track of size, not used to detect redundancy

//level2 Globals
///map<ub4, vector<Reference>> HASH_REFERENCE; 
map<ub4, Reference> HASH_REFERENCE; 
map<int, PacketHolder> ID_PACKET; 
map<int, vector<ub4>> ID_HASHES;
int SIZE=0;

// Instantiate Functions
vector<tuple<uint32_t, uint32_t>> getPacketsInfo(char *);
void * threaded_read(void *);
void * threaded_process(void *);
void * threaded_process_L2(void *);
ub4 hash_function(char k[2400], unsigned long int length, register ub4 initval);

//////////// Main Execution ////////////
int main(int argc, char *argv[]) {
	srand(time(NULL));
	int LEVEL = 2;
	int THREADS = 2;
	string c;
	vector<string> files;
	cout << "Welcome to Project 4 - ThreadedRE by JAME\n";

	// Process command line arguments
	for (int i=1; i < argc; i++) {
		string arg = argv[i];
		if (arg.length() >5)
		if (arg.substr(arg.length() - 5) == ".pcap") {
			files.push_back(arg);
			continue;
		}

		if (strcmp(argv[i], "-level") == 0) {
			LEVEL = atoi(argv[i+1]);
			i++;
		}

		else if (strcmp(argv[i], "-thread") == 0) {
			THREADS = atoi(argv[i+1]);
			i++;
		} else {
			cout << "Improper argument detected\n";
			exit(1);
		}
	}

	// Check the files specified
	if (files.size() == 0) {
		cout << "You must specify at least one file to process\n";
		exit(1);
	}

	// Check the specified thread number
	if (THREADS > 8 || THREADS < 2) {
		cout << "Too many threads\n";
		exit(1);
	}

	// Check the level specified
	if (LEVEL == 1)
		cout << "Now operating in Level 1 mode - full payload detection\n";
	else if (LEVEL == 2)
		cout << "Now operating in Level 2 mode - partial payload detection\n";
	else {
		cout << "This is not a valid level number\n";
		exit(1);
	}

	// Basic Output
	cout << "Threads Allowed: " << THREADS << endl;
	cout << "Allocating " << THREADS/2 << " threads to file I/O, ";
	cout << THREADS - THREADS/2 << " threads to processing\n";
	cout << "Files to process: ";
	for (unsigned int i = 0; i < files.size(); i++)
		cout << files[i] << " ";
	cout << "\n";
	cout << "\nResults:\n";

	// Iterate through each file
	for (unsigned int i = 0; i < files.size(); i++) {
		string name = files[i];	
		char fname[100];
		strcpy(fname, name.c_str());
		PacketsInfo = getPacketsInfo(fname);
		TOTALPACKETS += PacketsInfo.size();

		// Populate threads
		pthread_t p[THREADS];
		int vector_len = PacketsInfo.size();
		int pro_th = THREADS/2;
		int inc = ceil(vector_len/(float)pro_th);

		// Producer Thread Creation use arithmetic magic to figure out which packets each producer thread will fread()
		struct Producer_Threads producer_threads[pro_th];
		for (int i = 0; i < pro_th; i++) {	
			producer_threads[i].vector_start = i*(inc);
			if ((((i+1)*inc)-1) > (vector_len-1))
				producer_threads[i].vector_end = (i+1)*(inc)-2;
			else
				producer_threads[i].vector_end = (i+1)*(inc)-1;
			producer_threads[i].filename = fname;
			pthread_create(&p[i], NULL, threaded_read, &producer_threads[i]);
		}

		// Consumer Thread Creation
		for (int i = pro_th; i < THREADS; i++) {	
			if (LEVEL == 1) 
				pthread_create(&p[i], NULL, threaded_process, NULL);
			else if (LEVEL == 2)
				pthread_create(&p[i], NULL, threaded_process_L2, NULL);
		}

		// Join threads
		for (int i = 0; i < THREADS; i++) {
			pthread_join(p[i], NULL);
		}
	}

	// Compute redundancy and other values
	float savings = (float)TOTALREDUNDANCY / (float) TOTALSIZE;
	cout << (float)TOTALSIZE/1000000 << " MB processed\n";
	cout << (float)TOTALREDUNDANCY/1000000 << " MB redundant\n";
	cout <<  TOTALHITS << " hits" << endl;
	cout << savings*100 << "% redundancy detected\n";

}

//Create the PacketsInfo vector where each tuple is (packet starting point, packet size)
//PacketsInfo will be used by the producer threads
//PACKETSINFO ONLY CONTAINS RELEVANT PACKETS (128 < size < 2400)
vector<tuple<uint32_t, uint32_t>> getPacketsInfo(char *fname){
	vector<tuple< uint32_t, uint32_t >> PI;
	FILE *fp;
	if (!(fp = fopen(fname, "r"))) {
		if (errno == EACCES) cout << fname << "file not readable\n";
		else if (errno == ENOENT) cout << fname << "file not exist\n";
		else cout << fname << "file error\n";
	}
	fseek(fp, 24, SEEK_CUR); //skip past the Global Header	
	//walk the file and save where each packet starts and each packets size
	while(1){
		uint32_t packet_length = 0;
		fseek(fp, 8, SEEK_CUR); //skip two, 4byte fields
		fread(&packet_length, 4, 1, fp);
		fseek(fp, 4, SEEK_CUR); //skip one last 4byte field
		if(packet_length == 0) break;
		if(packet_length < 2400 && packet_length > 128){
			uint32_t packet_position = ftell(fp);
			uint32_t packet_size = packet_length;
			tuple<uint32_t, uint32_t> item;
			item = make_tuple(packet_position, packet_size);
			PI.push_back(item);
		}
		fseek(fp, packet_length, SEEK_CUR);
	}
	fclose(fp);
	return PI;
}

//Threaded Read Function (producer)
void * threaded_read(void * pData){
	struct Producer_Threads *temp = (struct Producer_Threads *) pData;
	int vstart = temp->vector_start;
	int vend =  temp->vector_end;
	char *fname = temp->filename;
	FILE *fp;

	if (!(fp = fopen(fname, "r"))) {
		if (errno == EACCES) cout << fname << "file not readable\n";
		else if (errno == ENOENT) cout << fname << "file not exist\n";
		else cout << fname << "file error\n";
	}
	//for the packets that this thread is responsible for loading
	for(int i=vstart; i<=vend; i++){
		//skip 52bytes of garbage bytes into the packet payload
		rewind(fp);
		uint32_t payloadstart = get<0>(PacketsInfo[i])+52;
		uint32_t payloadsize = get<1>(PacketsInfo[i])-52;
		fseek(fp, payloadstart, SEEK_CUR);
		//read into a data buffer
		char data[2400];
		memset(data, '\0', 2400);

		// fread should return payloadsize items
		// error if it reads in less than that
		if (fread(data, 1, payloadsize, fp) < payloadsize)
			cout << "Error: Could not read whole packet\n";
		//fread(data, payloadsize, 1, fp);

		PacketHolder temp;
		memcpy(temp.packetdata, data, 2400);
		temp.length = payloadsize;

		pthread_mutex_lock(&data_mutex);
		TOTALSIZE += payloadsize;
		DATA_Q.push(temp);
		pthread_cond_signal(&filled);
		pthread_mutex_unlock(&data_mutex);
	}
	fclose(fp);
	return NULL;
}

// Threaded Process Function Level 1(consumer)
void * threaded_process(void * pData){
	while(PROCESSEDPACKETS < TOTALPACKETS){
		pthread_mutex_lock(&data_mutex);

		//condition variable waiting
		while(DATA_Q.empty()){
			//this if takes care of the odd case that processedpackets is incremented in between 
			//iterations of the loop by another process
			if (PROCESSEDPACKETS >= TOTALPACKETS) {
				pthread_mutex_unlock(&data_mutex);
				return NULL;
			}
			pthread_cond_wait(&filled, &data_mutex);
		}

		register ub4 h = 0;
		ub4 hash;
		PacketHolder data = DATA_Q.front();
		DATA_Q.pop();
		PROCESSEDPACKETS += 1;
		pthread_mutex_unlock(&data_mutex);

		h = hash_function(data.packetdata, 2400, h);
		hash = (ub4)h;

		pthread_mutex_lock(&lookup_mutex);
		// Lookup Table Eviction Code //
		// if the structure size if greater than the 64MB (give or take 10MB) then use eviction
		if(STRUCTURE_SIZE >= 70000000){
			while(STRUCTURE_SIZE > 60000000){
				int randN = rand() % KEYS.size();
				ub4 randKey = KEYS[randN];
				if(LOOKUP.count(randKey)){
					for(unsigned int x=0; x<LOOKUP[randKey].size(); x++){
						STRUCTURE_SIZE -= sizeof(LOOKUP[randKey][x]);
					}
					STRUCTURE_SIZE -= sizeof(ub4);
					LOOKUP.erase(randKey);
				} else { //if the random number happened to have already been deleted
					continue;
				}
			}
		}
		// End Lookup Table Eviction Code //

		if(LOOKUP.count(hash)) { //if hash key exists
			//loop through vector of PacketHolders and memcmp
			for(unsigned int i=0; i<LOOKUP[hash].size(); i++){
				if(memcmp(LOOKUP[hash][i].packetdata, data.packetdata, data.length) == 0){
					TOTALREDUNDANCY += data.length;
					TOTALHITS += 1;
					break;
				//else save the data and push it onto the vector
				} else {
					PacketHolder temp;
					memcpy(temp.packetdata, data.packetdata, 2400);
					LOOKUP[hash].push_back(temp);
					STRUCTURE_SIZE += (sizeof(temp));
				}
			}
		} else {//else save the data and push it onto the vector
			PacketHolder temp;
			memcpy(temp.packetdata, data.packetdata, 2400);
			LOOKUP[hash].push_back(temp);
			STRUCTURE_SIZE += (sizeof(temp)+sizeof(ub4));
			KEYS.push_back(hash);
		}
		pthread_mutex_unlock(&lookup_mutex);
	}
	return NULL;
}

// Threaded Process Function for Level 2(consumer)
void * threaded_process_L2(void * pData){
	while(PROCESSEDPACKETS < TOTALPACKETS){
		pthread_mutex_lock(&data_mutex);

		//condition variable and wait
		while(DATA_Q.empty()){
			if (PROCESSEDPACKETS >= TOTALPACKETS) {
				pthread_mutex_unlock(&data_mutex);
				return NULL;
			}
			pthread_cond_wait(&filled, &data_mutex);
		}
		PacketHolder data = DATA_Q.front();
		DATA_Q.pop();
		PROCESSEDPACKETS += 1;
		pthread_mutex_unlock(&data_mutex);

		int startbyte = 0;
		int endbyte = 63;
		int length  = (int)data.length; 
		int hashcounter = 0;
		pthread_mutex_lock(&lookup_mutex);

		//Data Structure Eviction
		if(STRUCTURE_SIZE >= 70000000){
			while(STRUCTURE_SIZE > 60000000){
				int randID = rand() % ID_HASHES.size();		
				vector<ub4> randHashes = ID_HASHES[randID];

				if(ID_PACKET.count(randID)){
					STRUCTURE_SIZE -= sizeof(ID_PACKET[randID]);
					STRUCTURE_SIZE -= sizeof(int);
					ID_PACKET.erase(randID);

					for(unsigned int i=0; i< randHashes.size(); i++){
						STRUCTURE_SIZE -= sizeof(ub4);
						STRUCTURE_SIZE -= sizeof(randHashes[i]);
						HASH_REFERENCE.erase( randHashes[i] );
					}					
				} else{
					continue;
				}
			}
		}
		//End Data Structure Eviction

		//sliding window feature, where we analyze segments of a packet
		while(endbyte < length-1){
			register ub4 h = 0;
			ub4 hash;
			char temp[2400];
			memset(temp, '\0', 2400);
			memcpy(temp, data.packetdata+startbyte, endbyte-startbyte);
			h = hash_function(temp, 2400, h);
			hash = (ub4)h;

			if(HASH_REFERENCE.count(hash)){ //if hash key exists
				//locate the hash the current one has matched with and load it
				Reference old_packet_reference;
				PacketHolder old_packet_holder;
				old_packet_reference = HASH_REFERENCE[hash];
				old_packet_holder = ID_PACKET[old_packet_reference.packet_reference];
				int old_start = old_packet_reference.start_byte;
				int old_end = old_packet_reference.end_byte;
				char old_payload[2400];
				memset(old_payload, '\0', 2400);
				memcpy(old_payload, old_packet_holder.packetdata+old_start, old_end-old_start);

				if(memcmp(temp, old_payload, endbyte-startbyte) == 0){ //if the window of data matches 
					int extra_match = 1;
					//keep going byte by byte until there is a mismatch, or you have exceeded the length of the packet
					while( memcmp(data.packetdata+endbyte+extra_match, old_packet_holder.packetdata+old_end+extra_match, 1)==0 ){
						if (endbyte+extra_match >= length) break;
						extra_match += 1;
					}
					extra_match -= 1;
					startbyte = endbyte+extra_match;
					endbyte = startbyte+63;
					TOTALREDUNDANCY += (64+extra_match);
					TOTALHITS += 1;
					break;
				// else if the key has not been seen, then save the hash, startbyte, endbyte - if the hashcounter is a multiple of 32
				} else {
					if(hashcounter % 32 == 0){ //if there is a 32 bytes gap between hashes, overwrite the old value
						Reference rtemp;
						rtemp.start_byte = startbyte;
						rtemp.end_byte = endbyte;
						rtemp.packet_reference = PROCESSEDPACKETS;
						STRUCTURE_SIZE += sizeof(rtemp); 
						STRUCTURE_SIZE -= sizeof(HASH_REFERENCE[hash]); 
						HASH_REFERENCE[hash] = rtemp;
						ID_HASHES[PROCESSEDPACKETS].push_back(hash);
						if(hashcounter == 0){ //if its the first time seeing this packet, save a reference of it
							PacketHolder ptemp;
							memcpy(ptemp.packetdata, data.packetdata, 2400);
							ID_PACKET[PROCESSEDPACKETS] = ptemp;
							STRUCTURE_SIZE += sizeof(ptemp); 
						}
					}
					startbyte += 1;
					endbyte += 1;
				}
			// else if the key has not been seen, then save the hash, startbyte, endbyte - if the hashcounter is a multiple of 32
			} else {
				if(hashcounter % 32 == 0){ //if there is a 32 bytes gap between hashes, save it
					Reference rtemp;
					rtemp.start_byte = startbyte;
					rtemp.end_byte = endbyte;
					rtemp.packet_reference = PROCESSEDPACKETS;
					HASH_REFERENCE[hash] = rtemp;
					STRUCTURE_SIZE += sizeof(rtemp); 
					ID_HASHES[PROCESSEDPACKETS].push_back(hash);
					if(hashcounter == 0){ //if its the first time seeing this packet, save a copy of it
						PacketHolder ptemp;
						memcpy(ptemp.packetdata, data.packetdata, 2400);
						ID_PACKET[PROCESSEDPACKETS] = ptemp;
						STRUCTURE_SIZE += sizeof(ptemp); 
					}
				}
				//move window
				startbyte += 1;
				endbyte += 1;
			}
			hashcounter += 1;
		}
		pthread_mutex_unlock(&lookup_mutex);
	}
	return NULL;
}

//Hash Code adopted from the Jenkins Hash linked in the project document
/*
 --------------------------------------------------------------------
 hash() -- hash a variable-length key into a 32-bit value
   k       : the key (the unaligned variable-length array of bytes)
   len     : the length of the key, counting by bytes
   initval : can be any 4-byte value
Returns a 32-bit value.  Every bit of the key affects every bit of
the return value.  Every 1-bit and 2-bit delta achieves avalanche.
About 6*len+35 instructions.

The best hash table sizes are powers of 2.  There is no need to do
mod a prime (mod is sooo slow!).  If you need less than 32 bits,
use a bitmask.  For example, if you need only 10 bits, do
  h = (h & hashmask(10));
In which case, the hash table should have hashsize(10) elements.

If you are hashing n strings (ub1 **)k, do it like this:
  for (i=0, h=0; i<n; ++i) h = hash( k[i], len[i], h);

By Bob Jenkins, 1996.  bob_jenkins@burtleburtle.net.  You may use this
code any way you wish, private, educational, or commercial.  It's free.

See http://burtleburtle.net/bob/hash/evahash.html
Use for hash table lookup, or anything where one collision in 2^^32 is
acceptable.  Do NOT use for cryptographic purposes.
--------------------------------------------------------------------
*/

ub4 hash_function(char k[2400], unsigned long int length, register ub4 initval)
{
	//cout << "HASH DATA \n";
	//cout << "    " << k << endl;
   register ub4 a,b,c,len;

   /* Set up the internal state */
   len = length;
   a = b = 0x9e3779b9;  /* the golden ratio; an arbitrary value */
   c = initval;         /* the previous hash value */

   /*---------------------------------------- handle most of the key */
   while (len >= 12)
   {
      a += (k[0] +((ub4)k[1]<<8) +((ub4)k[2]<<16) +((ub4)k[3]<<24));
      b += (k[4] +((ub4)k[5]<<8) +((ub4)k[6]<<16) +((ub4)k[7]<<24));
      c += (k[8] +((ub4)k[9]<<8) +((ub4)k[10]<<16)+((ub4)k[11]<<24));
      mix(a,b,c);
      k += 12; len -= 12;
   }

   /*------------------------------------- handle the last 11 bytes */
   c += length;
   switch(len)              /* all the case statements fall through */
   {
   case 11: c+=((ub4)k[10]<<24);
   case 10: c+=((ub4)k[9]<<16);
   case 9 : c+=((ub4)k[8]<<8);
      /* the first byte of c is reserved for the length */
   case 8 : b+=((ub4)k[7]<<24);
   case 7 : b+=((ub4)k[6]<<16);
   case 6 : b+=((ub4)k[5]<<8);


   case 5 : b+=k[4];
   case 4 : a+=((ub4)k[3]<<24);
   case 3 : a+=((ub4)k[2]<<16);
   case 2 : a+=((ub4)k[1]<<8);
   case 1 : a+=k[0];
     /* case 0: nothing left to add */
   }
   mix(a,b,c);
   /*-------------------------------------------- report the result */
   return c;
}
