/*
 * AUTHOR: Satya Sundar Sahu
 * DATE: 18-Aug-2019
 * Contact: tinkusahu.com@gmail.com
 * DESC: This is main file for image processing project
 * */
#include"my_header.h"

int main()
{
	int ret = -1;
	int choice = 0;
	while(1) {
		printf("Please Enter below choice\n");
		printf("0: Exit\n1: Copy Image SRC to DEST\n2: RGB to greay convert\n3: Convert to black and white\n4: Increase Brightness\n");
		scanf("%d",&choice);
		switch(choice) {
		case 0:
			exit(0);
		case 1: 
			//printf("Please enter src image name and dst image name\n");
			ret = image_copy();
			break;
		case 2: 
			//printf("Please enter src image name and dst image name\n");
			ret = bmp_rgb_to_gry();
			break;
		case 3: 
			//printf("Please enter src image name and dst image name\n");
			ret = bmp_img_to_blkwhi();
			break;
		case 4: 
			//printf("Please enter src image name and dst image name\n");
			ret = bmp_img_increase_bright();
			break;
		default:
			printf("Invalid choice\n");
		}
	}
	return 0;
}
