/*
 * AUTHOR: Satya Sundar Sahu
 * DATE: 18-Aug-2019
 * Contact: tinkusahu.com@gmail.com
 * DESC: This is main file for image processing project
 * */

#include"my_header.h"

#define WHITE   255
#define BLACK   0
#define THRESHOLD   150

/*
 * Name: bmp_img_to_blkwhi()
 * Desc: This is used for Convert RGB to greay scale image.
 * Parameter: No Parameter
 * Return : 0 = on Success
 *          < 0 = On Failure
 * */
int bmp_img_to_blkwhi()
{
	FILE *fp_src = NULL;
	int ret = -1;

	char img_name_src_path[IMG_NAME_PATH_LENGTH] = {0};
	char img_name_dst_path[IMG_NAME_PATH_LENGTH] = {0};
	char src_img_name[IMG_NAME_BUFF_LENGTH] = {0};
	struct image_reader img_rd;
	struct image_writer img_wr;
	int img_size;
	int temp;

	printf("Please Enter bmp image name\n");
	scanf("%s",src_img_name);
	sprintf(img_name_src_path, "%s/%s",IMG_SEARCH_PATH, src_img_name);
	sprintf(img_name_dst_path, "%s/blkwhite_%s",IMG_SEARCH_PATH, src_img_name);
	printf("Source image:%s\nDest image:%s\n",img_name_src_path, img_name_dst_path);

	strcpy(img_rd.image_name, img_name_src_path);
	ret = bmp_image_read(&img_rd);
	if (ret < 0) {
		printf("Error return from bmp_image_read()\n");
	} else {
		printf("Image read success\n");
        }

	
	strcpy(img_wr.new_image_name, img_name_dst_path);
	printf("====> New name: %s\n",img_wr.new_image_name);
	memcpy(img_wr.header, img_rd.header, sizeof(img_rd.header));
	memcpy(img_wr.colorTable, img_rd.colorTable, sizeof(img_rd.colorTable));
	//memcpy(img_wr.buf, img_rd.buf, sizeof(img_rd.buf));
	img_wr.bitDepth = img_rd.bitDepth;

	img_size = (img_rd.height * img_rd.width);

	unsigned char buffer[img_size];
	int index_rd = 0;
	int index_wr = 0;

	for (int i = 0; i < img_size; i++) {
		buffer[i] = img_rd.buf[i];
		buffer[i] = ((buffer[i] > THRESHOLD) ? WHITE:BLACK);
		img_wr.buf[i] = buffer[i];
	}
	ret = bmp_image_write(&img_wr);
	if (ret < 0) {
		printf("Error return from bmp_image_write()\n");
	} else {
		printf("Image Write success\n");
        }
	
	return 0;
}
