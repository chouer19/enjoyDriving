#include <iostream>
#include <ctime>
#include <sstream>
#include <fstream>
 
using namespace std;
 
// timestamp returns the current time as a string 
std::string timestamp();    
 
class LogStatement;
ostream& operator<<(ostream& ost, const LogStatement& ls);
 
class LogStatement
{
public:
        LogStatement(std::string s): data(s), time_string( timestamp() )
        { };
 
        //This method handles all the outputs.    
        friend ostream& operator<<(ostream&, const LogStatement&);   
private:
        std::string data;
        std::string time_string;
    
};
 
ostream& operator<<(ostream& ost, const LogStatement& ls)
{
        ost<<"~|"<<ls.time_string<<'|'<<ls.data<<"|~";
        return ost;
}
 
std::string timestamp() 
{
        //Notice the use of a stringstream, yet another useful stream medium!
        ostringstream stream;    
        time_t rawtime;
        tm * timeinfo;
 
        time(&rawtime);
        timeinfo = localtime( &rawtime );
 
        stream << (timeinfo->tm_year)+1900<<" "<<timeinfo->tm_mon
        <<" "<<timeinfo->tm_mday<<" "<<timeinfo->tm_hour
        <<" "<<timeinfo->tm_min<<" "<<timeinfo->tm_sec;
        // The str() function of output stringstreams return a std::string.
        return stream.str();   
}
 
int main(int argc, char** argv)
{
        if(argc<2)
        {
              // A return of -1 denotes an error condition.
              return -1;  
        }
        ostringstream log_data;
        // This takes all the char arrays in the argv 
        // (except the filename) and produces a stream.
        for(int i=1;i<argc;i++)    
        {
               log_data<<argv[i]<<' '; 
        }
  
        LogStatement log_entry(log_data.str());
 
        //clog<<log_entry<<endl;
        cout<<log_entry<<endl;
 
        ofstream logfile("logfile",ios::app);
 
        // check for errors opening the file
        if ( ! logfile )      
        {
                cout << "No log!\n";
                return -1;
        }       
 
        logfile<<log_entry<<endl;
        logfile.close();
 
        return 0;
}
