/*
 * Copyright (C) 2012 The X-Live Project
 *
 * @author Richard Luo, cdominant7@gmail.com
 * @date   2012-09-25 11:00:01
 * 
 * 
 ****************************************************************** 
 */

#define LOG_TAG "coho_list_test"

#include <Base/List.h>
#include <stdio.h>
#include <utils/RefBase.h>
#include <utils/Log.h>

using namespace android;

struct Employee : public android::RefBase {
    TLink<Employee> mEmployeeLink;
    TLink<Employee> mManagerLink;
    unsigned        mSalary;
    const char      *mName;

    Employee(const char *name)
            : mSalary(0)
            , mName(name) {
    }
    
    void show() const {
        LOGFL("name:%s salary:%d", mName, mSalary);
    }

    virtual ~Employee() {
        LOGFL("--> ~Employee(), name:%s", mName);
    }
};

struct Manager : Employee {
    LIST_DECLARE(Employee, mManagerLink) mStaffList;

    Manager(const char *name)
            : Employee(name) {
    }

};

LIST_DECLARE(Employee, mEmployeeLink) s_employees;

static void normal_test() {
    // Hire Joe, a cashier
    sp<Employee> joe  = new Employee("joe");
    joe->mSalary     = 50 * 1000;
    s_employees.InsertTail(joe.get());

    // Hire Sally, a shift Manager
    sp<Manager> sally = new Manager("sally");
    sally->mSalary   = 80 * 1000;
    s_employees.InsertTail(sally.get());
    sally->mStaffList.InsertTail(joe.get());

    Employee *e = s_employees.Head();
    for (; e != NULL; e = s_employees.Next(e)) {
        e->show();
    }

    // Oops, Joe got caught with his hand in the till
    // delete joe;
    joe.clear();

    // Now that Joe is gone, Sally has no reports
    assert(sally->mStaffList.Empty());

    // And she is now the only Employee
    assert(s_employees.Head() == sally.get());
    assert(s_employees.Tail() == sally.get());

    printf("OK \n");
}

int main(int argc, char *argv[])
{
    normal_test();
    printf("offsetof(Employee, mManagerLink):%d \n", offsetof(Employee, mManagerLink));

    return 0;
}
