#ifndef TIME_SPAN_H
#define TIME_SPAN_H
#include <iostream>
using namespace std;

class TimeSpan{
    public:
        //constructors
        TimeSpan(double hr, double min,  double sec);
        TimeSpan(double min,  double sec);
        TimeSpan(double sec);
        TimeSpan();

        //getters and setters
        int hours() const; 
        int minutes() const; 
        int seconds()const; 
        double TimeInSec();
        void set_time(int hours, int minutes, int seconds);
        void set_hours(double hrs); 
        void set_minutes(double mins); 
        void set_seconds(double seconds); 


        //operator overloads
        friend ostream& operator << (ostream& out, const TimeSpan& obj);
        friend istream& operator >> (istream& in, TimeSpan& obj);
        TimeSpan operator + (const TimeSpan& obj) const;
        TimeSpan operator - (const TimeSpan& obj) const;
        TimeSpan operator-() const; 
        TimeSpan& operator += (const TimeSpan& obj);
        TimeSpan& operator -= (const TimeSpan& obj);
        bool operator == (const TimeSpan& obj) const;
        bool operator != (const TimeSpan& obj) const;
        bool operator >= (const TimeSpan& obj) const;
        bool operator <= (const TimeSpan& obj) const;
        bool operator < (TimeSpan& obj) const;
        bool operator > (TimeSpan& obj) const;

    private:
        int hour_;
        int minutes_;
        int seconds_;
        double time_in_seconds_;

        //overloaded to address all constructor types
        void CalculateTimeSec(double hr, double min, double sec);
        void CalculateTimeSec(double min, double sec);
        void CalculateTimeSec(double sec);
        //turns time into hours, minutes, and seconds
        void ConvertTime(double secs); 
        
};
#endif