#include "Vector.h"
#include <cstddef>
#include "general.h"
#include <iostream>
#include <math.h>
using namespace std;
//------------------------------ Implemenation  -----------------------------
Vector::Vector()
{
	size=0;
	buf=NULL;
}


Vector::Vector(int s)
{
	size=s;
	buf=new double[s];
}


Vector::Vector(const Vector& a)
{
	this->size = a.size;
	this->buf = new double[a.size];
	for(int i = 0;i < a.size;i++)
	this->buf[i]=a.buf[i];
}


Vector::~Vector()
{
	size=0;
	if (buf) delete[] buf;
	buf=NULL;
}


//Operator overloading


Vector& Vector::operator = (const Vector& B)
{
	if(this == &B) return *this;
	if(this->buf) delete[] buf;
	this->size = B.size;
	this->buf = new double[B.size];
	for(int i = 0;i < B.size;i++)
	this->buf[i] = B.buf[i];
	return *this;
}


bool Vector::operator ==(const Vector& B)
{
	if(this->size != B.size) return false;
	for(int i = 0;i < size;i++)
	if(buf[i] != B.buf[i]) return false;
	return true;
}


bool Vector::operator !=(const Vector& B)
{
	return !(*this == B);
}


Vector Vector::operator +(const Vector& B)
{
	Vector tmp(size);
	for(int i=0;i < size; i++)
		tmp.buf[i] = buf[i] + B.buf[i];
	return tmp;
}


Vector Vector::operator -(const Vector& B)
{
        Vector tmp(size);
        for(int i=0;i<size;i++)
                tmp.buf[i]=buf[i]-B.buf[i];
	return tmp;
}


Vector Vector::operator *(double a) //vector A*a
{
        Vector tmp(size);
        for(int i = 0;i <size; i++)
                tmp.buf[i] = buf[i]*a;
	return tmp;
}


double Vector::operator *(const Vector& B) //dot product
{
	if(size != B.size || size == 0)
	{
		cout << "Wrong size" << endl;
		return 0.0;
	}
	double x = 0;
        for(int i = 0;i < size; i++)
		x = x + buf[i] * B.buf[i];
	return x;
}


double& Vector::operator [](int i)//A[i];
{
	if( i< 0||i >= size)
	{
		cout<< "Invalid" <<endl;
		return buf[0];
	}
	return buf[i]; //unsafe!
}



double& Vector::operator [](int i) const//A[i], read only;
{
        if(i < 0||i >= size)
        {
                cout << "Invalid" << endl;
                return buf[0];
        }
	return buf[i]; //unsafe!
}



//Member functions
int Vector::Size() const //get the size of the Vector
{
	return size;
}


bool Vector::Insert(double x, int location) //insert x at location
{
	if(buf == NULL) return false;
	if(location > size-1) return false;
	if(location < 0) return false;
	if(size == 0) return false;
	size++;
	for(int i = size-1;i > location; i--)
	{
		buf[i] = buf[i-1];
	}
	buf[location] = x;
        for(int i = 0;i < size;i++)
        {
                cout << buf[i] << " " << endl;
        }
	return true;
}


bool Vector::Remove(int location)//remove the value at location
{
	int size = this->size;
	int bCount = 0;
	for (int i = 0; i <size; i++)
	{
	if (i == location)
		bCount++;
	}
	if (bCount <= 0)
		return true;
	double *buf = new double[size-bCount];
	int j = 0;
	for (int i = 0; i < size; i++)
	{
		if(i != location)
			buf[j++] = this->buf[i];
	}
	delete[] this->buf;
	this->buf = buf;
}


void Vector::Clear()//remove all data from the Vector.
{
	if (this->buf) delete[] this->buf;
	this->buf = NULL;
}


void Vector::Sort(bool Ascending) //sorting.
{
	if(this->buf==NULL)
	{
		return;
	}
        if(this->size==0)
        {
                return;
        }
	cout<<"before"<<endl;
	for(int i=0;i<this->size;i++)
        {
                cout<<this->buf[i]<<endl;
        }
	for(int j=0;j<this->size;j++)
	{
		for(int i=j;i<this->size;i++)
		{
			if(Ascending)
			{
				if(this->buf[i]<this->buf[j])
				{
					double small=this->buf[i];
					this->buf[i]=this->buf[j];
					this->buf[j]=small;
				}
			}
                        if(!Ascending)
                        {
                                if(this->buf[i]>this->buf[j])
                                {
                                        double big=this->buf[i];
                                        this->buf[i]=this->buf[j];
                                        this->buf[j]=big;
                                }
                        }
		}
	}
	cout<<"sorted"<<endl;
        for(int i=0;i<this->size;i++)
        {
		cout<<this->buf[i]<<endl;
        }
}


ostream& operator << (ostream& output, const Vector& A)
{
	// should we output the dimension first?
	cout << "dimension" << A.Size()<<endl;
	for (int i = 0; i < A.Size(); i++)
	{
		output << A.buf[i] << "\t ";
		output << endl;
	}
	return output;
}


istream& operator >> (istream& input, Vector& A)
{
	// use BypassComment to skip comments.
	cout << "Reading" << endl;
	BypassComment(input);
	input >> A.size;
	if (A.buf) delete[] A.buf;
	A.buf = new double [A.size];
	BypassComment(input);
	for (int i = 0; i < A.size; i++)
	{
		input >> A.buf[i];
		BypassComment(input);
	}
	return input;
}


Vector operator *(double a, const Vector&A)	// a*A, why global function overloading?
{
	Vector tmp;
 	tmp = A;
	for (int i=0; i < A.Size(); i++)
	{
	tmp[i] = a * A[i];
	}
	return tmp;
}

