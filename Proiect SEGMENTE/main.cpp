#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <cstdlib> //rand() function is used in C++ to generate random numbers in the range [0, RAND_MAX)
#include <time.h>   //time()
using namespace std;

struct punct
{
    int x, y;
};

struct dreptunghi
{
    punct SS, DJ;
};

struct buton
{
    dreptunghi D;
    int culoare;
    char text[20];
}B[7];
int nrButoane=4;

void makeMenu()
{
    initwindow(800,800,"JOC SEGMENTE");
    readimagefile("BG.jpg",0,0,getmaxx(),getmaxy());
    readimagefile("SEGMENTE.jpg",100,100,600,500);
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL,BLUE);

    for (int index=1; index<=nrButoane; index++)
    {
        B[index].D.SS.x=100*index+50;
        B[index].D.SS.y=550;
        B[index].D.DJ.x=100*(index+1)+40;
        B[index].D.DJ.y=580;

        switch(index)
        {
        case 1:
            strcpy(B[index].text,"PLAY");
            break;
        case 2:
            strcpy(B[index].text,"ABOUT");
            break;
        case 3:
            strcpy(B[index].text,"SETARI");
            break;
        case 4:
            strcpy(B[index].text,"EXIT");
            break;
        }
        rectangle(B[index].D.SS.x, B[index].D.SS.y, B[index].D.DJ.x, B[index].D.DJ.y);
        bar(B[index].D.SS.x, B[index].D.SS.y+30, B[index].D.DJ.x, B[index].D.SS.y); //cat umple cu culoare
        setbkcolor(BLUE);   //seteaza backgroundul fontului din dreptunghi
        outtextxy(B[index].D.SS.x+25,B[index].D.SS.y+10,B[index].text); //+25 si +10 pentru centrare
    }
}

int butonAles()
{
    int x, y;
    while (!ismouseclick(WM_LBUTTONDOWN));
    getmouseclick(WM_LBUTTONDOWN, x, y);

    for (int index=1; index<=nrButoane; index++)
    {
        if (x>=B[index].D.SS.x && x<=B[index].D.DJ.x && y>=B[index].D.SS.y && y<=B[index].D.DJ.y)
        {
            return index;
        }
    }
    return 0;
}

void drawButtons(int contor)
{
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL,BLUE);

    B[5].D.SS.x=getmaxx()-200, B[5].D.SS.y=30;
    B[5].D.DJ.x=getmaxx()-100, B[5].D.DJ.y=60;

    rectangle(B[5].D.SS.x, B[5].D.SS.y, B[5].D.DJ.x, B[5].D.DJ.y);
    bar(B[5].D.SS.x, B[5].D.SS.y+30, B[5].D.DJ.x, B[5].D.SS.y);
    setbkcolor(BLUE);
    if(contor == 0)
    {
        outtextxy(B[5].D.SS.x+30,B[5].D.SS.y+10," BACK");
    }
    else
    {
        outtextxy(B[5].D.SS.x+30,B[5].D.SS.y+10,"RESET");
    }
}

int apasatButon(int contor)
{
    while(!ismouseclick(WM_LBUTTONDOWN));

    int x, y, ok=0;
    getmouseclick(WM_LBUTTONDOWN, x, y);

    if(x>=B[contor].D.SS.x && x<=B[contor].D.DJ.x && y>=B[contor].D.SS.y && y<=B[contor].D.DJ.y)
    {
        clearmouseclick(WM_LBUTTONDOWN);
        ok=1;
        if(contor==5) cout<<"Comanda Inapoi"<<endl;
        else cout<<"comanda schimba limba"<<endl;
    }
    return ok;
}

int Dots;
punct vect_pct[1000];

void generarePuncte()
{
    int x, y, c, i, maxi=1, Dots2, ind=1;

    srand(time(0));

    Dots = rand() % (18-14) + 14;
    Dots2=Dots-2;

    x = rand() % 50;
    while(x<30)
        x = rand() % 50;

    y = rand() % (100-75) + 75;
    while(y<90)
        y = rand() % (100-75) + 80;

    vect_pct[ind].x = x;
    vect_pct[ind].y = y;
    ind++;

    setfillstyle(SOLID_FILL,MAGENTA);
    circle(x,y,5);
    floodfill(x,y,WHITE);

    while(Dots2>=0)
    {
        for(i=1; i<=Dots-Dots2; i++)
        {
            x = rand() % (1100-50) + 50;
            y = rand() % (650-100) + 100;

            while(((vect_pct[i].x < x && vect_pct[i].x > x-50) || (vect_pct[i].x > x && vect_pct[i].x < x+50)) || ((vect_pct[i].y < y && vect_pct[i].y > y-50) || (vect_pct[i].y > y && vect_pct[i].y < y+50)))
            {
                while((vect_pct[i].x < x && vect_pct[i].x > x-50) || (vect_pct[i].x > x && vect_pct[i].x-x < 50) || x<25)
                    x = rand() % (1100-100) + 100;
                while((vect_pct[i].y < y && vect_pct[i].y > y-50) || (vect_pct[i].y > y && vect_pct[i].y < y+50) || y<25)
                    y = rand() % (500-100) + 100;
            }
        }

        c=rand()%3;
        if(c==1)
        {
            setfillstyle(SOLID_FILL,MAGENTA);
            circle(x,y,5);
            floodfill(x,y,WHITE);

            vect_pct[ind].x = x;
            vect_pct[ind].y = y;
            ind++;

            maxi++;
            Dots2--;
        }
        if(Dots2!=0 && maxi>=50) break;
    }
}

void mesajEroare(int val)
{
    if(val==1) outtextxy(450, 650, "Punct indisponibil.");
    else if(val==2) outtextxy(450,650, "Punct Blocat.");
    else outtextxy(450, 650, "Segment imposibil.");
    delay(1000);
    setfillstyle(SOLID_FILL,BLACK);
    bar(400,650,800,675);
}

void colorCode(int x, int y, int color)
{
    if(color == 1)
    {
        setfillstyle(SOLID_FILL, YELLOW);
        floodfill(x,y,WHITE);
    }
    else
    {
        if(color == 2)
        {
            setfillstyle(SOLID_FILL, CYAN);
            floodfill(x,y,WHITE);
        }
    }
}

void desenareSegment(punct p, punct q, int &color)
{
    if (color == 1)
    {
        setcolor(YELLOW);
        color=2;
    }
    else
    {
        setcolor(CYAN);
        color=1;
    }
    setlinestyle(SOLID_LINE, 4, THICK_WIDTH);
    line(p.x, p.y, q.x, q.y);
}

void ind_cerc(int x, int y, int &ind)//returneaza numarul punctului in care ne aflam
{
    for(ind=1; ind<=Dots; ind++)
    {
        if ((x-vect_pct[ind].x)*(x-vect_pct[ind].x) + (y-vect_pct[ind].y)*(y-vect_pct[ind].y) <= 25)
        {
            break;
        }
    }
}

char str[1000];
void selectarePuncte(int k, int &ind_pct1, int &ind_pct2, int color)
{
    while(!ismouseclick(WM_LBUTTONDOWN));
    int x, y, ind=0;
    getmouseclick(WM_LBUTTONDOWN,x,y);

    if(getpixel(x,y) == YELLOW || getpixel(x,y) == CYAN) mesajEroare(1);
    if(getpixel(x,y) == GREEN) mesajEroare(2);

    if(getpixel(x,y) != MAGENTA) selectarePuncte(k, ind_pct1, ind_pct2, color);
    else
    {
        setbkcolor(BLACK);
        if(color == 1) setcolor(YELLOW);
        else setcolor(CYAN);
        sprintf(str,"Player %d", color);
        outtextxy(220,25,str);

        k++;
        if(k==1)
        {
            colorCode(x,y,color);
            ind_cerc(x,y,ind);
            ind_pct1 = ind;

            selectarePuncte(k, ind_pct1, ind_pct2, color);
        }
        if(k==2)
        {
            colorCode(x,y,color);
            ind_cerc(x,y,ind);
            ind_pct2 = ind;
        }
    }
}

int verifColiziune(int a, int b, int c, int x, int y, int ind)
{
    ///ec dreptei: ax + by + c = 0
    int dist=(abs(a * x + b * y + c)) / sqrt(a * a + b * b); //distanta de la centrul punctului la segmentul trasat
    if(5 == dist) return 1;
    else if(5 > dist) return 1;
    else return 0;
}

int ok(punct p, punct q)
{
    for(int ind=1; ind<=Dots; ind++)
    {
        if (vect_pct[ind].x < max(p.x, q.x) && vect_pct[ind].x > min(p.x, q.x) && vect_pct[ind].y < max(p.y, q.y) && vect_pct[ind].y > min(p.y, q.y))
        {
            if(verifColiziune(p.y-q.y, q.x-p.x, p.x*(q.y-p.y)-p.y*(q.x-p.x), vect_pct[ind].x, vect_pct[ind].y, ind))
            {
                if((vect_pct[ind].x != p.x && vect_pct[ind].x !=q.x) && (vect_pct[ind].y != p.y && vect_pct[ind].y !=q.y))
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}

int orientation(punct p, punct q, punct r)
{
    int val=(q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if(val == 0) return 0; // coliniare
    if(val > 0) return 1;
    else return 2; // clock or counterclock wise
}

bool doIntersect(punct p1, punct q1, punct p2, punct q2)//extremitatile segmentelor verificate
{
    int o1=orientation(p1, q1, p2);
    int o2=orientation(p1, q1, q2);
    int o3=orientation(p2, q2, p1);
    int o4=orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4) return true;
    return false;
}

struct segment
{
    punct a, b;
};

segment vect_segm[1000];
int index_segm=1;

int segm_valid(int ind_pct1, int ind_pct2)
{
    if(ok(vect_pct[ind_pct1], vect_pct[ind_pct2]))
    {
        for(int i=1; i<index_segm; i++)
        {
            if(doIntersect(vect_segm[i].a, vect_segm[i].b, vect_pct[ind_pct1], vect_pct[ind_pct2]))
            {
                return 0;
            }
        }
        vect_segm[index_segm].a = vect_pct[ind_pct1];//capul 1 al segm
        vect_segm[index_segm].b = vect_pct[ind_pct2];//capatul 2 al segm
        return 1;
    }
    else
    {
        return 0;
    }
}

struct block
{
    punct a;
};

block vect_blk[1000];
int index_blk=0;

bool apartineSegment(punct p)
{
    for(int ind=1; ind<=index_segm; ind++)
        if((vect_segm[ind].a.x==p.x && vect_segm[ind].a.y==p.y) || (vect_segm[ind].b.x==p.x && vect_segm[ind].b.y==p.y))
            return true;
    return false;
}

bool apartinePBlk(punct p)
{
    for(int ind=0; ind<index_blk; ind++)
        if(p.x == vect_blk[ind].a.x && p.y == vect_blk[ind].a.y) return true;
    return false;
}

int verifBlocat(int p1)
{
    int cnt=0;
    for(int p2=1; p2<=Dots; p2++)
    {
        if(vect_pct[p1].x == vect_pct[p2].x && vect_pct[p1].y == vect_pct[p2].y)
        {
            continue;
        }
        else
        {
            if(!apartineSegment(vect_pct[p2]))
            {
                for(int ind=1; ind<=index_segm; ind++)
                {
                    if(doIntersect(vect_segm[ind].a, vect_segm[ind].b, vect_pct[p1], vect_pct[p2]))
                    {
                        cnt++;
                        ind=index_segm; //iesim fortat din forul de segmente pt ca am gasit un segment care strica punctul p2
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        }
    }
    if(cnt==Dots-(index_segm*2)-1) return 1;
    return 0;
}

int SwitchLanguage(int Limba)
{
    if(Limba==6)Limba=7;
    else Limba=6;
    return Limba;
}

void languageButton(int Limba)
{
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL,BLUE);

    B[6].D.SS.x=125, B[6].D.SS.y=480;
    B[6].D.DJ.x=430, B[6].D.DJ.y=500;

    rectangle(B[6].D.SS.x, B[6].D.SS.y, B[6].D.DJ.x, B[6].D.DJ.y);
    bar(B[6].D.SS.x, B[6].D.SS.y+40, B[6].D.DJ.x, B[6].D.SS.y);
    setbkcolor(BLUE);
    if(Limba == 6) outtextxy(B[6].D.SS.x+30,B[6].D.SS.y+10,"Schimbati Limba");
    else outtextxy(B[6].D.SS.x+30,B[6].D.SS.y+10,"Change Language");
}

void openWindow()
{
    int butonApasat, total, used=0, ind_pct1=0, ind_pct2=0, cnt=0, color=1;

    do
    {
        butonApasat=butonAles();
        if (butonApasat)
        {
            cout<<"Comanda "<<butonApasat<<endl;
            switch(butonApasat)
            {
            case 1:
            {
                closegraph();
                initwindow(1200, 700, "SEGMENTE");
                readimagefile("BG.jpg",0,0,1200,75);
                generarePuncte();
                total = Dots;
                drawButtons(1);
                do
                {
                    settextstyle(TRIPLEX_FONT,0,3);
                    setcolor(WHITE);
                    setfillstyle(SOLID_FILL,BLACK);
                    bar(390,20, 810, 55);
                    setbkcolor(BLACK);
                    sprintf(str,"T=%d && U=%d && B=%d", total, used, index_blk);
                    outtextxy(400,25,str);

                    if(apasatButon(5)==0)
                    {
                        selectarePuncte(cnt, ind_pct1, ind_pct2, color);
                        if(segm_valid(ind_pct1, ind_pct2))
                        {
                            cnt=0;
                            total-=2;
                            used+=2;
                            desenareSegment(vect_pct[ind_pct1], vect_pct[ind_pct2], color);
                            for(int p1=1; p1<=Dots; p1++)
                            {
                                if(apartinePBlk(vect_pct[p1])==0 && apartineSegment(vect_pct[p1])==0)
                                {
                                    if(verifBlocat(p1)==1)
                                    {
                                        vect_blk[index_blk].a.x = vect_pct[p1].x;
                                        vect_blk[index_blk].a.y = vect_pct[p1].y;
                                        index_blk++;
                                        total--;

                                        setfillstyle(SOLID_FILL, GREEN);
                                        floodfill(vect_pct[p1].x, vect_pct[p1].y,WHITE);
                                    }
                                }
                            }
                            setfillstyle(SOLID_FILL,BLACK);
                            setcolor(WHITE);
                            bar(390,20, 810, 55);
                            sprintf(str,"T=%d && U=%d && B=%d", total, used, index_blk);
                            outtextxy(400,25,str);
                            index_segm++;
                        }
                        else
                        {
                            setfillstyle(SOLID_FILL, MAGENTA);
                            floodfill(vect_pct[ind_pct2].x, vect_pct[ind_pct2].y,WHITE);
                            mesajEroare(0);
                            cnt=1;
                        }
                    }
                    else
                    {
                        vect_pct[1000] = {0};
                        block vect_blk[100] = {0};
                        index_blk=0;
                        segment vect_segm[100] = {0};
                        index_segm=1;

                        cleardevice();
                        closegraph();
                        makeMenu();
                        openWindow();
                    }
                }
                while(total>0);

                punct vect_pct[1000] = {0};
                block vect_blk[100] = {0};
                index_blk=0;
                segment vect_segm[100] = {0};
                index_segm=1;

                setfillstyle(SOLID_FILL,BLACK);
                bar(390,20, 810, 55);
                outtextxy(460,25,"IS THE WINNER!");

                while(!apasatButon(5));
                cleardevice();
                closegraph();
                makeMenu();
                openWindow();
            }
            break;
            case 2:
            {
                closegraph();
                initwindow(800, 800, "INFORMATII DESPRE JOC");
                readimagefile("BG2.jpg", 0, 0, getmaxx(), getmaxy());

                drawButtons(0);

                settextstyle(TRIPLEX_FONT,0,3);
                setbkcolor(BLACK);

                int center_x = 125, center_y= 150;
                outtextxy(center_x, center_y, " Segmente este un simplu joc de");
                outtextxy(center_x, center_y+30, "strategie, scopul lui este de a-l ");
                outtextxy(center_x, center_y+30*2, "lasa pe celalalt jucator fara");
                outtextxy(center_x, center_y+30*3, "posibilitatea de a trasa un segment. ");
                outtextxy(center_x, center_y+30*4, "");
                outtextxy(center_x, center_y+30*5, " Singura regula este ca segmentele");
                outtextxy(center_x, center_y+30*6, "nu se pot intersecta cu alte");
                outtextxy(center_x, center_y+30*7, "segmente.");
                outtextxy(center_x, center_y+30*8, "");
                outtextxy(center_x, center_y+30*9, "Totodata, orice punct de la care nu");
                outtextxy(center_x, center_y+30*10, " se poate trasa un segment ");
                outtextxy(center_x, center_y+30*11, "va fi un punct blocat.");

                while(!apasatButon(5));
                closegraph();
                makeMenu();
            }
            break;
            case 3:
            {
                closegraph();
                initwindow(800, 800, "SETARI");
                readimagefile("BG2.jpg", 0, 0, getmaxx(), getmaxy());

                int Limba=6;
                drawButtons(0);

                readimagefile("soundicon.jpg", 450,400,650,600);
                settextstyle(TRIPLEX_FONT,0,2);

                if(Limba==6)
                {
                    setfillstyle(SOLID_FILL, BLACK);
                    bar(190,200,430,230);
                    outtextxy(200, 200, "Limba: Romana");
                    languageButton(Limba);

                    int nr=apasatButon(5);
                    while(!apasatButon(5))
                    {
                        if(apasatButon(6)) SwitchLanguage(Limba);
                    }
                    closegraph();
                    makeMenu();
                    openWindow();
                }
                else if(Limba==7)
                {
                    setfillstyle(SOLID_FILL, BLACK);
                    bar(190,200,470,230);
                    outtextxy(200, 200, "Language: English");
                    languageButton(Limba);

                    while(!apasatButon(5))
                    {
                        if(apasatButon(6)) SwitchLanguage(Limba);
                    }
                    closegraph();
                    makeMenu();
                    openWindow();
                }
                while(!apasatButon(5));
                closegraph();
                makeMenu();
            }
            break;
            case 4:
                closegraph(ALL_WINDOWS);
                break;
            }
        }
    }
    while(butonApasat!=4);
}

int main()
{
    makeMenu();
    openWindow();
    closegraph();
    return 0;
}
