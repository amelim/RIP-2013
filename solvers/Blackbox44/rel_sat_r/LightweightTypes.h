#ifndef LightweightTypes_h
#define LightweightTypes_h

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This file contains typedefs, enums, and definitions of their special values.
typedef int DomainValue;
#define NON_VALUE   -1                  // The NON_VALUE is a special domain value. Domain values are usually positive integers.

typedef int VariablePosition;     // Used to specify that a Variable is being represented by its index in an array 
typedef int VariableID;    
#define NON_ID      -1

typedef unsigned char boolean;


#define TRUE 1
#define FALSE 0

#endif // LightweightTypes_h
