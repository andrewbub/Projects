#include "fs.h"
#include "disk.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <math.h>

#define FS_MAGIC           0xf0f03410
#define INODES_PER_BLOCK   128
#define POINTERS_PER_INODE 5
#define POINTERS_PER_BLOCK 1024

struct fs_superblock {
	int magic;
	int nblocks;
	int ninodeblocks;
	int ninodes;
};

struct fs_inode {
	int isvalid;
	int size;
	int direct[POINTERS_PER_INODE];
	int indirect;
};

union fs_block {
	struct fs_superblock super;
	struct fs_inode inode[INODES_PER_BLOCK];
	int pointers[POINTERS_PER_BLOCK];
	char data[DISK_BLOCK_SIZE];
};

int INODE_BITMAP[20*INODES_PER_BLOCK]; // bitmap for allocating inode information	
int DATA_BITMAP[200]; // bitmap for allocating data block information
int MOUNTED = 0; // flag to remember if file system is mounted
void inode_load(int inumber, struct fs_inode *inode); 
void inode_save(int inumber, struct fs_inode *inode); 
int find_block_no_from_index(struct fs_inode *inode, int block_index);
int min(int input1, int input2);
int find_next_data_block();
void free_inode(int inumber);

//create new file system on the disk
int fs_format()
{
	union fs_block block;
	disk_read(0,block.data);
	if(MOUNTED) return 0;

	int numblocks;
	int numinodeblocks;
	numblocks = disk_size();	
	numinodeblocks = ceil(0.1*numblocks);

	union fs_block superblock;
	superblock.super.magic = FS_MAGIC;
	superblock.super.nblocks = numblocks;
	superblock.super.ninodeblocks = numinodeblocks;
	superblock.super.ninodes = numinodeblocks*INODES_PER_BLOCK;

	disk_write(0, superblock.data);

	int i;
	for (i = 1; i <= numinodeblocks; i++) {
		union fs_block inodeblock;
		int j;
		for (j = 0; j < 128; j++) {
			inodeblock.inode[j].isvalid = 0;
		}
		disk_write(i, inodeblock.data);
	}	
	
	return 1;
}

//walk through the inodes and output size and in/direct data blocks
void fs_debug()
{
	union fs_block block;
	disk_read(0, block.data);

	printf("superblock:\n");
	if(block.super.magic == FS_MAGIC)
		printf(" magic number is valid\n");
	else
		printf(" magic number is invalid\n");
	printf("   %d blocks on disk\n",block.super.nblocks);
	printf("   %d blocks for inode\n",block.super.ninodeblocks);
	printf("   %d inodes total\n",block.super.ninodes);

	int block_num;
	int inode_counter = -1;

	for(block_num=1; block_num<=block.super.ninodeblocks; block_num++){
		union fs_block temp;
		disk_read(block_num, temp.data);

		int i;
		for(i=0; i<INODES_PER_BLOCK; i++){
			inode_counter++;
			if(inode_counter >= block.super.ninodes) return; 
			struct fs_inode curr_inode = temp.inode[i];

			if(curr_inode.isvalid == 1){
				printf("inode %d:\n", (inode_counter));
				printf("	size: %d\n", curr_inode.size);

				int num_direct = ceil(curr_inode.size / 4096.0);

				if (num_direct == 0) continue;
				
				if(num_direct <= POINTERS_PER_INODE){
					int j;
					printf("	direct blocks:");
					for(j=0; j<num_direct; j++)
						printf(" %d  ",curr_inode.direct[j]);
					printf("\n");
				} else {
					int j;
					printf("	direct blocks:");
					for(j=0; j<POINTERS_PER_INODE; j++)
						printf(" %d  ",curr_inode.direct[j]);
					printf("\n");

					printf("	indirect block: %d", curr_inode.indirect);
					union fs_block indirect;
					disk_read(curr_inode.indirect, indirect.data);
					printf("\n\tindirect data blocks:");
					int pointer_index;
					for(pointer_index=0; pointer_index<POINTERS_PER_BLOCK; pointer_index++){
						if(indirect.pointers[pointer_index] == 0) break;
						printf(" %d  ", indirect.pointers[pointer_index]);
					}
					printf("\n");
				}
			}
		}
	}

}

//create and walk the bitmaps
int fs_mount()
{
	union fs_block block;

	disk_read(0, block.data);
	if(block.super.magic != FS_MAGIC) return 0;

	memset(&DATA_BITMAP, -1, sizeof(DATA_BITMAP));
	memset(&INODE_BITMAP, -1, sizeof(INODE_BITMAP));

	int i;

	for (i = 1+block.super.ninodeblocks; i < block.super.nblocks; i++) {
		DATA_BITMAP[i] = 0;
	}
	for (i = 0; i < block.super.ninodes; i++) {
		INODE_BITMAP[i] = 0;
	}

	int block_num;
	int inode_counter = 0;

	for(block_num=1; block_num<=block.super.ninodeblocks; block_num++){
		union fs_block temp;
		disk_read(block_num, temp.data);

		int i;
		for(i=0; i<INODES_PER_BLOCK; i++){
			if(inode_counter >= block.super.ninodes) return 0; 
			struct fs_inode curr_inode = temp.inode[i];
			if(curr_inode.isvalid == 1){
				INODE_BITMAP[inode_counter] = 1;
				int num_direct = ceil(curr_inode.size / 4096.0);

				if(num_direct <= POINTERS_PER_INODE){
					int j;
					for(j=0; j<num_direct; j++)
						DATA_BITMAP[curr_inode.direct[j]] =1;
				} else {
					int j;
					for(j=0; j<POINTERS_PER_INODE; j++)
						DATA_BITMAP[curr_inode.direct[j]] = 1;
					DATA_BITMAP[curr_inode.indirect] = 1;

					union fs_block indirect;
					disk_read(curr_inode.indirect, indirect.data);

					int pointer_index;
					for(pointer_index=0; pointer_index<POINTERS_PER_BLOCK; pointer_index++){
						if(indirect.pointers[pointer_index] == 0) break;
						DATA_BITMAP[indirect.pointers[pointer_index]] = 1;
					}
				}
			}
			inode_counter++;
		}
	}
	
	MOUNTED = 1;
	return 1;
}

int fs_create()
{
	if (MOUNTED == 0) return 0;	

	int inumber = find_next_inode();
	if (inumber == -1) return 0;

	struct fs_inode newinode;
	newinode.isvalid = 1;
	newinode.size = 0;
	newinode.direct[0] = 0;
	newinode.direct[1] = 0;
	newinode.direct[2] = 0;
	newinode.direct[3] = 0;
	newinode.direct[4] = 0;
	newinode.indirect = 0;

	inode_save(inumber, &newinode);

	INODE_BITMAP[inumber] = 1;
	return inumber;
}

//walk through an inode and delete it's data and update the bitmaps
int fs_delete( int inumber )
{
	if (MOUNTED == 0) return 0;	

	struct fs_inode inodetodelete;
	inode_load(inumber, &inodetodelete);
	if (inodetodelete.isvalid == 0) return 0;
	int num_direct = ceil(inodetodelete.size / 4096.0);
	if(num_direct <= POINTERS_PER_INODE){
		int j;
		for(j=0; j<num_direct; j++)
			DATA_BITMAP[inodetodelete.direct[j]] =0;
	} else {
		int j;
		for(j=0; j<POINTERS_PER_INODE; j++)
			DATA_BITMAP[inodetodelete.direct[j]] = 0;
		DATA_BITMAP[inodetodelete.indirect] = 0;

		union fs_block indirect;
		disk_read(inodetodelete.indirect, indirect.data);

		int pointer_index;
		for(pointer_index=0; pointer_index<POINTERS_PER_BLOCK; pointer_index++){
			if(indirect.pointers[pointer_index] == 0) break;
			DATA_BITMAP[indirect.pointers[pointer_index]] = 0;
		}
	}
	INODE_BITMAP[inumber] = 0;
	inodetodelete.isvalid = 0;
	inodetodelete.size = 0;
	inodetodelete.direct[0] = 0;
	inodetodelete.direct[1] = 0;
	inodetodelete.direct[2] = 0;
	inodetodelete.direct[3] = 0;
	inodetodelete.direct[4] = 0;
	inodetodelete.indirect = 0;
	inode_save(inumber, &inodetodelete);
	return 1;
}

int fs_getsize( int inumber )
{
	if (MOUNTED == 0) return -1;	

	struct fs_inode inode;
	inode_load(inumber, &inode);

	if (inode.isvalid == 0) return -1;
	
	return inode.size;	

}

//return the block number from what its inode index is
int find_block_no_from_index(struct fs_inode *inode, int block_index) {
    if (block_index < POINTERS_PER_INODE) {
        return inode->direct[block_index];
    } else {
        union fs_block block;
        disk_read(inode->indirect, block.data);
        return block.pointers[block_index - POINTERS_PER_INODE];
    }
}

int min(int input1, int input2) {
	if (input1 <= input2) return input1;
	else return input2;
}

int fs_read( int inumber, char *data, int length, int offset )
{
	if (MOUNTED == 0){
		printf("ERROR: Mount First\n");
		return -1;	
	}
	struct fs_inode inode;
	inode_load(inumber, &inode);

	// check if the inode is valid
	if (inode.isvalid == 0) return 0; 

	// ensure the offset doesn't want you to start after the end of the data
	if (offset >= inode.size) return 0; 

	// reset the length if it goes over the file size
	if (length+offset > inode.size) 
		length = inode.size-offset;

	int bytesread = 0;
	union fs_block block;
   int starting_block_index = offset / DISK_BLOCK_SIZE;
   int ending_block_index = (offset + length) / DISK_BLOCK_SIZE;
	int block_index;
	
   for (block_index = starting_block_index; block_index <= ending_block_index; block_index++) {
		int block_no = find_block_no_from_index(&inode, block_index);
        
		// Read data into block
		disk_read(block_no, block.data);
        
      // Copy data from block to destination
		int bytes_to_read = min(length, DISK_BLOCK_SIZE);
		memcpy(data + bytesread, block.data, bytes_to_read);
		length -= bytes_to_read;
		bytesread += bytes_to_read;
	}
	return bytesread;
}


int fs_write( int inumber, const char *data, int length, int offset )
{
	if (MOUNTED == 0){
		printf("ERROR: Mount First\n");
		return -1;	
	}    

	struct fs_inode inode;
	inode_load(inumber, &inode);

	//If it is your first time opening this inode, scrap whatever was inside
	if(offset == 0){
		free_inode(inumber);
		inode_load(inumber, &inode);
		if(length > DISK_BLOCK_SIZE * POINTERS_PER_INODE){
			inode.indirect = find_next_data_block();
			if(inode.indirect == -1) return 0;
			union fs_block block;
			memset(&block, 0, sizeof(block));
			disk_write(inode.indirect, block.data);
			DATA_BITMAP[inode.indirect] = 1;
		}
	}

	// check if the inode is valid
	if (inode.isvalid == 0) return 0; 

	int totalbyteswrote = 0;
	//union fs_block block;
   int starting_block_index = offset / DISK_BLOCK_SIZE;
   int ending_block_index = (offset + length) / DISK_BLOCK_SIZE;
	int block_index;

    for (block_index = starting_block_index; block_index <= ending_block_index; block_index++) {
		//UPDATE INODE STRUCTURE
		int new_data_block_no = find_next_data_block();
		if (new_data_block_no == -1) return 0;
		DATA_BITMAP[new_data_block_no] = 1;

		int bytes_to_write = min(length, DISK_BLOCK_SIZE);

		//direct
		if(block_index < 5) {
			inode.direct[block_index] = new_data_block_no;
		//indirect
		} else {
			union fs_block block;
			disk_read(inode.indirect, block.data);
			block.pointers[block_index-POINTERS_PER_INODE] = new_data_block_no;
			disk_write(inode.indirect, block.data);
		}
		inode.size += bytes_to_write;
		inode_save(inumber, &inode);
		//END UPDATE INODE//
		
		//WRITE GIVEN DATA TO THE ACTUAL BLOCK//
		union fs_block data_block_to_save;
		memcpy(data_block_to_save.data, data+totalbyteswrote, bytes_to_write);
		disk_write(new_data_block_no, data_block_to_save.data);

		length -= bytes_to_write;
		totalbyteswrote += bytes_to_write;
	}
	return totalbyteswrote;
}

//clean the inode, free the bitmaps 
void free_inode(int inumber){
	struct fs_inode inodetodelete;
	inode_load(inumber, &inodetodelete);
	int num_direct = ceil(inodetodelete.size / 4096.0);
	if(num_direct <= POINTERS_PER_INODE){
		int j;
		for(j=0; j<num_direct; j++)
			DATA_BITMAP[inodetodelete.direct[j]] =0;
	} else {
		int j;
		for(j=0; j<POINTERS_PER_INODE; j++)
			DATA_BITMAP[inodetodelete.direct[j]] = 0;
		DATA_BITMAP[inodetodelete.indirect] = 0;

		union fs_block indirect;
		disk_read(inodetodelete.indirect, indirect.data);

		int pointer_index;
		for(pointer_index=0; pointer_index<POINTERS_PER_BLOCK; pointer_index++){
			if(indirect.pointers[pointer_index] == 0) break;
			DATA_BITMAP[indirect.pointers[pointer_index]] = 0;
		}
	}
	inodetodelete.size = 0;
	inodetodelete.direct[0] = 0;
	inodetodelete.direct[1] = 0;
	inodetodelete.direct[2] = 0;
	inodetodelete.direct[3] = 0;
	inodetodelete.direct[4] = 0;
	inodetodelete.indirect = 0;
	inode_save(inumber, &inodetodelete);
}

int find_next_inode()
{
	int i;
	for (i=1; i<20*INODES_PER_BLOCK; i++) {
		if (INODE_BITMAP[i] == 0) return i;
	}
	return -1;
}

int find_next_data_block()
{
	int i;
	for (i=1; i<200; i++) {
		if (DATA_BITMAP[i] == 0) return i;
	}
	return -1;
}

//read inode
void inode_load(int inumber, struct fs_inode *inode) 
{
	int inodenumber = inumber%128;
	int iblock = ceil(inumber/128.0);

	union fs_block inodeblock;
	disk_read(iblock, inodeblock.data);

	*inode = inodeblock.inode[inodenumber];
}

//write inode to disk
void inode_save(int inumber, struct fs_inode *inode) 
{
	int inodenumber = inumber%128;
	int iblock = (inumber/128.0)+1;

	union fs_block inodeblock;
	disk_read(iblock, inodeblock.data);

	inodeblock.inode[inodenumber].isvalid = inode->isvalid;
	inodeblock.inode[inodenumber].size = inode->size;
	inodeblock.inode[inodenumber].direct[0] = inode->direct[0];
	inodeblock.inode[inodenumber].direct[1] = inode->direct[1];
	inodeblock.inode[inodenumber].direct[2] = inode->direct[2];
	inodeblock.inode[inodenumber].direct[3] = inode->direct[3];
	inodeblock.inode[inodenumber].direct[4] = inode->direct[4];
	inodeblock.inode[inodenumber].indirect = inode->indirect;

	disk_write(iblock, inodeblock.data);
}
