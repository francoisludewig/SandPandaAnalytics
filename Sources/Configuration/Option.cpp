#include "../../Includes/Configuration/Option.h"

#include <cstring>
#include <iostream>

Option::Option() noexcept {
	sprintf(directory,"./");
}

int Option::Management(char **argv, int argc) noexcept {
	list = argv;
	Nlist = argc;
	for(int i = 1 ; i < argc ; i++){
		if(argv[i][0] == 45){
			switch(argv[i][1]){
				case 'h':
					if(!strcmp(argv[i], "-help")){
						printf("SanPanda Version 5.0 c++\nOptions are :\n");
						printf("\t-p or -parallel for parallel contact detection with OpenMP\n");
						printf("\t-s or -sequential for sequential contact detection (default option)\n");
						printf("\t-d or -directory to indicate the current directory of the simulation (default option is the current directory)\n");
						return 0;
					}
					if(!strcmp(argv[i], "-h")){
						printf("SanPanda Version 5.0 c++\nOptions are :\n");
						printf("\t-p or -parallel for parallel contact detection with OpenMP\n");
						printf("\t-s or -sequential for sequential contact detection (default option)\n");
						printf("\t-d or -directory to indicate the current directory of the simulation (default option is the current directory)\n");
						return 0;
					}
					break;
				case 'p':
					if(!strcmp(argv[i], "-parallel")){
						printf("Parallel\n");
						sscanf(argv[i+1],"%d",&Nprocess);
						i++;
						parallel = 1;
					}
					if(!strcmp(argv[i], "-p")){
						printf("Parallel\n");
						sscanf(argv[i+1],"%d",&Nprocess);
						i++;
						parallel = 1;
					}
					break;
				case 's':
					if(!strcmp(argv[i], "-sequential")){
						printf("Sequential\n");
						parallel = 0;
					}
					if(!strcmp(argv[i], "-s")){
						printf("Sequential\n");
						parallel = 0;
					}
					break;
				case 'd':
					if(!strcmp(argv[i], "-directory")){
						sscanf(argv[i+1],"%s",directory);
						printf("Directory : %s\n",directory);
						i++;
					}
					if(!strcmp(argv[i], "-d")){
						sscanf(argv[i+1],"%s",directory);
						printf("Directory : %s\n",directory);
						i++;
					}
					break;
				default: ;
			}
		}
	}
	return 1;
}

void Option::Record() noexcept {
	// Enregistrement des options
	FILE *ft;
	char FileName[2048];
	sprintf(FileName,"%s/option.txt",directory);
	ft =fopen(FileName,"w");
	for(int i = 1 ; i < Nlist ; i++){
		if(list[i][0] == 45){
			fprintf(ft,"\n%s ",list[i]);
		}
		else{
			fprintf(ft,"%s ",list[i]);
		}
	}
	fclose(ft);
	fflush(ft);
}
