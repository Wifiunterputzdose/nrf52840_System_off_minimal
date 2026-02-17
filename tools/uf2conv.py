#!/usr/bin/env python3
import sys
import struct

UF2_MAGIC_START0 = 0x0A324655
UF2_MAGIC_START1 = 0x9E5D5157
UF2_MAGIC_END = 0x0AB16F30

def convert_to_uf2(binfile, outfile):
    with open(binfile, "rb") as f:
        data = f.read()

    block_size = 256
    num_blocks = (len(data) + block_size - 1) // block_size

    with open(outfile, "wb") as out:
        for blockno in range(num_blocks):
            chunk = data[blockno*block_size:(blockno+1)*block_size]
            chunk += b'\x00' * (block_size - len(chunk))

            out.write(struct.pack("<IIIIIIII",
                UF2_MAGIC_START0,
                UF2_MAGIC_START1,
                0x0,
                0x1000 + blockno*block_size,
                block_size,
                blockno,
                num_blocks,
                0xADA52840
            ))
            out.write(chunk)
            out.write(b'\x00' * (476 - len(chunk)))
            out.write(struct.pack("<I", UF2_MAGIC_END))

if __name__ == "__main__":
    convert_to_uf2(sys.argv[1], sys.argv[2])
