#include <iostream> 
#include "time_span.h" 
using namespace std; 
 
int main() 
{  
TimeSpan dur1(77.4, 15, 6), dur2(127.86), dur3(8, -23, 0), dur4(0, 0, 0); 
TimeSpan dur5(-3, 73, 2), dur6(7, 35, 120), dur7, dur8, dur9(7,-3), dur10(-190), dur11(3,-90,120);
TimeSpan dur12(1, -64.5, -60.5), dur13(50), dur14(9, 9, 9), dur15(-100,100,10), dur16(4, 3, 22), dur17(1,1,1);

 dur7 = dur1 + dur3; 
 cout << dur1 << endl; 
 cout << dur2 << endl; 
 cout << dur3 << endl; 
 cout << dur4 << endl; 
 cout << dur5 << endl; 
 cout << dur6 << endl; 
 cout<<dur8<<endl;
 cout<<endl;
 cout<<"Dur7 and Dur3 tests"<<endl;
 cout << dur7 << endl; 
 dur7 += dur3; 
 cout << dur3 << endl; 
 cout << dur7 << endl; 
 dur7-=dur3;
 cout << dur7 << endl; 
 cout<<endl;
 cout<<"Before change: "<<endl;
 cout<<dur13<<endl;
 cout<<"After change: "<<endl;
 dur13.set_time(5,-900,20);
 cout<<dur13<<endl;
 cout<<endl;
 if (dur3 != dur6) 
 { 
  cout << "Durations are different." << endl; 
 } 
 else if (dur3 == dur6)
 { 
  cout << "Durations are the same" << endl;  
 } 

 if (dur1 > dur10) 
 { 
  cout << "Duration 1 is greater." << endl; 
 } 
cout<<endl;
cout<<"dur12: ";
cout<<dur12<<endl;
cout<<"dur13: ";
cout<<dur13<<endl;

if (dur13 < dur12)
 { 
  cout << "Durations 13 is less" << endl;  
 } 
cout<<endl;
cout<<"dur14 - "<<dur14<<endl;
cout<<"dur15 - "<<dur15<<endl;
 if (dur14>= dur15){
    cout<<"Dur14 greater than or equal"<<endl;
 }
 if (dur14<= dur15){
    cout<<"Dur14 less than or equal"<<endl;
 }
 cout<<endl;
 cout<<"dur14 set time testing"<<endl;
 cout<<"original- " << dur14<<endl;
 dur14.set_hours(14);
 cout<<dur14<<endl;
 dur14.set_minutes(61);
 cout<<dur14<<endl;
 dur14.set_seconds(90);
 cout<<dur14<<endl;

cout<<endl;
cout<<"negative test"<<endl;
cout<<-dur14<<endl;
cout<<dur14<<endl;
dur13 = -dur14;
cout<<dur13<<endl;
cout<<endl;
cout<<dur17<<endl;
dur17 = dur17 + dur17;
cout<<dur17<<endl;

 return 0;
} 
 