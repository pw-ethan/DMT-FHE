#ifndef TASK_H
#define TASK_H

class CTask
{
public:
    int i;

    CTask(int i_ = 0) : i(i_) { }
    int operator() () {
        return i * 2;
    }
};

#endif // TASK_H
