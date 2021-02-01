#include <iostream>
#include <fstream>
#include <memory>

class line_writer
{
    private:
        std::ofstream* file;
    public:
        line_writer()
        {
            file=new std::ofstream();
            file->open("sample.txt");
        }
        void write(std::string mess){*file<<mess;}
        ~line_writer(){file->close();}
};

void fun(std::shared_ptr<line_writer>& s)
{
    std::shared_ptr<line_writer> sx(s);
    sx->write("shared_ptr from fun\n");
}

int main()
{
    std::shared_ptr<line_writer> sp1(new line_writer());
    std::shared_ptr<line_writer> sp2(sp1);
    std::shared_ptr<line_writer> sp3(sp2);
    sp1->write("shared_ptr1 from main\n");
    sp2->write("shared_ptr2 from main\n");
    fun(sp2);
    sp3->write("shared_ptr3 from main\n");
    sp1.~__shared_ptr();
    sp2->write("shared_ptr2 again from main\n");
    sp2.~__shared_ptr();
    sp3->write("shared_ptr3 again from main\n");
    sp3.~__shared_ptr();
}