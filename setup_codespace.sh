mkdir avr-gcc
cd avr-gcc 
wget https://github.com/Nextag-lasergame/avr-gcc-toolchains/releases/download/v13.2/avr-gcc-13.2.0-x64-linux.tar.gz
tar -xf avr-gcc-13.2.0-x64-linux.tar.gz
echo export PATH=/workspaces/Nextag-Embedded-Platform/avr-gcc/avr-gcc-13.2.0-x64-linux/bin:$PATH > ~/.bashrc
cd ..

sudo wget -qO /usr/local/bin/ninja.gz https://github.com/ninja-build/ninja/releases/latest/download/ninja-linux.zip
sudo gunzip /usr/local/bin/ninja.gz
sudo chmod a+x /usr/local/bin/ninja

wget -qO - https://apt.kitware.com/keys/kitware-archive-latest.asc | sudo apt-key add -
sudo apt-add-repository 'deb https://apt.kitware.com/ubuntu/ focal main'
sudo apt update
sudo apt install simavr cmake -y

source ~/.bashrc

cmake -B build -S . -DNEXTAG_EMBEDDED_PLATFORM_CONFIGURE_AS_UNO=ON -G Ninja