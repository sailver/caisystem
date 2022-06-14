#ifndef CBASIC_H
#define CBASIC_H
#include <string>
using namespace std;

class CourseBasic {
    public:
        friend ostream& operator<<(ostream& out, CourseBasic &courseBasic);
        friend istream& operator>>(istream& in, CourseBasic &courseBasic);
        friend bool operator==(CourseBasic a, CourseBasic b);
        void setId(int id){this->id = id;};
        void SetName(string name);
        void SetTeacher(string teacher);
        void SetDay(int day);
        void SetPeriod(int time);
        void SetType(string time);
        void SetDuration(int duration);
        void SetLocation(string location);
        void SetWeek(int week);
        int GetId();
        string GetName();
        string GetTeacher();
        string GetNameP();
        string GetTeacherP();
        int GetDay();
        int GetPeriod();
        string GetType();
        int GetDuration();
        string GetLocation();
        int GetWeek();
        int GetCourseDetailId();
        string TranslateWeek();
        CourseBasic(){};
        CourseBasic(int id,
                    string name,
                    string teacher,
                    int day,
                    int period,
                    string type,
                    int duration,
                    string location,
                    int week,
                    int courseDetailId
                    );
    private:
        int id;
        string name;
        string nameP;
        string teacher;
        string teacherP;
        int day;
        int period;
        string type;
        int duration;
        string location;
        int week; // 32位保存上课周数(1~32周)，如串 0···0101 表示第一周和第三周有课
        int courseDetailId;
};
#endif
