//numberTheory.h

#ifndef numberTheory_h
#define numberTheory_h

template <class X>

X modPower(const X& base, const X& exponent, const X& modulus)
{
    /*creates answer to store what I want modPower to return and creates repeatedNum to store the recursively calculated number that is used several times */
    X answer;
    X repeatedNum;
    
    //base case of when the exponent is 0 and the answer is 1 instead of a recursive call
    if (exponent == 0)
      {repeatedNum = 1;
      }

    //else do recursion and store the end result
    else
      {
      repeatedNum = modPower(base, exponent/2, modulus);
      }
    
    //checks if it's even or odd and multiplies accordingly. Mods after 2 numbers are multiplied
    if (exponent % 2 == 0)
      {
      answer = (repeatedNum * repeatedNum) % modulus;
      }
    else
      {
      answer = (((base * repeatedNum) % modulus) * repeatedNum) % modulus;
      }
    return answer;
    
}

template <class X>

bool isPrime(const X& num)
{ //accounts for when num is 0 or 1
  if (num == 0 ||num == 1)
    {return false;
    }

  
  X highest = num/2;
  X i;

  /*i starts at the highest thing it needs to test and decreases by 1 until is proven not prime or becomes one and exits the loop*/
  for( i = highest; i>1; i--)
    {
    if (num % i == 0)
      {
      //returns false when it is proven not prime
      return false;
      }
    }
  /* only if it checks everything from highest to 2 (inclusive) does it say it's   prime */
  return true;
}


template <class X>
//takes 2 numbers (int not float) and 2 pointers
//returns the gcd
/*updates the values(x and y) at the pointer addresses to supply the x and y from the equation ax + by = gcd*/
X extendedEuclid(const X& a, const X& b, X* x, X* y)
{  //base case
  if (b == 0)
    {*x = 1;
     *y = 0;
     return a;
    }

  else
    { //variable to store the gcd
      X d;
      
      //recursive call to the func taking b, a%b instead of a, b
      d = extendedEuclid(b, (a % b), x, y);


      
      X j = *y;
      X k = *x - *y * (a/b);

      //updates x and y out of scope using pointers
      *x = j;
      *y = k;
      
      //returns the gcd
      return d; 
    }
}





#endif /* numberTheory_h */
