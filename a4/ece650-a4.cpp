#include <memory>
#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>

//finding combination
int combination(int n,int t);
//negative combinations
std::vector<int> neg_combination(int atoms,std::vector<int> indexes,int n,int k);
//end combinations
std::vector<int> end_combination(std::vector<int> edges,std::vector<int> littral_indexes,int n,int k);

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
        int get_total_edges();
        void del_arr();
        void display_arr();
        std::vector<int> get_uniq_edges();
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

int Edges::get_total_edges()
{
    int cc=0;
    if(size1!=0)
    {
        for(int i=0;i<size1;i++)
        {
            for(int j=0;j<size1;j++)
            {
                if(get_edge(i,j)==1)
                    cc++;
            }
        }
        return(cc/2);
    }
    else
    return cc;
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
            std::cout<<array_E[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}

std::vector<int> Edges::get_uniq_edges()
{
    std::vector<int> num;
    if(size1!=0)
    {
        for(int i=0;i<size1;i++)
        {
            for(int j=i;j<size1;j++)
            {
                if(get_edge(i,j)==1)
                    {
                        num.push_back(i);
                        num.push_back(j);
                    }
            }
        }
        return num;
    }
    else
    return num;
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

void set_edges_in_matrices(std::vector<int> &nums, Edges obj1)
{
    if (!nums.empty()) {
            for (int x=0;x< int(nums.size()-1);) {
                    int i=x;
                    int j=x+1;
                    if(nums[i]==nums[j])
                    {
                        x=x+2;
                        continue;
                    }
                    obj1.set_edge(nums[i],nums[j]);
                    obj1.set_edge(nums[j],nums[i]);
                    x=x+2;
                // print a comma if not the last number
            }
        }
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



int cal_clause_no(int e,int k,int n)
{
    int p=2;
    int total=e+k+(combination(n,p) *k)+((combination(k,p))*n);
    return total;
}

int combination(int n,int r)
{
    int c=(n*(n-1))/2;
    return c;
}

std::vector<int> neg_combination(int atoms,std::vector<int> indexes,int n,int k)
{
    std::vector<int> nums;
    for(int ww=0;ww<n;ww++)
    {
        for(int kk=ww;kk<(n*k);)
        {
            for(int kkr=kk+n;kkr<(n*k);)
            {
                nums.push_back(indexes.at(kk));
                nums.push_back(indexes.at(kkr));
                kkr=kkr+n;
            }
            kk=kk+n;
        }
    }
    int count3=0;
    for(int pw=0;pw<indexes.size();pw++)
    {

        if((pw==0) || (pw%n==0))
        {
            for(int ps=pw+1;ps<pw+n;ps++)
            {
            nums.push_back(indexes.at(pw));
            nums.push_back(indexes.at(ps));
            }
            count3++;
        }
        else
        {
            for(int ps=pw+1;ps<(n*count3);ps++)
            {
            nums.push_back(indexes.at(pw));
            nums.push_back(indexes.at(ps));
            }
        }

    }
    return nums;
}




int main(void) {
   try
   {
        const char comma = ',';
        bool flag_V=false;            //flags for checking the sequencing of V and E commands
        bool flag_E=false;
        Edges obj1;
        while (!std::cin.eof())
        {
            //get input line
            std::string line;
            std::getline(std::cin, line);
            std::istringstream input(line);

            //check count of V and E commands
            std::istringstream vv(line);
            std::istringstream ee(line);
            int count_for_e=0;
            int count_for_v=0;

            while (!vv.eof())
            {
                std::string ch12;
                vv>>ch12;
                if(vv.fail())
                {
                    break;
                }
                else
                {
                    count_for_v++;
                }
            }
            //checks the number of inputs for E command
            while (!ee.eof())
            {
                std::string ch12;
                ee>>ch12;
                if(ee.fail())
                {
                    break;
                }
                else
                {
                    count_for_e++;
                }
            }
            std::vector<int> nums;
            char option;                        //stores command character
            int count=0;
            int count1=0;
            int count_option=0;
            int err_counter=0;
            int num_V;
            bool flag_cmd=true;
            while (!input.eof())
            {
                count++;                        //counting numbers of words traversed
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
                else if((ch=="V" || ch=="E" ) && count==1)       //first letter must be V or E
                {
                    option=ch[0];
                    count_option++;
                }
                else if((option=='V' || option=='E') && count==2)
                {
                    switch(option)
                    {
                        case 'V':
                            if (((flag_V==false && flag_E==false) || (flag_V==true && flag_E==true)) && count_for_v==2)
                            {
                                num_V=check_num_V(ch);
                                if(num_V<=0)
                                {
                                    std::cerr<<"Error: V must be greater than 0\n";
                                    err_counter++;
                                    break;
                                }
                                obj1.del_arr();                     // delete the previous 2D aaray

                                obj1.set_arr_size(num_V);           //set new 2D array
                                flag_E=false;
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
                        if ((flag_V==true && flag_E==false ) && (count_for_e==2))
                        {
                            if (ch=="{}")
                            {
                                flag_E=true;
                              break;
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
                            //obj1.display_arr();
                            bool stop=true;
                            int n=num_V;
                            int k=1;
                            int countk=1;

                            std::vector<int> final_littrals;
                            int final_k;
                            bool flag_sat=false;
                            int min1=1;
                            int max1=n;
                            while(stop || (min1==(max1+1)))         //loop for setting k
                            {

                                std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());
                                std::vector<int> littral_indexes;
                                k=min1;
                                //no of atoms
                                int atom=k*n;
                                int e=obj1.get_total_edges();
                                //if no edge exists
                                if(e==0)
                                    break;
                                int clause_no;
                                clause_no=cal_clause_no(e,k,n);

                                //initialization
                                Minisat::vec<Minisat::Lit> littrals;
                                //making new variables or littrals
                                for(int i = 0; i <atom; i++)
                                {
                                    Minisat::Lit l = Minisat::mkLit(solver->newVar());
                                    littrals.push(l);
                                }


                                //adding positive littral clauses in minisat
                                for(int i=0;i<k;i++)
                                {
                                     Minisat::vec<Minisat::Lit> cla_add;
                                    for(int j=0;j<n;j++)
                                    {
                                        int pos=(i+(k*j));
                                        littral_indexes.push_back(pos);
                                        cla_add.push(littrals[pos]);
                                    }
                                     solver->addClause(cla_add);
                                }


                                int len_of_neg_lit=n+(combination(n,2)*2);
                                //adding negative littral clauses in minisat
                                std::vector<int> neg_combi=neg_combination(len_of_neg_lit,littral_indexes,n,k);
                                for(int i=0;i<neg_combi.size();)
                                {
                                    Minisat::vec<Minisat::Lit> cla_add;
                                    cla_add.push(~littrals[neg_combi.at(i)]);
                                     cla_add.push(~littrals[neg_combi.at(i+1)]);
                                     solver->addClause(cla_add);
                                    i=i+2;
                                }

                                //getting edges and and adding end clauses in minisat
                                std::vector<int> edges=obj1.get_uniq_edges();
                                std::vector<int> nums;
                                for(int i=0;i<edges.size();)
                                {
                                    Minisat::vec<Minisat::Lit> cla_add;
                                    int countt=0;
                                    for(int j=0;j<k;j++)
                                    {
                                        cla_add.push(littrals[littral_indexes.at(edges.at(i)+(countt*n))]);
                                        cla_add.push(littrals[littral_indexes.at(edges.at(i+1)+(countt*n))]);
                                        countt++;
                                    }
                                    solver->addClause(cla_add);
                                    i=i+2;
                                }


                                //getting result
                                bool res = solver->solve();
                                if(res==1)
                                {
                                    flag_sat=true;
                                    final_k=k;
                                    std::vector<int> litt;
                                    final_littrals.empty();
                                    for(int i=0;i<atom;i++)
                                    {
                                        int ress=Minisat::toInt(solver->modelValue(littrals[i]));
                                        litt.push_back(ress);
                                        final_littrals.push_back(ress);
                                    }
                                      std::vector<int> vert;
                                        stop=false;
                                        for(int i=0;i<final_littrals.size();i++)
                                        {

                                            if(final_littrals.at(i)==0)
                                            {
                                                int p=i/final_k;
                                                vert.push_back(p);
                                            }
                                        }

                                         std::sort(vert.begin(),vert.end());
                                         for(int i=0;i<vert.size();i++)
                                            std::cout<<vert.at(i)<<" ";
                                         std::cout<<""<<std::endl;
                                }
                                else
                                {
                                    min1++;
                                }
                                flag_E=true;
                            }
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

            }

        }
   }
   catch(const std::exception& e)
   {
       std::cerr<<"Error: "<<e.what()<<std::endl;
   }
}
