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
    t_img img[61][61];
	int drum[N];
}               t_allimg;

typedef struct nod

{

	int val;

	struct nod *urm;

}NOD;

NOD *p[N];
t_img img[61][61];
t_allimg allimg[N];

int m[N],g[N][N];

int n;
void *ptr;
void *win;
void *ptr2;
void *win2;
char *str;

char					*ft_itoa_base(int value, int base)
{
	static char rep[] = "0123456789abcdef";
	static char buf[50];
	char *ptr;
	int num;

	ptr = &buf[49];
	*ptr = '\0';
	num = value;
	if (value < 0 && base == 10)
		value *= -1;
	if (value == 0)
		*--ptr = rep[value % base];
	while (value != 0)
	{
		*--ptr = rep[value % base];
		value /= base;
	}
	if (num < 0 && base == 10)
		*--ptr = '-';
	return (ptr);
}


void linelow(int x0, int y0, int x1, int y1, void *mlx_win, void *mlx_ptr)
{
    int dx;
    int dy;
    int yi;
    dy = y1 - y0;
    yi = 1;
    dx = x1 - x0;
    if (dy < 0)
    {
        yi = -1;
        dy *= -1;
    }
    int D = 2 * dy - dx;
    int y = y0;
    int x = x0;
    while (x < x1)
    {
        mlx_pixel_put (mlx_ptr, mlx_win, x, y, 0x00ff00);
        if (D > 0)
        {
            y = y + yi;
            D = D - 2*dx;
        }
        D = D + 2 * dy;
        x++;
    }
}

void linehigh(int x0, int y0, int x1, int y1, void *mlx_win, void *mlx_ptr)
{
    int dx;
    int dy;
    int xi;
    xi = 1;
    dy = y1 - y0;
    dx = x1 - x0;
    if (dx < 0)
    {
        xi = -1;
        dx *= -1;
    }
    int D = 2 * dx - dy;
    int x = x0;
    int y = y0;
    while (y < y1)
    {
        mlx_pixel_put (mlx_ptr, mlx_win, x, y, 0x00ff00);
        if (D > 0)
        {
            x = x + xi;
            D = D - 2 * dy;
        }
        D = D + 2 * dx;
        y++;
    }
}

void line(int x0, int y0, int x1, int y1, void *mlx_win, void *mlx_ptr)
{
    if (abs(y1 - y0) < abs(x1 - x0))
    {
        if (x0 > x1)
            linelow(x1, y1,x0,y0, mlx_win, mlx_ptr);
        else
            linelow(x0,y0,x1,y1, mlx_win, mlx_ptr);
    }
    else if (y0 > y1)
        linehigh(x1,y1,x0,y0, mlx_win, mlx_ptr);
    else
        linehigh(x0,y0,x1,y1,mlx_win, mlx_ptr);
}


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
		j = -1;
		while (++j < n)
			allimg[i].drum[j] = 0;
		while(c->val)

		{	
			r = NULL;

			r = (NOD*)malloc(sizeof(NOD));

			scanf("%d",&r->val);

			r->urm = NULL;		
			allimg[i].drum[c->val - 1] = 1;
			c->urm = r;
			c = r;
		}
	}
    ptr = mlx_init();
    win = mlx_new_window(ptr, 600, 600, "Graf de acoperire Initial");
	x = -1;
    while (++x < n)
    {
    	i = -1;
    	while (++i < 61)
        {
        	j = -1;
            while (++j < 61)
            {
                allimg[x].img[i][j].x = j - 30;
                allimg[x].img[i][j].y = 30 - i;
                if ((allimg[x].img[i][j].x * allimg[x].img[i][j].x) + (allimg[x].img[i][j].y * allimg[x].img[i][j].y) <= (24 * 24))
                    allimg[x].img[i][j].color = 0x00ff00;
                else
                    allimg[x].img[i][j].color = 0x000000;
            }
        }
    }
    if (n % 2 == 0)
    {
        x = -1;
        lung = 0;
        while (++x < n / 2)
        {
            i = -1;
            while(++i < 61)
            {
                j = -1;
                while (++j < 61)
                {
                    allimg[x].img[i][j].x = j + 600 / n + lung;
                    allimg[x].img[i][j].y = i + 200;
					mlx_string_put(ptr, win, allimg[x].img[30][30].x, allimg[x].img[30][30].y, 0xff0000, ft_itoa_base(x + 1, 10));
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
            while(++i < 61)
            {
                j = -1;
                while (++j < 61)
                {
                    allimg[x].img[i][j].x = j + 600 / n + lung;
                    allimg[x].img[i][j].y = i + 400;
					mlx_string_put(ptr, win, allimg[x].img[30][30].x, allimg[x].img[30][30].y, 0xff0000, ft_itoa_base(x + 1, 10));
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
            while(++i < 61)
            {
                j = -1;
                while (++j < 61)
                {
                    allimg[x].img[i][j].x = j + 600 / n + lung;
                    allimg[x].img[i][j].y = i + 200;
					mlx_string_put(ptr, win, allimg[x].img[30][30].x, allimg[x].img[30][30].y, 0xff0000, ft_itoa_base(x + 1, 10));
                    mlx_pixel_put(ptr, win, allimg[x].img[i][j].x, allimg[x].img[i][j].y, allimg[x].img[i][j].color);
                }
            }
        	lung += 100;
		}
		x = n / 2 - 1;
        lung = 0;
        while (++x < n - 1)
        {
            i = -1;
            while(++i < 61)
            {
                j = -1;
                while (++j < 61)
                {
                    allimg[x].img[i][j].x = j + 600 / n + lung;
                    allimg[x].img[i][j].y = i + 400;
					mlx_string_put(ptr, win, allimg[x].img[30][30].x, allimg[x].img[30][30].y, 0xff0000, ft_itoa_base(x + 1, 10));
                    mlx_pixel_put(ptr, win, allimg[x].img[i][j].x, allimg[x].img[i][j].y, allimg[x].img[i][j].color);
                }
            }
            lung += 100;
        }
		x = n  - 1;
		i = -1;
		lung = (lung / n) + 12;
        while(++i < 61)
        {
            j = -1;
            while (++j < 61)
            {
                allimg[x].img[i][j].x = j + allimg[0].img[30][60].x * 2 - allimg[n / 2].img[30][0].x;
                allimg[x].img[i][j].y = i + 300;
				mlx_string_put(ptr, win, allimg[x].img[30][30].x, allimg[x].img[30][30].y, 0xff0000, ft_itoa_base(x + 1, 10));
                mlx_pixel_put(ptr, win, allimg[x].img[i][j].x, allimg[x].img[i][j].y, allimg[x].img[i][j].color);
            }
        }
	}
	x = -1;
	while (++x < n)
	{
		i = -1;
		while (++i < n)
		{
			if (allimg[x].drum[i] != 0)
			{
				line(allimg[x].img[30][30].x, allimg[x].img[30][30].y, allimg[i].img[30][30].x, allimg[i].img[30][30].y, win, ptr);
			}
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

	int i, j, x;

	i = -1;
	while (++i < n)
	{
		j = -1;
		while (++j < n)
			allimg[i].drum[j] = 0;
	}
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

		printf("X%d -> ",i+1);
		for(j=0; j<n; j++)

			if (g[i][j])
			{
				printf("%d, ",j+1);
				allimg[i].drum[j] = 1;
			}

		printf("0\n");

	}
	ptr2 = mlx_init();
	win2 = mlx_new_window(ptr, 600, 600, "graf de dacoperire rezultat");
	x = -1;
	while (++x < n)
	{
		i = -1;
		while (++i < 61)
		{
			j = -1;
			while (++j < 61)
			{
				if (allimg[x].img[i][j].color == 0x00ff00)
					mlx_pixel_put(ptr2, win2, allimg[x].img[i][j].x, allimg[x].img[i][j].y, allimg[x].img[i][j].color);
			}
		}
		mlx_string_put(ptr2, win2, allimg[x].img[30][30].x, allimg[x].img[30][30].y, 0xff0000, ft_itoa_base(x + 1, 10));
	}
	x = -1;
	while (++x < n)
	{
		i = -1;
		while (++i < n)
		{
			if (allimg[x].drum[i] != 0)
			{
				line(allimg[x].img[30][30].x, allimg[x].img[30][30].y, allimg[i].img[30][30].x, allimg[i].img[30][30].y, win2, ptr2);
			}
		}
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
