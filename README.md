DefusingTheDragon - Fun from POC || GTFO
=================

Earlier this year, Nathan Keltner and I started down the curious path of Qualcomm SoC security. The boot chain in particular piqued my interest, the lack of documentation double it... the following is a portion of the results. (btw: thx mudge).

Qualcomm internally utilizes a 16kb bank of one time programmable fuses (named QFPROM by the manufacturer) on the Snapdragon S4 Pro SoC (MSM8960) as well as the other processors manufactured. These fuses, though publicly undocumented, are purported to hold the bulk of inter-chip configuration settings as well as the cryptographic keys to the device. Analysis of leaked documentation has shown that the fuses contain the primary hardware keys used to verify the Secure Boot 3.0 process as well as the cryptographic information used to secure Trust Zone and other security related functionality embedded in the chip. Furthermore, the fuse bank controls hardwired security paths for Secure Boot functionality (including where on disk to acquire the bootable images). The 16k block of fuses also contains space for end user cryptographic key storage and vendor specific configurations.

These one time programmable fuses are not intended to be directly accessed by the end user of the device and in some cases, such as the basic cryptographic keys, the Android kernel itself is not allowed to view the contents of the QFPROM block. These fuses and keys are documented to be hardware locked and accessible only by very controlled paths. Preliminary research has shown the and unknown 4k subset of the 16k block is mapped into the kernel IMEM at physical location 0x700000. The fuses are also documented to be shadowed at 0x704000 in memory. Furthermore, there exists somewhat unused source code from the Code Aurora project in the Android kernel that documents how to read and write to the 4k block of exposed fuses.

Aside from the Aurora code, most vendors have also created and publicly shared code to play with the fuses. LG is the exemplar here, with a wonderful little kernel module that maps and explores LG specific bit-flags. In general, there is an acceptable amount of existing code that will walk an interested person through the process.

Below are simplistic excerpts for my tool that should help you explore these toys with a little more granularity. To note, writing eFuse or QFPROM values can and probably will brick your device, so be careful. A last interesting tidbit though, and one that will hopefully entice the reader... SoC and other hardware debugging is typically turned off with a blown fuse. This becomes interesting because there exists a secondary fuse that turns this functionality back on (specifically for the use of RMA and other requests). Also as stated, the fuses hold the blueprint for where and how Secure Boot 3.0 works as well as where the device should look for binary blobs to load during setup phases. 

//--------------------------------------------------------
// Before we can crawl, we must have appendages
//--------------------------------------------------------
static int map_the_things (void) 
{
	uint32_t i;
	uint8_t stored_data_temp;


	//--------------------------------------------------------
	// Stage 1: Hitting the eFuse memory directly (this is not supposed to work)
	//--------------------------------------------------------
	pr_info("m0nk -> and we run until we read: %i lovely bytes\n", QFPROM_FUSE_BLOB_SIZE);

	for (i = 0; i < QFPROM_FUSE_BLOB_SIZE; i++) {
		
		stored_data_temp = readb_relaxed((QFPROM_BASE_MAP_ADDRESS + i));

	 	if (!stored_data_temp) {
	 		pr_info("m0nk -> location: , byte number: %i, has no valid value\n", i);
	 		base_fuse_map[i] = 0;
	 	}else{
	 		pr_info("\tm0nk -> location: , byte number: %i, has value: %x\n", i, stored_data_temp);
	 		base_fuse_values[i] = stored_data_temp;
	 		base_fuse_map[i] = 1;
	 	}
	}

	stored_data_temp = 0;

	//--------------------------------------------------------
	// Stage 2: Hitting the eFuse shadow memory (this is supposed to work)
	//--------------------------------------------------------
	// for (i = 0; i < QFPROM_FUSE_BLOB_SIZE; i++) {
		
	// 	stored_data_temp = readb_relaxed((QFPROM_SHADOW_MAP_ADDRESS + i));

	//  	if (!stored_data_temp) {
	//  		pr_info("m0nk -> location: , byte number: %i, has no valid value\n", i);
	//  		shadow_fuse_map[i] = 0;
	//  	}else{
	//  		pr_info("\tm0nk -> location: , byte number: %i, has value: %x\n", i, stored_data_temp);
	//  		shadow_fuse_values[i] = stored_data_temp;
	//  		shadow_fuse_map[i] = 1;
	//  	}
	// }	

	return 0;
}	


//--------------------------------------------------------
// Now we can crawl, and we do so blindly
//--------------------------------------------------------
static int dump_the_things (void) 
{
	// This should get populated with code to dump the arrays to a file for offline use.
	uint32_t i;

	pr_info("\n\nm0nk-> Known QF-PROM Direct Contents!\n");

	for (i = 0; i < QFPROM_FUSE_BLOB_SIZE; i++) {
	 	if (base_fuse_map[i] == 1)
	 		pr_info("m0nk -> offset: 0x%x (%i), has value: 0x%x (%i)\n", i, i, base_fuse_values[i], base_fuse_values[i]);
	}

	// pr_info("\n\nm0nk-> Known QF-PROM Shadow Contents!\n");

	// for (i = 0; i < QFPROM_FUSE_BLOB_SIZE; i++) {
	//  	if (shadow_fuse_map[i] == 1)
	//  		pr_info("m0nk -> offset: 0%xx, has value: 0x%x (%i)\n", i, shadow_fuse_values[i], shadow_fuse_values[i]);
	// }


	return 0;
}

Writing is slightly more complex, but basically amounts to pushing a voltage to the eFuse for a specified temporal scope in order for the fuse to blow (covered in the complete tool). My complete introspection tool will be on github soon, look for it here: https://github.com/monk-dot/DefusingTheDragon

WARNING: Portions of the code are commented out and may need a little love for compilation. I leave this up to the reader, the blueprint is there. #JoinTheWar

Have fun, break with caution and enjoy.
