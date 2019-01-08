// Compile with c++ ece650-a2cpp -std=c++11 -o ece650-a2
#include <iostream>
#include <sstream>
#include <vector>
//Edge list 2D Array Matrix
class Edges
{
    private:
        int **array_E;
         int  size1;
    public:
      Edges()
      {
        size1=0;
      }
        void set_arr_size( int  num);
        void set_edge(int i,int j);
        int get_edge(int i,int j);
        void del_arr();
        void display_arr();
};
void Edges::set_arr_size( int  num)
{
    array_E=new int* [num];
    size1=num;
    for (int n=0;n<num;n++)
        array_E[n]=new int[num];
    for (int i=0;i<size1;i++)
    {
        for (int j=0;j<size1;j++)
        {
            array_E[i][j]=0;
        }
    }
}
void Edges::set_edge(int i,int j)
{
    array_E[i][j]=1;
}
int Edges::get_edge(int i,int j)
{
  if (size1!=0)
   return  array_E[i][j];
   else
   return 0;
}
void Edges::del_arr()
{
   if (size1!=0)
    delete[] array_E;
    //return true;
}
void Edges::display_arr()
{
    for (int i=0;i<size1;i++)
    {
        for (int j=0;j<size1;j++)
        {
            std::cout<<array_E[i][j]<<"\t";
        }
        std::cout<<std::endl;
    }
}

//Queue for performing the enqueue and dequeue operations
struct node{
    int data;
    node *next;
};

class Queue{
    private :
        node *head,*tail;
        int size1=0;
    public :
        Queue()
        {
            head=NULL;
            tail=NULL;
        }
        void enqueue(int num);
        int dequeue();
        bool isempty();
        void display();
};
void Queue::enqueue(int num)
{
    size1=size1+1;
    node *fob= new node;
    fob->data=num;
    fob->next=NULL;
    if(head==NULL)
    {
        head=fob;
        tail=fob;
        fob=NULL;
    }
    else
    {
        tail->next=fob;
        tail=fob;
        fob=NULL;
    }
}
int Queue::dequeue()
{
    if (size1==0)
        return -1;
    if (size1==1)
        tail=tail->next;
    node *fob=new node;
    fob=head;
    int value=head->data;
    head=head->next;

    size1--;
    delete fob;
    return value;
}

bool Queue::isempty()
{
    if(size1==0)
        return true;
    else
        return false;
}

void Queue::display()
{
    if (size1!=0)
    {
        node *bof=new node();
        bof=head;
        int count2=0;
        while(count2<size1)
        {
            count2++;
            int val=bof->data;
            std::cout<<val<<"->";
            bof=bof->next;
        }
    }
}

//check the edges in E command and return the edges in vector
std::vector<int> check_edge(std::string s_cmd,int num_V)
{
    char comma=',';
    int count3=0;
    std::string final_str="";
    std::vector<int> nums;
    std::istringstream inp(s_cmd);
    while (!inp.eof())
        {
            int num;
            inp >> num;
            count3++;
            if (inp.fail())
            {
                nums.clear();// noexcept;
                return nums;
            }
            else if(num<0)
            {
                nums.clear();// noexcept;
                return nums;
            }
            else
            {
                if(num<num_V)
                {
                    nums.push_back(num);
                }
                else
                    {
                        nums.clear() ; //noexcept;
                        return nums;
                    }
            }

            if (inp.eof())
                break;
            char separator;
            inp >> separator;

            // if error parsing, or if the character is not a comma
            if (inp.fail() || separator != comma)
            {
                nums.clear() ;//noexcept;
                return nums;
            }
        }
    return nums;
}

//set valid edges in 2d Array matrix
void set_edges_in_matrices(std::vector<int> &nums, Edges obj1)
{
    if (!nums.empty()) {
            for (int x=0;x< int(nums.size()-1);) {
                    int i=x;
                    int j=x+1;
                    obj1.set_edge(nums[i],nums[j]);
                    obj1.set_edge(nums[j],nums[i]);
                    x=x+2;
                // print a comma if not the last number
            }
        }
}

//check the number of vertices given in V command
int check_num_V(std::string ch)
{
    bool flag=false;
    int num=0;
    for (int i=0;i< int(ch.length());i++)
    {
        if( std::isdigit(ch[i]))
        {
            int kk = ch[i] - '0';
            num=num*10 + kk;
            flag=true;
        }
        else
            return -1;
    }
    if (flag==true)
        return num;
    else
        return -1;
}

//check the format of E command
std::string check_edge_list(std::string ch, int num_V)
{
    std::string final_str="";
    bool flag1=false;
    bool flag2=false;
    int comma_count=1;
    std::string num="";
    for (int c=0;c< int(ch.length());c++)
    {
        if (c==0 && ch[c]!='{')
            return "false";
        else if(c==0 && ch[c]=='{')
            flag1=true;
        else if(c==1 && ch[c]!='<')
            return "false";
        else if((flag2==false && flag1==true) && ch[c]=='<' && comma_count==1)
        {
            comma_count=0;
            num="";
            flag2=true;
        }
        else if((flag1==true && flag2==true) && (ch[c]=='0' || ch[c]=='1' || ch[c]=='2' || ch[c]=='3' || ch[c]=='4' || ch[c]=='5'|| ch[c]=='6' || ch[c]=='7' || ch[c]=='8' || ch[c]=='9') )
        {
            num=num+ch[c];
        }
        else if(ch[c]==',' && flag2==true && flag1== true && comma_count==0)
        {
            int k=check_num_V(num);
            if (k==-1 || k>=num_V)
                return "false";
            else
            {
            final_str=final_str+num+",";
            num="";
            comma_count=1;
            }
        }
        else if(ch[c]==',' && flag2==false && flag1==true && comma_count==0)
        {
            comma_count=comma_count+1;
        }
        else if(ch[c]=='>' && flag2==true && flag1==true && comma_count==1)
        {
            comma_count=0;
            flag2=false;
            int k=check_num_V(num);
            if (k==-1 || k>=num_V)
                return "false";
            else
            {
            if (c== int(ch.length())-2)
                final_str=final_str+num;
            else
                final_str=final_str+num+ ",";
            num="";
            }
        }
        else if(ch[c]=='}' && flag2==false && comma_count==0  && (c== int(ch.length())-1))
        {
            flag1=false;
        }
        else
        {
           return "false";
        }
    }
    if (flag1==true || flag2==true || comma_count!=0 || final_str=="" || final_str==" ")
        return "false";
    return final_str;
}

//implement BFS to find shortest path
std::string B_F_S(int s,int d, Edges obj, int num_V)
{
    if(s==d )
    {
        std::string str;
        std::ostringstream str1;   // stream used for the conversion
        str1 << d;
        str=str1.str();
        return str;
    }
    int color[num_V];
    int dist[num_V];
    std::string path[num_V];
    for(int i=0;i<num_V;i++)
    {
        if (i!=s)
        {
            color[i]=0;
            dist[i]=-1;
            path[i]="";
        }
    }
    color[s]=1;
    dist[s]=0;
    path[s]="";
    Queue obj1;
    obj1.enqueue(s);
    bool flag_get_path=false;
    while((!obj1.isempty()) && flag_get_path==false)
    {
        int k=obj1.dequeue();
        for (int j=0;j<num_V;j++)
        {
            if(obj.get_edge(k,j)==1 && k!=j && color[j]==0)
            {
                if(k==s)
                {
                    std::string str;
                    std::ostringstream str1;   // stream used for the conversion
                    str1 << s;
                    str=str1.str();
                    path[k]=str+"-";
                }
                else if(k!=s) {
                    /*std::string str;
                    std::ostringstream str1;   // stream used for the conversion
                    str1 << j;
                    str=str1.str();
                    path[j]+=str+"-";
                    dist[j]=dist[j]+1;
                    color[j]=1;
                    obj1.enqueue(j);*/
                }
                if(j==d)
                {
                    color[j]=1;
                    std::string str;
                    std::ostringstream str1;   // stream used for the conversion
                    str1 << d;
                    str=str1.str();
                    path[j]=path[k]+str;
                    dist[j]=dist[j]+1;
                    flag_get_path=true;
                    return path[j];
                }
                else if(j!=d)
                {
                    color[j]=1;
                    std::string str;
                    std::ostringstream str1;   // stream used for the conversion
                    str1 << j;
                    str=str1.str();
                    path[j]=path[k]+str+"-";
                    dist[j]=dist[j]+1;
                    obj1.enqueue(j);
                }


            }
            /*else if (obj.get_edge(k,j)==1 && k!=j && color[j]==2 && j==d && j==s)
            {
              color[j]=1;
              std::string str;
              std::ostringstream str1;   // stream used for the conversion
              str1 << d;
              str=str1.str();
              path[j]=path[k]+str;
              dist[j]=dist[j]+1;
              flag_get_path=true;
              return path[j];
            }*/
        }
        color[k]=2;
    }
    if(dist[d]==-1)
        return "no path";
    return "no path";
}

int main(int argc, char** argv) {
  try{
    const char comma = ',';
    bool flag_V=false;            //flags for checking the sequencing of V ,E and s commands
    bool flag_E=false;
    bool flag_s=true;
    Edges obj1;                   //object that points to 2-D array matrix to stores edges
    while (!std::cin.eof()) {
      //gets the line
        std::string line;
        std::getline(std::cin, line);
        std::string error_line="Error: failed to generate valid input for 25 simultaneous attempts";
        std::istringstream input(line);
        if(error_line.compare(line)==0)
        {
            std::cerr<<error_line<<std::endl;
            continue;
            //return 0;
            //abort();
        }
        std::istringstream ss(line);
        std::istringstream vv(line);
        std::istringstream ee(line);
        int count_for_s=0;
        int count_for_v=0;
        int count_for_e=0;
        //checks the number of inputs for s command
        while (!ss.eof())
        {
            std::string ch12;
            ss>>ch12;
            //std::cout<<ch12;
            if(ss.fail())
            {
                break;
            }
            else
            {
                count_for_s++;
            }
        }
        //checks the number of inputs for v command
        bool vb=false;
        while (!vv.eof())
        {
            std::string ch12;
            vv>>ch12;
           /* if(ch12=="V" || vb==true)
            {
                  std::cout<<ch12<<" ";
                  vb=true;
            } */


            if(vv.fail())
            {
                break;
            }
            else
            {
                count_for_v++;
            }
        }
        if (vb==true)
        std::cout<<std::endl;
        //checks the number od inputs for E command
        bool eb=false;
        while (!ee.eof())
        {
            std::string ch12;
            ee>>ch12;
           /*  if(ch12=="E" || eb==true)
            {
                if(ch12=="E")
                  std::cout<<ch12<<" ";
                else
                   std::cout<<ch12;
                  eb=true;
            }
*/
            if(ee.fail())
            {
                break;
            }
            else
            {
                count_for_e++;
            }
        }
        if (eb==true)
         std::cout<<std::endl;
        std::vector<int> nums;
        char option;                        //stores command character
        int count=0;
        int count1=0;
        int count_option=0;
        int err_counter=0;
        int num_V;
        bool flag_cmd=true;
        std::string s_cmd="";
        while (!input.eof()) {              //traversing the words in a Line
            count++;                        //counting numbers of woords traversed
            std::string ch;
            input>>ch;
            if(input.fail())
            {
              if (count_option>0 && count==2)
                {
                  count=1;
                  count1=0;
                }
              else
                count1++;
              break;
            }
           else if((ch=="V" || ch=="E" || ch=="s") && count==1)       //first letter must be V,E or s
            {
                option=ch[0];
                count_option++;
            }
           else if((option=='V' || option=='E') && count==2)
           {
                switch(option)
                {
                    case 'V':
                        if (((flag_V==false && flag_E==false) || flag_s==true || (flag_V==true && flag_E==true)) && count_for_v==2)
                        {
                             num_V=check_num_V(ch);
                             if(num_V<=0)
                             {
                                 /* std::cerr<<"Error: V must be greater than 0\n";
                                 err_counter++;
                                 break; */
				std::cout<<line<<std::endl;
                                flag_E=false;
                                flag_s=false;
                                flag_V=true;
                               // break;
                             }
                             else
                            {
                                std::cout<<line<<std::endl;
                            }


                            obj1.del_arr();                     // delete the previous 2D aaray

                            obj1.set_arr_size(num_V);           //set new 2D array
                            flag_E=false;
                            flag_s=false;
                            flag_V=true;
                        }
                        else
                        {
                            if (count_for_v!=2)
                            {
                            std::cerr<<"Error: Input must be in form V 6\n";
                            err_counter++;
                            }
                            else
                            {
                              std::cerr<<"Error: V must be followed by E\n";
                              err_counter++;
                            }
                        }
                        break;
                    case 'E':
                        if ((flag_V==true && flag_E==false && flag_s==false) && (count_for_e==2))
                        {
                            if (ch=="{}")
                            {
				std::cout<<line<<std::endl;
                                flag_E=true;
                                break;
                            }
                            else
                            {
                                std::cout<<line<<std::endl;
                            }

                            std::string  edg_err = check_edge_list(ch,num_V);
                            if(edg_err=="false")
                            {
                                std::cerr<<"Error: input must be in form \" E {<a,b>,<n,h>,...}\"\n";
                                err_counter++;
                                break;
                            }
                            std::istringstream inp(edg_err);
                            while (!inp.eof())
                                {
                                    int num;
                                    inp >> num;
                                    if (inp.fail())
                                    {
                                        std::cerr << "Error parsing a number\n";
                                        err_counter++;
                                        break;
                                    }
                                    else
                                        nums.push_back(num);
                                    if (inp.eof())
                                        break;

                                    char separator;
                                    inp >> separator;

                                      // if error parsing, or if the character is not a comma
                                    if (inp.fail() || separator != comma)
                                    {
                                        std::cerr << "Error parsing separator\n";
                                        err_counter++;
                                        break;
                                    }
                                }
                            set_edges_in_matrices(nums,obj1);
                            flag_E=true;
                        }
                        else{
                          if(count_for_e!=2)
                          {
                             std::cerr<<"Error: Input must be in form {<1,2>,...}\n";
                             err_counter++;
                           }
                           else{
                             std::cerr<<"Error: V must be followed by E\n";
                             err_counter++;
                           }
                        }
                        break;
                    default:
                        break;
                }
           }
           else if(option=='s' && count!=1)
           {
                if (flag_E==true && flag_V==true )
                {
                    if (count<3)
                        s_cmd=s_cmd+ch+",";
                    else
                        s_cmd=s_cmd+ch;
                    if ((count_for_s>3) || (count_for_s<3))
                    {
                        s_cmd="";
                        std::cerr<<"Error: input must be in form \"s 2 3\"\n";
                        err_counter++;
                        break;
                    }
                    else if (count_for_s==3 && count==3)
                    {
                        std::vector<int> num1 = check_edge(s_cmd,num_V);
                        if (num1.empty())
                        {
                           std::cerr<<"Error: input must be in form \"s 2 3\"\n";
                           err_counter++;
                            break;
                        }
                        else
                        {
                            int s1=num1.at(0);
                            int d=num1.at(1);
                            std::string result=B_F_S(s1, d,obj1, num_V);
                            if(result=="no path")
                            {
                                std::cerr<<"Error: no path found\n";
                                err_counter++;
                                break;
                            }
                            else
                                std::cout<<result<<std::endl;

                            flag_s=true;
                        }
                    }
                }
                else
                {
                    std::cerr<<"Error: s must follow V then E \n";
                    err_counter++;
                    break;
                }
           }
           else if (err_counter==0)
           {
            std::cerr<<"Error: Wrong input command\n";
            flag_cmd=false;
            break;
           }
           else if(err_counter>0)
           {break;}
        }
        if (count==1 && flag_cmd==true && count1==0)
        {
            std::cerr<<"Error: Invalid input command\n";
        }
    }
  }
  catch(const std::exception& e)
  {
    std::cerr<<"Error: "<<e.what()<<std::endl;
  }

}
