/*
Main program for the virtual memory project.
Make all of your modifications to this file.
You may add or rearrange any code or data as you need.
The header files page_table.h and disk.h explain
how to use the page table and disk interfaces.
*/

#include "page_table.h"
#include "disk.h"
#include "program.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <time.h>

// GLOBALS
const char *algorithm;
struct disk *disk;
char *virtmem;
char *physmem;
int num_page_faults;
int num_access_faults;
int num_disk_reads;
int num_disk_writes;
int nframes;
int npages;
int phys_free[1024];

// Globals for fifo
int FIFO[4096];
int popindex=0;
int pushindex=0;

// Globals for NRU (custom)
int NRU[4096];
int NRU_popindex=0;
int NRU_pushindex=0;
int BUFFSIZE; // number of "recently used" pages = nframes/BUFFSIZE

void page_fault_handler( struct page_table *pt, int page)
{
	int frame;
	int bits;
	page_table_get_entry(pt, page, &frame, &bits);	
	int frame_num;	

	// Check permission bits
	if (!(bits&PROT_READ)) {
		num_page_faults++;
		bool found_free = false;
		int i;
		for (i=0; i<nframes; i++) {
			if (phys_free[i] == 0) {
				found_free = true;
				frame_num = i;
				page_table_set_entry(pt, page, frame_num, PROT_READ);

				//if fifo, push onto Q
				if (strcmp(algorithm, "fifo") == 0) {
					FIFO[pushindex] = page;
					pushindex += 1;
				}

				//if custom, push to buffer 
				if (strcmp(algorithm, "custom") == 0) {
					NRU[NRU_pushindex] = page;
					NRU_pushindex++;
					if (NRU_pushindex-NRU_popindex == nframes/BUFFSIZE)	
						NRU_popindex++;
				}

				disk_read(disk, page, &physmem[frame_num*PAGE_SIZE]); 
				phys_free[i] = 1;
				num_disk_reads++;
				break;	
			}
		}

		if (!found_free)	{	
			// Implement proper algorithm
			if (strcmp(algorithm, "rand") == 0) {
				// Check what was previously in a random spot in physcial memory
				int prev_bits = 0;
				int pagenum;
				while (!(prev_bits&PROT_READ)) {
					pagenum = rand() % npages;
					page_table_get_entry(pt, pagenum, &frame_num, &prev_bits);	
				}
				// Check that spot in vitual memory to see it it has write permissions
				// If it does, write that value back to disk and remove from virtual
				if (prev_bits&PROT_WRITE) {
					disk_write(disk, pagenum, &physmem[frame_num*PAGE_SIZE]);	
					num_disk_writes++;
				}
				page_table_set_entry(pt, pagenum, 0, 0);
				page_table_set_entry(pt, page, frame_num, PROT_READ);
				disk_read(disk, page, &physmem[frame_num*PAGE_SIZE]); 
				num_disk_reads++;
					
			} else if (strcmp(algorithm, "fifo") == 0) {
				int pagenum;
				int prev_bits = 0;
				// Pop from queue to get pagenum
				pagenum = FIFO[popindex];
				popindex += 1;
				page_table_get_entry(pt, pagenum, &frame_num, &prev_bits);	

				//printf("      popping %d\n", pagenum);
				
				// Check that spot in vitual memory to see it it has write permissions
				// If it does, write that value back to disk and remove from virtual
				if (prev_bits&PROT_WRITE) {
					disk_write(disk, pagenum, &physmem[frame_num*PAGE_SIZE]);	
					num_disk_writes++;
				}
				page_table_set_entry(pt, pagenum, 0, 0);
				page_table_set_entry(pt, page, frame_num, PROT_READ);

				//if fifo, push onto Q
				FIFO[pushindex] = page;
				pushindex += 1;

				disk_read(disk, page, &physmem[frame_num*PAGE_SIZE]); 
				num_disk_reads++;
			} else if (strcmp(algorithm, "custom") == 0) {
				// Our implementation is a Not Recently Used strategy
				// Check what was previously in a random spot in physcial memory
				int prev_bits = 0;
				int pagenum;
				while (!(prev_bits&PROT_READ)) {
					pagenum = rand() % npages;
					page_table_get_entry(pt, pagenum, &frame_num, &prev_bits);
					int i;
					// Check if that page has been recently used
					for (i = NRU_popindex; i <= NRU_pushindex; i++) {
						if (pagenum == NRU[i]) {
							prev_bits = 0;
							
							break;
						}	
					}
				}
				// Check that spot in vitual memory to see it it has write permissions
				// If it does, write that value back to disk and remove from virtual
				if (prev_bits&PROT_WRITE) {
					disk_write(disk, pagenum, &physmem[frame_num*PAGE_SIZE]);	
					num_disk_writes++;
				}
				page_table_set_entry(pt, pagenum, 0, 0);
				page_table_set_entry(pt, page, frame_num, PROT_READ);
				
				// Push the new page to recently used and update the index	
				NRU[NRU_pushindex] = page;
				NRU_pushindex++;
				if (NRU_pushindex-NRU_popindex == nframes/BUFFSIZE)	
					NRU_popindex++;

				disk_read(disk, page, &physmem[frame_num*PAGE_SIZE]); 
				num_disk_reads++;
					
			} else {
				fprintf(stderr,"unknown approach\n");
				exit(1);
			}
		}

		return;

	} else if (!(bits&PROT_WRITE)) {
		num_access_faults++;
		page_table_set_entry(pt, page, frame, PROT_READ|PROT_WRITE);
		return;
	}

}

int main( int argc, char *argv[] )
{
	srand(1);
	if(argc!=5) {
		printf("use: virtmem <npages> <nframes> <rand|fifo|lru|custom> <sort|scan|focus>\n");
		return 1;
	}

	npages = atoi(argv[1]);
	nframes = atoi(argv[2]);
	// BUFFSIZE determines the size of the NRU buffer
	// It depends on the number of frames
	if (nframes < 10) BUFFSIZE = 3;
	else BUFFSIZE = 10;
	if (npages < 3 || nframes < 3) {
		fprintf(stderr,"Too few pages or frames. Must be greater than 2\n");
		return 1;
	}
	if (npages < nframes){
		fprintf(stderr,"Number of pages must be greater than or equal to the number of frames.\n");
		return 1;
	}

	algorithm = argv[3];
	const char *program = argv[4];
	num_page_faults = 0;
	num_access_faults = 0;
	num_disk_reads = 0;
	num_disk_writes = 0;

	int i;
	for (i=0; i<nframes; i++) {
		phys_free[i] = 0;
	}


	disk = disk_open("myvirtualdisk",npages);
	if(!disk) {
		fprintf(stderr,"couldn't create virtual disk: %s\n",strerror(errno));
		return 1;
	}

	struct page_table *pt = page_table_create( npages, nframes, page_fault_handler );
	if(!pt) {
		fprintf(stderr,"couldn't create page table: %s\n",strerror(errno));
		return 1;
	}

	virtmem = page_table_get_virtmem(pt);
	physmem = page_table_get_physmem(pt);

	if(!strcmp(program,"sort")) {
		sort_program(virtmem,npages*PAGE_SIZE);

	} else if(!strcmp(program,"scan")) {
		scan_program(virtmem,npages*PAGE_SIZE);

	} else if(!strcmp(program,"focus")) {
		focus_program(virtmem,npages*PAGE_SIZE);

	} else {
		fprintf(stderr,"unknown program: %s\n",argv[3]);
		return 1;
	}

	page_table_delete(pt);
	disk_close(disk);
	
	printf("Real Page Faults: %d\n", num_page_faults);
	printf("Access Page Faults: %d\n", num_access_faults);
	printf("\nTotal Page Faults: %d\n", num_page_faults+num_access_faults);
	printf("Disk Reads:  %d\n", num_disk_reads);
	printf("Disk Writes: %d\n", num_disk_writes);

	return 0;
}
