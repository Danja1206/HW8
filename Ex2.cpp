#include <iostream>
#include <exception>

using namespace std;

class Ex
{
public:
    Ex(double _x) : x(_x) {}

    double what() const noexcept { return x; };

private:
    double x;
};

class Bar
{
public:
    Bar() : y(0) {}

    void set(double a)
    {
        if (y + a > 100) throw Ex(a * y);
        else y = a;
    }

private:
    double y;
};

int main()
{
    setlocale(LC_ALL, "rus");
    Bar bar;
    double n;
    try
    {
        do
        {
            cin >> n;
            bar.set(n);
            cout << endl;

        } while (n != 0);
    }
    catch (Ex& ex)
    {
        cerr << "Ошибка: Ex с параметром - " << ex.what() << endl;
    }
    catch (...)
    {
        cerr << "Ошибка" << endl;
    }
}

