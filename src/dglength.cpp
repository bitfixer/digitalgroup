#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int flength(char* fname)
{
    FILE* fp = fopen(fname, "rb");
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fclose(fp);

    return size;
}

int main(int argc, char** argv)
{
    char* fname = argv[1];
    char* outFname = argv[2];

    // get size of input file
    int size = flength(fname);

    printf("size of %s is %d\n", fname, size);
    size = (size + 0x0100) - 1;
    uint8_t size_lo = size & 0x00FF;
    uint8_t size_hi = (size & 0xFF00) >> 8;

    printf("size_lo %X\n", size_lo);
    printf("size_hi %X\n", size_hi);

    uint8_t* outData = (uint8_t*)malloc(size);
    FILE* fp = fopen(fname, "rb");
    fread(outData, 1, size, fp);
    fclose(fp);

    outData[26] = size_lo;
    outData[27] = size_hi;

    fp = fopen(outFname, "wb");
    fwrite(outData, 1, size, fp);
    fclose(fp);
}


/*
import os
import sys

#print sys.argv[1]
size = os.path.getsize(sys.argv[1])
print "size of " + sys.argv[1] + " is " + str(size)

size = (size + 0x0100) - 1;
size_lo = size & 0x00FF
size_hi = (size & 0xFF00) >> 8

print "size_lo " + str(size_lo) + " " + format(size_lo, '#04X')
print "size_hi " + str(size_hi) + " " + format(size_hi, '#04X')

fh = open(sys.argv[1], "rb")
ba = bytearray(fh.read())
fh.close()

#replace address bytes
ba[26] = size_lo
ba[27] = size_hi

of = open(sys.argv[2], "wb")
of.write(ba)
of.close()
*/