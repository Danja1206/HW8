#include <iostream>
#include <exception>
#include <string>

using namespace std;

int FIELD_SIZE = 10;

struct Pos
{
    int x, y;
};

enum class Direction
{
    UP, DOWN, LEFT, RIGHT, other
};

class OffTheField : public exception
{
public:
    OffTheField(Pos pos, Direction direct)
    {
        error = " Позиция - ";
        error += " x: ";
        error += to_string(pos.x);
        error += ";";
        error += " y: ";
        error += to_string(pos.y);
        error += " - направление движения: ";
        switch (direct)
        {
        case Direction::UP:
            error += "вверх";
            break;
        case Direction::DOWN:
            error += "вниз";
            break;
        case Direction::LEFT:
            error += "влево";
            break;
        case Direction::RIGHT:
            error += "вправо";
            break;
        default:
            break;
        }
    }

    ~OffTheField() {}

    const char* what() const noexcept { return error.c_str(); };

private:
    string error;
};

class IllegalCommand : public exception
{
public:
    IllegalCommand() {}
};

class Robot
{
public:
    Robot() : currentPosition{} {}
    
    ~Robot() {}

    void move(Direction direct)
    {
        switch (direct)
        {
        case Direction::UP:
            if (--currentPosition.y < 0)
            {
                ++currentPosition.y;
                throw OffTheField(currentPosition, direct);
            }
            break;
        case Direction::DOWN:
            if (++currentPosition.y >= FIELD_SIZE)
            {
                --currentPosition.y;
                throw OffTheField(currentPosition, direct);
            }
            break;
        case Direction::LEFT:
            if (--currentPosition.x < 0)
            {
                ++currentPosition.x;
                throw OffTheField(currentPosition, direct);
            }
            break;
        case Direction::RIGHT:
            if (++currentPosition.x >= FIELD_SIZE)
            {
                --currentPosition.x;
                throw OffTheField(currentPosition, direct);
            }
            break;
        default: throw IllegalCommand();
            break;
        }
    }
    void print()
    {
        for (int i = 0; i < FIELD_SIZE; i++)
        {
            for (int j = 0; j < FIELD_SIZE; j++)
            {
                if (j == currentPosition.x && i == currentPosition.y) cout << "R";
                else cout << "_";
            }
            cout << endl;
        }
    }

private:
    Pos currentPosition;
};



int main()
{
    setlocale(LC_ALL, "rus");
    Robot rbt;
    char c;
    do
    {
        rbt.print();
        cin >> c;
        try
        {
            switch (c)
            {
            case 'd':
            case 'D':
                rbt.move(Direction::RIGHT);
                break;
            case 'a':
            case 'A':
                rbt.move(Direction::LEFT);
                break;
            case 'w':
            case 'W':
                rbt.move(Direction::UP);
                break;
            case 's':
            case 'S':
                rbt.move(Direction::DOWN);
                break;
            case 'e':
            case 'E':
                break;
            default:
                rbt.move(Direction::other);
            }
        }
        catch (OffTheField& ex)
        {
            cerr << "Попытка покинуть поле!" << ex.what() << endl;
       
        }
        catch (IllegalCommand& ex)
        {
            cerr << "Неизвестное направление" << endl;
        }
        catch (...)
        {
            cerr << "Ошибка" << endl;
        }
    } while (c != 'e' && c != 'E');
}

