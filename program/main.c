#include"my_header.h"

int main()
{
	int ret = -1;
	int choice = 0;
	while(1) {
		printf("Please Enter below choice\n");
		printf("0: Exit\n1: Copy Image SRC to DEST\n");
		scanf("%d",&choice);
		switch(choice) {
		case 0:
			exit(0);
		case 1: 
			printf("Please enter src image name and dst image name\n");
			ret = image_copy();
			break;
		default:
			printf("Invalid choice\n");
		}
	}
	return 0;
}
