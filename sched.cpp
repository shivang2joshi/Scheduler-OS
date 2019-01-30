#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<bits/stdc++.h>

#define VVP vector<pair<int,pair<int,int> > >
#define tup pair<int,pair<int,int> >
#define ArvlTime(pno) process[(pno)].second.first
#define PID(pno) process[(pno)].first
#define BurstTime(pno) process[(pno)].second.second

using namespace std;

//-------  Function Declarations -------- 
void Sched_FCFS(VVP &process);
void Sched_RR(VVP &process, int time_quantom);
void Sched_SJF(VVP &process);
int string2number(char *s);
bool FCFSsort(const tup &p1, const tup &p2);
bool SJFsort(const tup &p1, const tup &p2);
//--------------------------------------


int main(int argc, char *argv[])
{
    if(argc<3)
    {
        perror("Insufficient Arguments :(\nUsage:\t ./Sched [input_file] [FCFS|RR|SJF] <time_quantom>\nExample:\t ./Sched input.txt FCFS\n\n");
        return 0;
    }

    //taking data from input file stream
    ifstream inputs(argv[1]);
    /*if(ios::fail())
    {
        perror("Couldn't open selected file !\nHint:   try to open file which exists :)\n\n");
        return 0;
    }*/

    //storing it into vector
    VVP process;
    int pid,arvl,burst;
    while(inputs>>pid>>arvl>>burst)
        process.push_back(make_pair(pid,make_pair(arvl,burst)));
    //done

    //identifying scheduling algorithm
    if(strcmp(argv[2],"FCFS")==0)
        Sched_FCFS(process);
    else if(strcmp(argv[2],"RR")==0)
    {
        if(argc==4)
            Sched_RR(process,string2number(argv[3]));
        else
            perror("You have to enter the value of time_quantom for RR\nUsage: ./Sched [input_file] [FCFS|RR|SJF] <time_quantom>\n\n");
    }
    else if(strcmp(argv[2],"SJF")==0)
        Sched_SJF(process);
    else
        perror("Enter Valid Scheduling algorithm name\n\n");
    //done

    return 0;
}


void Sched_FCFS(VVP &process)
{
    sort(process.begin(),process.end(),FCFSsort);

    int sys_time=0;
    int pno=0;
    for(;;sys_time++)
    {
        if(ArvlTime(pno) <= sys_time && BurstTime(pno)>0)
        {
            cout<<"<system time "<<sys_time<<"> process "<<PID(pno)<<" is running\n";
            BurstTime(pno)--;
        }
        else if(BurstTime(pno)==0)
        {
             cout<<"<system time "<<sys_time<<"> process "<<PID(pno)<<" is Finished...\n";
             pno++;
	     if(pno<process.size())
             {
		cout<<"<system time "<<sys_time<<"> process "<<PID(pno)<<" is running\n";
	     	BurstTime(pno)--;
	     }
	     else break;
        }
        else
            cout<<"<system time "<<sys_time<<">      --- CPU idle ---\n";
        
    }
    cout<<"<system time "<<sys_time<<"> All Process are done now.";
	
}


void Sched_RR(VVP &process,int time_quantom)
{
    

}


void Sched_SJF(VVP &process)
{
    sort(process.begin(),process.end(),SJFsort);

    int sys_time=0;
    int pno=0;
    int n = process.size();
    for(;;sys_time++)
    {
        if(ArvlTime(pno) <= sys_time && BurstTime(pno)>0)
        {
            cout<<"<system time "<<sys_time<<"> process "<<PID(pno)<<" is running\n";
            BurstTime(pno)--;
        }
        else if(BurstTime(pno)==0)
        {
             cout<<"<system time "<<sys_time<<"> process "<<PID(pno)<<" is Finished...\n";
             pno++;
             for(int i=pno;i<n;i++)
             {
                 if(ArvlTime(i)<sys_time)
                    ArvlTime(i)=sys_time;   //bringing up the arrival time so to sort it later
             }
             sort(process.begin()+pno,process.end(),SJFsort);
             
            if(pno<n)
            {
                cout<<"<system time "<<sys_time<<"> process "<<PID(pno)<<" is running\n";
                BurstTime(pno)--;
            }
	        else break;
        }
        else
            cout<<"<system time "<<sys_time<<">      --- CPU idle ---\n";
        
    }
    cout<<"<system time "<<sys_time<<"> All Process are done now.";
	
}



bool FCFSsort(const tup &p1, const tup &p2)
{
   return (p1.second.first<p2.second.first) || 
           (p1.second.first==p2.second.first && p1.first<p2.first);
}

bool SJFsort(const tup &p1, const tup &p2)
{
   return (p1.second.first<p2.second.first) || 
           (p1.second.first==p2.second.first && p1.second.second<p2.second.second);
}


int string2number(char *s)
{
    int number=0;
    int len = strlen(s);
    int place=1;
    for(int i=len-1;i>=0;i--)
    {
        if(s[i]<'0' || s[i]>'9')
        {
            perror("Please Enter a valid Numerical Value for time_quantom.\n");
            exit(1);
        }
        number += (s[i]-'0')*place;
        place *= 10;
    }
    return number;
}
