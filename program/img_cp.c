/*
 * AUTHOR: Satya Sundar Sahu
 * DATE: 18-Aug-2019
 * DESC: This is main file for image processing project
 * */

#include"my_header.h"

/*
 * Name: bmp_image_write()
 * Desc: This is used for write an image.
 * Parameter: img_wr is a strusture. for structure member
 * 	      Refer "my_header.h" file.
 * Return : 0 = on Success
 * 	    < 0 = On Failure
 * */
int bmp_image_write(struct image_writer *img_wr)
{
	FILE *fp_dst = NULL;

	if (img_wr == NULL) {
		printf("%s parameter NULL\n",__FUNCTION__);
		return -1;
	}

	/* Start Writting BMP File */
	fp_dst = fopen(img_wr->new_image_name, "wb");
	if (fp_dst == NULL) {
		printf("File Not Present\n");
		return -1;
	} else {
		printf("Dst file open successfuly\n");
	}

	/* Writting Header to new file */
	fwrite(img_wr->header, sizeof(unsigned char), BMP_HEADER_SIZE, fp_dst);

	/* Writting Color Table  to new file */
	if (img_wr->bitDepth <= 8) {
		fwrite(img_wr->colorTable, sizeof(unsigned char), 1024, fp_dst);
	}

	/* Writting Data to new file */
	fwrite(img_wr->buf,sizeof(unsigned char),CUSTOM_IMG_SIZE, fp_dst);

	fclose(fp_dst);

	return 0;
}

/*
 * Name: bmp_image_read()
 * Desc: This is used for Read an image. 
 * Parameter: img_rd is a struct image_reader.
 * Return : 0 = on Success
 * 	    < 0 = On Failure
 * */
int bmp_image_read(struct image_reader *img_rd)
{
	FILE *fp_src = NULL;

	if (img_rd == NULL) {
		printf("%s parameter NULL\n",__FUNCTION__);
		return -1;
	}

	/* Start Reading BMP File */
	fp_src = fopen(img_rd->image_name, "rb");
	if (fp_src == NULL) {
		printf("File Not Present\n");
		return -1;
	} else {
		printf("Src file open successfuly\n");
	}

	/* Reading Header 54 bytes in BMP image */
	for (int i = 0; i < BMP_HEADER_SIZE; i++) {
		img_rd->header[i] = getc(fp_src);
	}

	/* Reading Width From Header */
	(img_rd->width) = *(int *)(&(img_rd->header[18]));

	/* Reading Height From Header */
	(img_rd->height) = *(int *)(&(img_rd->header[22]));

	/* Reading bitDepth From Header. This is use for identify either color
	   Table is present or not
	 */
	(img_rd->bitDepth) = *(int *)(&(img_rd->header[28]));

	printf("Width = %d\nHeight = %d\nDepth = %d\n",(img_rd->width), (img_rd->height), (img_rd->bitDepth));
	/* Reading Color Table */
	if ((img_rd->bitDepth) <= 8) {
		printf("Image having color table\n");
		fread(img_rd->colorTable, sizeof(unsigned char), 1024, fp_src);
	}
	/* Reading Data */
	fread(img_rd->buf, sizeof(unsigned char), CUSTOM_IMG_SIZE, fp_src);

	fclose(fp_src);

	return 0;
}

/*
 * Name: image_copy()
 * Desc: This is used for copy an image from one location
 *	 to other location.
 * Parameter: No Parametr.
 * Return : 0 = on Success
 * 	    < 0 = On Failure
 * */
int image_copy()
{
	FILE *fp_src = NULL;
	int ret = -1;

	char img_name_src_path[IMG_NAME_PATH_LENGTH] = {0};
	char img_name_dst_path[IMG_NAME_PATH_LENGTH] = {0};
	char src_img_name[IMG_NAME_BUFF_LENGTH] = {0};
	struct image_reader img_rd;
	struct image_writer img_wr;

	printf("Please Enter Src image name\n");
	scanf("%s",src_img_name);
	sprintf(img_name_src_path, "%s/%s",IMG_SEARCH_PATH, src_img_name);
	sprintf(img_name_dst_path, "%s/copy_%s",IMG_SEARCH_PATH, src_img_name);
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
	memcpy(img_wr.buf, img_rd.buf, sizeof(img_rd.buf));
	img_wr.bitDepth = img_rd.bitDepth;
	ret = bmp_image_write(&img_wr);
	if (ret < 0) {
		printf("Error return from bmp_image_write()\n");
	} else {
		printf("Image write success\n");
	}
#if 0
	/* Start Reading BMP File */
	fp_src = fopen(img_name_src_path, "rb");
	if (fp_src == NULL) {
		printf("File Not Present\n");
		return -1;
	} else {
		printf("Src file open successfuly\n");
	}

	/* Reading Header 54 bytes in BMP image */
	for (int i = 0; i < BMP_HEADER_SIZE; i++) {
		img_rd.header[i] = getc(fp_src);
	}
	(img_rd.width) = *(int *)(&(img_rd.header[18]));
	(img_rd.height) = *(int *)(&(img_rd.header[22]));
	(img_rd.bitDepth) = *(int *)(&(img_rd.header[28]));
	printf("Width = %d\nHeight = %d\nDepth = %d\n",(img_rd.width), (img_rd.height), (img_rd.bitDepth));
	if ((img_rd.bitDepth) <= 8) {
		printf("Image having color table\n");
		fread(img_rd.colorTable, sizeof(unsigned char), 1024, fp_src);
	}
	fread(img_rd.buf, sizeof(unsigned char), CUSTOM_IMG_SIZE, fp_src);
	fclose(fp_src);
	/* Stop Reading BMP File */
#endif	
	return 0;
}