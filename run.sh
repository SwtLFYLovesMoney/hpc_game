echo "****** run: $1"
program_path=$(pwd)
echo "****** locat: $program_path"

qemu-arm-static -L /usr/arm-linux-gnueabihf/ $program_path/$1