DefusingTheDragon
=================

( Fun from POC || GTFO )

Earlier this year, Nathan Keltner and I started down the curious path of Qualcomm SoC security. The boot chain in particular piqued my interest, the lack of documentation double it... the following is a portion of the results. (btw: thx mudge).

Qualcomm internally utilizes a 16kb bank of one time programmable fuses (named QFPROM by the manufacturer) on the Snapdragon S4 Pro SoC (MSM8960) as well as the other processors manufactured. These fuses, though publicly undocumented, are purported to hold the bulk of inter-chip configuration settings as well as the cryptographic keys to the device. Analysis of leaked documentation has shown that the fuses contain the primary hardware keys used to verify the Secure Boot 3.0 process as well as the cryptographic information used to secure Trust Zone and other security related functionality embedded in the chip. Furthermore, the fuse bank controls hardwired security paths for Secure Boot functionality (including where on disk to acquire the bootable images). The 16k block of fuses also contains space for end user cryptographic key storage and vendor specific configurations.

These one time programmable fuses are not intended to be directly accessed by the end user of the device and in some cases, such as the basic cryptographic keys, the Android kernel itself is not allowed to view the contents of the QFPROM block. These fuses and keys are documented to be hardware locked and accessible only by very controlled paths. Preliminary research has shown the and unknown 4k subset of the 16k block is mapped into the kernel IMEM at physical location 0x700000. The fuses are also documented to be shadowed at 0x704000 in memory. Furthermore, there exists somewhat unused source code from the Code Aurora project in the Android kernel that documents how to read and write to the 4k block of exposed fuses.

Aside from the Aurora code, most vendors have also created and publicly shared code to play with the fuses. LG is the exemplar here, with a wonderful little kernel module that maps and explores LG specific bit-flags. In general, there is an acceptable amount of existing code that will walk an interested person through the process.

Below are simplistic excerpts for my tool that should help you explore these toys with a little more granularity. To note, writing eFuse or QFPROM values can and probably will brick your device, so be careful. A last interesting tidbit though, and one that will hopefully entice the reader... SoC and other hardware debugging is typically turned off with a blown fuse. This becomes interesting because there exists a secondary fuse that turns this functionality back on (specifically for the use of RMA and other requests). Also as stated, the fuses hold the blueprint for where and how Secure Boot 3.0 works as well as where the device should look for binary blobs to load during setup phases. 

Writing is slightly more complex, but basically amounts to pushing a voltage to the eFuse for a specified temporal scope in order for the fuse to blow (covered in the complete tool). My complete introspection tool will be on github soon, look for it here: https://github.com/monk-dot/DefusingTheDragon

WARNING: Portions of the code are commented out and may need a little love for compilation. I leave this up to the reader, the blueprint is there. #JoinTheWar

Have fun, break with caution and enjoy.
