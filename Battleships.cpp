#include<iostream>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<ctype.h>
#include<dos.h>
#include<time.h>
#include<windows.h>
#include<mmsystem.h>
using namespace std;
void delay(clock_t a)              //FUNCTION FOR TIME DELAY
{
    clock_t start;
    start  = clock();
    while(clock()-start<a)
    {

    }
}
char waterdrop[100]="D:\\Academics\\Sem2\\DSA\\Practice\\Sounds\\Water Drop - Sound Effects.wav";
char criticalhit[100]="D:\\Academics\\Sem2\\DSA\\Practice\\Sounds\\Critical Hit. (Sound Effect).wav";
char foghorn[100]="D:\\Academics\\Sem2\\DSA\\Practice\\Sounds\\INCEPTION FOG HORN.wav";
char mouse[100]="D:\\Academics\\Sem2\\DSA\\Practice\\Sounds\\Mouse click - Sound effect.wav";
char reload[100]="D:\\Academics\\Sem2\\DSA\\Practice\\Sounds\\Gun Reload sound effect.wav";
char gunshot[100]="D:\\Academics\\Sem2\\DSA\\Practice\\Sounds\\hand gun Sound effect #2.wav";
char explosion[100]="D:\\Academics\\Sem2\\DSA\\Practice\\Sounds\\C4 Explosion #3 Sound Effect.wav";
//STRINGS TO DISPLAY ON TITLE SCREEN
char st[20]="BATTLESHIPS", st1[30]="MADE BY VARUN VARATHARAJAN";
//10X10 MATRIX TO STORE P1s SHIPS AS "X", TO STORE P2s HITS, TO STORE P1s SHIPS w NAMES
char field[10][10],field2[10][10],fieldX[10][10],c='A';
//COUNT 1= AIRCRAFT, 2=BATTLESHIP,  PLAYER: TO CHECK WHICH PLAYER IS PLAYING, OPTION: TOGGGLE MENU OPTIONS
int i,j,count,player=1,option;
// VAR FOR STORING ORIENTATION CHOICE AND ARRAY FOR COORDINATES
char o, pos1[2];
int pos[2],x,y, flag=0,flag2=0,hits,shots,A,B,D,S,P;
float accuracy;
struct player_details
{
    char _name[20];
    int _shots;
    float _accuracy;
}p1,p2;
void create_field(char f[10][10])
{

    for (i=0; i<10; i++)
    {
        for(j=0; j<10; j++)
        {
                f[i][j]='\0';
        }
    }
}

void disp_field(char f[10][10])
{
      c='A';
      for (i=0; i<11; i++)
        {
            for (j=0; j<11; j++)
            {
                if(i==0)
                {
                    if(j==0)
                        cout<<"     | ";
                    else
                        cout<<c++<<" | ";
                }
                else if(j==0)
                {
                    if(i!=0)
                        cout<<"   "<<i-1<<" | ";
                }
                else
                {
                    cout<<f[i-1][j-1]<<" | ";
                }
            }

            if(player==2 && i==2)
                cout<<"               LEGEND";
            else if(player==2 && i==4)
                cout<<"               * - MISS";
            else if(player==2 && i==5)
                cout<<"               # - HIT";
            else if(player==2 && i==7)
                cout<<"               MISSILES FIRED: "<<shots;
            else if(player==2 && i==8 && shots!=0)
            {
                accuracy=(hits*100)/shots;
                cout<<"               ACCURACY: "<<accuracy<<"%";
            }

            cout<<endl;
        }
}

void set_ships()
{
    flag=0;count=1;
    int mark_ships();

    while(count<=5)
    {
        disp_field(field);
        do
        {
            if(count==1)
                cout<<"\n Placing Aircraft Carrier (5 Units)-";
            else if(count==2)
                cout<<"\n Placing Battleship (4 Units)-";
            else if(count==3)
                cout<<"\n Placing Destroyer (3 Units)-";
            else if(count==4)
                cout<<"\n Placing Submarine (3 Units)-";
            else if(count==5)
                cout<<"\n Placing Patrol Boat (2 Units)-";
            cout<<"\n Orientation (Horizontal-H; Vertical-V): ";
            cin>>o;
            PlaySound(TEXT(mouse),NULL,SND_SYNC);
            o=toupper(o);
            if(o=='H'|| o=='V')
                break;
        }while(1);
        again:
        do
        {
            flag=0;
            cout<<"\n Enter coordinates with space: (Eg: A 6)";
            cin>>pos1[0]>>pos1[1];
            PlaySound(TEXT(reload),NULL,SND_SYNC);
            pos1[0]=toupper(pos1[0]);
            pos[0]=int(pos1[0]-65);
            pos[1]=int(pos1[1]-48);
            y=pos[0];
            x=pos[1];
            if(count==1)
            {
                if(o=='H')
                    if(x>=0&&y>=0&&y<=5&&x<10)
                        flag=1;
                if(o=='V')
                    if(x>=0&&y>=0&&x<=5&&y<10)
                       flag=1;
            }
            if(count==2)
            {
                if(o=='H')
                    if(x>=0&&y>=0&&y<=6&&x<10)
                        flag=1;
                if(o=='V')
                    if(x>=0&&y>=0&&x<=6&&y<10)
                       flag=1;
            }
            if(count==3 || count==4)
            {
                if(o=='H')
                    if(x>=0&&y>=0&&y<=7&&x<10)
                        flag=1;
                if(o=='V')
                    if(x>=0&&y>=0&&x<=7&&y<10)
                       flag=1;
            }
            if(count==5)
            {
                if(o=='H')
                    if(x>=0&&y>=0&&y<=8&&x<10)
                        flag=1;
                if(o=='V')
                    if(x>=0&&y>=0&&x<=8&&y<10)
                       flag=1;
            }
        }while(!flag);
        flag=mark_ships();
        if(flag==0)
        {
            cout<<"\n Ship already exists";
            goto again;
        }
        //getch();
        system("CLS");
        count++;
    }
    disp_field(field);
    cout<<"\n Press any key to proceed";
    _getch();

}

int mark_ships()
{
    int a;
    if(count==1)
    {
        if(o=='H')
        {
            for(a=y;a<y+5; a++)
                if (field[x][a]!='\0')
                    return 0;
            for(a=y;a<y+5; a++)
            {
                field[x][a]='X';
                fieldX[x][a]='A';
            }
        }

        else if(o=='V')
        {
            for(a=x; a<x+5; a++)
                if(field[a][y]!='\0')         //CHECKING IF SHIP IS PLACED PREVIOUSLY
                    return 0;
            for(a=x; a<x+5; a++)
            {
                field[a][y]='X';
                fieldX[a][y]='A';
            }
        }

    }
    if(count==2)
    {
        if(o=='H')
        {
            for(a=y;a<y+4; a++)
                if (field[x][a]!='\0')
                    return 0;
            for(a=y;a<y+4; a++)
            {
                field[x][a]='X';
                fieldX[x][a]='B';
            }
        }

        else if(o=='V')
        {
            for(a=x; a<x+4; a++)
                if(field[a][y]!='\0')         //CHECKING IF SHIP IS PLACED PREVIOUSLY
                    return 0;
            for(a=x; a<x+4; a++)
            {
                field[a][y]='X';
                fieldX[a][y]='B';
            }
        }

    }
    if(count==3 || count==4)
    {
        if(o=='H')
        {
            for(a=y;a<y+3; a++)
                if (field[x][a]!='\0')
                    return 0;
            for(a=y;a<y+3; a++)
            {
                field[x][a]='X';
                if(count==3)
                    fieldX[x][a]='D';
                if(count==4)
                    fieldX[x][a]='S';
            }
        }

        else if(o=='V')
        {
            for(a=x; a<x+3; a++)
                if(field[a][y]!='\0')         //CHECKING IF SHIP IS PLACED PREVIOUSLY
                    return 0;
            for(a=x; a<x+3; a++)
            {
                field[a][y]='X';
                if(count==3)
                    fieldX[a][y]='D';
                if(count==4)
                    fieldX[a][y]='S';

            }
        }

    }
    if(count==5)
    {
        if(o=='H')
        {
            for(a=y;a<y+2; a++)
                if (field[x][a]!='\0')
                    return 0;
            for(a=y;a<y+2; a++)
            {
                field[x][a]='X';
                fieldX[x][a]='P';
            }
        }

        else if(o=='V')
        {
            for(a=x; a<x+2; a++)
                if(field[a][y]!='\0')         //CHECKING IF SHIP IS PLACED PREVIOUSLY
                    return 0;
            for(a=x; a<x+2; a++)
            {
                field[a][y]='X';
                fieldX[a][y]='P';
            }
        }

    }
    return 1;
}

void chk_impact()
{
    if(field2[x][y]=='#')
    {
        flag=0;
        shots--;
        disp_field(field2);
        cout<<"\n Already fired here";
    }
    else if(field[x][y]=='\0')
    {
        field2[x][y]='*';
        disp_field(field2);
        cout<<"\n MISS!";
        PlaySound(TEXT(waterdrop),NULL,SND_SYNC);
    }
    else if(fieldX[x][y]=='A')
    {
        field2[x][y]='#';
        hits++;A++;
        disp_field(field2);
        cout<<"\n Aircraft Carrier(5 units) hit!!";
        if(A==5)
        {
            cout<<"\n Aircraft Carrier sunk!!!";
            PlaySound(TEXT(explosion),NULL,SND_SYNC);
        }
        else
            PlaySound(TEXT(gunshot),NULL,SND_SYNC);
    }
     else if(fieldX[x][y]=='B')
    {
        field2[x][y]='#';
        hits++;B++;
        disp_field(field2);
        cout<<"\n Battleship(4 units) hit!!";
        if(B==4)
        {
            cout<<"\n Battleship sunk!!!";
            PlaySound(TEXT(explosion),NULL,SND_SYNC);
        }
        else
            PlaySound(TEXT(gunshot),NULL,SND_SYNC);
    }
     else if(fieldX[x][y]=='D')
    {
        field2[x][y]='#';
        hits++;D++;
        disp_field(field2);
        cout<<"\n Destroyer(3 units) hit!!";
        if(D==3)
        {
            cout<<"\n Destroyer sunk!!!";
            PlaySound(TEXT(explosion),NULL,SND_SYNC);
        }
        else
            PlaySound(TEXT(gunshot),NULL,SND_SYNC);
    }
     else if(fieldX[x][y]=='S')
    {
        field2[x][y]='#';
        hits++;S++;
        disp_field(field2);
        cout<<"\n Submarine(3 units) hit!!";
        if(S==3)
        {
            cout<<"\n Submarine sunk!!!";
            PlaySound(TEXT(explosion),NULL,SND_SYNC);
        }
        else
            PlaySound(TEXT(gunshot),NULL,SND_SYNC);
    }
     else if(fieldX[x][y]=='P')
    {
        field2[x][y]='#';
        hits++;P++;
        disp_field(field2);
        cout<<"\n Patrol Boat(2 units) hit!!";
        if(P==2)
         {
            cout<<"\n Patrol Boat sunk!!!";
            PlaySound(TEXT(explosion),NULL,SND_SYNC);
         }
         else
            PlaySound(TEXT(gunshot),NULL,SND_SYNC);
    }
}

void shoot()
{
    flag2=0;hits=0;shots=0;flag=0;A=0;B=0;D=0;S=0;P=0;
    disp_field(field2);
    while(flag2==0)
    {
        again2:
        do
        {
            flag=0;
            cout<<"\n Firing coordinates (Eg: A 6):";
            cin>>pos1[0]>>pos1[1];
            pos1[0]=toupper(pos1[0]);
            pos[0]=int(pos1[0]-65);
            pos[1]=int(pos1[1]-48);
            y=pos[0];
            x=pos[1];
            if(x>=0 && x<10 && y>=0 && y<10)
                flag=1;
        }while(!flag);
        shots++;
        system("CLS");
        chk_impact();
        if(flag==0)
            goto again2;
        if(hits==17)
            flag2=1;
    }
    cout<<"\n Press any key to proceed";
    _getch();

}
void control()
{
    void menu();
    if(option==1)
    {
        void get_player();
        get_player();
        cout<<"\n"<<p1._name<<", set your ships";
        _getch();
        PlaySound(TEXT(mouse),NULL,SND_SYNC);
        system("cls");
        create_field(field);
        create_field(fieldX);
        set_ships();
        system("CLS");
        player=2;
        cout<<"\n"<<p2._name<<", your chance to shoot";
        _getch();
        PlaySound(TEXT(mouse),NULL,SND_SYNC);
        system("cls");
        create_field(field2);
        cout<<endl;
        shoot();
        p1._shots=shots;
        p1._accuracy=accuracy;
        system("cls");
        player=1;
        cout<<"\n"<<p2._name<<", set your ships";
        _getch();
        PlaySound(TEXT(mouse),NULL,SND_SYNC);
        system("cls");
        create_field(field);
        create_field(fieldX);
        set_ships();
        system("CLS");
        player=2;
        cout<<"\n"<<p1._name<<", your chance to shoot";
        _getch();
        PlaySound(TEXT(mouse),NULL,SND_SYNC);
        system("cls");
        create_field(field2);
        cout<<endl;
        shoot();
        p2._shots=shots;
        p2._accuracy=accuracy;
        void result();
        result();
        menu();
    }
    else if(option==2)
    {
        cout<<"\n INSTRUCTIONS";
        cout<<"\n\n\n\n\n\n\n\n\n\n PRESS ANY KEY TO GO BACK";
        _getch();
        menu();
    }
    else if(option==3)
    {
        exit(0);
    }
}
void menu()
{
    char chh;
    option=1;
    do
    {
        system("CLS");
        if(option==1)
        {
            cout<<"\n       MENU";
            cout<<"\n >>PLAY GAME";
            cout<<"\n INSTRUCTIONS";
            cout<<"\n EXIT";
        }
        else if(option==2)
        {
            cout<<"\n       MENU";
            cout<<"\n PLAY GAME";
            cout<<"\n >>INSTRUCTIONS";
            cout<<"\n EXIT";
        }
        else if(option==3)
        {
            cout<<"\n       MENU";
            cout<<"\n PLAY GAME";
            cout<<"\n INSTRUCTIONS";
            cout<<"\n >>EXIT";
        }
        cout<<"\n\n\n\n\n\n\n\n\n\n\n\n USE ARROW KEYS TO SCROLL AND ENTER TO SELECT";
        chh=_getch();
        if(chh==72)           //UP ARROW KEY
        {
            option--;
            PlaySound(TEXT(mouse),NULL,SND_SYNC);
        }
        else if(chh==80)      //DOWN ARROW KEY
        {
            option++;
            PlaySound(TEXT(mouse),NULL,SND_SYNC);
        }
        if(option==0)
            option=3;
        else if(option==4)
            option=1;
    }while(chh!=13);
    PlaySound(TEXT(reload),NULL,SND_SYNC);
    system("CLS");
    control();

}
void title()
{
    //delay(1000);
    PlaySound(TEXT(foghorn),NULL,SND_SYNC);
    for(i=0;i<10;i++)
    {
        cout<<"\n";
    }
    for(i=0;i<30;i++)
    {
        cout<<" ";
    }
    for(i=0;st[i]!='\0';i++)
    {
        cout<<st[i];
        delay(100);
    }
    cout<<endl;
    for(i=0;i<30;i++)
    {
        cout<<" ";
    }
    for(i=0;st1[i]!='\0';i++)
    {
        cout<<st1[i];
        delay(100);
    }
    delay(1500);
    system("cls");
}

void result()
{
    system("cls");
    cout<<"\n RESULT\n";
    if(p1._accuracy>p2._accuracy)
        cout<<"\n WINNER:"<<p1._name;
    else if(p1._accuracy<p2._accuracy)
        cout<<"\n WINNER:"<<p2._name;
    else
        cout<<"\n MATCH DRAWN";
    cout<<"\n STATS-";
    cout<<"\n\n "<<p1._name<<"-";
    cout<<"\n SHOTS: "<<p1._shots;
    cout<<"\n ACCURACY: "<<p1._accuracy<<"%";
    cout<<"\n\n "<<p2._name<<"-";
    cout<<"\n SHOTS: "<<p2._shots;
    cout<<"\n ACCURACY: "<<p2._accuracy<<"%";
    cout<<"\n\n Press any key to return to the menu";
    _getch();
}

void get_player()
{
    cout<<"\n Enter player 1 name: ";
    cin>>p1._name;
    PlaySound(TEXT(mouse),NULL,SND_SYNC);
    cout<<"\n Enter player 2 name: ";
    cin>>p2._name;
    PlaySound(TEXT(mouse),NULL,SND_SYNC);
    //delay(500);
    system("cls");
}
int main()
{
    title();
    menu();
    return 0;
}
