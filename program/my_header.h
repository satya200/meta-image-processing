/*
 * AUTHOR: Satya Sundar Sahu
 * DATE: 18-Aug-2019
 * DESC: This is main file for image processing project
 * */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define IMG_NAME_BUFF_LENGTH	16
#define IMG_NAME_PATH_LENGTH	256
//#define IMG_SEARCH_PATH		"~/satya_git/meta-image-processing/TestImages"
#define IMG_SEARCH_PATH		"/home/satya/satya_git/meta-image-processing/TestImages"

#define BMP_HEADER_SIZE         54
#define BMP_COLOR_TABLE_SIZE    1024
#define CUSTOM_IMG_SIZE         1024*1024

struct image_reader {
	char image_name[IMG_NAME_PATH_LENGTH];
	int height;
	int width;
	int bitDepth;
	unsigned char header[BMP_HEADER_SIZE];
	unsigned char colorTable[BMP_COLOR_TABLE_SIZE];
	unsigned char buf[CUSTOM_IMG_SIZE];
};

struct image_writer {
	char new_image_name[IMG_NAME_PATH_LENGTH];
	unsigned char header[BMP_HEADER_SIZE];
	unsigned char colorTable[BMP_COLOR_TABLE_SIZE];
	unsigned char buf[CUSTOM_IMG_SIZE];
	int bitDepth;
};

int bmp_image_read(struct image_reader *img_rd);
int bmp_image_write(struct image_writer *img_wr);
int image_copy();
int bmp_rgb_to_gry();
