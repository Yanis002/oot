# The Legend of Zelda: Ocarina of Time

## Poison/Healing Water Actor - Version 1.0

## General Stuff
This custom actor was made for the Hylian Modding Community Project, [more informations on Discord](https://discord.gg/nGFZ394)

## Documentation
ACTOR ID: 0x1

OBJECT ID: 0x4

In order to use this actor, copy the ``object_poisoned_water`` folder from ``assets_custom/objects`` and paste it in ``assets/objects``.


```
PARAMETERS:
0000 0000 0011 1111 - Switch Flag       - 0x003F, ``params & 0x3F``
0000 0001 1100 0000 - Default Color Array Index - 0x01C0, ``(params >> 6) & 0x7``
0000 1110 0000 0000 - Size              - 0x0E00, ``(params >> 9) & 0x3``
1111 0000 0000 0000 - Amount of Damages - 0xF000, ``(params >> 12) & 0xF`` - 1 for 1/4 hearts
```

```
X-ROTATION: (useless if Z-Rot's bit 0x1000 set to 0)
1111 1111 0000 0000 - Poison Color R - ``(rot.x >> 8) & 0xFF``
0000 0000 1111 1111 - Poison Color G - ``rot.x & 0xFF``
```

```
Y-ROTATION: (useless if Z-Rot's bit 0x1000 set to 0)
1111 1111 0000 0000 - Poison Color B - ``(rot.y >> 8) & 0xFF``
0000 0000 1111 1111 - Poison Color A (32 will set it to 128) - ``rot.y & 0xFF``
```

```
Z-ROTATION:
0000 0000 0000 1111 - Frequency (base frequency) - 0x000F, ``rot.z & 0x000F`` - 1 for 1 second
0000 0000 1111 0000 - Divisor (increases speed)  - 0x00F0, ``rot.z & 0x00F0`` - 1 for 1 sec, 2 for 0.5 secs, ...
0000 0001 0000 0000 - Mode: Poison to Heal if Switch Flag's set - ``(rot.z >> 8) & 0x1`` - 0: disable heal mode, 1: enable heal mode
0000 1110 0000 0000 - Healing Water Color Index - ``(rot.z >> 9) & 0x7``
0001 0000 0000 0000 - Set custom RGBA poison color (see X/Y rotations) - ``(rot.z >> 12) & 0x1``
```

## Example of Usage
``{ Actor ID,                 X,    Y,   Z,     rX,   rY,     rZ, Params },``

``{ ACTOR_BG_POISONED_WATER, -3, -125, 137, 0x8000, 0x20, 0x1031, 0x1501 },``

```
--- Parameters: 0x1501 = 0001 0101 0000 0001 ---
Switch Flag: 1
Default Color Array Index: 4 (overriden by Z-Rot's custom color bit)
Size: 2
Amount of Damages: 1 (corresponds to 1/4 hearts)
```

```
--- X-Rotation: 0x8000 = 1000 0000 0000 0000 ---
Color R = 128
Color G = 0
```

```
--- Y-Rotation: 0x0020 = 0000 0000 0010 0000 ---
Color B = 0
Alpha = 32 (in-game: 128)
```

```
--- Z-Rotation: 0x0031 = 0000 0000 0011 0001 ---
Frequency (base frequency): 1 (corresponds to 1 second)
Divisor (increases speed): 1 (keep the current frequency of damage dealing)
Mode: Poison Only
Healing Water Color Index: 0
```

## Additionnal Informations
- If you choose the poison only mode: Healing Water Color Index and Switch Flag not used
- The divisor bits are only meant to increase the frequency, set it to 1 if you need to increase the frequency
- In this context "Frequency" means how much time do you want between two damage dealt to the Player
- If you deal a positive amount of damages it will heal Link
- poisonColors[] & healColors[] are the same but that's intended to allow more customisation
- The poisonColors[] array will be overriden by the custom color if it's enabled
- With that mode, the Alpha set in the Y-Rot will be multiplied by 4 later in the code (see examples)
- Small note for hexadecimal newbies: ``0x0008 == 0x8`` but ``0x8000 != 0x8``
- If the poison color is the same as the heal color the actor will make a noise to tell the user there's an issue (NA_SE_VO_Z1_CRY_0)
- Contact Yanis on the Hylian Modding Discord if you have any issues or questions

[![Build Status][jenkins-badge]][jenkins] [![Decompilation Progress][progress-badge]][progress] [![Contributors][contributors-badge]][contributors] [![Discord Channel][discord-badge]][discord]

[jenkins]: https://jenkins.deco.mp/job/OOT/job/master
[jenkins-badge]: https://img.shields.io/jenkins/build?jobUrl=https%3A%2F%2Fjenkins.deco.mp%2Fjob%2FOOT%2Fjob%2Fmaster

[progress]: https://zelda64.dev/games/oot
[progress-badge]: https://img.shields.io/endpoint?url=https://zelda64.dev/assets/csv/progress-oot-shield.json

[contributors]: https://github.com/zeldaret/oot/graphs/contributors
[contributors-badge]: https://img.shields.io/github/contributors/zeldaret/oot

[discord]: https://discord.zelda64.dev
[discord-badge]: https://img.shields.io/discord/688807550715560050?color=%237289DA&logo=discord&logoColor=%23FFFFFF

```diff
- WARNING! -

This repository is a work in progress, and while it can be used to make certain changes, it's still
constantly evolving. If you use it for modding purposes in its current state, please be aware that
the codebase can drastically change at any time. Also note that some parts of the ROM may not be
'shiftable' yet, so modifying them could be difficult at this point.
```

This is a WIP **decompilation** of ***The Legend of Zelda: Ocarina of Time***. The purpose of the project is to recreate a source code base for the game from scratch, using information found inside the game along with static and/or dynamic analysis. **It is not producing a PC port.** For more information you can get in touch with the team on our [Discord server](https://discord.zelda64.dev).

The only build currently supported is Master Quest (Debug), but other versions are planned to be supported.

It builds the following ROM:

* zelda_ocarina_mq_dbg.z64 `md5: f0b7f35375f9cc8ca1b2d59d78e35405`

**Note: This repository does not include any of the assets necessary to build the ROM. A prior copy of the game is required to extract the needed assets.**

**Website:** <https://zelda64.dev>

**Discord:** <https://discord.zelda64.dev>

## Installation

We recommend using WSL on Windows, or native Linux, which the rest of this readme describes. We currently have instructions for

* [Windows](#Windows), with and without WSL
* [macOS](docs/BUILDING_MACOS.md)
* [Linux](#Linux-Native-or-under-WSL--VM), natively or using WSL / VM
* [Docker](docs/BUILDING_DOCKER.md)

(These will also depend on the Linux instructions.)
Some of these may also be out of date or unmaintained; usually our contributors use WSL, Linux, and macOS, so these instructions should be up to date.

### Windows

For Windows 10 or 11, install WSL and a distribution by following this
[WSL Installation Guide](https://docs.microsoft.com/en-us/windows/wsl/install).
We recommend using Ubuntu 20.04 as the Linux distribution.

For older versions of Windows, install a Linux VM or refer to either [Cygwin](docs/BUILDING_CYGWIN.md) or [Docker](docs/BUILDING_DOCKER.md) instructions.


### Linux (Native or under WSL / VM)

#### 1. Install build dependencies

The build process has the following package requirements:

* git
* build-essential
* binutils-mips-linux-gnu
* python3
* libpng-dev

Under Debian / Ubuntu (which we recommend using), you can install them with the following commands:

```bash
sudo apt-get update
sudo apt-get install git build-essential binutils-mips-linux-gnu python3 libpng-dev
```

If you are using GCC as the compiler for Ocarina of Time, you will also need:

* gcc-mips-linux-gnu

#### 2. Clone the repository

**N.B.** If using WSL, we strongly encourage you to clone into WSL's Linux filesystem using Linux's `git`.
Cloning into the Windows filesystem will result in much slower read/write speeds, and often causes issues when Windows copies the files with the wrong line endings, which the compiler IDO cannot handle correctly.

Clone `https://github.com/zeldaret/oot.git` where you wish to have the project, with a command such as:

```bash
git clone https://github.com/zeldaret/oot.git
```

This will copy the GitHub repository contents into a new folder in the current directory called `oot`. Change into this directory before doing anything else:

```bash
cd oot
```

#### 3. Prepare a base ROM

Copy over your copy of the Master Quest (Debug) ROM inside the root of this new project directory.
Rename the file to "baserom_original.z64", "baserom_original.n64" or "baserom_original.v64", depending on the original extension.

#### 4. Setup the ROM and build process

Setup and extract everything from your ROM with the following command:

```bash
make setup
```

This will generate a new ROM called "baserom.z64" that will have the overdump removed and the header patched.
It will also extract the individual assets from the ROM.

#### 5. Build the ROM

Run make to build the ROM.
Make sure your path to the project is not too long, otherwise this process may error.

```bash
make
```

If all goes well, a new ROM called "zelda_ocarina_mq_debug.z64" should be built and the following text should be printed:

```bash
zelda_ocarina_mq_dbg.z64: OK
```

If you instead see the following:

```bash
zelda_ocarina_mq_dbg.z64: FAILED
md5sum: WARNING: 1 computed checksum did NOT match
```

This means that the built ROM isn't the same as the base one, so something went wrong or some part of the code doesn't match.

**NOTE:** to speed up the build, you can either:

* pass `-jN` to `make setup` and `make`, where N is the number of threads to use in the build. The generally-accepted wisdom is to use the number of virtual cores your computer has.
* pass `-j` to `make setup` and `make`, to use as many threads as possible, but beware that this can use too much memory on lower-end systems.

Both of these have the disadvantage that the ordering of the terminal output is scrambled, so for debugging it is best to stick to one thread (i.e. not pass `-j` or `-jN`).


## Contributing

All contributions are welcome. This is a group effort, and even small contributions can make a difference.
Some tasks also don't require much knowledge to get started.

Most discussions happen on our [Discord Server](https://discord.zelda64.dev), where you are welcome to ask if you need help getting started, or if you have any questions regarding this project and other decompilation projects.
