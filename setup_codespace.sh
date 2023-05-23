mkdir avr-gcc
cd avr-gcc 
wget https://github.com/ZakKemble/avr-gcc-build/releases/download/v12.1.0-1/avr-gcc-12.1.0-x64-linux.tar.bz2
tar -xf avr-gcc-12.1.0-x64-linux.tar.bz2
echo export PATH=/workspaces/Nextag-Embedded-Platform/avr-gcc/avr-gcc-12.1.0-x64-linux/bin:$PATH > ~/.bashrc
cd ..

sudo wget -qO /usr/local/bin/ninja.gz https://github.com/ninja-build/ninja/releases/latest/download/ninja-linux.zip
sudo gunzip /usr/local/bin/ninja.gz
sudo chmod a+x /usr/local/bin/ninja

sudo apt update
sudo apt install simavr -y

cmake -B build -S . -DNEXTAG_EMBEDDED_PLATFORM_CONFIGURE_AS_UNO=ON -G Ninja