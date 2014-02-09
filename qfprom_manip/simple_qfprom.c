/**
 *  -------------------------------------------
 *  -={ From the magic land of the Ker Nel! }=-
 *  -------------------------------------------
 *
 * This file was developed by Josh Thomas of Atredis (atredis.com) / @m0nk_dot on the twitterz
 *
 * Sole intent of this program is to map, print, abuse and manipulate eFuse / QFPROM hardware in Qualcomm chipsets 
 *			(The MSM8960 specifically, though the path is universal?)
 *
 * Secondary intent: the lulz
 *
 * There is little chance this file can be used responsibly, so please use it sparingly.
 *
 * I somewhat apologize for the 3 discrete comment narritives throughout this file... might have transgressed a bit
 *	during the development period.
 *
 **/

//--------------------------------------------------------
// Standard Includes
//--------------------------------------------------------
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/regulator/consumer.h>
//--------------------------------------------------------
// Get the mappings from the header file
//--------------------------------------------------------
#ifdef MONK_WAS_HERE
	#include "qfuse_mappings_not_so_public.h"
 #endif

 #include "qfuse_mappings_public.h"
 

/** 
 * Notes from the front (Hacker v. Grey Beard Coding War):
 *  
 * Dearest,
 * 	I find myself comfortably sitting in a Starbucks, the air filled with a surreal combination of 
 *  smooth jazz christmas musak and the audio leakage of the gentalman across from me piping some
 * 	experimental combination of reggeton and dubstep at ear splitting levels, sans headphones of course.
 *
 * The day is young and the prior night was long, so I will keep this report short. The grey bearded
 * perfectionist coder internal to my very psyche and I are now on the verge of war. He is highly 
 * annoyed and offended I would find myself typing anything less than full production quality code... 
 * But alas, I strive simply to break all the toys and am no longer drawn into the trappings of 
 * double reviewed and well architected elegance.
 * 
 * To begin this internal battle, I will create a static global array to store some data randomly across this 
 * simple minded program. I expect this shall rouse the beast and we shall fight the good fight.
 *
 * If that does not stir the ancient one into battle, the usage of an integer array over a boolean bitmask 
 * should alone ignite the flames of war.
 *
 * Yours as always,
 *
 * -m0nk
**/
static uint8_t base_fuse_map[QFPROM_FUSE_BLOB_SIZE];
static uint8_t base_fuse_values[QFPROM_FUSE_BLOB_SIZE];

// static uint8_t shadow_fuse_map[QFPROM_FUSE_BLOB_SIZE];
// static uint8_t shadow_fuse_values[QFPROM_FUSE_BLOB_SIZE];

//--------------------------------------------------------
// This should be the fun part
//--------------------------------------------------------

//--------------------------------------------------------
// Helpful functions go here:
//--------------------------------------------------------

//--------------------------------------------------------
// Unhelpful functions go here:
//--------------------------------------------------------

//--------------------------------------------------------
// Before we can crawl, we must have appendages
//--------------------------------------------------------
static int map_the_things (void) 
{
	uint32_t i;
	uint8_t stored_data_temp;

	/** 
	 * Notes from the front (Hacker v. Grey Beard Coding War):
	 *  
	 * Darling,
	 * 	The ancient one stirs and grumbles incoherently as I type. Currently nestled back in the hotel as a soaking rain
	 * 	traps me inside. Starbucks has closed its doors for the day and caffeine is already in scarce supply. 
	 *
	 * 	As I feared, this round of battle with the grey fossil is in full swing. I toss out simple spaghetti code
	 * 	that in all outward appearances was written by a neanderthal rushing to the finish line, whilst the enemy
	 *	pushes hard for refactoring and cleanliness. I expect to prevail during this initial skirmish, but the war will
	 *  be long and hard won.
	 *
	 *  Currently, I have generated a copy paste nightmare of duplicate functionality without simply moving the generic
	 *  solution into a looped method. This offensive trickery has confused and slowed the adversary to some extent,
	 *  but I expect horrible retaliation for the basic C transgressions.
	 *
	 * For now, 
	 *
	 * -m0nk
	**/

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

//--------------------------------------------------------
// Not really walking unassisted, but ~upright at least
//--------------------------------------------------------
static int document_the_things (void) 
{
	//In here, we need to reverse map the arrays back to known values.
	//
	//I leave this to the reader, hint would be to check the .h file
	return 0;
}

// //--------------------------------------------------------
// // Flails arms wildy, randomly hits things and stubs finger
// //--------------------------------------------------------
// static int write_the_things (uint32_t *address, uint32_t data) 
// {
	
// 	/** 
// 	 * Notes from the front (Hacker v. Grey Beard Coding War):
// 	 *  
// 	 * Dearest,
// 	 *
// 	 * I have infiltrated the source repository of the elders and plundered the riches
// 	 * without intnet of fessing up to my crimes. Whilst the neck beard sleeps off the lack
// 	 * of flowing coffee, I shall hack and slash from the depths of qfp_fuse.c as authored
// 	 * by the illustrious Rohit Vaswani. Just to taunt the grumpy one, I will remove all
// 	 * the error checking and code protection measures... Failing gracefully is simply
// 	 * planning to fail, I shall blindy jump forth without pause for contemplating consequence.
// 	 *
// 	 * While the code itself shall be tweaked without reguard, the comments I shall not touch,
// 	 * for they are philisophically deep, as if Rohit himself was Yoda incarnate. Even I fear
// 	 * transgressing those depths.
// 	 *
// 	 * Alas, I feel the creeping hands of the GPL closing in on me... 
// 	 *  darkness aproaches and I must remain hidden from the lawyers of Boston.... 
// 	 *
// 	 * -m0nk
// 	**/
// 	//Take a location and a value, write it.
// 	uint32_t blow_status = 0;
// 	uint32_t read_data;
// 	uint32_t timeout;
// 	int err;

// 	/* Set QFPROM  blow timer register */
// 	writel_relaxed(QFPROM_BLOW_TIMER_VALUE,
// 			QFPROM_BASE_MAP_ADDRESS + QFPROM_BLOW_TIMER_OFFSET);
// 	mb();

// 	/* Enable LVS0 regulator */
// 	err = regulator_enable(qfp_priv->fuse_vdd);
// 	if (err != 0)
// 		pr_err("Error (%d) enabling regulator... you should probably care about this.\n", err);
	
// 	/*
// 	 * Wait for about 1ms. However msleep(1) can sleep for
// 	 * up to 20ms as per Documentation/timers/timers-howto.txt.
// 	 * Time is not a constraint here.
// 	 */
// 	 // m0nk: ^^ that is deep ^^
// 	msleep(20);

// 	/* Write data */
// 	__raw_writel(data, addr);
// 	mb();

// 	/* blow_status = QFPROM_BLOW_STATUS_BUSY; */
// 	timeout = QFPROM_BLOW_TIMEOUT_US;
// 	/* wait for 400us before checking for the first time */
// 	udelay(400);
// 	do {
// 		*status = readl_relaxed(
// 			QFPROM_BASE_MAP_ADDRESS + QFPROM_BLOW_STATUS_OFFSET);

// 		if (!(*status & QFPROM_BLOW_STATUS_BUSY))
// 			return 0;

// 		timeout--;
// 		udelay(1);
// 	} while (timeout);
	
// 	pr_err("Timeout waiting for FUSE blow, status = %x . This is probably important\n", *status);

// 	/* Check error status */
// 	if (blow_status & QFPROM_BLOW_STATUS_ERROR)
// 		pr_err("Fuse blow status error: %d. Bummer, I was hoping that would work\n", blow_status);

// 	/* Disable regulator */
// 	err = regulator_disable(qfp_priv->fuse_vdd);
// 	if (err != 0)
// 		pr_err("Error (%d) disabling regulator, I can't just turn it off??? WTF\n", err);
	
// 	/*
// 	 * Wait for about 1ms. However msleep(1) can sleep for
// 	 * up to 20ms as per Documentation/timers/timers-howto.txt.
// 	 * Time is not a constraint here.
// 	 */
// 	 // m0nk: ^^ again, that is deep ^^
	
// 	msleep(20);

// 	/* Verify written data */
// 	read_data = readl_relaxed(addr);
// 	if (read_data != data) {
// 		pr_err("Error: read/write data mismatch\n");
// 		pr_err("Address = %p written data = %x read data = %x. WHY U NO MATCH BRO?\n",
// 			addr, data, read_data);
// 	}

// 	return 0;
// }

// //--------------------------------------------------------
// // Mad at the stubbed finger, we now destroy all nice toys
// //--------------------------------------------------------
// static int stomp_the_things (void) 
// {
// 	//Loop over the entire block, write all the things
// 	//This SHOULD break the phone
// 	//If this works, you should feel bad about using it.
	
// 	uint32_t i;
// 	uint32_t qfprom_direct_address;
// 	uint32_t qfprom_blob_size;
// 	uint8_t data_to_write;
	
// 	data_to_write			= QFPROM_VALUE_TO_WRITE;
// 	qfprom_direct_address 	= QFPROM_BASE_MAP_ADDRESS;
// 	qfprom_blob_size 		= QFPROM_FUSE_BLOB_SIZE;

// 	for (i = 0; i < qfprom_blob_size; i++) {
// 		qfprom_direct_address = QFPROM_BASE_MAP_ADDRESS + i;
// 		write_the_things( &qfprom_direct_address, data_to_write);
// 	}

// 	return 0;
// }

// //--------------------------------------------------------
// // Even bad modules clean thier rooms at night
// //--------------------------------------------------------
// static int clean_the_things (void) 
// {
// 	// Should probably ensure regulators are reset and mem is released...
// 	return 0;
// }

//--------------------------------------------------------
// Please have a valid reason for calling this method, no good can come of it. 
//--------------------------------------------------------
//static int landfill (void) 
// {
// 	stomp_the_things();
// 	return 0;
// }



//--------------------------------------------------------
// Boring Module stuff
//--------------------------------------------------------

static int __init simple_qfprom_init(void)
{
	// Reading Rainbow section of the code, thx Geordi
	//--------------------------------------------------------
	map_the_things(); 			// Before we can crawl, we must have apendages
	dump_the_things();		// Now we can crawl, and we do so blindly
	document_the_things();	// Not really walking unassisted, but ~upright at least
	//--------------------------------------------------------

	// Sadly, there was no "Writing Rainbow"... probably should put in an Electric Company / Bill Cosby reference here instead
	//--------------------------------------------------------
	//write_the_things();		// Flails arms wildy, randomly hits things and stubs finger
	//stomp_the_things();		// Mad at the stubbed finger, we now destroy all nice toys
	//clean_the_things();		// Even bad modules clean thier rooms at night
	//landfill();				// Really, you are not a good person for calling this
	//--------------------------------------------------------

	return 0;
}

static void __exit simple_qfprom_exit(void)
{
	//platform_driver_unregister(&moto_qfprom_driver);
}

module_init(simple_qfprom_init);
module_exit(simple_qfprom_exit);

MODULE_DESCRIPTION("Akwardly childish module that likes to hug eFuses when no one is looking");
MODULE_AUTHOR("m0nk <josh@atredis.com>");
MODULE_LICENSE("GPL");

//--------------------------------------------------------
// ~ fin
//--------------------------------------------------------
