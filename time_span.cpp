#include <iostream>
#include <cmath> //to use the round function
#include "time_span.h"
using namespace std; 

        //constructors
        TimeSpan::TimeSpan( double hr, double min, double sec){
            CalculateTimeSec(hr,min,sec);
            ConvertTime(TimeInSec());
        };
        TimeSpan::TimeSpan( double min,  double sec){
            CalculateTimeSec(min,sec);
            ConvertTime(TimeInSec());
        }
        TimeSpan::TimeSpan( double sec){
            CalculateTimeSec(sec);
            ConvertTime(TimeInSec());
        }
        TimeSpan::TimeSpan(){
            hour_ = 0;
            minutes_ = 0;
            seconds_ = 0;
        }
        //getters
        int TimeSpan:: hours() const{
            return hour_;
        }
        int TimeSpan:: minutes() const{
            return minutes_;
        } 
        int TimeSpan:: seconds()const{
            return seconds_;
        } 
        double TimeSpan::TimeInSec(){
            return time_in_seconds_;
        };

        //setters
        void TimeSpan::set_time( int hours, int minutes, int seconds){
               CalculateTimeSec(hours, minutes, seconds);
               ConvertTime(TimeInSec());
        }

        void TimeSpan::set_hours(double hrs){
            CalculateTimeSec(hrs, minutes(), seconds());
            ConvertTime(TimeInSec());
        }

        void TimeSpan::set_minutes(double mins){
            CalculateTimeSec(hours(), mins, seconds());
            ConvertTime(TimeInSec());
        } 

        void TimeSpan::set_seconds(double seconds){
            CalculateTimeSec(hours(), minutes(), seconds);
            ConvertTime(TimeInSec());
        } 
        

        //operator overloads
        ostream& operator << (ostream& out, const TimeSpan& duration){
            return out<<"Hours: "<< duration.hours() << ", Minutes: "<< duration.minutes() <<", Seconds: "<< duration.seconds();
        }
         istream& operator >> (istream& in, TimeSpan& duration){
            cout<<"Input hours, minutes, and seconds: ";
            int hrs;
            int mins;
            int secs;
            in>>hrs>>mins>>secs;
            //Do conversion to get proper time
            duration.CalculateTimeSec(hrs,mins,secs);
            duration.ConvertTime(duration.TimeInSec());
            return in;
        }
        
        TimeSpan& TimeSpan::operator += ( const TimeSpan& duration){
            double hrs = hours() + duration.hours(); 
            double mins = minutes() + duration.minutes(); 
            double secs = seconds()+ duration.seconds();
            CalculateTimeSec(hrs,mins,secs);
            ConvertTime(TimeInSec());
            return *this;
        }
        TimeSpan TimeSpan::operator + (const TimeSpan& duration) const{
            TimeSpan result = *this;
            result += duration;
            return result;
        }

        TimeSpan& TimeSpan::operator -= (const TimeSpan& duration) {
            double hrs = hours() - duration.hour_; 
            double mins = minutes() - duration.minutes_; 
            double secs = seconds() - duration.seconds_;
            //update hours, minutes, and seconds
            CalculateTimeSec(hrs,mins,secs);
            ConvertTime(TimeInSec());
            return *this;
        }

        TimeSpan TimeSpan::operator - (const TimeSpan& duration) const{
            TimeSpan result = *this;
            result -= duration;
            return result;
        }
        TimeSpan TimeSpan::operator-() const{
            return TimeSpan(-hour_, -minutes_, -seconds_);
        }
        
        bool TimeSpan::operator < (TimeSpan& duration) const{
            if (hours()<duration.hours()){
                return true;
            } else if (hours()>duration.hours()){
                return false;
            } else if(minutes() < duration.minutes()){
                return true;
            } else if (minutes()>duration.minutes()){
                return false;
            } else if (seconds()< duration.seconds()){
                return true;
            }else{
                return false;
            }
        }
            
        bool TimeSpan::operator > (TimeSpan& duration) const{
            if (hours()>duration.hours()){
                return true;
            } else if (hours()<duration.hours()){
                return false;
            } else if(minutes() > duration.minutes()){
                return true;
            } else if (minutes()<duration.minutes()){
                return false;
            } else if (seconds()> duration.seconds()){
                return true;
            }else{
                return false;
            }
        }

        bool TimeSpan::operator >= (const TimeSpan& duration) const{
            if (hours()>=duration.hours()){
                return true;
            } else if (hours()<duration.hours()){
                return false;
            } else if(minutes() >= duration.minutes()){
                return true;
            } else if (minutes()<duration.minutes()){
                return false;
            } else if (seconds()>= duration.seconds()){
                return true;
            }else{
                return false;
            }
        }

        bool TimeSpan::operator <= (const TimeSpan& duration) const{
            if (hours()<=duration.hours()){
                return true;
            } else if (hours()>duration.hours()){
                return false;
            } else if(minutes() <= duration.minutes()){
                return true;
            } else if (minutes()>duration.minutes()){
                return false;
            } else if (seconds()<= duration.seconds()){
                return true;
            }else{
                return false;
            }
        }

        bool TimeSpan::operator != (const TimeSpan& duration) const{
            if (hours() == duration.hours()){
                return false;
            } else if (minutes() == duration.minutes()){
                return false;
            } else if (seconds() == duration.seconds()){
                return false;
            }
            return true;
        }

        bool TimeSpan::operator == (const TimeSpan& duration) const{
            if (hours() != duration.hours()){
                return false;
            } else if (minutes() != duration.minutes()){
                return false;
            } else if (seconds() != duration.seconds()){
                return false;
            }
            return true;
        }
        //private functions/methods
        void TimeSpan::CalculateTimeSec(double hr, double min, double sec){
            time_in_seconds_ = hr*3600+ min*60 + sec;
        }
        void TimeSpan::CalculateTimeSec(double min, double sec){
            time_in_seconds_ = min*60 + sec;
        }
        void TimeSpan::CalculateTimeSec(double sec){
            time_in_seconds_ = sec;
        }

        void TimeSpan::ConvertTime(double secs){
            hour_ = (int)secs/3600;
            double carry_over=((secs/3600) - hour_) * 60;
            minutes_ = (int) carry_over;
            carry_over = carry_over - minutes_;
            seconds_ = round(carry_over*60);
            //if we round and 60 seconds are leftover we need to handle this edge case
            if (seconds_ == 60){
                minutes_+=1;
                seconds_ =0;
            } else if (seconds_==-60){
                minutes_-=1;
                seconds_=0;
            }

        }