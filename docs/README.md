To get to original SMB:

sh createheader.sh
sh createchr.sh  # Change path as needed (just trying to get the last 8192 bytes)


dosbox .
x816 smbdis.asm (you need to download x816 from https://www.romhacking.net/download/utilities/956/)
cat header.bin SMBDIS.BIN chr.bin > smb.nes 

