//ReallyLongInt.cc

#include "ReallyLongInt.h"
#include <cmath>
#include <iostream>
#include <climits>



ReallyLongInt::ReallyLongInt()
{  unsigned* tempArr = new unsigned[1];
  tempArr[0] = 0;
   isNeg = false;
   digits = tempArr;
   numDigits = 1;
   
}

ReallyLongInt::ReallyLongInt(long long num)
{
  if (num == 0)
    {numDigits = 1;
      isNeg = false;
    }
  else if (num > 0)
    {numDigits = log10(num) + 1;
      isNeg = false;
    }
  else
    {isNeg = true;
      num = num * -1;
      numDigits = log10(num) + 1;
    }

  //make temp array
  unsigned* myArray = new unsigned[numDigits];

  //fill in array
  unsigned i;
  for (i = numDigits - 1; i > 0; i--)
    
    {
      myArray[i] = num % 10;
      
      num = num / 10; 
    }

  myArray[i] = num;
  
  //points digits to temp array
  digits = myArray;

  
 }

void ReallyLongInt::removeLeadingZeros(unsigned* x, unsigned& numDigits) 
{//updates i until x[i] is no longer 0 or it reaches the end of the array
    unsigned i = 0;  
    while (i < numDigits && x[i] == 0)
      {i++;
      }
    
    //in case they were all 0s make the size 1
    if (i == numDigits)
      {numDigits =  1;
      }
    
    //at least 1 leading number was 0 (but not for only zero(s))
    else if (i != 0 && numDigits != 1)
    {unsigned newSize = numDigits - i;
     
     //shift the significant digits toward the front of the array
     unsigned shiftHolder = 0;
     while(i < numDigits)
	{x[shiftHolder] = x[i];
	 ++i;
	 ++shiftHolder;
	}

     //update size of array
     numDigits = newSize;

    }
}


ReallyLongInt::ReallyLongInt(const string& numStr)
{ unsigned j;
  if (numStr[0]== '-')
    {isNeg = true;
      j = 1;
      numDigits = numStr.size()-1;
    }
  else
    {isNeg = false;
	j = 0;
      numDigits = numStr.size();
    }



  //make the array 
  unsigned* myArray = new unsigned[numDigits];

  
  //fills in the array 
  unsigned i;
  for (i = 0; i < numDigits; i++)
    { 
      myArray[i] = int(numStr[j]) - 48;
      j++;
     
    } 

  removeLeadingZeros(myArray, numDigits);

  if (myArray[0]== 0)
    {isNeg = false;
    }
    

  digits = myArray;
  
  
}


ReallyLongInt::~ReallyLongInt()
{
  delete[] digits;

}


ostream& ReallyLongInt::print(ostream& out) const
{ if (isNeg == true)
    {out << "-";
    }

  unsigned i;
  for (i = 0; i < numDigits; i++)
    {
      out << digits[i];
    }

  return out;
}

ostream& operator<<(ostream& out, const ReallyLongInt& x)
{x.print(out);
  return out;
}

ReallyLongInt::ReallyLongInt(const ReallyLongInt& other)
{numDigits = other.numDigits;
  isNeg = other.isNeg;

  unsigned* newArray = new unsigned[numDigits];

  for (unsigned i = 0; i < numDigits; i++)
    {newArray[i] = other.digits[i];
    }

  
  digits = newArray;
}

ReallyLongInt& ReallyLongInt::operator=(const ReallyLongInt& other)
{swap(other);
 return *this;
}

void ReallyLongInt::swap(ReallyLongInt other)
{
  //temp variable fill with this-> data
  const unsigned* swapDig = this->digits;
  unsigned swapNumD = this->numDigits;
  bool swapNeg = this->isNeg;

  //swaps
  this->digits = other.digits;
  this->numDigits = other.numDigits;
  this->isNeg = other.isNeg;
  other.digits = swapDig;
  other.numDigits = swapNumD;
  other.isNeg = swapNeg;
}


ReallyLongInt::ReallyLongInt(unsigned* digitsArr, unsigned arrSize, bool isNeg)
{removeLeadingZeros(digitsArr, arrSize);
  digits = digitsArr;
  numDigits = arrSize;
  
  
  if (digits[0] == 0)
    {this->isNeg = false;
    }
  else
    {this->isNeg = isNeg;
    }
}


bool ReallyLongInt::equal(const ReallyLongInt& other) const
{//if different sizes or isNeg values, false
  if (other.numDigits != this->numDigits || this->isNeg != other.isNeg)
    {return false;
    }

  //go through all the idx's
  for (unsigned i = 0; i < this->numDigits; i++)
    { //return false if anything doesn't match
      if (this->digits[i] != other.digits[i])
	{return false;
	}
    }
  //if none of the digits were different return true
   return true;
}

bool ReallyLongInt::absGreater(const ReallyLongInt& other) const
{ 
  if (other.numDigits > this->numDigits)
    {return false;
    }
  
  else if (this->numDigits > other.numDigits)
    {return true;
    }
  //same size, start comparing from left to right
  else
    {
     for (unsigned i = 0; i < this->numDigits; i++)
       {//if x's digit is larger return true
	  if (this->digits[i] > other.digits[i])
	    {return true;
	    }
	  //if y's is larger return false
	  else if (other.digits[i] > this->digits[i])
	    {return false;
	    }
	}
    }

  
  //if they are the same return false
   return false;

  
   
}


bool ReallyLongInt::greater(const ReallyLongInt& other) const
{if (this->isNeg == true && other.isNeg == false)
    {return false;
    }
  else if(this->isNeg == false && other.isNeg ==true)
    {return true;
    }
  else if (this->isNeg == true && other.isNeg == true)
    {return other.absGreater(*this);
    }
  
  else
    {return absGreater(other);
    }
  
}


bool operator==(const ReallyLongInt& x, const ReallyLongInt& y)
{return x.equal(y);
}

bool operator!=(const ReallyLongInt& x, const ReallyLongInt& y)
{return !x.equal(y);
}

bool operator>(const ReallyLongInt& x, const ReallyLongInt& y)
{return x.greater(y);
}

bool operator<(const ReallyLongInt& x, const ReallyLongInt& y)
{return y.greater(x);
}

bool operator>=(const ReallyLongInt& x, const ReallyLongInt& y)
{return x.greater(y) || x.equal(y);
}
bool operator<=(const ReallyLongInt& x, const ReallyLongInt& y)
{return y.greater(x)||y.equal(x);
}




ReallyLongInt ReallyLongInt::absAdd(const ReallyLongInt& other) const
{ int  smallSize;
  int  bigSize;
  const unsigned* bigArray;

  
  if (other.numDigits <= this->numDigits)
    {smallSize = other.numDigits;
      bigSize = this->numDigits;    
      bigArray = this->digits;
    }
  
  else //other bigger
    {smallSize = this->numDigits;
      bigSize = other.numDigits;
      bigArray = other.digits;
    }

  
  unsigned* newArray = new unsigned[bigSize + 1];
  unsigned resultSize = bigSize + 1;
 
  //for all of the idx in the smaller array
  unsigned holder = 0;
  int idxAdj = 1; 
  while (idxAdj <= smallSize)
    {unsigned sum = this->digits[this->numDigits - idxAdj] + other.digits[other.numDigits - idxAdj] + holder;
      
      //puts the number in the new array and updates holder
      newArray[bigSize + 1 - idxAdj] = sum % 10;
      holder = sum / 10;
        
      idxAdj++;
    }
  
  while (bigSize - idxAdj >= 0)
    {
     newArray[bigSize + 1 -idxAdj] = (bigArray[bigSize - idxAdj] + holder) % 10;
     holder = (bigArray[bigSize - idxAdj] + holder) / 10;
     idxAdj++;
    }
    
  
  //takes care of the first digit in the sum array with whatever is in holder
  newArray[0] = holder;

  
  
  return ReallyLongInt(newArray, resultSize, false);
}


ReallyLongInt ReallyLongInt::absSub(const ReallyLongInt& other) const
{ unsigned  smallSize;
  unsigned bigSize;
  const unsigned* smallArray;
  const unsigned* bigArray;

  
  if (this->absGreater(other)||this->equal(other))
    {smallSize = other.numDigits;
      smallArray = other.digits;
      bigSize = this->numDigits;    
      bigArray = this->digits;
    }
  
  else //other bigger
    {smallSize = this->numDigits;
      smallArray = this->digits;
      bigSize = other.numDigits;
      bigArray = other.digits;
     
    }

  unsigned* newArray = new unsigned[bigSize];
  unsigned resultSize = bigSize;


  //for idx of small array
  int holder = 0;
  unsigned idxAdj = 1; 
  int difference = 0;
  while (idxAdj <= smallSize)
    {
      if (int((bigArray[bigSize - idxAdj]) - holder) < int(smallArray[smallSize - idxAdj]))
	{difference = (bigArray[bigSize - idxAdj] - holder + 10)- smallArray[smallSize - idxAdj];
	  holder = 1;
	  
	}
      else
	{difference = (bigArray[bigSize - idxAdj] - holder) - smallArray[smallSize - idxAdj];
	  holder = 0;
	   
	}

      
      //puts the number in the new array 
      newArray[bigSize - idxAdj] = difference;
      
           
      idxAdj++;
    }
  
  while (idxAdj <= bigSize && holder == 1)
    {newArray[bigSize - idxAdj] = (bigArray[bigSize - idxAdj] - holder);
      holder = 0;
      idxAdj++;
    }

  while (idxAdj <= bigSize)
    {newArray[bigSize - idxAdj] = (bigArray[bigSize - idxAdj]);
      idxAdj++;
    }


  return ReallyLongInt(newArray, resultSize, other.absGreater(*this));
 
}



void ReallyLongInt::flipSign()
{if (digits[0] == 0)
    {
      isNeg = false;
    }
  else
    {
      isNeg = !isNeg;
    }
}

ReallyLongInt ReallyLongInt::operator-() const
{ ReallyLongInt newRLInt = ReallyLongInt(*this);
  newRLInt.flipSign();
  return newRLInt;
}


ReallyLongInt ReallyLongInt::add(const ReallyLongInt& other) const
{if (!isNeg && !other.isNeg)
    {return absAdd(other);
    }
  else if (isNeg && other.isNeg)
    {ReallyLongInt tempThing = absAdd(other);
     tempThing.flipSign();
     return tempThing;
   }
  else if (isNeg && !other.isNeg)
    {return other.absSub(*this);
    }
  else//left +, right -
    {return absSub(other);
    }


}

ReallyLongInt ReallyLongInt::sub(const ReallyLongInt& other) const
{ if (!isNeg && !other.isNeg)
    {return absSub(other);
    }
  else if(isNeg && other.isNeg)
    { ReallyLongInt tempThing = absSub(other);
      tempThing.flipSign();
      return tempThing;
    }
  else if(isNeg && !other.isNeg)
    {ReallyLongInt tempThing = absAdd(other);
      tempThing.flipSign();
      return tempThing;
    }
  else//left +, right -
    {
      return absAdd(other);
    }

}


ReallyLongInt operator+(const ReallyLongInt& x, const ReallyLongInt& y)
{return x.add(y);
}


ReallyLongInt operator-(const ReallyLongInt& x, const ReallyLongInt& y)
{return x.sub(y);
}


ReallyLongInt& ReallyLongInt::operator+=(const ReallyLongInt& other)
{
  return *this = *this + other;
}

ReallyLongInt& ReallyLongInt::operator-=(const ReallyLongInt& other)
{
  return *this = *this - other;
}

ReallyLongInt& ReallyLongInt::operator++()
{
  return *this += 1;
}

ReallyLongInt& ReallyLongInt::operator--()
{
  return *this -= 1;
}

ReallyLongInt ReallyLongInt::operator++(int dummy)
{ReallyLongInt copyOfInt = *this;
  ++*this;
  return copyOfInt;
}

ReallyLongInt ReallyLongInt::operator--(int dummy)
{ReallyLongInt copyOfInt = *this;
  --*this;
  return copyOfInt;
}


ReallyLongInt ReallyLongInt::absMult(const ReallyLongInt& other) const
{//makes product array and fills it with 0's
  unsigned* p = new unsigned[numDigits + other.numDigits];
  for (unsigned i = 0; i < numDigits + other.numDigits; i++)
    {p[i] = 0;
    }
  unsigned resultSize = numDigits + other.numDigits;

  //for the spaces in x
  for (unsigned idx = 0; idx < numDigits; idx++)
    { 
      unsigned c = 0;

      //for the spaces in y
      for (unsigned jIdx = 0; jIdx < other.numDigits; jIdx++)
	{ /*finds the idx for the product array and updates it */
	  int d = numDigits + other.numDigits - idx -jIdx - 1;
	  unsigned sum = p[d] + digits[numDigits - idx - 1] * other.digits[other.numDigits - jIdx - 1] + c;
	  p[d] = sum % 10;
	  c = sum/10;
	}

      //updates product array
      p[numDigits - idx- 1] = p[numDigits - idx - 1] + c;
    }
  
  return ReallyLongInt(p, resultSize, false);
}


ReallyLongInt ReallyLongInt::mult(const ReallyLongInt& other) const
{if (!isNeg && !other.isNeg)
    {return absMult(other);
    }
  else if (isNeg && other.isNeg)
    {return absMult(other);
    }
  else//one +, one -
    {ReallyLongInt tempThing = absMult(other);
      tempThing.flipSign();
      return tempThing;
    }

}


ReallyLongInt operator*(const ReallyLongInt& x, const ReallyLongInt& y)
{return x.mult(y);
}

ReallyLongInt& ReallyLongInt::operator*=(const ReallyLongInt& other)
{return *this = *this * other;
}


void ReallyLongInt::absDiv(const ReallyLongInt& other, ReallyLongInt& quotient, ReallyLongInt& remainder) const
{if (other == 0)
 {std::cout << "You can't divide by Zero!" << endl;
  quotient = 0;
  remainder = 0;
   }
 else
    {
  ReallyLongInt r(0);
  
  ReallyLongInt nonNegOther(0);
  unsigned* q = new unsigned[numDigits];

  if(other.isNeg)
    {nonNegOther = ReallyLongInt(other);
      nonNegOther.flipSign();
    }  
   else
     {nonNegOther = ReallyLongInt(other);
     }
  
  
  for(unsigned i = 0; i < numDigits; ++i)
    {
      r = 10 * r;
      r = r + digits[i];
      int d = 0;
      
      
      while(r >= nonNegOther)
	{r -=  nonNegOther;
	  ++d;
	}
      q[i]= d;
     }
 
  quotient = ReallyLongInt(q, numDigits, false);
  remainder = r;

  }//else bracket that keeps other = 0 from running 
}


void ReallyLongInt::div(const ReallyLongInt& other, ReallyLongInt& quotient, ReallyLongInt& remainder) const
{if (!isNeg && !other.isNeg)
    {absDiv(other, quotient, remainder);
    }
  else if(isNeg && other.isNeg)
    {absDiv(other, quotient, remainder);
      if (remainder != 0)
	{remainder.flipSign();
	}
      
    }
  else if(isNeg && !other.isNeg)
    {absDiv(other, quotient, remainder);
      if (quotient != 0)
	{quotient.flipSign();
	}
      if(remainder != 0)
	{remainder.flipSign();
	}
    }
  else //x is +, y is -
    {absDiv(other, quotient, remainder);
      if (quotient != 0)
	{quotient.flipSign();
	}
    }
}

ReallyLongInt operator/(const ReallyLongInt& x, const ReallyLongInt& y)
{ReallyLongInt quotient;
  ReallyLongInt remainder;
  x.div(y,quotient, remainder);
  return quotient;
}

ReallyLongInt operator%(const ReallyLongInt& x, const ReallyLongInt& y)
{ReallyLongInt quotient;
  ReallyLongInt remainder;
  x.div(y, quotient, remainder);
  return remainder;
}


ReallyLongInt& ReallyLongInt::operator/=(const ReallyLongInt& other)
{*this = *this /other;
  return *this;
}

ReallyLongInt& ReallyLongInt::operator%=(const ReallyLongInt& other)
{*this = *this % other;
return *this;
}


long long ReallyLongInt::toLongLong() const
{ReallyLongInt maxP1(LLONG_MAX);
  ++maxP1;
  ReallyLongInt canFitVal = *this % maxP1; 
  
  long long ans = canFitVal.digits[canFitVal.numDigits - 1];
  
  long long tenHolder = 10;

  for(int i = canFitVal.numDigits - 2; i >= 0; --i)
    {
      ans += (tenHolder * canFitVal.digits[i]);
     tenHolder = tenHolder * 10;
    }

  if(isNeg && ans != 0)
    {ans *= -1;
    }

  return ans;
}
