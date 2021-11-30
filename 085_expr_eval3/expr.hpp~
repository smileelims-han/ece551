#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

//eval 1

class Expression {
 public:
  virtual string toString() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression {
 private:
  long n;

 public:
  NumExpression(long i) : n(i) {}
  virtual string toString() const {
    stringstream out;
    out << n;
    return out.str();
  }
  virtual ~NumExpression() {}
};

class PlusExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  PlusExpression(Expression * l, Expression * r) : lhs(l), rhs(r) {}
  virtual string toString() const {
    stringstream out;
    out << "(" << lhs->toString() << "+" << rhs->toString() << ")";
    return out.str();
  }
  virtual ~PlusExpression() {
    delete lhs;
    delete rhs;
  }
};

//eval 2

class MinusExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  MinusExpression(Expression * l, Expression * r) : lhs(l), rhs(r) {}
  virtual string toString() const {
    stringstream out;
    out << "(" << lhs->toString() << "-" << rhs->toString() << ")";
    return out.str();
  }
  virtual ~MinusExpression() {
    delete lhs;
    delete rhs;
  }
};

class TimesExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  TimesExpression(Expression * l, Expression * r) : lhs(l), rhs(r) {}
  virtual string toString() const {
    stringstream out;
    out << "(" << lhs->toString() << "*" << rhs->toString() << ")";
    return out.str();
  }
  virtual ~TimesExpression() {
    delete lhs;
    delete rhs;
  }
};

class DivExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  DivExpression(Expression * l, Expression * r) : lhs(l), rhs(r) {}
  virtual string toString() const {
    stringstream out;
    out << "(" << lhs->toString() << "/" << rhs->toString() << ")";
    return out.str();
  }
  virtual ~DivExpression() {
    delete lhs;
    delete rhs;
  }
};
