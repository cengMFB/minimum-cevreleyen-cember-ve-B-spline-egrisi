#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <graphics.h>

int main()
{

    int gd = DETECT, gm;//GRAFIK FONKSIYONU

    initwindow(1350,900);//pencere boyutu
    FILE *dosya;//dosya okuma
//------------------------------------DOSYADAKİ VERI SAYISINI OKUYAN BOLUM---------------------------
    int i=0, sayac=0;
    char karakter;
    dosya=fopen("deneme.txt","r");
    while(feof(dosya)==NULL)
    {
        karakter=getc(dosya);
        if(karakter=='\n')
        {
            sayac++;
        }

    }

    fclose(dosya);
    int noktasayisi=sayac+1;
//--------------------------------------------------------------------------------------------------------

    float koordinatsistemx[noktasayisi];//KOORDİNAT SISTEMININ X EKSENINI TANIMLAYAN DIZI
    float koordinatsistemy[noktasayisi];//KOORDİNAT SISTEMININ Y EKSENINI TANIMLAYAN DIZI



//----------------------------------------DOSYADAKI VERILERI OKUYUP TANIMLANAN DIZILERE ESİTLER-----------------------
    int a=0,b=0;
    dosya=fopen("deneme.txt","r");
    for(i=0; i<2*(noktasayisi); i++)
    {
        if(i%2==0)
        {
            fscanf(dosya,"%f",&koordinatsistemx[a]);
            a++;
        }
        if(i%2==1)
        {
            fscanf(dosya,"%f",&koordinatsistemy[b]);
            b++;
        }



        if(feof(dosya))
            break;
    }
//--------------------------------------------------------------------------------------------------------------------------



    for(int i=0; i<(noktasayisi); i++) //KOORDINATLARI YAZAR
        printf("%f %f\n",koordinatsistemx[i],koordinatsistemy[i]);



    double enb=0,yaricap;//YARICAPI VE NOKTALARI KIYASLAMAK ICIN VERILEN DEGISKEN

    double merkezx,merkezy;
//MERKEZ KOORDINATLARI BULMAK ICIN VERILEN DEGISKENLER
    double x1,x2,x3,y1,y2,y3;
//-----------------------------------------------NOKTALARI KAPSAYAN CEMBERIN MERKEZINI VE YARICAPINI BULAN DONGU-----------------------
    for(int i=0; i<(noktasayisi); i++)
    {
        for(int j=0; j<(noktasayisi); j++)
        {
            if(sqrt(pow(koordinatsistemx[i]-koordinatsistemx[j],2)+pow(koordinatsistemy[i]-koordinatsistemy[j],2))>enb)
            {
                x1=koordinatsistemx[i];
                x2=koordinatsistemx[j];
                y1=koordinatsistemy[i];
                y2=koordinatsistemy[j];
                enb=sqrt(pow(koordinatsistemx[i]-koordinatsistemx[j],2)+pow(koordinatsistemy[i]-koordinatsistemy[j],2));
                yaricap=enb/2;
                if(koordinatsistemx[i]>koordinatsistemx[j])
                    merkezx=koordinatsistemx[j]+(koordinatsistemx[i]-koordinatsistemx[j])/2;
                else
                    merkezx=koordinatsistemx[i]+fabs(koordinatsistemx[i]-koordinatsistemx[j])/2;

                if(koordinatsistemy[i]>koordinatsistemy[j])
                {
                    merkezy=koordinatsistemy[j]+(koordinatsistemy[i]-koordinatsistemy[j])/2;
                }
                else
                {
                    merkezy=koordinatsistemy[i]+fabs(koordinatsistemy[i]-koordinatsistemy[j])/2;
                }
            }
            setcolor(7);
            circle(getmaxx()/2+koordinatsistemx[i]*15,getmaxy()/2-koordinatsistemy[i]*15,4);
            char nokta[3];
            setcolor(2);
            settextstyle(2,HORIZ_DIR,4);
            int px=koordinatsistemx[i];
            int py=koordinatsistemy[i];
            sprintf(nokta,"(%d,",px);
            outtextxy(getmaxx()/2+koordinatsistemx[i]*15-15,getmaxy()/2-koordinatsistemy[i]*15+10,nokta);
            sprintf(nokta,"%d)",py);
            outtextxy(getmaxx()/2+koordinatsistemx[i]*15,getmaxy()/2-koordinatsistemy[i]*15+10,nokta);
        }

    }
//----------------------------------------------------------------------------------------------


    for(int i=0; i<noktasayisi; i++)
    {
        if(sqrt(pow(koordinatsistemx[i]-merkezx,2)+pow(koordinatsistemy[i]-merkezy,2))>yaricap)
        {

            x3=koordinatsistemx[i];
            y3=koordinatsistemy[i];
            double  x12 = x1 - x2;
            double x13 = x1 - x3;

            double  y12 = y1 - y2;
            double  y13 = y1 -y3;

            double  y31 = y3 - y1;
            double  y21 = y2 - y1;

            double  x31 = x3 - x1;
            double  x21 = x2 - x1;


            double karex13 = pow(x1, 2) - pow(x3, 2);


            double  karey13 = pow(y1, 2) - pow(y3, 2);

            double  karex21 = pow(x2, 2) - pow(x1, 2);

            double karey21 = pow(y2, 2) - pow(y1, 2);

            double  f =((karex13) * (x12)+ (karey13) * (x12)+ (karex21) * (x13)+ (karey21) * (x13))/ (2 * ((y31) * (x12) - (y21) * (x13)));

            double  g = ((karex13) * (y12)+ (karey13) * (y12)+ (karex21) * (y13)+ (karey21) * (y13))/ (2 * ((x31) * (y12) - (x21) * (y13)));

            double  c = -pow(x1, 2) - pow(y1, 2) - 2 * g * x1 - 2 * f * y1;


            double  h = -g;
            double  z = -f;
            double  carpim = h * h + z * z - c;

            double  yeniyrcp = sqrt(carpim);


            merkezx=h;
            merkezy=z;
            yaricap=yeniyrcp;
        }
    }

//--------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------KOORDINAT CIZGILERI----------------------------------------------

    setcolor(14);

    line(getmaxx()/2,getmaxy(),getmaxx()/2,0);
    line(0,getmaxy()/2,getmaxx(),getmaxy()/2);
//-----------------------------------------------------------------------------------------------------
    double t;
    double koordinatsistemxt,koordinatsistemyt;
    if(noktasayisi>=4)
    {
        for(i=0; i<noktasayisi; i++)
        {

            for(t = 0.0; t <1.0; t += 0.0005)
            {
                if(i+3>=noktasayisi)
                    break;
                koordinatsistemxt = (pow (1-t, 3) * koordinatsistemx[i] + (3 *pow (t, 3)-6*pow (t, 2)+4) * koordinatsistemx[i+1] +
                                     (-3 * pow (t, 3) +3*pow (t, 2)+3*t+1)* koordinatsistemx[i+2] + (pow (t, 3))* koordinatsistemx[i+3])/6;


                koordinatsistemyt = (pow (1-t, 3) * koordinatsistemy[i] + (3 *pow (t, 3)-6*pow (t, 2)+4) * koordinatsistemy[i+1] +
                                     (-3 * pow (t, 3) +3*pow (t, 2)+3*t+1)* koordinatsistemy[i+2] + (pow (t, 3))* koordinatsistemy[i+3])/6;

                putpixel(getmaxx()/2+koordinatsistemxt*15, getmaxy()/2-koordinatsistemyt*15, WHITE);

            }
        }
    }

    if(noktasayisi==3)
    {

        for(i=0; i<noktasayisi; i++)
        {
            for(t = -0.2; t <1.2; t += 0.0005)
            {
                if(i+2<noktasayisi)
                {
                    koordinatsistemxt = (pow (1-t, 3) * koordinatsistemx[i] + (3 *pow (t, 3)-6*pow (t, 2)+4) * koordinatsistemx[i+1] +
                                         (-3 * pow (t, 3) +3*pow (t, 2)+3*t+1)* koordinatsistemx[i+1] + (pow (t, 3))* koordinatsistemx[i+2])/6;


                    koordinatsistemyt = (pow (1-t, 3) * koordinatsistemy[i] + (3 *pow (t, 3)-6*pow (t, 2)+4) * koordinatsistemy[i+1] +
                                         (-3 * pow (t, 3) +3*pow (t, 2)+3*t+1)* koordinatsistemy[i+1] + (pow (t, 3))* koordinatsistemy[i+2])/6;

                    putpixel(getmaxx()/2+koordinatsistemxt*15, getmaxy()/2-koordinatsistemyt*15, WHITE);

                }
            }
        }
    }

    setcolor(15);

    if(noktasayisi==2)
    {
        line(getmaxx()/2+koordinatsistemx[0],getmaxy()/2-koordinatsistemy[0],getmaxx()/2+koordinatsistemx[1],getmaxy()/2-koordinatsistemy[1]);
    }


//----------------------------------------------CEMBERI VE CEMBERIN YARICAPINI EKRANA CIKARAN BOLUM----------------------------------
    setcolor(13);
    circle(getmaxx()/2+merkezx*15,getmaxy()/2-merkezy*15,6);//ÇEMBERIN MERKEZI
    printf("\nmerkez koordinatlari=%lf,%lf",merkezx,merkezy);
    printf("\nyaricapi:%lf",yaricap);
    setcolor(12);
    circle(getmaxx()/2+merkezx*15,getmaxy()/2-merkezy*15,yaricap*15);

//--------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------KOORDINAT SISTEMINE SAYILARI YAZAN KISIM------------------------------------------
    char koordinat[3];
    setcolor(9);
    settextstyle(2,HORIZ_DIR,4);
    for(int i=1; i<700; i++)
    {
        sprintf(koordinat,"%d",i*5);
        outtextxy(getmaxx()/2+i*75,getmaxy()/2+10,koordinat);

        sprintf(koordinat,"-%d",i*5);
        outtextxy(getmaxx()/2-i*75,getmaxy()/2+10,koordinat);

        sprintf(koordinat,"-%d",i*5);
        outtextxy(getmaxx()/2+10,getmaxy()/2+i*75,koordinat);

        sprintf(koordinat,"%d",i*5);
        outtextxy(getmaxx()/2+10,getmaxy()/2-i*75,koordinat);

    }
//-------------------------------------------------------------------------------------------------------------------------------------
    getch();
    closegraph();
}
