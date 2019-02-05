## Instructions

1.  [Build OBS-Studio](https://github.com/obsproject/obs-studio/wiki/Install-Instructions#debian-based-build-directions):


    	$ sudo apt-get install build-essential pkg-config cmake git-core checkinstall

    	$ sudo apt-get install libx11-dev libgl1-mesa-dev libvlc-dev libpulse-dev libxcomposite-dev \

    			libxinerama-dev libv4l-dev libudev-dev libfreetype6-dev \

    			libfontconfig-dev qtbase5-dev libqt5x11extras5-dev libx264-dev \

    			libxcb-xinerama0-dev libxcb-shm0-dev libjack-jackd2-dev libcurl4-openssl-dev \

    			luajit-5.1-dev swig python3.6-dev

        # Clone this repository
        $ git clone https://bitbucket.org/eyal-myplay/obs-headless-poc

    	# Install obs-studio inside the repository folder (the DISABLE_UI part is important) 
    	$ git clone --recursive https://github.com/obsproject/obs-studio.git

    	$ cd obs-studio

    	$ mkdir build && cd build

    	$ cmake -DUNIX_STRUCTURE=1 DISABLE_UI=true -DCMAKE_INSTALL_PREFIX=/usr ..

    	$ make -j4

    	$ sudo checkinstall --pkgname=obs-studio --fstrans=no --backup=no \

    	--pkgversion="\$(date +%Y%m%d)-git" --deldoc=yes

2.  Compile and run

        $ mkdir build && cd build

        $ cmake ..

        $ make

        $ ./app
