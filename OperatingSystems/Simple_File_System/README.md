project6: File Systems
John Villaflor (jvillafl)
Andrew Bub (abub)
Molly Pierce (mpierce3)
Erica Boyd (eboyd)

Built a file system from scratch, called SimpleFs, which is very similar to the Unix inode layer. 
Each "file" is identified by an integer called an "inumber".
The inumber is simply an index into the array of inode structures that starts in block one. When a file is
created, SimpleFS chooses the first available inumber and returns it to the user. All further references to that
file are made using the inumber.

The SimpleFS system has three major components: the shell, the filesystem itself, and the emulated disk.

SimpleFS has the following layout on disk. It assumes that disk blocks are the common size of 4KB. The first
block of the disk is a "superblock" that describes the layout of the rest of the filesystem. A certain number of
blocks following the superblock contain inode data structures. Typically, ten percent of the total number of
disk blocks are used as inode blocks. The remaining blocks in the filesystem are used as plain data blocks,
and occasionally as indirect pointer blocks.
Each field of the superblock is a 4-byte (32-bit) integer. The first field is always the "magic" number
FS_MAGIC (0xf0f03410) The format routine places this number into the very first bytes of the superblock as
a sort of filesystem "signature". When the filesystem is mounted, the OS looks for this magic number. If it is
correct, then the disk is assumed to contain a valid filesystem. If some other number is present, then the
mount fails, perhaps because the disk is not formatted or contains some other kind of data.
The remaining fields in the superblock describe the layout of the filesystem. nblocks is the total number of
blocks, which should be the same as the number of blocks on the disk. ninodeblocks is the number of blocks
set aside for storing inodes. ninodes is the total number of inodes in those blocks. The format routine is
responsible for choosing ninodeblocks: this should always be 10 percent of nblocks, rounding up. Note that
the superblock data structure is quite small: only 16 bytes. The remainder of disk block zero is left unusued.
Each field of the inode is a 4-byte (32-bit) integer. The isvalid field is one if the inode is valid (i.e. has been
created) and is zero otherwise. The size field contains the logical size of the inode data in bytes. There are 5
direct pointers to data blocks, and one pointer to an indirect data block. In this context, "pointer" simply
means the number of a block where data may be found. A value of zero may be used to indicate a null block
pointer. Each inode occupies 32 bytes, so there are 128 inodes in each 4KB inode block.
