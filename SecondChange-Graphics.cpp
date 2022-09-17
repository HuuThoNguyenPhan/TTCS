#include<graphics.h>
#include<bits/stdc++.h>
using namespace std;

int faults=0;
char to_char(int n)
{
	if(n>=0 && n<=9)
	{
		return n+48;
	}
	else
	{
		return ' ';
	}
}

void pf(int x, int y, int n)
{
	int f = faults;
	for(int i=0;f>0;i++)
	{
		int tmp = f%10;
		char a[10];
		a[0] = to_char(tmp);
		settextstyle(8,0,3);
		outtextxy(350-i*15,130+43*n+40,a);
		f=f/10;
	}
}

void draw(int x, int y, int frame[], int n)
{
	settextstyle(8,0,4);
	outtextxy(60,20,"Second Chancepage replacement algorithm");
	
	setcolor(GREEN);
    settextstyle(8,0,3);
    char a[100];
    for(int i = 0; i < n ; i++)
    {
    	a[i]=to_char(frame[i]);
    }
    for(int i = 0 ; i < n; i++)
    {
    	char p[10];
    	p[0] = a[i];
    	rectangle(y,x+i*43,y+43,x+(1+i)*43); 
    	if(i==0)
    	{
    		outtextxy(y+15,x+12,p);
    	}
    	else
    	{
    		outtextxy(y+15,x+12+i*43,p);
    	}
    }
	
	settextstyle(8,0,3);
	outtextxy(35,130+43*n+40,"Number of page faults: ");
	pf(x,y,n);	
	
}

int present(int frame[], int nf, int page, int bit[])
{
	for(int i=0; i<nf; i++)
		if(page == frame[i])
		{
			bit[i] = 1;
			return 1;
		}

	return 0;
}

void print(int frame[], int nf)
{
	for(int i=0; i<nf; i++)
	{
		if(frame[i] == -1)
			printf("-- ");
		else
			printf("%2d ", frame[i]);
	}
	printf("|");
}
int findpos(int frame[], int m, int x, int pos, int bit[])
{
	while(true)
	{
		if(!bit[pos])
        {
            frame[pos] = x;
            return (pos + 1) % m;
        }
        bit[pos] = 0;
        pos = (pos + 1) % m;
	}
}
void add(int frame[], int m, int n, int page[],int bit[])
{
	int pos=0;
	char a[100];
    for(int i=0;i<n;i++)
    {
    	a[i]=to_char(page[i]);
    	char p[10];
    	p[0] = a[i];
    	setcolor(GREEN);
    	settextstyle(8,0,3);
    	outtextxy(45+i*80,70,p);
        printf(" %2d | ",page[i]);
        if(!present(frame,m,page[i],bit))
        {
        	setcolor(YELLOW);
           	circle(52+i*80,132+pos*43,19);
           	pos = findpos(frame,m,page[i],pos,bit);
           	print(frame,m);
           	printf(" *\n");
           	faults ++;
           	setcolor(GREEN);
           	settextstyle(8,0,3);
           	outtextxy(45+i*80,130+43*m,"*");
           	draw(110,30+i*80,frame,m);
           	continue;
        }
        print(frame,m);
		printf("\n");
		draw(110,30+i*80,frame,m);
    }
}

int main()
{
    int np,nf,i;
	printf("*\n\tSecond Chance page replacement algorithm\n*\n");
    printf("\nEnter number of frames: ");
    scanf("%d",&nf);
    int frame[nf], bit[nf];
    for(i=0;i<nf;i++)
    {
        frame[i]=-1;
        bit[i] = 0;
    }
	int choice;
	printf("\n*\n\tEnter '1' :Create an array: 0, 4, 1, 4, 2, 4, 3, 4, 2, 4, 0, 4, 1, 4, 2, 4, 3, 4\n");
	printf(" \n\tEnter '2' :Custom\n");
	printf(" \n\tEnter '3' :Input from file\n*\n");
	printf("\nchoose: ");
	scanf("%d",&choice);
	switch (choice)
	{
		case 1:
        {
        	int np = 18;
            int page[np]={0, 4, 1, 4, 2, 4, 3, 4, 2, 4, 0, 4, 1, 4, 2, 4, 3, 4};
            printf("Number of pages: 12\n");
            printf("\nposition of frame table after each request\n\n");
            initwindow(1400, 700);
    		setbkcolor(BLACK);
    		cleardevice();
            add(frame,nf,np,page,bit);
            break;
        }
        case 2:
        {
        	printf("Enter number of pages: ");
    		scanf("%d",&np);
            int page[np];
    		printf("\nEnter page value:\n");
    		for(i=0;i<np;i++)
    		{
    			printf("page[%d] = ",i);
        		scanf("%d",&page[i]);
    		}
    		printf("\nposition of frame table after each request\n\n");
    		initwindow(1400, 700);
    		setbkcolor(BLACK);
    		cleardevice();
    		add(frame,nf,np,page,bit);
    		
            break;
        }
        case 3:
        {
        	ifstream FileIn;
        	char name[30];
        	printf("\nEnter the path of file (Ex: 'D:\\Input.txt'): ");
        	 scanf("%s", name);
        	FileIn.open(name,ios_base::in);
        	if(FileIn.fail()==true)
        	{
        		printf("\nFile not exist!\n");
        		system("pause");
        		return 0;
        	}
            int page[100];
    		int np;
    		FileIn >> np;
    		for(i=0;i<np;i++)
    		{
    			FileIn >> page[i];
    		}
    		printf("\nposition of frame table after each request\n\n");
    		add(frame,nf,np,page,bit);
    		initwindow(1400, 700);
    		setbkcolor(BLACK);
    		cleardevice();
            break;
        }
	}
    
    printf("\nNumber of page faults : %d\n\n", faults);
    
    
    while(!kbhit()) delay(1);        // pause screen
    return 0;
}
