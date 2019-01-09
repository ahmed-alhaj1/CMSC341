// File: Sally.h
//
// CMSC 341 Fall 2018 Project 2
//
// Class declarations for Sally Forth interpreter
//

#ifndef _SALLY_H_
#define _SALLY_H_

#include <iostream>
#include <string>
#include <list>
#include <stack>
#include <map>
#include <stdexcept>
using namespace std ;


// thrown by lexical parser when end of file reached
//
class EOProgram : public runtime_error {
public:
   EOProgram(const string& what) : runtime_error(what) { }
} ;


enum TokenKind { UNKNOWN, KEYWORD, INTEGER, VARIABLE, STRING } ;


// lexical parser returns a token 
// programs are lists of tokens
//
class Token {

public:

   Token(TokenKind kind=UNKNOWN, int val=0, string txt="" ) ;
   TokenKind m_kind ;
   int m_value ;      // if it's a known numeric value
   string m_text ;    // original text that created this token

} ;



// type of a C++ function that does the work 
// of a Sally Forth operation.
//
class Sally ; 
typedef void (* operation_t)(Sally *Sptr) ;



// entry in the symbol table has this type
//
class SymTabEntry {
public:
   SymTabEntry(TokenKind kind=UNKNOWN, int val=0, operation_t fptr=NULL) ;
   TokenKind m_kind ;
   int m_value ;            // variables' values are stored here
   operation_t m_dothis ;   // pointer to a function that does the work
} ;



// Main Sally Forth class
//
class Sally {

public:

   Sally(istream& input_stream=cin) ;  // make a Sally Forth interpreter

   void mainLoop() ;  // do the main interpreter loop


private:

   // Where to read the input
   //
   istream& istrm ;


   // Sally Forth operations to be interpreted
   //
   list<Token> tkBuffer ;   
   list<Token> myList; 
   // track the level of if 
   int m_if;
   int m_endif ;

   // Sally Forth parameter stack
   //
   stack<Token> params ;    

   // Sally Forth symbol table
   // keywords and variables are store here
   //
   map<string,SymTabEntry> symtab ;   


   // add tokens from input to tkBuffer
   //
   bool fillBuffer() ;


   // give me one more token.
   // calls fillBuffer() for you if needed.
   //
   Token nextToken() ;


   // static member functions that do what has
   // to be done for each Sally Forth operation
   // 
   // pointers to these functions are stored 
   // in the symbol table
   //
   static void doDUMP(Sally *Sptr) ;    // for debugging

   static void doPlus(Sally *Sptr) ;
   static void doMinus(Sally *Sptr) ;
   static void doTimes(Sally *Sptr) ;
   static void doDivide(Sally *Sptr) ;
   static void doMod(Sally *Sptr) ;
   static void doNEG(Sally *Sptr) ;

   static void doDot(Sally *Sptr) ;
   static void doSP(Sally *Sptr) ;
   static void doCR(Sally *Sptr) ;
//## my code ###//

   static void doDup(Sally *sptr);
   static void doDrop(Sally *sptr ) ;
   static void doSwap(Sally *sptr);
   static void doRot(Sally *sptr); 
   static void doAnd(Sally *sptr);
   static void doOr(Sally *sptr);
   static void doNot(Sally *sptr);
   static void doSet(Sally *sptr);
   static void doRetrive(Sally * sptr);
   static void doReset(Sally* sptr);
   static void doGreatThan(Sally *sptr);
   static void doLessThan(Sally *sptr);
   static void doGreatOrEqu(Sally *sptr);
   static void doLessOrEqu(Sally *sptr);
   static void doEqu(Sally *sptr);
   static void doIF(Sally *sptr);
   static void doElse(Sally *sptr);
   static void doDO(Sally *sptr);
   static void doUntil(Sally * sptr);
   static void doEndif(Sally *sptr);
   static void doNotEqu(Sally *sptr);
} ;

#endif
