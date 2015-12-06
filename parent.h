#ifndef _PARENT_H_
#define _PARENT_H_

_Task Parent {
    private:
        unsigned int _numStudents;
        unsigned int _parentalDelay;
        Printer& _prt;
        Bank& _bank;
        void main();
    public:
        Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay );
};

#endif
