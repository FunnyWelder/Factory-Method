#include <iostream>

using namespace std;

enum COLOR {GREEN, BLUE, BLACK, ORANGE};

string getColor(COLOR color) {
    switch (color) {
        case GREEN: return "GREEN";
        case BLUE: return "BLUE";
        case BLACK: return "BLACK";
        case ORANGE: return "ORANGE";
    }
}

class Figure {
private:
    float x0;
    float y0;
    COLOR color;

public:
    Figure(float x0, float y0, COLOR color) {
        this->x0=x0;
        this->y0=y0;
        this->color=color;
    }
    virtual ~Figure() {};
    virtual string Operation() const = 0;

    const float &getx0() const {
        return x0;
    }
    const float &gety0() const {
        return y0;
    }
    const COLOR &getcol() const {
        return color;
    }
};

class Circle : public Figure {
private:
    float R1;
public:
    Circle(float x0, float y0, float R1, COLOR color) : Figure(x0, y0, color) {
        this->R1=R1;
    }
    string Operation() const override {
        return (string("Круг ") + string("координаты: ") + to_string(getx0()) + ", " + to_string(gety0()) + ' ' + string("радиус: ") + to_string(R1) + ' ' + string("цвет: ") + getColor(getcol()));
    }
};

class Square : public Figure {
private:
    float x1;
    float y1;
public:
    Square(float x0, float y0, float x1, float y1, COLOR color) : Figure(x0, y0, color) {
        this->x1=x1;
        this->y1=y1;
    }
    string Operation() const override {
        return (string("Квадрат ") + string("координаты: ") + to_string(getx0()) + ", " + to_string(gety0()) + ", " + to_string(x1) + ", " + to_string(y1) + ' ' + string("цвет: ") + getColor(getcol()));
    }
};

class Draw {
public:
    virtual ~Draw(){};
    virtual Figure* FactoryMethod() const = 0;

    string SomeOperation() const {
        Figure* figure = this->FactoryMethod();
        string result = "это " + figure->Operation();
        delete figure;
        return result;
    }
};

class DrawCircleOrangeSmall : public Draw {
public:
    Circle *FactoryMethod() const override {
        return new Circle(1.0, 1.0, 5.0, ORANGE);
    }
};

class DrawCircleGreenBig : public Draw {
public:
    Circle *FactoryMethod() const override {
        return new Circle(0.0, 0.0, 20.0, GREEN);
    }
};

class DrawSquareBlackMedium : public Draw {
public:
    Square* FactoryMethod() const override {
        return new Square(1.1, 1.1, 4.4, 4.4, BLACK);
    }
};

class DrawSquareBlueSmall : public Draw {
public:
    Square* FactoryMethod() const override {
        return new Square(0.0, 0.0, 1.1, 1.1, BLUE);
    }
};

void ClientCode(const Draw& creator) {
    cout << "Фигура - " << creator.SomeOperation() << endl;
}


int main() {
    Draw* creator = new DrawCircleOrangeSmall();
    ClientCode(*creator);cout << endl;

    Draw* creator2 = new DrawCircleGreenBig();
    ClientCode(*creator2);cout << endl;

    Draw* creator3 = new DrawSquareBlackMedium();
    ClientCode(*creator3);cout << endl;

    Draw* creator4 = new DrawSquareBlueSmall();
    ClientCode(*creator4);cout << endl;

    delete creator;
    delete creator2;
    delete creator3;
    delete creator4;
    return 0;
}
