#include <iostream>
#include <exception>

using namespace std;

class DivisionByZero : public exception
{
public:
    DivisionByZero(const string& _error = "Division by zero!") : error(_error) {}

    const char* what() const noexcept { return error.c_str(); }
private:
    string error;
};

template<typename T>
double div(T _first, T _second)
{
    if (_second == 0) throw DivisionByZero();
    return static_cast<double>(_first) / _second;
}

int main()
{
    int a, b;
    double A, B, result;
    try
    {
        cin >> a;
        cin >> b;
        result = div<int>(a, b);
        cout << a << "/" << b << " = " << result << endl;

        cin >> A;
        cin >> B;
        result = div<double>(A, B);
        cout << A << "/" << B << " = " << result << endl;
    }
    catch (exception& exception)
    {
        cerr << "Ошибка: " << exception.what() << endl;
    }
    catch (...)
    {
        cerr << "Ошибка" << endl;
    }
}

