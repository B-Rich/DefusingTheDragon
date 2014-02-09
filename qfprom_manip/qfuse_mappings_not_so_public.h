//--------------------------------------------------------
// Just some "borrowed" and "discovered" defines...
//		nothing to see here ;)
//
//--------------------------------------------------------

//--------------------------------------------------------
// m0nk's mappings from the Qualcomm Doc Dump
//
//	So, this is where we get kinda awkward.  XDA and other "open source" intel
//		claims that the eFuse block is 4k in size and that the whole thing is mapped
//		into "shawdow" mem at roughly 0x706000. The "leaked" docs claim the 8960 actually
//		hosts a 16k fuse block. It further states that "some" of the fuses are accessilbe via
//		shadow mem, but others are only mapped via registers.
//
//	Below is a simple mapping of what is known from physical layout, no offsets provided and no
//		promise that the values are actually mapped into RAM
//--------------------------------------------------------

// 0x000 - 0x4AC (the first 19 rows of 64 bits) are marked "reserved"
#define LOWER_JTAG_ID 					0x500	//Value for bits 9:0 
#define LOWER_JTAG_ID_FEC				0x50B	//Unknown length (assuming 5 by deduction), so the rest of the JTAG ID may be incorrect...
#define UPPER_JTAG_ID 					0x510	//Value for bits 19:10				
#define UPPER_JTAG_ID_FEC 				0x51B	//Unknown length (assuming 5 by deduction)
#define ALL_WRITE_PERMISSIONS			0x540 	// Values from 63:0
#define ALL_READ_PERMISSIONS			0x580 	// Values from 63:0
#define PTE_FUSED						0x5C0	// Values from 63:0
// 64 bits at 0x600 are "reserved"
#define FIRST_RESERVED_BLOCK_START		0x640	// Unsure what the block is, but it is big
#define FIRST_RESERVED_BLOCK_STOP 		0xF3F 	// See, I told you!  Maybe you should start listening to me more often.
#define OEM_ANTI_REPLAY					0xF40	// Values from 63:0
// Format for the rest of the data blocks (63 -> 0)
// 	[63 : 61]	3 bits FEC
//	[60 : 60]	0
//	[59 : 55]	5 bits FEC
//	[54 : 45]	10 bits data
//	[44 : 40]	5 bits FEC
//	[39 : 30]	10 bits data
//	[29 : 25]	5 bits FEC
//	[24 : 15]	10 bits data
//	[14 : 10]	5 bits FEC
//	[09 : 00]	10 bits data

//After base + 0x17C0, there be dragons... the fuses SHOULD extend all the way to: 0x4000.
// One thing that is probably up here is the "Customer private key (general-purpose 2048-bit for use by OEMs or carriers)"

