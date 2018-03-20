#include <stdio.h>

#define FONT_H (8)
#define PAD (15)
#define GRAPH_W (10)
#define DATA_NUM (sizeof(data)/sizeof(data[0]))
short data[] = {
    50, 10, 10, 10, 40, 210, 20, 
    50, 10, 20, 20, 40, 100, 20, 
    50, 10, 20, 30, 30, 100, 20, 
    50, 10, 20, 30, 40, 100, 20, 
    50, 10, 20, 30, 40, 100, 20, 
};

int GetMax()
{
    int i = 0;
    int max = 0;
    for (i=0; i<DATA_NUM; i++) {
        if (max < data[i]) {
            max = data[i];
        }
    }
    return max;
}

int GetGridHeight()
{
    int h = 0;
    int max = GetMax();
    for (h=1; h<60000; h*=10) {
        if (max/h <= 4) {
            break;
        } else if (max/h <= 8) {
            h *= 2;
            break;
        } else if (max/h <= 20) {
            h *= 5;
            break;
        } else {
            /* next */
        }
    }
    return h;
}

int main(int argc, char **argv){

    int i = 0;
    int max = GetMax();
    int grid_height = GetGridHeight();

    printf("<!DOCTYPE html>\n");
    printf("<html>\n");
    printf("<body>\n");
    
    printf("<svg width='1000' height='500' viewBox='0 0 %d %d'>\n", DATA_NUM * GRAPH_W + PAD * 2, max + PAD * 2);
    printf("<rect width='100%%' height='100%%' fill='#fafafa' />\n");

    printf("<g font-size='%d' transform='translate(%d, %d)'>\n", FONT_H, PAD, PAD);
    {
        for (i=0; i<=max; i+=grid_height) {
            printf("<line x1='%d' y1='%d' x2='%d' y2='%d' stroke='#e2e2e3' stroke-width='2'/>\n", 
                0, max - i, DATA_NUM * GRAPH_W, max - i
            );
        }

        printf("<path stroke='#0176c0' stroke-width='1' fill='#01a8f7' d='\n");
        printf("M0,%d\n", max);
        for (i=0; i<DATA_NUM; i++) {
            printf("V%d V%d h%d\n", max, max - data[i], GRAPH_W);
        }
        printf("V%d\n", max);
        printf("z\n");
        printf("'/>\n");
        
        for (i=0; i<DATA_NUM; i++) {
            if ( (i==0) || (data[i] != data[i-1]) ) {
                printf("<text x='%d' y='%d'>%d</text>\n", i * GRAPH_W, max - data[i] - FONT_H / 4, data[i]);
            }
        }
    }
    
    printf("</g>\n");
    printf("</svg>\n");
    printf("</body>\n");
    printf("</html>\n");
    
	return 0;
}
