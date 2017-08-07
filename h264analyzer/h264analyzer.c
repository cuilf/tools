/*************************************************************************
    > File Name: h264analyzer.c
    > Author: cuilf
    > Mail: cuilongfeiii@163.com 
    > Created Time: 2017年08月04日 星期五 16时19分51秒
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>

#include "h264analyzer.h"

static bool is_nalu_startcode(uint8_t *data)
{
	bool is_startcode = false;
	if ((data[0] == 0x00) && (data[1] == 0x00) && (data[2] == 0x00) && (data[3] == 0x01))
    {
        printf ("is nalu startcode\n");
		is_startcode = true;
		
    }
	return is_startcode;
}

static AM_VIDEO_FRAME_TYPE frame_type_anyalyze(uint8_t *data)
{
	AM_VIDEO_FRAME_TYPE frame_type = AM_VIDEO_FRAME_TYPE_NONE;
	if ((data[0] != 0) || (data[1] != 0) || (data[2] != 0) || (data[3] != 1))
    {
       // printf("error nalu header:%02x %02x %02x %02x\n", data[0], data[1], data[2], data[3]);
        return (frame_type);
    }

    switch (data[NALU_HDR_LEN] & NALU_TYPE_MASK)
    {
    case 1:
    {
        printf ("SLICE:");

        switch ((data[NALU_HDR_LEN + 1] & SLICE_TYPE_MASK) >> 1)
        {
            case 4:
            {
                printf ("I frame\n");
                frame_type = AM_VIDEO_FRAME_TYPE_I;
                break;
            }
            case 5:
            {
                printf ("P frame\n");
                frame_type = AM_VIDEO_FRAME_TYPE_P;
                break;
            }
            default:
            {
                printf ("error frame type : %u\n", data[NALU_HDR_LEN + 1]);
                break;
            }
        }

        break;
    }
        case 7:
        {
            printf ("SPS\n");
            frame_type = AM_VIDEO_FRAME_TYPE_IDR;
            break;
        }
        case 8:
        {
            printf ("PPS\n");
            frame_type = AM_VIDEO_FRAME_TYPE_IDR;
            break;
        }
        case 5:
        {
            printf ("IDR\n");
            frame_type = AM_VIDEO_FRAME_TYPE_IDR;
            break;
        }
        default:
        {
            printf ("error nalu type : %u\n", data[NALU_HDR_LEN]);
            break;
        }
    }


    return frame_type;
}
int main(int argc, char* argv[])
{
    FILE *fp;
    AM_VIDEO_FRAME_TYPE type;
    
    int  k;
    
    char *buffer_addr[4] ; 	
    unsigned int buffer_size[4];
    
    buffer_size[0] = 13251;
    buffer_size[1] = 750;
    buffer_size[2] = 642;
    buffer_size[3] = 771;
    
    
    fp = fopen(argv[1], "r");
    if (NULL == fp)
    {
    	perror("open file failed:");
		return -1;
    }
    
    for (k = 0; k < 4; k++)
    {
        buffer_addr[k] = (unsigned char*)malloc(sizeof (char) * buffer_size[k]);
        fread (buffer_addr[k], buffer_size[k], 1, fp);
    }     
    fclose (fp);


    

	
	

	uint8_t *frame_in_idr_addr[3];
	uint32_t frame_in_idr_size[3];
	uint8_t *frame_in_idr_addr_base;
	uint8_t *nalu_addr;
	uint32_t nalu_size;
	
	
    for (k = 0; k < 4; k++)
    {
        nalu_addr = buffer_addr[k];
        nalu_size = buffer_size[k];
        
        type = frame_type_anyalyze(nalu_addr); //frame buffer type 


        if (AM_VIDEO_FRAME_TYPE_IDR == type)
        {        
        	uint32_t i = 0, j = 0;
	        frame_in_idr_addr_base = nalu_addr;
            for (i = 0; i < nalu_size; i++)
	        {
		        if (is_nalu_startcode(nalu_addr)) //IDR buffer
		        {	
			        frame_in_idr_addr[j] = nalu_addr;
			        frame_in_idr_size[j] = nalu_addr - frame_in_idr_addr_base;
		
			        frame_in_idr_addr_base = nalu_addr;
			        j++;
		        }
		        nalu_addr++;
	        }
	        frame_in_idr_size[0] = frame_in_idr_size[1];
	        frame_in_idr_size[1] = frame_in_idr_size[2];
	        frame_in_idr_size[2] = nalu_size - frame_in_idr_size[1] - frame_in_idr_size[0];
	
	
	        for (i = 0; i < 3; i++)
	        {
		        printf ("addr data = %x %x %x %x %x %x ,data_size = %d\n", \
		        *(frame_in_idr_addr[i]), *(frame_in_idr_addr[i]+1), *(frame_in_idr_addr[i]+2), *(frame_in_idr_addr[i]+3), \
		        *(frame_in_idr_addr[i]+4), *(frame_in_idr_addr[i]+5), frame_in_idr_size[i]);
		         
	        }       
        }
        else 
        {
            printf ("size = %d \n", nalu_size);
        }


		


	   
    }
    
    return 0;

}
