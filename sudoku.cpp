#include<iostream>
#include<algorithm>
#include<list>
#include<unistd.h>

using namespace std;

int init[]={1,2,3,4,5,6,7,8,9};

struct cell
{
    int val;
    int block;
    list<int> allowed;
}c[9][9];


struct Block
{
    int cnum[9][2];

}blk[9];

void show()
{
        cout<<endl;
        for(int i=0;i<9;i++)
        {
                for(int j=0;j<9;j++)
                {
                        if(c[i][j].val!=0)
                                cout<<c[i][j].val<<" ";
                        else
                                cout<<"_"<<" ";
                }
                cout<<endl;
        }
}

void initblocks()
{
    /*blk[0].cnum={0,0,
                0,1,
                0,2,
                1,0,
                1,1,
                1,2,
                2,0,
                2,1,
                2,2
                };
        */
    for(int k=0;k<9;k++)
    {
        blk[0].cnum[k][0]=k/3;
        blk[0].cnum[k][1]=k%3;
        c[k/3][k%3].block=0;
    }


    /*blk[1].cnum={0,3,
                0,4,
                0,5,
                1,3,
                1,4,
                1,5,
                2,3,
                2,4,
                2,5
                };
        */
    for(int k=0;k<9;k++)
    {
        blk[1].cnum[k][0]=k/3;
        blk[1].cnum[k][1]=(k%3)+3;
        c[k/3][(k%3)+3].block=1;
    }

    /*blk[2].cnum={0,6,
                0,7,
                0,8,
                1,6,
                1,7,
                1,8,
                2,6,
                2,7,
                2,8
                };
        */
     for(int k=0;k<9;k++)
    {
        blk[2].cnum[k][0]=k/3;
        blk[2].cnum[k][1]=(k%3)+6;
        c[k/3][(k%3)+6].block=2;
    }

    /*blk[3].cnum={3,0,
                3,1,
                3,2,
                4,0,
                4,1,
                4,2,
                5,0,
                5,1,
                5,2
                };
        */
    for(int k=0;k<9;k++)
    {
        blk[3].cnum[k][0]=(k/3)+3;
        blk[3].cnum[k][1]=(k%3);
        c[(k/3)+3][k%3].block=3;
    }


    /*blk[4].cnum={3,3,
                3,4,
                3,5,
                4,3,
                4,4,
                4,5,
                5,3,
                5,4,
                5,5
                };
        */

    for(int k=0;k<9;k++)
    {
        blk[4].cnum[k][0]=(k/3)+3;
        blk[4].cnum[k][1]=(k%3)+3;
        c[(k/3)+3][(k%3)+3].block=4;
    }

    /*blk[5].cnum={3,6,
                3,7,
                3,8,
                4,6,
                4,7,
                4,8,
                5,6,
                5,7,
                5,8
                };
        */

    for(int k=0;k<9;k++)
    {
        blk[5].cnum[k][0]=(k/3)+3;
        blk[5].cnum[k][1]=(k%3)+6;
        c[(k/3)+3][(k%3)+6].block=5;
    }

    /*blk[6].cnum={6,0,
                6,1,
                6,2,
                7,0,
                7,1,
                7,2,
                8,0,
                8,1,
                8,2
                };
        */

    for(int k=0;k<9;k++)
    {
        blk[6].cnum[k][0]=(k/3)+6;
        blk[6].cnum[k][1]=(k%3);
        c[(k/3)+6][k%3].block=6;
    }

    /*blk[7].cnum={6,3,
                6,4,
                6,5,
                7,3,
                7,4,
                7,5,
                8,3,
                8,4,
                8,5
                };
        */

    for(int k=0;k<9;k++)
    {
        blk[7].cnum[k][0]=(k/3)+6;
        blk[7].cnum[k][1]=(k%3)+3;
        c[(k/3)+6][(k%3)+3].block=7;
    }




    /*blk[8].cnum={6,6,
                6,7,
                6,8,
                7,6,
                7,7,
                7,8,
                8,6,
                8,7,
                8,8,
                };
        */

    for(int k=0;k<9;k++)
    {
        blk[8].cnum[k][0]=(k/3)+6;
        blk[8].cnum[k][1]=(k%3)+6;
        c[(k/3)+6][(k%3)+6].block=8;
    }
}

void show_allw()
{
        list<int>::iterator p;
        for(int i=0;i<9;i++)
        {
                for(int j=0;j<9;j++)
                {
                        p=c[i][j].allowed.begin();
                        cout<<endl<<"c["<<i<<"]["<<j<<"]: ";
                        while(p!=c[i][j].allowed.end())
                        {
                                cout<<*p<<" ";
                                p++;

                        }
                }
        }

        //usleep(4000000);
}

void showblk()
{
        for(int i=0;i<9;i++)
        {
                for(int j=0;j<9;j++)
                {
                        cout<<endl<<"c["<<i<<"]["<<j<<"]: ";
                        cout<<c[i][j].block<<endl;
                }
        }

        //usleep(5000000);
}

void update_row(int i,int j)
{
    for(int k=0;k<9;k++)
        c[i][k].allowed.remove(c[i][j].val);
}

void update_col(int i,int j)
{
    for(int k=0;k<9;k++)
        c[k][j].allowed.remove(c[i][j].val);
}

void update_blk(int i,int j)
{
        int b=c[i][j].block;

        int r,s;
        for(int x=0;x<9;x++)
        {
                r=blk[b].cnum[x][0];
                s=blk[b].cnum[x][1];
                c[r][s].allowed.remove(c[i][j].val);
        }
}

void update_con(int i,int j)
{
    update_row(i,j);
    update_col(i,j);
    update_blk(i,j);
}

void update_allw()
{
        initblocks();
        for(int i=0;i<9;i++)
        {
                for(int j=0;j<9;j++)
                {
                        if(c[i][j].val==0)
                                c[i][j].allowed.insert(c[i][j].allowed.end(),init,init+9);
                        else
                                c[i][j].allowed.clear();
                }
        }




        for(int i=0;i<9;i++)
        {
                for(int j=0;j<9;j++)
                {
                        if(c[i][j].val!=0)
                        {
                                update_con(i,j);
                        }
                }

        }

        show_allw();
}

void init0(int ar[])
{
        for(int i=0;i<9;i++)
                ar[i]=0;
}


int main()
{
    int cnt=0,n;
    cout<<"Welcome to SUDOKU Wizard"<<endl<<endl;
    cout<<"Enter the Number of Elements Given: ";
    cin>>n;

    cout<<"Enter the Value at the Given Cells: "<<endl;
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            cout<<"c["<<i<<"]["<<j<<"]: ";
            cin>>c[i][j].val;
        }
    }


    update_allw();

    show();

    int ar[9];



    cnt=81-n;

    int flag=0;

    int *ptr;

    int vl;

    int r,s;




    list<int>::iterator p;
    /*
    for(int k=0;k<9;k++)
    {
            for(int m=0;m<9;m++)
            {
                    p=c[k][m].allowed.begin();

                    cout<<"c["<<k<<"]["<<m<<"]: ";
                    while(p!=c[k][m].allowed.end())
                    {
                            cout<<*p<<" ";
                            p++;
                    }

                    cout<<endl;
            }
    }

    usleep(4000000);

    */

    while(cnt>0)
    {
        int prev=cnt;

        if(cnt>0)
        {
                //cout<<"In SINGLE - LOOP"<<endl;
                for(int i=0;i<9;i++)
                {
                        for(int j=0;j<9;j++)
                        {
                                if(c[i][j].allowed.size()==1)
                                {
                                        c[i][j].val=c[i][j].allowed.back();
                                        c[i][j].allowed.clear();
                                        update_con(i,j);
                                        cnt--;
                                }
                        }
                }
        }

        //show_allw();
        //show();
        //usleep(4000000);


        //FOR EACH BLOCK
        if(cnt>0)
        {

                //cout<<"BLOCK PROCESSING:"<<endl;

                for(int b=0;b<9;b++)//SEARCHING IN EACH BLOCK AT A TIME
                {
                        init0(ar);

                        for(int x=1;x<=9;x++)//THE NUMBER
                        {
                               for(int i=0;i<9;i++)//INDEX LOOP FOR b BLOCK
                               {
                                        r=blk[b].cnum[i][0];
                                        s=blk[b].cnum[i][1];

                                       if(c[r][s].val==0)
                                       {
                                               p=find(c[r][s].allowed.begin(),--c[r][s].allowed.end(),x);

                                               if((*p)==x)
                                                {
                                                        ar[x-1]++;

                                                }
                                       }

                               }
                        }

                        ptr=find(ar,ar+8,1);


                        if((*ptr)==1)
                        {

                        vl=ptr-ar+1;
                        for(int i=0;i<9;i++)
                        {
                                r=blk[b].cnum[i][0];
                                s=blk[b].cnum[i][1];

                                if(c[r][s].val==0)
                                       {
                                               p=find(c[r][s].allowed.begin(),--c[r][s].allowed.end(),vl);

                                               if((*p)==vl)
                                                {
                                                        c[r][s].val=vl;
                                                        c[r][s].allowed.clear();
                                                        update_con(r,s);
                                                        cnt--;
                                                        break;

                                                }
                                       }


                        }
                        }




                }
        }

        //show_allw();
        //show();
        //usleep(4000000);



        //FOR EACH ROW
        if(cnt>0)
        {

                //cout<<"ROW PROCESSING:"<<endl;

                for(int i=0;i<9;i++)//FOR ROW
                {
                        init0(ar);

                        for(int x=1;x<=9;x++)//FOR NUMBER
                        {
                                for(int j=0;j<9;j++)//FOR COLUMN
                                {
                                        if(c[i][j].val==0)
                                        {
                                                p=find(c[i][j].allowed.begin(),--c[i][j].allowed.end(),x);

                                                if((*p)==x)
                                                        ar[x-1]++;
                                        }
                                }

                        }


                        ptr=find(ar,ar+8,1);

                        if((*ptr)==1)
                        {
                                vl=ptr-ar+1;
                                for(int w=0;w<9;w++)
                                {
                                        p=find(c[i][w].allowed.begin(),--c[i][w].allowed.end(),vl);
                                        if((*p)==vl)
                                        {
                                                c[i][w].val=vl;
                                                c[i][w].allowed.clear();
                                                update_con(i,w);
                                                cnt--;
                                                break;
                                        }
                                }

                        }

                }

        }

        //show_allw();
        //show();
        //usleep(4000000);


        //FOR EACH COLUMN
        if(cnt>0)
        {
                //cout<<"COLUMN PROCESSING:"<<endl;

                for(int j=0;j<9;j++)
                {
                        init0(ar);

                        for(int x=1;x<=9;x++)
                        {
                                for(int i=0;i<9;i++)
                                {
                                        if(c[i][j].val==0)
                                        {
                                                p=find(c[i][j].allowed.begin(),--c[i][j].allowed.end(),x);

                                                if((*p)==x)
                                                        ar[x-1]++;
                                        }
                                }
                        }

                        ptr=find(ar,ar+8,1);

                        if((*ptr)==1)
                        {
                                vl=ptr-ar+1;
                                for(int w=0;w<9;w++)
                                {
                                        p=find(c[w][j].allowed.begin(),--c[w][j].allowed.end(),vl);
                                        if((*p)==vl)
                                        {
                                                c[w][j].val=vl;
                                                c[w][j].allowed.clear();
                                                update_con(w,j);
                                                cnt--;
                                                break;
                                        }
                                }
                        }
                }
        }

        //show_allw();
        //show();
        //usleep(4000000);

         if(cnt!=prev)show(),show_allw();
    }

    cout<<"SOLUTION"<<endl;

    show();

    return 0;
}

