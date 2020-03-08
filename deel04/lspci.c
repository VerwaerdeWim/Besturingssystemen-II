#include <sys/io.h>
#include <stdio.h>
#include <stdlib.h>

#define CONFIG_ADDRESS 0xcf8
#define CONFIG_DATA 0xcfc
#define REGISTER_OFFSET 4 

unsigned int get_response(int, int, int, int);

int main(int argc, char **argv){
	// Veiliger dan iopl
	if(ioperm(CONFIG_ADDRESS,4,1) == -1){
		perror(argv[0]);
		exit(1);
	}

	if(ioperm(CONFIG_DATA,4,1) == -1){
		perror(argv[0]);
		exit(1);
	}

	//Onderstaande code geeft toegang tot elke poort 
	/*
	if(iopl(3) == -1){
		perror(argv[0]);
		exit(1);
	} 
	*/

	int bus;
	int device;
	int function;

	for(bus = 0; bus < 256; bus++){
		for(device = 0; device < 32; device++){
			for(function = 0; function < 8; function++){
                unsigned int response_reg_0 = get_response(bus, device, function, 0);

				if(response_reg_0 != 0xffffffff) {
					unsigned int response_reg_2 = get_response(bus, device, function, 2);

	                printf("%02x:%02x.%01x %04x: %04x:%04x",
                        bus,
                        device,
                        function,
                        response_reg_2 >> 16,               // class
                        response_reg_0 & ((1<<16)-1),       // vendor id
                        response_reg_0 >> 16                // device id
                    );	

	                if(response_reg_2 & ((1<<8)-1)) {
	                	printf(" (rev %02x)",response_reg_2 & ((1<<8)-1));	// revision id
	                }
	                printf("\n");
				}
			}
		}
		
	}	
    exit(0);	
}

unsigned int get_response(int bus, int device, int functie, int reg){
	unsigned int request = (1 << 31) | (bus << 16) | (device << 11) | (functie << 8) | (REGISTER_OFFSET * reg);
	outl(request, CONFIG_ADDRESS);
	return inl(CONFIG_DATA);
}
