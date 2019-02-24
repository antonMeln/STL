# STL
// ConsoleApplication12.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Student
{
     string Name;
     string GroupId;
     map< string, unsigned> Ratings;
    
    Student( string Name,  map< string, unsigned> Ratings) {
        this->Name = Name;
        this->Ratings = Ratings;
    }
  
    float adv(){
        float summ = 0;
        for(auto i = Ratings.begin() ; i != Ratings.end() ; ++i){
            summ += (*i).second;
        }
        return summ / Ratings.size();
    }
    bool bad_result(){
        for(auto i = Ratings.begin() ; i != Ratings.end() ; ++i){
            if((*i).second <=2 ){
                return true;
            }
        }
        return false;
    }
    bool exams_result(){
        bool result = false;
        for(auto i = Ratings.begin() ; i != Ratings.end() ; ++i){
            if((*i).second == 5) result = true;
            else {
                result = false;
                break;
            }
    }
        return result;
    }
    bool good_math() {
        if (this->Ratings["Math"] == 5) {
            return true;
        }
        return false;
    }
    
    void get_mark()
    {
        Ratings["Political"] = 5;
    }
    
};

void print(const Student &s){
     cout<<s.Name<<'\n';
    for (auto it = s.Ratings.begin(); it != s.Ratings.end(); ++it) {
         cout<<it->first<<":"<<it->second<<'\n';
    }
 cout<<'\n'<<'\n';
}


int main (){
    Student v1("Melnikov", {{"Math",3},{"Political",2},{"French",5}});
	Student v2("Maximov",{{"Math",5},{"Political",3},{"French",5}});
	Student v3("Litvinov",{{"Math",5},{"Political",5},{"French",5}});
     vector<Student> students {v1,v2,v3};
    
     cout<<"#1"<<'\n'; // по алфавиту
     sort(students.begin(), students.end(), [](const Student a,const Student b){
        return (a.Name.compare(b.Name)<0);
    });
     for_each(students.begin(), students.end(), print);
    
     cout<<"#2"<<'\n'; // по результатам
     sort(students.begin(), students.end(), []( Student a, Student b){
        return (a.adv() > b.adv());
    });
     for_each(students.begin(), students.end(), print);
    
     cout<<"#3"<<'\n'; // количество неудов
    unsigned long c = 0;
    c =  count_if(students.begin(), students.end(),[](Student a){
        return (a.bad_result());
    });
     cout<<c<<'\n';
    
     cout<<"#4"<<'\n'; // количество отличников
    unsigned long a = 0;
    a =  count_if(students.begin(), students.end(),[](Student a){
        return (a.exams_result());
    });
     cout<<a<<'\n';
    
     cout<<"#5"<<'\n'; // студенты с хорошей математикой 
     vector<Student> target;
     copy_if(students.begin(),students.end(), back_inserter(target), [](Student a){
        return a.good_math();
    });
     for_each(target.begin(), target.end(),print);
    
     cout<<"#6"<<'\n'; // отличники по политлогии,замена оценок (преобразование исходного вектора в вектор отличников по политологии)
     transform(students.begin(), students.end(), students.begin(), [](Student a){
        a.get_mark();
        return a;
    });
     for_each(students.begin(), students.end(), print);
    return 0;
}
