//
// Created by gaojinliang on 2023/1/8.
//
#include <string>
#include <iostream>

using namespace std;

struct Student {
private:
    int age;
    string name;

public:
    Student(int _age, string _name) : age(_age), name(move(_name)) {}

    int getAge() const {
        return age;
    }

    void setAge(int _age) {
        this->age = _age;
    }

    const string &getName() const {
        return name;
    }

    void setName(const string &_name) {
        Student::name = _name;
    }

    virtual ~Student() = default;
};
int main(){
    auto s = new Student(1,"fadsf");
    s->getName();
    s->setName("fadsfdd");
    cout<<""<<s->getAge()<<endl;
}