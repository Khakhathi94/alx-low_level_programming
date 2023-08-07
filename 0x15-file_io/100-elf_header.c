#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <sys/types.h>
typedef struct 
{
	unsigned char magic[4];
    unsigned char class;
    unsigned char data;
    unsigned char version;
    unsigned char os_abi;
    unsigned char abi_version;
    unsigned char padding[7];
    unsigned short type;
    unsigned short machine;
    unsigned int version2;
    unsigned long entry;
} ElfHeader;
void print_elf_header_info(const ElfHeader *header) 
{
	printf("Magic: %02x %02x %02x %02x\n", header->magic[0], header->magic[1], header->magic[2], header->magic[3]);
    printf("Class: %d\n", header->class);
    printf("Data: %d\n", header->data);
    printf("Version: %d\n", header->version);
    printf("OS/ABI: %d\n", header->os_abi);
    printf("ABI Version: %d\n", header->abi_version);
    printf("Type: %d\n", header->type);
    printf("Entry point address: %lx\n", header->entry);
}
int main(int argc, char *argv[]) 
{
	if (argc != 2) 
    {
	    fprintf(stderr, "Usage: %s elf_filename\n", argv[0]);
	return 1;
    }
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) 
    {
	    fprintf(stderr, "Error opening file: %s\n", argv[1]);
	return 2;
    }
    ElfHeader header;
    if (read(fd, &header, sizeof(header)) != sizeof(header)) {
	    fprintf(stderr, "Error reading ELF header from file: %s\n", argv[1]);
	close(fd);
	return 3;
    }
    if (header.magic[0] != 0x7f || header.magic[1] != 'E' || header.magic[2] != 'L' || header.magic[3] != 'F') {
	    fprintf(stderr, "Error: Not an ELF file: %s\n", argv[1]);
	close(fd);
	return 98;
    }
    print_elf_header_info(&header);
    close(fd);
    return 0;
}
