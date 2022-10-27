#include <string>
class Lable
{
    public:
    int x;
    int y;
    std::string text;
    
    public:
    Lable(int x, int y, std::string txt);
    void draw() const;
};
