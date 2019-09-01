/*
 * AUTHOR: Satya Sundar Sahu
 * DATE: 18-Aug-2019
 * DESC: This is main file for image processing project
 * */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define IMG_NAME_BUFF_LENGTH	32
#define IMG_NAME_PATH_LENGTH	512
//#define IMG_SEARCH_PATH		"~/satya_git/meta-image-processing/TestImages"
#define IMG_SEARCH_PATH		"/home/satya/satya_git/meta-image-processing/TestImages"
//#define IMG_SEARCH_PATH		"/home/nullbyte/satya_bitbucket/my-git/meta-image-processing/TestImages"

#define BMP_HEADER_SIZE         54
#define BMP_COLOR_TABLE_SIZE    1024
#define CUSTOM_IMG_SIZE         1024*1024

enum image_type {
	GREAY = 0,
	RGB
};

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

struct image_reader_mat {
	char image_name[IMG_NAME_PATH_LENGTH];
	int height;
	int width;
	int bitDepth;
	unsigned char header[BMP_HEADER_SIZE];
	unsigned char colorTable[BMP_COLOR_TABLE_SIZE];
	unsigned char **buf;
};

struct image_writer_mat {
	char new_image_name[IMG_NAME_PATH_LENGTH];
	unsigned char header[BMP_HEADER_SIZE];
	unsigned char colorTable[BMP_COLOR_TABLE_SIZE];
	int bitDepth;
	unsigned char **buf;
};

int bmp_image_read(struct image_reader *img_rd);
int bmp_image_write(struct image_writer *img_wr);
int bmp_image_read_mat(struct image_reader_mat *img_rd);
int bmp_image_write_mat(struct image_writer_mat *img_wr, int);
int image_copy();
int bmp_rgb_to_gry();
int bmp_img_to_blkwhi();
int bmp_img_increase_bright();
int bmp_img_reduce_grey_level();
int bmp_creat_histogram();
int bmp_histogram_equ();
int bmp_brightness_correction();
int bmp_image_rotation();
