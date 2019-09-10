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
		printf("0: Exit\n1: Copy Image SRC to DEST\n2: RGB to greay convert\n3: Convert to black and white\n4: Increase Brightness\n5: Reduce Greay Level\n6: Plot Histogram\n7: Histogram Equlization\n8: Brightness Correction\n9: Image rotation\n10: Convert to negative image\n11: Convert to Blur Image\n");
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
		case 5:
			ret = bmp_img_reduce_grey_level();
			break;
		case 6:
			ret = bmp_creat_histogram();
			break;
		case 7:
			ret = bmp_histogram_equ();
			break;
		case 8:
			ret = bmp_brightness_correction();
			break;
		case 9:
			ret = bmp_image_rotation();
			break;
		case 10:
			ret = bmp_negative_img();
			break;
		case 11:
			ret = bmp_blur_img();
			break;
		default:
			printf("Invalid choice\n");
		}
	}
	return 0;
}
