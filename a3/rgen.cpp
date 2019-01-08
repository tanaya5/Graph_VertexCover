#include <unistd.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

int generate_random(int min1,int max1)
{
    std::ifstream urandom("/dev/urandom");

    // check that it did not fail
    if (urandom.fail()) {
        std::cerr << "Error: cannot open /dev/urandom\n";
        return 1;
    }
    unsigned int num = 42;
    urandom.read((char*)&num, sizeof(int));
    return min1 + num % (max1 - min1);
    //int random=num%100;
}



int main (int argc, char **argv)
{
    int s=10;                   //number of streets
    int n=5;                    //number of line segments
    int l=5;                    //wait seconds
    int c=20;                   //range for coordinates
    int w;
    opterr = 0;

    //bool sflag=0;
    //bool nflag=0;
    //bool lflag=0;
    //bool cflag=0;

    int s_rand=s;
    int n_rand=n;

    std::string c_tempc;
    int c_temp;

    while ((w = getopt (argc, argv, "s:n:l:c:")) != -1)  //-1 means no more options present
        switch (w)
        {
        case 's':
            c_tempc=optarg;
            c_temp=atoi(c_tempc.c_str());
            if(c_temp>=2)
                s=c_temp;
            else
            {
                std::cerr << "Error: below the range: " << optopt << std::endl;
                return 1;

            }
            //sflag = true;
            break;
        case 'n':
           c_tempc=optarg;
            c_temp=atoi(c_tempc.c_str());
            if(c_temp>=1)
                n=c_temp;
            else
            {
                std::cerr << "Error: below the range: " << optopt << std::endl;
                return 1;
            }
            //nflag = true;
            break;
        case 'l':
            c_tempc=optarg;
            c_temp=atoi(c_tempc.c_str());
            if(c_temp>=5)
                l=c_temp;
            else
            {
                std::cerr << "Error: below the range: " << optopt << std::endl;
                return 1;
            }
            //lflag=true;
            break;
        case 'c':
            c_tempc=optarg;
            c_temp=atoi(c_tempc.c_str());
            if(c_temp>=1)
                c=c_temp;
            else
            {
                std::cerr << "Error: below the range: " << optopt << std::endl;
                return 1;
            }
            //cflag=true;
            break;
        case '?':
            if (optopt == 'c' || optopt=='l' || optopt=='n' ||optopt=='s')
                std::cerr << "Error: option -" << optopt
                          << " requires an argument." << std::endl;
            else
                std::cerr << "Error: unknown option: " << optopt << std::endl;
            return 1;
        default:
            return 0;
        }

    static std::vector<std::string> v;
    v = {"Werber Street", "King Street","Airport Street","Central Street","Copper Street","Delta Street","Dock Street","Elisabeth Street","Empire Avenue","Eppink Square",
        "Federation Square","Forest Street","Freedom Avenue","Gateway Street","Heritage Avenue","Highway Avenue","Hurbadome Avenue","Ida Street","Industry Street","Innovation Avenue",
        "King Arthur street","Law Street","Lucy Street","Mandarin Park Lane","Maple Street","Marine Avenue","Mayores Road","Medieval Street","Mill Place","Mitch Cromwood Avenue",
        "Monorail Street","Museum Avenue","Newhaven Avenue","New Orleans Street","Newport Street","New Street","Noble City Path","Northern Abby Avenue","Ocean Avenue","Oceana Sidestreet",
        "Old Port Avenue","Old Wharf","Overbanken Road","Paul Hladovka Avenue","Pine Avenue","Pine Street","Plaza Street","Poet Street","Prague Avenue","Princess Avenue",
        "Quarry Avenue","Rail Avenue","Railway Street","River Side Road","River Street","Rome Avenue","Sebastian Street","School Street","Shall Street","Shopping Avenue",
        "Silver Street","Sobrance Path","Southern Abby Avenue","Southern Avenue","Southern Millstreet Avenue","Southern Street","Square Street","State Avenue","Stone Street","Storm Alley",
        "Subway Street","Swamp Street","Swit Street","Sylvania Avenue","Technology Avenue","Temmar Eastwood Avenue","Theater Street","Venice Street","Vienna Street","Wallstreet",
        "Water lily Avenue","Water Street","Western Cesta","William Street","Woodstock Street","Zosnul Street","Alexandra Drive","Albion Avenue","Alba Place","Angela Street",
        "Apostle Road","Archery Close","Arlington Avenue","Astell Street","Athlone Street","Aviland Street","Avondale Rise","Ayres Street","Bacton Street","Balfe Street"
        };


   int time=l*1000000;
   int count=0;
   bool prev_street_flag=false;
   std::vector<std::string> prev_streets;
   while(true)
   {
       n_rand=generate_random(1,n+1);
        s_rand=generate_random(2,s+1);


    int coor_pair=n_rand+1;

        int v_flag[100];         //array for storing the flag values of streets
        for (int i=0;i<100;i++)
            v_flag[i]=0;
        std::vector<std::string> streets;
       int count_s=0;
       int count_c1=1;
       //int arr_allseg[n*2*s];
       std::vector<int> allseg;
        std::string name;

        std::vector<std::string> temp_streets;
        std::string final_streets="";
        std::string remove_streets="";
       while(count_s!=s_rand)
       {
           //generates a street with vertices
            int random_street_name=generate_random(0,100);
            int count_for_street=0;
            while(count_for_street!=40)
            {
                //generating street names
                random_street_name=generate_random(0,100);
                if(v_flag[random_street_name]==0)
                    {
                        name=v.at(random_street_name);
                        temp_streets.push_back(name);
                        //prev_streets.push_back(name);
                        name="a \"" +name+"\" ";
                        v_flag[random_street_name]=1;

                        //std::cout<<name<<std::endl;
                        break;
                    }
                count_for_street++;
            }
            if (count_for_street==40)
            {
                std::cerr << "Error: search for  valid street is taking too long" << std::endl;
                return 1;
            }


            //generating coordinates
            int arr[2*coor_pair];


            {
                int x=-(generate_random(0,c+1));
                int y=-(generate_random(0,c+1));
                arr[0]=x;
                arr[1]=y;
                allseg.push_back(x);
                allseg.push_back(y);
                int ocount=0;
                for(int k=1;k<coor_pair;)
                {

                    int range=int(((2*c)/n)+3);
                    //std::cout<<range<<std::endl;
                    int z=(generate_random(0,range));
                    //std::cout<<z<<std::endl;
                    int b=(generate_random(0,range));
                    if(((x+z)<=c) && ((x+z)>=(-c)) && (z!=0))
                        x=x+z;
                    else if((x+2)<=c && ((x+2)>=(-c)))
                        x=x+2;
                    else if((x+1)<=c && ((x+1)>=(-c)))
                        x=x+1;
                    if(((y+b)<=c) && ((y+b)>=(-c)) &&(b!=0))
                        y=y+b;
                    else if(((y+2)<=c) && ((y+2)>=(-c)))
                        y=y+2;
                    else if(((y+1)<=c) && ((y+1)>=(-c)))
                        y=y+1;
                    else if(((y-1)<=c) && ((y-1)>=(-c)))
                        y=y-1;
                    bool root1=true;
                    //std::cout<<"hh"<<std::endl;
                    for (int f=0;f<(2*coor_pair);)
                    {
                        if((arr[f]==x) && (arr[f+1]==y))
                        {
                            //k--;
                            ocount++;
                            root1=false;
                            break;
                        }
                        f=f+2;
                    }
                     //std::cout<<"ppppppp"<<std::endl;
                    if (root1==true  && allseg.size()>=4)
                    {
                         for(int i = 0; i <= allseg.size()-4; )
                        {
                        //std::cout<<"tyuiop"<<std::endl;
                        if((allseg.at(i)==arr[(k*2)-2])&&(allseg.at(i+1)==arr[(k*2)-1]) &&(allseg.at(i+2)==x) && (allseg.at(i+3)==y))
                           {
                              //k--;
                              ocount++;
                              root1=false;
                              break;
                           }
                        else if((allseg.at(i)==x)&&(allseg.at(i+1)==y) &&(allseg.at(i+2)==arr[(k*2)-2]) && (allseg.at(i+3)==arr[(k*2)-1]))
                           {
                              //k--;
                              ocount++;
                              root1=false;
                              break;
                           }
                        else if((allseg.at(i)==x)&&(allseg.at(i+1)==y))
                        {
                           {
                              //k--;
                              ocount++;
                              root1=false;
                              break;
                           }
                        }
                        i=i+2;
                        }
                    }
                    if (root1==true)
                    {
                        arr[k*2]=x;
                        arr[(k*2)+1]=y;
                        allseg.push_back(x);
                        allseg.push_back(y);
                        k++;
                    }
                    if (ocount ==25)
                    {
                        std::cerr <<"Error: failed to generate valid input for 25 simultaneous attempts" << std::endl;
                        exit(1);
                    }
                }
            }

            std::string coor="";
            std::string temp="";
            /*for(int p=0;p<(2*coor_pair);p++)
            {
                std::cout<<arr[p]<<std::endl;
            }*/
            for(int p=0;p<(2*coor_pair);p++)
            {
               if(p%2==0 )
               {
                   temp=std::to_string(arr[p]);
                   coor=coor+"("+temp+",";
               }
               else
               {
                   temp=std::to_string(arr[p]);
                   coor=coor+temp +")"+" ";
               }
            }
            name=name+coor;
            streets.push_back(name);
            //std::cout<<name<<std::endl;

           count_s++;
       }
        for(int i = 0; i < streets.size(); i++)
        {
            if(i<streets.size()-1)
            {
                final_streets+=streets.at(i)+"\n";
            }
            else
            {
                final_streets+=streets.at(i);
            }
        }
        std::string lol="\"";
        if(prev_street_flag)
        {
            for (int u=0;u<prev_streets.size();u++)
            {
                if(u!=prev_streets.size()-1)
                    remove_streets+="r "+lol+prev_streets.at(u)+lol+"\n";
                else
                    remove_streets+="r "+lol+prev_streets.at(u)+lol+"\n";
            }
        }
        prev_streets=temp_streets;
        std::cout<<remove_streets<<std::flush;
        std::cout<<final_streets<<std::endl<<std::flush;
        std::cout<<"g"<<std::endl<<std::flush;
        prev_street_flag=true;
       count++;
       usleep(time);
       //std::cout<<"**********************"<<std::endl;
   }
   //exit(0);
        return 0;

}


            /*for(std::vector<std::string>::size_type i = 0; i != streets.size(); i++)
        {
        std::cout << streets[i]<<std::endl;}*/
