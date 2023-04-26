#ifndef COMPLEX_COMPLEX_H
#define COMPLEX_COMPLEX_H
#include <iostream>
#include <math.h>

// Helper:   a+bi / m+ni
// REAL:    (am + bn) / (m^2 + n^2)
// IMAG:    (mb - an)/ (m^2 + n^2)

using namespace std;

void zero_check(const double arg)
{
    if(arg == 0)
    {
        cout << "Dzielenie przez 0!\n";
        exit(1);
    }
}


double convert(const double radian)
{
    return(radian * (180/M_PI));
}


double real_part(const double re, const double im, const double y_re, const double y_im)
{
    double licznik, mianownik;

    licznik = (re * y_re) + (im * y_im);
    mianownik = pow(y_re, 2) + pow(y_im, 2);
    zero_check(mianownik);

    return licznik / mianownik;
}


double imag_part(const double re, const double im, const double y_re, const double y_im)
{
    double licznik, mianownik;

    licznik = (y_re * im) - (re * y_im);
    mianownik = pow(y_re, 2) + pow(y_im, 2);
    zero_check(mianownik);

    return licznik / mianownik;
}

class Complex
{
    private:
        double Real, Imag;


    public:
        Complex(double Re=0, double Im=0) : Real(Re), Imag(Im){};


        Complex& operator=(const Complex& s)
        {
            Real = s.Real;
            Imag = s.Imag;
            return *this;
        };


        Complex operator-() const
        {
            return Complex(-Real, -Imag);
        };


        Complex& operator=(double co)
        {
            Real = co;
            Imag = 0;
            return *this;
        };


        Complex operator+(const Complex& co) const
        {
            Complex n;
            n.Real = this->Real + co.Real;
            n.Imag = this->Imag + co.Imag;
            return n;
        };


        Complex& operator-=(Complex co)
        {
            Real -= co.Real;
            Imag -= co.Imag;
            return *this;
        };


        Complex operator/(const Complex& y) const
        {
            Complex x;

            x.Real = real_part(this->Real, this->Imag, y.Real, y.Imag);
            x.Imag = imag_part(this->Real, this->Imag, y.Real, y.Imag);

            return x;
        };


        Complex& operator/=(const Complex y)
        {
            double Re, Im;

            Re = real_part(this->Real, this->Imag, y.Real, y.Imag);
            Im = imag_part(this->Real, this->Imag, y.Real, y.Imag);

            this->Imag = Im;
            this->Real = Re;

            return *this;
        };


        double phase() const
        {	
			double rad = atan2(this->Imag, this->Real);
			if(this->Imag < 0)
				rad += 2*M_PI;
				
			return convert(rad);
        }


        double abs() const
        {
            return sqrt(pow(this->Real,2) + pow(this->Imag, 2));
        }


        void conj()
        {
            this->Imag = this->Imag * (-1);
        }


        friend Complex operator-(Complex, Complex);
        friend ostream& operator<<(ostream& s, const Complex& c)
        {
            s << "(" << c.Real << ", " << c.Imag << ")";
            return s;
        };
};


inline Complex operator-(Complex s1, Complex s2)
{
    Complex n(s1);
    return n -= s2;
}


inline Complex operator/(const double val, const Complex y)
{
    Complex x(val);

    return x / y;
}


#endif
