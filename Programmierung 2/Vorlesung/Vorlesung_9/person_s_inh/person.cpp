#include <iostream>

using namespace std;

const int na = 30;
const int sg = 20;

class person { char name[na];
	       int  jahr;
  public:
	person(char n[na]="", int j=2005):jahr(j){
	    strncpy_s(name,sizeof(name),n,sizeof(name)-1); 
	}
	virtual void dummy(){} //wegen dynamic_cast<student *>

	int get_jahr() const { return jahr; }
	const char * const get_name() const { return name; }
};

class student : public person {
	unsigned long matrnr;
	char studg[sg];
  public:
	student(char n[na]="", int j=2005, 
	unsigned long m=4711, 
	char s[sg]="WI04"): person(n, j), matrnr(m){
	  strncpy_s(studg, sizeof(studg), s, sizeof(studg)-1); 
	}
	unsigned long get_matrnr() const { return matrnr; }
	const char * const get_studg() const { 
		return studg; 
	}
};

void main(){
	person *p1 = new student("Lehmann", 1984, 22337, "WI07");
	cout<<"p1->jahr   = "<<p1->get_jahr()<<endl;
	cout<<"p1->name   = "<<p1->get_name()<<endl;
	cout<<"p1->matrnr = "<<((student *)p1)->get_matrnr()<<endl;           //unsafe, true
	cout<<"p1->studg  = "<<static_cast<student *>(p1)->get_studg()<<endl; //unsafe, true

	person *p2 = new person("Schulze", 1964);
	cout<<"p2->jahr   = "<<p2->get_jahr()<<endl;
	cout<<"p2->name   = "<<p2->get_name()<<endl;
	cout<<"p2->matrnr = "<<((student *)p2)->get_matrnr()<<endl;           //unsafe, false
	cout<<"p2->studg  = "<<static_cast<student *>(p2)->get_studg()<<endl; //unsafe, false

	cout<<"p1->studg  = "<<(dynamic_cast<student *>(p1) ?
		                    dynamic_cast<student *>(p1)->get_studg():
		                    "unzulaessiger Downcast")<<endl;             //safe, true

	try { dynamic_cast<student &>(*p2);					//alternativ nur mit Referenz !
	      cout<<"p2->studg  = "<<dynamic_cast<student *>(p2)->get_studg()<<endl;
	}
	catch(...){
		  cout<<"p2->studg  = "<<"unzulaessiger downcast"<<endl;		//safe, false
	}

	delete p1; p1=0; delete p2; p2=0;
	cin.ignore();
}

/* 
p1->jahr   = 1984
p1->name   = Lehmann
p1->matrnr = 22337
p1->studg  = WI07
p2->jahr   = 1964
p2->name   = Schulze
p2->matrnr = 4261281277       //false
p2->studg  = ½½½½½½½½¯■¯■     //false
p1->studg  = WI07
p2->studg  = unzulaessiger downcast
*/

