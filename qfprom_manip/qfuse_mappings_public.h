//--------------------------------------------------------
// Just some "borrowed" and "discovered" defines...
//		nothing to see here ;)
//
//--------------------------------------------------------

#include <mach/msm_iomap.h>
//--------------------------------------------------------
// m0nk created
//--------------------------------------------------------
//more than 1000 and we get kernel page faults... look into that 
#define QFPROM_FUSE_BLOB_SIZE				0x1000

#define QFPROM_SHADOW_MAP_ADDRESS			(MSM_QFPROM_BASE + 0x4000)	//0x704000 
#define QFPROM_VALUE_TO_WRITE				0xFF

//--------------------------------------------------------
// because it makes perfect, logical sense to ioctl the fuses
//--------------------------------------------------------
#define QFP_FUSE_IOC_MAGIC          		0x92
#define QFP_FUSE_IOC_WRITE          		_IO(QFP_FUSE_IOC_MAGIC, 1)
#define QFP_FUSE_IOC_READ           		_IO(QFP_FUSE_IOC_MAGIC, 2)


/*
 * Time QFPROM requires to reliably burn a fuse.
 */
#define QFPROM_BLOW_TIMEOUT_US      		10
#define QFPROM_BLOW_TIMER_OFFSET    		0x2038
/*
 * Denotes number of cycles required to blow the fuse.
 */
#define QFPROM_BLOW_TIMER_VALUE     		(QFPROM_BLOW_TIMEOUT_US * 83)

#define QFPROM_BLOW_STATUS_OFFSET   		0x204C
#define QFPROM_BLOW_STATUS_BUSY     		0x01
#define QFPROM_BLOW_STATUS_ERROR    		0x02

#define QFP_FUSE_READY              		0x01
#define QFP_FUSE_OFF                		0x00

//--------------------------------------------------------
// These are "borrowed" from the LG codebase (lge_qfprom_access.c)
//--------------------------------------------------------
/* service ID inside tzbsp */
#define QFPROM_SVC_ID           			8
#define TZBSP_SVC_OEM           			254
#define TZBSP_ADDITIONAL_CMD    			0x1
#define QFPROM_WRITE_CMD        			0x3
#define QFPROM_READ_CMD	       				0x5
#define QFPROM_PRNG_CMD         			0x7
#define QFPROM_OVERRIDE_CMD     			0x8

/* tzbsp_boot_milestone_status type */
#define TZBSP_MILESTONE_TRUE    			0x0132DD1B
#define TZBSP_MILESTONE_FALSE   			0x013302A1

/* qfprom read type */
#define QFPROM_ADDR_SPACE_RAW  				0
#define QFPROM_ADDR_SPACE_CORR 				1

/* It's not a Hublot, but it'll have to do */
#define QFPROM_CLOCK           				(0x40*1000)

/* QFPROM address to blow (as denoted by LGE) */
#define QFPROM_SPARE_REGION_22  			0x700410
#define QFPROM_SPARE_REGION_24  			0x700428
#define QFPROM_SPARE_REGION_25  			0x700430
#define QFPROM_SPARE_REGION_26  			0x700438
#define QFPROM_SPARE_REGION_27  			0x700440

/* A map of interesting locations */
#define QFPROM_BASE_MAP_ADDRESS				MSM_QFPROM_BASE	//0x700000 
#define QFPROM_HW_KEY_STATUS           		0x702050
#define QFPROM_SECURE_BOOT_ENABLE      		0x700310
#define QFPROM_OEM_CONFIG              		0x700230
#define QFPROM_DEBUG_ENABLE            		0x700220
#define QFPROM_SECONDARY_HW_KEY        		0x7002A0
#define QFPROM_READ_PERMISSION         		0x7000A8
#define QFPROM_WRITE_PERMISSION	    		0x7000B0
#define QFPROM_OVERRIDE_REG         		0x7060C0
#define QFPROM_CHECK_HW_KEY            		0x123456

/* secondary hw key status flag */
#define SEC_HW_KEY_BLOWN  					0x00000001
#define PRIM_HW_KEY_BLOWN 					0x00000002
#define HW_KEYS_BLOCKED   					0x00000004

