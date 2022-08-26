#include <iostream>

struct Expression
{
    virtual double evaluate() const = 0;
    ~Expression() 
    {

    };
};

struct Number : Expression
{
    Number(double value) : value(value) {}
    ~Number() 
    {

    };
    double evaluate() { 
        return value; 
    }
    virtual double evaluate() const { 
        return value; 
    }

private:   
    double value;
};

struct BinaryOperation : Expression
{
    BinaryOperation(Expression const* left, char op, Expression const* right)
        : left(left), op(op), right(right)
    { }
    virtual double evaluate() const {
        if (op == '+') {
            return (left->evaluate() + right->evaluate());
        }
        else 
            if (op == '-') {
            return (left->evaluate() - right->evaluate());
        }
        else 
                if (op == '*') {
            return (left->evaluate() * right->evaluate());
        }
        else 
                    if (op == '/') {
            return (left->evaluate() / right->evaluate());
        }

    }

    ~BinaryOperation() {
        delete left;
        delete right;
    }

private:
    Expression const* left;
    Expression const* right;
    char op;
};



bool check_equals(Expression const* left, Expression const* right)
{
    return (*((size_t*)left) == *((size_t*)right));
}

void task56() {
    Expression* sube = new BinaryOperation(new Number(4.5), '*', new Number(5));
    Expression* expr = new BinaryOperation(new Number(3), '+', sube);
    std::cout << expr->evaluate() << std::endl;
    Expression* kek = new BinaryOperation(new BinaryOperation(new Number(4.5), '*', new Number(5)), '*', new BinaryOperation(new Number(4.5), '*', new Number(5)));
    std::cout << kek->evaluate() << std::endl;
    std::cout << check_equals(kek, expr);

}


int main() {
    task56();
}