Project 4: Threaded Redundancy Elimination
Group Members: Erica Boyd (eboyd), John Villaflor (jvillafl), Molly Pierce (mpierce3), Andrew Bub (abub)

Description of Code:
Our code is split up into 4 central functions and a main function. Our main function deals with the command line arguments, and reads in the file, level, and number of threads. 
For level 1, each file is processed into packets by the function getPacketsInfo, which takes the name of a file and outputs a vector of tuples. Each tuple contains the size of the packet, and where each packet starts in terms of byte address of the file. The vector contains all the packet information in the file, skipping the bytes that are not essential to the packet (such as the header fields). After the packet information is stored, the number of threads specified by the command line argument are created. The number of threads is then split up into consumer threads and producer threads, as explained below (in strategy for threading). The producer threads call the threaded_read function, where they read in each packet based on the information in the vector of tuples (PacketsInfo). Once the entire packet is read, it is saved into the global variable DATA_Q, and the condition variable filled is signaled to let the consumer know that the queue has information in it to be processed. The consumer threads then call the function threaded_processes which is where each thread is processed by the function hash_function. The hash_function is a modified version of Jenkin's hash (modifed fromthe Jenkins code linked in the project document) that is able to take in a char buffer and outputs a digest as a ub4 type (unsigned long int). The consumer threads then use this hash to look up if the hash already exists in the LOOKUP data structure. If the hash exists in the key of the LOOKUP map, then the total redundancy is increased by the length of the packet, and the total hits is incremented by 1. If it does not exist, the hash is added as a key to the LOOKUP, and the packet is added to the vector. At the very end of the program, the amount of MB processed, total hits, and % redundancy in total of all the files is outputted.

For level 2, a second consumer thread function was created. In threaded_process_L2 we implemented the "sliding window" feature to crawl along each packet in a 64byte window. If it recognized those 64bytes (by the hash) then it would compare each byte past the window (for example the 65th byte) until it reached the end of the packet or it found two different bytes.  

In order to calculate the percent redundancy we used a TOTALREDUNDANCY counter and a TOTALSIZE counter. The TOTALSIZE counter was increased by the packet size 
of each of the packets that were in the correct range and not including the first 52 bytes of each packet (the bytes we were supposed to ignore).  Each time that
we found a redundant packet we added that amount of bytes to TOTALREDUNDANCY.  In level 1, since it only matched full packets, it would add the packet size (not
including those first 52 bytes).  In level 2, we added as many bits as found to be identical as we went along each packet.  We calculated the percent shown as
TOTALREDUNDANCY/TOTALSIZE * 100.

Strategy for threading:
For threading, we split up the number of threads inputted by the user into consumer threads and producer threads (half go to the consumer, and half go to the producer). In order to decide which part of the packet to read in, the producer threads are created based on arithmeticso that no producer thread reads the same packet (i.e. the work is divided up among threads). As discussed above, the producer threads call the function threaded_read in order to read in the packet and store the information in a PacketHolder called temp. Each packet has corresponding data in the global variable PacketsInfo which is read in at the beginning of the program. Once the packet is read and stored, we lock the program, increment the total size and push the packet information into the data queue (DATA_Q). 
Because this means there is information ready to be processed, the condition variable filled is then signaled and the mutex unlocks. Each consumer thread goes into the threaded_process function, where it waits until the queue is not empty in order to begin processing. If the queue is not empty, and the lock is free, then the data from the queue is popped and the packet information is passed into the hash_function (for both level 1 and level 2). Once the hash is received, the mutex is locked (using the lookup mutex) and if the hash appears in the lookup map, then the redundancy is increased and the total hits is incremented. If not, the hash is added to the map, and then the mutex is unlocked. By splitting up our threads this way, we figured we could increase efficiency, because one thread would be producing the data and other threads consuming the data by calling the hash function. 

Strategy for cache eviction:
For cache eviction, we are using a random method to determine which piece of data to remove. Given that we have some room for error, we only check
when the size of the total Redundancy Data Structures (RDS) is >70MB. We keep track of the size of our RDS using a counter variable (so that we 
don't have to recalculate the sizes on every iteration). Whenever we have to resize our RDS, we delete elements until the size of the RDS is <60MB.
We implemented our random strategy by keeping a separate data structure that indexed all of our Keys (level1) or all of our 
Packet IDs and References (level2). 
For level1 we picked a random Key from the separate data structure and then deleted it from our Lookup table until the size of the Lookup table was <60MB.
For level2, this strategy involved picking a random packet to evict (we picked a random packetID) from our ID_PACKETS structure. We then deleted the
packet data and also any references to this packet in our HASH_REFERENCES structure. We continued this until the size of both data structures was <60MB.

Performance for Level 1:
	2 Threads:
		107.459 MB (Dataset-Big.pcap) processed in 1.253 seconds = 85,761 KB/sec
	Optimal Threads:
		7 Threads: 107.459 MB (Dataset-Big.pcap) processed in 1.059 seconds = 101,472 KB/sec

Performance for Level 2:
	2 Threads:
		107.459 MB (Dataset-Big.pcap) processed in 318.296 s = 337.607 KB/sec
	Optimal Threads:
		As we tested more threads, the time for the program to run increased. Therefore, 2 threads was the fasted process time for level 2. 
