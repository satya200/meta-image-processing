/*
 * AUTHOR: Satya Sundar Sahu
 * DATE: 27-Aug-2019
 * DESC: File contains Histogram Equalization of an Image
 * */

#include"my_header.h"

/*
 * Name: histogram()
 * Desc: This is used for write an image.
 * Parameter: @img_rd is a strusture. for structure member
 *            Refer "my_header.h" file.
 *	      @img_hist holds the histogram data
 *	      @type holds the type of image going to process
 *	      @index_max & index_min holds the max and min intensity of an Image
 * Return : 0 = on Success
 *          < 0 = On Failure
 * */
static int histogram(struct image_reader img_rd, float *img_hist, enum image_type type, int index_max, 
		int index_min, char *name)
{
	int ret = -1;
	FILE *fp = NULL;
	long int sum = 0;
	int row, col, i, j, pos = 0;
	long int ihist[256] = {0};
	int val_max, val_min;
	char hist_name[IMG_NAME_PATH_LENGTH] = {0};

	if (name == NULL) {
		strcpy(hist_name, "hist.txt");
	} else {
		sprintf(hist_name, "hist_%s.txt", name);
	}
	row = img_rd.height;
	col = img_rd.width;

	if (type == GREAY) {
		fp = fopen(hist_name, "w");
		if (fp == NULL) {
			printf("Unable create histogram file fopen NULL\n");
			return -1;
		}
		printf("File created successfully\n");
		for (i = 0; i < row; i++) {
			for (j = 0; j < col; j++) {
				pos = *((img_rd.buf)+i+j*col);
				ihist[pos] = ihist[pos] + 1;
				sum += 1;
			}
		}
		printf("Satya\n");
		val_max = 0;
		val_min = ihist[0];
		for (i = 0; i <= 255 ; i++) {
			if (ihist[i] > val_max) {
				val_max = ihist[i];
				index_max = i;
			}
			if (ihist[i] < val_min) {
				val_min = ihist[i];
				index_min = i;
			}
			img_hist[i] = (float)ihist[i]/(float)sum;
			fprintf(fp,"\n%f",img_hist[i]);
			//printf("%d:%f\n",i,img_hist[i]);
		}
		printf("Maximum frequency index_max=%d and val_max=%d\n",index_max, val_max);
		printf("Minimum frequency index_min=%d and val_min=%d\n",index_min, val_min);
		/*for(i = 0; i<=255; i++) {
			fprintf(fp,"\n%f",img_hist[i]);
		}*/
		printf("Satya2\n");
		ret = 0;
		fclose(fp);
	}
	return ret;
}

/*
 * Name: bmp_create_histogram()
 * Desc: This is used to create histogram data of an Image.
 * Parameter: No parameter
 *
 * Return : 0 = on Success
 *          < 0 = On Failure
 * */
int bmp_creat_histogram()
{
	int ret = -1;

	char img_name_src_path[IMG_NAME_PATH_LENGTH] = {0};
	//char img_name_dst_path[IMG_NAME_PATH_LENGTH] = {0};
	char src_img_name[IMG_NAME_BUFF_LENGTH] = {0};
	struct image_reader img_rd;
	struct image_writer img_wr;
	int img_size;
	float *img_hist = NULL;
	int temp, index_max, index_min;

	printf("Please Enter greay scale image name\n");
	scanf("%s",src_img_name);
	sprintf(img_name_src_path, "%s/%s",IMG_SEARCH_PATH, src_img_name);
	//sprintf(img_name_dst_path, "%s/grey_%s",IMG_SEARCH_PATH, src_img_name);
	printf("Source image:%s\n",img_name_src_path);

	strcpy(img_rd.image_name, img_name_src_path);
	ret = bmp_image_read(&img_rd);
	if (ret < 0) {
		printf("Error return from bmp_image_read():%d\n",ret);
	} else {
		printf("Image read success\n");
	}

	if (img_rd.bitDepth == 24) {
		printf("This is RGB Image\n");
		//ret = histogram(img_rd, img_hist, RGB);
	} else if (img_rd.bitDepth == 8) {
		printf("This is Grey Scale Image\n");
		img_hist = (float *)malloc(256 * sizeof(float));
		if (img_hist == NULL) {
			printf("malloc return NULL\n");
			return -1;
		}
		ret = histogram(img_rd, img_hist, GREAY, index_max, index_min, src_img_name);
		if (ret < 0) {
			ret = -1;
			printf("Unable to get histogram:%d\n",ret);
		} else {
			ret = 0;
			printf("Histogram get Success\n");
		}
	} else {
		ret = -3;
		printf("Sorry This image format will not support:%d\n",img_rd.bitDepth);
	}
	if (img_hist != NULL) {
		free(img_hist);
		img_hist = NULL;
	}
	return ret;
}

int bmp_histogram_equ()
{
	int ret = -1;
	int i, j, x, y, row, col, index_max, index_min;
	char img_name_src_path[IMG_NAME_PATH_LENGTH] = {0};
	char img_name_dst_path[IMG_NAME_PATH_LENGTH] = {0};
	char src_img_name[IMG_NAME_BUFF_LENGTH] = {0};
	struct image_reader img_rd;
	struct image_writer img_wr;
	int img_size;
	float sum = 0.0;
	int histeq[256] = {0};
	float *img_hist = NULL;

	printf("Please Enter greay scale image name\n");
	scanf("%s",src_img_name);
	sprintf(img_name_src_path, "%s/%s",IMG_SEARCH_PATH, src_img_name);
	sprintf(img_name_dst_path, "%s/histeq_%s",IMG_SEARCH_PATH, src_img_name);
	printf("Source image:%s\n",img_name_src_path);

	strcpy(img_rd.image_name, img_name_src_path);
	strcpy(img_wr.new_image_name, img_name_dst_path);
	ret = bmp_image_read(&img_rd);
	if (ret < 0) {
		printf("Error return from bmp_image_read():%d\n",ret);
	} else {
		printf("Image read success\n");
	}

	row = img_rd.height;
        col = img_rd.width;

	if (img_rd.bitDepth == 24) {
		printf("This is RGB Image\n");
		//ret = histogram(img_rd, img_hist, RGB);
	} else if (img_rd.bitDepth == 8) {
		printf("This is Grey Scale Image\n");
		img_hist = (float *)malloc(256 * sizeof(float));
		if (img_hist == NULL) {
			printf("malloc return NULL\n");
			return -1;
		}

		memcpy(img_wr.header, img_rd.header, sizeof(img_rd.header));
		memcpy(img_wr.colorTable, img_rd.colorTable, sizeof(img_rd.colorTable));
		img_wr.bitDepth = img_rd.bitDepth;
		/* Get Histogram Details */
		ret = histogram(img_rd, img_hist, GREAY, index_max, index_min, src_img_name);
		if (ret < 0) {
			ret = -1;
			printf("Unable to get histogram:%d\n",ret);
		} else {
			printf("Histogram Eq Started\n");
			for (i = 0; i < 256; i++) {
				sum = 0.0;
				for (j = 0; j <= i; j++) {
					sum = sum+img_hist[j];
				}
				histeq[i] = (int)(255*sum+0.5);
			}
			/* Histogram Equilization Algo */
			for (i = 0; i < row; i++) {
				for (j = 0; j < col; j++) {
					*((img_wr.buf)+j+i*col) =  histeq[*((img_rd.buf)+j+i*col)];
				}
			}
			ret = bmp_image_write(&img_wr);
			if (ret < 0) {
				printf("Error return from bmp_image_write():%d\n",ret);
			} else {
				printf("Histogram Equ Image write success\n");
			}
			ret = 0;	
		}
	} else {
		ret = -3;
		printf("Sorry This image format will not support:%d\n",img_rd.bitDepth);
	}
	if (img_hist != NULL) {
		free(img_hist);
		img_hist = NULL;
	}
	return ret;
}
