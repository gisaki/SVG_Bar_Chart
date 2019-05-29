#include <stdio.h>

#define FONT_H (8)
#define PAD (15)
#define GRAPH_W (10)
#define DATA_NUM_MAX DATA_NUM(1)
#define DATA_NUM(i) (sizeof(data ## i)/sizeof(data ## i[0]))
#define DATA_SERIES(i) (data ## i)
short data1[] = {
    50, 10, 10, 10, 40, 210, 20, 
    50, 10, 20, 20, 40, 100, 20, 
    50, 10, 20, 30, 30, 100, 20, 
    50, 10, 20, 30, 40, 100, 20, 
    50, 10, 20, 30, 40, 100, 20, 
};
short data2[] = {
    10, 20, 30, 30, 100, 20, 50, 
    10, 20, 30, 40, 100, 20, 50, 
    10, 20, 30, 40, 100, 20, 50, 
};
#define YSCALE_NUM (5)

int GetMax()
{
    return 100; /* means 100% */
}

int main(int argc, char **argv){

    int i = 0;
    int max = GetMax();

    printf("<!DOCTYPE html>\n");
    printf("<html>\n");
    printf("<body>\n");
    
    printf("<svg width='%d' height='%d' viewBox='0 0 %d %d'>\n", 
		DATA_NUM_MAX * GRAPH_W + PAD * 2, 
		max + PAD * 2, 
		DATA_NUM_MAX * GRAPH_W + PAD * 2, 
		max + PAD * 2
	);
    printf("<rect width='100%%' height='100%%' fill='#F1F8E9' />\n");

    printf("<g font-size='%d' transform='translate(%d, %d)'>\n", FONT_H, PAD, PAD);
    {
		/* axis */
		/* Overwrite after drawing the path */

		/* distribute scale Y */
        for (i=0; i<=YSCALE_NUM; i++) {
			if (i != YSCALE_NUM) { /* no stroke for bottom line */
				printf("<path d='M%d %d h%d' stroke='#cccccc' stroke-width='1' stroke-dasharray='5 5' />", 0, max * i / YSCALE_NUM, DATA_NUM_MAX * GRAPH_W);
			}
			printf("<text x='%d' y='%d' text-anchor='end'>%d</text>", 0, max * i / YSCALE_NUM, (YSCALE_NUM - i) * 100 / YSCALE_NUM);
		}

		/* path */
		{
			const int data_num = DATA_NUM(1);
			short* data = DATA_SERIES(1);
			printf("<path stroke='#FF59bc' stroke-width='1' fill='#ffc8e9' fill-opacity='0.3' d='\n");
			printf("M0 %d L\n", max);
			for (i=0; i<data_num; i++) {
				printf("%d %d,\n", i * GRAPH_W + GRAPH_W / 2, max - data[i]);
			}
			printf("V%d\n", max);
			printf("z\n");
			printf("'/>\n");
		}
		{
			const int data_num = DATA_NUM(2);
			short* data = DATA_SERIES(2);
			printf("<path stroke='#06c3d3' stroke-width='1' fill='#afeaff' fill-opacity='0.3' d='\n");
			printf("M0 %d L\n", max);
			for (i=0; i<data_num; i++) {
				printf("%d %d,\n", i * GRAPH_W + GRAPH_W / 2, max - data[i]);
			}
			printf("V%d\n", max);
			printf("z\n");
			printf("'/>\n");
		}
        
		/* data label */
		{
			const int data_num = DATA_NUM(1);
			short* data = DATA_SERIES(1);
			for (i=0; i<data_num; i++) {
				if ( (i==0) || (data[i] != data[i-1]) ) {
					printf("<text x='%d' y='%d'>%d</text>\n", i * GRAPH_W, max - data[i] - FONT_H / 4, data[i]);
				}
			}
		}
		{
			const int data_num = DATA_NUM(2);
			short* data = DATA_SERIES(2);
			for (i=0; i<data_num; i++) {
				if ( (i==0) || (data[i] != data[i-1]) ) {
					printf("<text x='%d' y='%d'>%d</text>\n", i * GRAPH_W, max - data[i] - FONT_H / 4, data[i]);
				}
			}
		}

		/* axis */
		/* Overwrite after drawing the path */
		printf("<path d='M%d %d v%d' stroke='#333333' stroke-width='1' />", 0, 0, max);
		printf("<path d='M%d %d h%d' stroke='#333333' stroke-width='1' />", 0, max, DATA_NUM_MAX * GRAPH_W);

		printf("</g>\n");

    }
    
    printf("</g>\n");
    printf("</svg>\n");
    printf("</body>\n");
    printf("</html>\n");
    
	return 0;
}
