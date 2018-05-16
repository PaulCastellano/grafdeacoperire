#include <curses.h>

#include <stdio.h>

#include <stdlib.h>

#include <mlx.h>

# define N 50

typedef struct s_img
{
    int x;
    int y;
    int color;
}               t_img;

typedef struct s_allimg
{
    t_img img[60][60];
}               t_allimg;

typedef struct nod

{

	int val;

	struct nod *urm;

}NOD;

NOD *p[N];
t_img img[60][60];
t_allimg allimg[N];

int m[N],g[N][N];

int n;
void *ptr;
void *win;

void List_de_ad()

{
    int x;
    int j;
	int i;
    int lung;

	NOD *c,*r;

	printf("Introdu nunarul de virfuri: ");

	scanf("%d",&n);

	for(i=0; i<n; i++)

	{

		p[i] = NULL;

		c = NULL;

		printf("X%d -> ",i+1);

		c = (NOD*)malloc(sizeof(NOD));

		c->urm = NULL;

		scanf("%d",&c->val);

		p[i] = c;

		while(c->val)

		{

			r = NULL;

			r = (NOD*)malloc(sizeof(NOD));

			scanf("%d",&r->val);

			r->urm = NULL;

			c->urm = r;

			c = r;

		}

	}
    ptr = mlx_init();
    win = mlx_new_window(ptr, 600, 600, "GrafInitial");
	x = -1;
    while (++x < n)
    {
    	i = -1;
    	while (++i < 60)
        {
        	j = -1;
            while (++j < 60)
            {
                allimg[x].img[i][j].x = j - 30;
                allimg[x].img[i][j].y = 30 - i;
                if ((allimg[x].img[i][j].x * allimg[x].img[i][j].x) + (allimg[x].img[i][j].y * allimg[x].img[i][j].y) == (30 * 30))
                    allimg[x].img[i][j].color = 0x0000ff;
                else
                    allimg[x].img[i][j].color = 0x000000;
                printf("|%d||%d||%d|", x, allimg[x].img[i][j].x, allimg[x].img[i][j].y);
            }
			printf("\n");
        }
    }
    if (n % 2 == 0)
    {
        x = -1;
        lung = 0;
        while (++x < n / 2)
        {
            i = -1;
            while(++i < 60)
            {
                j = -1;
                while (++j < 60)
                {
                    allimg[x].img[i][j].x = j + 600 / n + lung;
                    allimg[x].img[i][j].y = i + 200;
                    mlx_pixel_put(ptr, win, allimg[x].img[i][j].x, allimg[x].img[i][j].y, allimg[x].img[i][j].color);
                }
            }
            lung += 100;
        }
		x = n / 2 - 1;
        lung = 0;
        while (++x < n)
        {
            i = -1;
            while(++i < 60)
            {
                j = -1;
                while (++j < 60)
                {
                    allimg[x].img[i][j].x = j + 600 / n + lung;
                    allimg[x].img[i][j].y = i + 400;
                    mlx_pixel_put(ptr, win, allimg[x].img[i][j].x, allimg[x].img[i][j].y, allimg[x].img[i][j].color);
                }
            }
            lung += 100;
        }
    }
	else 
	{
		x = -1;
        lung = 0;
        while (++x < n / 2)
        {
            i = -1;
            while(++i < 60)
            {
                j = -1;
                while (++j < 60)
                {
                    allimg[x].img[i][j].x = j + 600 / n + lung;
                    allimg[x].img[i][j].y = i + 100;
                    mlx_pixel_put(ptr, win, allimg[x].img[i][j].x, allimg[x].img[i][j].y, allimg[x].img[i][j].color);
                }
            }
			printf("|%d|", x);
        	lung += 100;
		}
		printf("\n");
		x = n / 2;
        lung = 0;
        while (++x < n)
        {
            i = -1;
            while(++i < 60)
            {
                j = -1;
                while (++j < 60)
                {
                    allimg[x].img[i][j].x = j + 600 / n + lung;
                    allimg[x].img[i][j].y = i + 500;
                    mlx_pixel_put(ptr, win, allimg[x].img[i][j].x, allimg[x].img[i][j].y, allimg[x].img[i][j].color);
                }
            }
            lung += 100;
			printf("|%d|", x);
        }
		printf("\n");
		x = n / 2;
		i = -1;
		lung /= (x * 2);
        while(++i < 60)
        {
            j = -1;
            while (++j < 60)
            {
                allimg[x].img[i][j].x = j + 600 / n + lung;
                allimg[x].img[i][j].y = i + 300;
                mlx_pixel_put(ptr, win, allimg[x].img[i][j].x, allimg[x].img[i][j].y, allimg[x].img[i][j].color);
            }
			lung += 100;
        }
	}
}

void adinc(NOD *y,int i)

{

	m[i-1] = 1;

	while(y->val)

	{

		if(!m[y->val-1])

		{

			g[i-1][y->val-1] = 1;

			g[y->val-1][i-1] = 1;

			adinc(p[y->val-1],y->val);

		}

		y = y->urm;

	}

}

void graf_de_acop()

{

	int i,j;

	for(i=0; i<n; i++)

		for(j=0; j<n; j++)

			g[i][j]=0;

	for(i=0; i<n; i++)

		m[i] = 0;

	for (i=0; i<n; i++)

		if(!m[i])

			adinc(p[i],i+1);

	for(i=0;i<n;i++)

	{

		printf("virf %d -> ",i+1);

		for(j=0; j<n; j++)

			if (g[i][j])

				printf("%d, ",j+1);

		printf("0\n");

	}

}

int main()

{

	int f;

	while(1)

	{

		system("cls");

		printf("[ 1 ] Introdu lista de adiacenta\n");

		printf("[ 2 ] Afisarea rezultatul\n\n");

		printf("[ 0 ] Exit\n\n");

		printf("Comanda » ");

		fflush(stdin);

		scanf("%d",&f);

		system("cls");

		switch(f)

		{

			case 0:

				exit(0);

				break;

			case 1:

				List_de_ad();

				break;

			case 2:

				graf_de_acop();

				break;

			default :

				printf("\aAti introdus o comanda gresita!\n");

				break;
		}

		getch();

	}

	return 0;

}
