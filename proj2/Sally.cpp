// File: Sally.cpp
// author : ahmed alhaj
// email : alhaj1@gl.umbc.edu
// CMSC 341 Fall 2018 Project 2
//
// Implementation of member functions of Sally Forth interpreter
//

#include <iostream>
#include <string>
#include <list>
#include <stack>
#include <stdexcept>
#include <cstdlib>
using namespace std ;

#include "Sally.h"


// Basic Token constructor. Just assigns values.
//
Token::Token(TokenKind kind, int val, string txt) {
   m_kind = kind ;
   m_value = val ;
   m_text = txt ;
}


// Basic SymTabEntry constructor. Just assigns values.
//
SymTabEntry::SymTabEntry(TokenKind kind, int val, operation_t fptr) {
   m_kind = kind ;
   m_value = val ;
   m_dothis = fptr ;
}


// Constructor for Sally Forth interpreter.
// Adds built-in functions to the symbol table.
//
Sally::Sally(istream& input_stream) :
   istrm(input_stream)  // use member initializer to bind reference
{

   symtab["DUMP"]    =  SymTabEntry(KEYWORD,0,&doDUMP) ;

   symtab["+"]    =  SymTabEntry(KEYWORD,0,&doPlus) ;
   symtab["-"]    =  SymTabEntry(KEYWORD,0,&doMinus) ;
   symtab["*"]    =  SymTabEntry(KEYWORD,0,&doTimes) ;
   symtab["/"]    =  SymTabEntry(KEYWORD,0,&doDivide) ;
   symtab["%"]    =  SymTabEntry(KEYWORD,0,&doMod) ;
   symtab["NEG"]  =  SymTabEntry(KEYWORD,0,&doNEG) ;

   symtab["."]    =  SymTabEntry(KEYWORD,0,&doDot) ;
   symtab["SP"]   =  SymTabEntry(KEYWORD,0,&doSP) ;
   symtab["CR"]   =  SymTabEntry(KEYWORD,0,&doCR) ;
   symtab["DUP"]  =  SymTabEntry(KEYWORD,0,&doDup);
   symtab["DROP"] =  SymTabEntry(KEYWORD,0,&doDrop);
   symtab["SWAP"] = SymTabEntry(KEYWORD, 0, &doSwap);
   symtab["ROT"] =   SymTabEntry(KEYWORD,0, &doRot);
   symtab["AND"]  =  SymTabEntry(KEYWORD,0,&doAnd) ;
   symtab["OR"] =    SymTabEntry(KEYWORD,0, &doOr );
   symtab["NOT"]  =  SymTabEntry(KEYWORD, 0, &doNot );
   symtab[">"]  =    SymTabEntry(KEYWORD, 0, &doGreatThan);
   symtab[">="] =    SymTabEntry(KEYWORD, 0,&doGreatOrEqu);
   symtab["<="]  =    SymTabEntry(KEYWORD, 0, &doLessOrEqu);
   symtab["<"]  =    SymTabEntry(KEYWORD, 0, &doLessThan);

   symtab["@"]  = SymTabEntry(KEYWORD , 0, &doRetrive );
   symtab["SET"]   =   SymTabEntry(KEYWORD, 0, &doSet );
   symtab["!"]   =   SymTabEntry(KEYWORD, 0, &doReset );
   symtab["=="]   =  SymTabEntry(KEYWORD, 0, &doEqu);
   symtab["!="] = SymTabEntry(KEYWORD, 0, &doNotEqu );
   symtab["IFTHEN"]	 =  SymTabEntry(KEYWORD , 0 , &doIF  );
   symtab["ELSE"] = SymTabEntry(KEYWORD, 0, &doElse );
   symtab["EndIF"] = SymTabEntry(KEYWORD, 0, &doEndif );
   symtab["DO"] =    SymTabEntry(KEYWORD , 0, &doDO );
   symtab["UNTIL"] = SymTabEntry(KEYWORD, 0, &doUntil );
}


// This function should be called when tkBuffer is empty.
// It adds tokens to tkBuffer.
//
// This function returns when an empty line was entered 
// or if the end-of-file has been reached.
//
// This function returns false when the end-of-file was encountered.
// 
// Processing done by fillBuffer()
//   - detects and ignores comments.
//   - detects string literals and combines as 1 token
//   - detetcs base 10 numbers
// 
//
bool Sally::fillBuffer() {
   string line ;     // single line of input
   int pos ;         // current position in the line
   int len ;         // # of char in current token
   long int n ;      // int value of token
   char *endPtr ;    // used with strtol()


   while(true) {    // keep reading until empty line read or eof

      // get one line from standard in
      //
      getline(istrm, line) ;   

      // if "normal" empty line encountered, return to mainLoop
      //
      if ( line.empty() && !istrm.eof() ) {
         return true ;
      }

      // if eof encountered, return to mainLoop, but say no more
      // input available
      //
      if ( istrm.eof() )  {
         return false ;
      }


      // Process line read

      pos = 0 ;                      // start from the beginning

      // skip over initial spaces & tabs
      //
      while( line[pos] != '\0' && (line[pos] == ' ' || line[pos] == '\t') ) {
         pos++ ; 
      }

      // Keep going until end of line
      //
      while (line[pos] != '\0') {

         // is it a comment?? skip rest of line.
         //
         if (line[pos] == '/' && line[pos+1] == '/') break ;

         // is it a string literal? 
         //
         if (line[pos] == '.' && line[pos+1] == '"') {

            pos += 2 ;  // skip over the ."
            len = 0 ;   // track length of literal

            // look for matching quote or end of line
            //
            while(line[pos+len] != '\0' && line[pos+len] != '"') {
               len++ ;
            }

            // make new string with characters from
            // line[pos] to line[pos+len-1]
            string literal(line,pos,len) ;  // copy from pos for len chars

            // Add to token list
            //
            tkBuffer.push_back( Token(STRING,0,literal) ) ;  

            // Different update if end reached or " found
            //
            if (line[pos+len] == '\0') {
               pos = pos + len ;
            } else {
               pos = pos + len + 1 ;
            }

         } else {  // otherwise "normal" token

            len = 0 ;  // track length of token

            // line[pos] should be an non-white space character
            // look for end of line or space or tab
            //
            while(line[pos+len] != '\0' && line[pos+len] != ' ' && line[pos+len] != '\t') {
               len++ ;
            }

            string literal(line,pos,len) ;   // copy form pos for len chars
            pos = pos + len ;

            // Try to convert to a number
            //
            n = strtol(literal.c_str(), &endPtr, 10) ;

            if (*endPtr == '\0') {
               tkBuffer.push_back( Token(INTEGER,n,literal) ) ;
            } else {
               tkBuffer.push_back( Token(UNKNOWN,0,literal) ) ;
            }
         }

         // skip over trailing spaces & tabs
         //
         while( line[pos] != '\0' && (line[pos] == ' ' || line[pos] == '\t') ) {
            pos++ ; 
         }

      }
   }
}



// Return next token from tkBuffer.
// Call fillBuffer() if needed.
// Checks for end-of-file and throws exception 
//
Token Sally::nextToken() {
      Token tk ;
      bool more = true ;

      while(more && tkBuffer.empty() ) {
         more = fillBuffer() ;
      }

      if ( !more && tkBuffer.empty() ) {
         throw EOProgram("End of Program") ;
      }

      tk = tkBuffer.front() ;
      tkBuffer.pop_front() ;
      return tk ;
}


// The main interpreter loop of the Sally Forth interpreter.
// It gets a token and either push the token onto the parameter
// stack or looks for it in the symbol table.
//
//
void Sally::mainLoop() {

   Token tk ;
   map<string,SymTabEntry>::iterator it ;

   try {
      while( 1 ) {
         tk = nextToken() ;

         if (tk.m_kind == INTEGER || tk.m_kind == STRING) {

            // if INTEGER or STRING just push onto stack
            params.push(tk) ;

         } else { 
            it = symtab.find(tk.m_text) ;
            
            if ( it == symtab.end() )  {   // not in symtab

               params.push(tk) ;

            } else if (it->second.m_kind == KEYWORD)  {

               // invoke the function for this operation
               //
               it->second.m_dothis(this) ;   
               
            } else if (it->second.m_kind == VARIABLE) {

               // variables are pushed as tokens
               //
               tk.m_kind = VARIABLE ;
               params.push(tk) ;

            } else {

               // default action
               //
               params.push(tk) ;

            }
         }
      }

   } catch (EOProgram& e) {

      cerr << "End of Program\n" ;
      if ( params.size() == 0 ) {
         cerr << "Parameter stack empty.\n" ;
      } else {
         cerr << "Parameter stack has " << params.size() << " token(s).\n" ;
      }

   } catch (out_of_range& e) {

      cerr << "Parameter stack underflow??\n" ;

   } catch (...) {

      cerr << "Unexpected exception caught\n" ;

   }
}

// -------------------------------------------------------


void Sally::doPlus(Sally *Sptr) {
   Token p1, p2 ;

   if ( Sptr->params.size() < 2 ) {
      throw out_of_range("Need two parameters for +.") ;
   }
   p1 = Sptr->params.top() ;
   Sptr->params.pop() ;
   p2 = Sptr->params.top() ;
   Sptr->params.pop() ;
   int answer = p2.m_value + p1.m_value ;
   Sptr->params.push( Token(INTEGER, answer, "") ) ;
}


void Sally::doMinus(Sally *Sptr) {
   Token p1, p2 ;

   if ( Sptr->params.size() < 2 ) {
      throw out_of_range("Need two parameters for -.") ;
   }
   p1 = Sptr->params.top() ;
   Sptr->params.pop() ;
   p2 = Sptr->params.top() ;
   Sptr->params.pop() ;
   int answer = p2.m_value - p1.m_value ;
   Sptr->params.push( Token(INTEGER, answer, "") ) ;
}


void Sally::doTimes(Sally *Sptr) {
   Token p1, p2 ;

   if ( Sptr->params.size() < 2 ) {
      throw out_of_range("Need two parameters for *.") ;
   }
   p1 = Sptr->params.top() ;
   Sptr->params.pop() ;
   p2 = Sptr->params.top() ;
   Sptr->params.pop() ;
   int answer = p2.m_value * p1.m_value ;
   Sptr->params.push( Token(INTEGER, answer, "") ) ;
}


void Sally::doDivide(Sally *Sptr) {
   Token p1, p2 ;

   if ( Sptr->params.size() < 2 ) {
      throw out_of_range("Need two parameters for /.") ;
   }
   p1 = Sptr->params.top() ;
   Sptr->params.pop() ;
   p2 = Sptr->params.top() ;
   Sptr->params.pop() ;
   int answer = p2.m_value / p1.m_value ;
   Sptr->params.push( Token(INTEGER, answer, "") ) ;
}


void Sally::doMod(Sally *Sptr) {
   Token p1, p2 ;

   if ( Sptr->params.size() < 2 ) {
      throw out_of_range("Need two parameters for %.") ;
   }
   p1 = Sptr->params.top() ;
   Sptr->params.pop() ;
   p2 = Sptr->params.top() ;
   Sptr->params.pop() ;
   int answer = p2.m_value % p1.m_value ;
   Sptr->params.push( Token(INTEGER, answer, "") ) ;
}


void Sally::doNEG(Sally *Sptr) {
   Token p ;

   if ( Sptr->params.size() < 1 ) {
      throw out_of_range("Need one parameter for NEG.") ;
   }
   p = Sptr->params.top() ;
   Sptr->params.pop() ;
   Sptr->params.push( Token(INTEGER, -p.m_value, "") ) ;
}


void Sally::doDot(Sally *Sptr) {

   Token p ;
   if ( Sptr->params.size() < 1 ) {
      throw out_of_range("Need one parameter for .") ;
   }

   p = Sptr->params.top() ;
   Sptr->params.pop() ;

   if (p.m_kind == INTEGER) {
      cout << p.m_value ;
   } else {
      cout << p.m_text ;
   }
}


void Sally::doSP(Sally *Sptr) {
   cout << " " ;
}


void Sally::doCR(Sally *Sptr) {
   cout << endl ;
}

void Sally::doDUMP(Sally *Sptr) {
   // do whatever for debugging
} 

void Sally::doDup(Sally *sptr){
		if(sptr->params.size() < 1 ){
		throw out_of_range("Need two parameter for . ");
	
	}
	Token p1; 
	p1 = sptr->params.top();

	sptr->params.push(Token(INTEGER, p1.m_value, ""));
}

void Sally::doDrop(Sally *sptr){
	if(sptr->params.size() < 1 ){
		throw out_of_range("Need two parameter for . ");
	
	}
	//Token p1; 
	sptr->params.pop();

}


void Sally::doSwap(Sally * sptr){
	if(sptr->params.size() < 2 ){
		throw out_of_range("Need two parameter for . ");
	
	}
	Token p1, p2 ;
	p1 = sptr->params.top();
        sptr->params.pop();
        p2 = sptr->params.top();
        sptr->params.pop();


        sptr->params.push(Token(INTEGER, p1.m_value , ""));
 	sptr->params.push(Token(INTEGER, p2.m_value , ""));



}


void Sally::doRot(Sally *sptr){

	if(sptr->params.size() <3){
		throw out_of_range("Need three parameter for . ");

	}

	Token p1,p2,p3;
	p1 = sptr->params.top();
        sptr->params.pop();
        p2 = sptr->params.top();
        sptr->params.pop();
	p3 = sptr->params.top();
        sptr->params.pop();
	
	sptr->params.push(Token(INTEGER, p2.m_value, ""));
 	sptr->params.push(Token(INTEGER, p1.m_value, ""));
	sptr->params.push(Token(INTEGER, p3.m_value, ""));




}
void Sally::doAnd(Sally *sptr){
	Token p1,p2;

	if(sptr->params.size() < 2 ){
	throw out_of_range("Need one parameter for . ");
	}
	
	p1 = sptr->params.top();
	sptr->params.pop();
	p2 = sptr->params.top();
	sptr->params.pop();
	int ans  = ( p1.m_value && p2.m_value)  ;
			

	sptr->params.push(Token(INTEGER, ans, ""));	

}

void Sally::doOr(Sally *sptr){
	   Token p1, p2 ;

   if ( sptr->params.size() < 2 ) {
      throw out_of_range("Need two parameters for +.") ;
   }
   p1 = sptr->params.top() ;
   sptr->params.pop() ;
   p2 = sptr->params.top() ;
   sptr->params.pop() ;
   int ans =  (p1.m_value || p2.m_value);

   sptr->params.push(Token(INTEGER, ans , "")); 

}

void Sally::doNot(Sally * sptr){
	Token p1;
	if ( sptr->params.size() < 1 ) {
		throw out_of_range("Need two parameters for +.") ;
   	}
   p1 = sptr->params.top() ;
   sptr->params.pop() ;

   int ans = !(p1.m_value );

   sptr->params.push(Token(INTEGER , ans, ""));   


}

void Sally::doSet(Sally * sptr){
   if ( sptr->params.size() < 2 ) {
      throw out_of_range("Need two parameters for +.") ;
   }else{
   
	Token p1, p2 ;
	//cout << "I am at set "<< endl;
	p1 = sptr->params.top() ;
   	sptr->params.pop() ;
	p2 = sptr->params.top() ;
   	sptr->params.pop() ;
	//print stat
   	//cout << "p1.val  -> " << p1.m_value << "p1.txt: " << p1.m_text  <<" p1.kind :" << p1.m_kind <<" p2.val" <<  p2.value  << "p2.txt "<< p2.m_text  << " p2.kind :  " << p2.m_kind <<  endl;


	if( sptr->symtab.find(p1.m_text) == sptr->symtab.end()  ){

		sptr->symtab[p1.m_text] = SymTabEntry(p1.m_kind, p2.m_value );
  	}else{
		cout << "the varaialbe is already exist in the symtab " << endl;
   	}
   
   
  
}
}

// DoReset() it reset a varaible in teh symtable.
void Sally::doReset(Sally * sptr){
  Token p1, p2 ;
  //cout << "I am at reset " << endl;
   if ( sptr->params.size() < 2 ) {
      throw out_of_range("Need two parameters for +.") ;
   }
   p1 = sptr->params.top() ;
   sptr->params.pop() ;
   p2 = sptr->params.top() ;
   sptr->params.pop() ;
   //cout << "p1 " << p1.m_value << "p2 " << p2.m_value << endl;
   if (sptr->symtab.find(p1.m_text) == sptr->symtab.end() ){
	cout <<"the varaible in the stack ! check your doSEt  "<<endl;
   }
   sptr-> symtab.find(p1.m_text )->second.m_value =p2.m_value ;
   

  
}
// doRetrive() retrive the value of the last value at the stack
void Sally::doRetrive(Sally *sptr){
	int size = sptr->params.size();
	//cout <<"I am @ retrive,  stack size :  "<< size  << endl;

	if ( size  < 1 ){
      		throw out_of_range("Need one parameters for +.") ;
	}
	Token p1; 
	p1 = sptr->params.top() ;
	sptr->params.pop() ;
	int ans = sptr->symtab.find(p1.m_text)->second.m_value ;
	//cout <<"@  p1 " << p1.m_value << "p1 str " << p1.m_text << endl;
	sptr->params.push(Token(INTEGER , ans , ""));
  

   
  
}
// doGreaThna() : checks if p1 > p2 
void Sally::doGreatThan(Sally *sptr){
   Token p1, p2 ;

   if ( sptr->params.size() < 2 ) {
      throw out_of_range("Need two parameters for +.") ;
   }
   p1 = sptr->params.top() ;
   sptr->params.pop() ;
   p2 = sptr->params.top() ;
   sptr->params.pop() ;
   
   int ans = p2.m_value  > p1.m_value ;
   sptr->params.push(Token(INTEGER, ans, ""));   
}


void Sally::doLessThan(Sally * sptr){
   Token p1, p2 ;

   if ( sptr->params.size() < 2 ) {
      throw out_of_range("Need two parameters for +.") ;
   }
   p1 = sptr->params.top() ;
   sptr->params.pop() ;
   p2 = sptr->params.top() ;
   sptr->params.pop() ;
   int ans = (p2.m_value  < p1.m_value );
   
   sptr->params.push(Token(INTEGER, ans, ""));   

}



void Sally::doGreatOrEqu(Sally *sptr){
   Token p1, p2 ;

   if ( sptr->params.size() < 2 ) {
      throw out_of_range("Need two parameters for +.") ;
   }
   p1 = sptr->params.top() ;
   sptr->params.pop() ;
   p2 = sptr->params.top() ;
   sptr->params.pop() ;
   int ans =  (p2.m_value  >= p1.m_value ) ; 

   sptr->params.push(Token(INTEGER, ans, ""));   

}
 
void Sally::doLessOrEqu(Sally *sptr){
   Token p1, p2 ;

   if ( sptr->params.size() < 2 ) {
      throw out_of_range("Need two parameters for +.") ;
   }
   p1 = sptr->params.top() ;
   sptr->params.pop() ;
   p2 = sptr->params.top() ;
   sptr->params.pop() ;
   int ans;

   ans = (p2.m_value  <= p1.m_value ) ;
   sptr->params.push(Token(INTEGER, ans, ""));   

}
void Sally::doEqu(Sally *sptr){
   Token p1, p2 ;

   if ( sptr->params.size() < 2 ) {
      throw out_of_range("Need two parameters for +.") ;
   }
   p1 = sptr->params.top() ;
   sptr->params.pop() ;
   p2 = sptr->params.top() ;
   sptr->params.pop() ;
   int ans;
   if (p1.m_kind == INTEGER ){
   	ans = (p1.m_value  == p2.m_value);
   }else {
	ans = (p1.m_text == p2.m_text  );
 
   }
   sptr->params.push(Token(INTEGER, ans, ""));   

}

void Sally::doNotEqu(Sally *sptr ){

   Token p1, p2 ;

   if ( sptr->params.size() < 2 ) {
      throw out_of_range("Need two parameters for +.") ;
   }
   p1 = sptr->params.top() ;
   sptr->params.pop() ;
   p2 = sptr->params.top() ;
   sptr->params.pop() ;
   int ans;
   //cout <<"p1.kind " << p1.m_kind << "p1.vale "<< p1.m_value  << endl;
   if (p1.m_kind == INTEGER ){
   	ans = (p1.m_value  != p2.m_value);
   }else {
	ans = (p1.m_text != p2.m_text  );
 
   }
   sptr->params.push(Token(INTEGER, ans, ""));   





}

void Sally::doIF(Sally *sptr){
	
	//cout << "I am at doif "<<endl;
	if(sptr->params.size() < 1 ){
		cout << " I am about to throw  " << endl;
		throw out_of_range("Need two parameter for doIF");
	}

	Token p1 ;
	p1 = sptr->params.top();
	sptr->params.pop();
	if ( !p1.m_value  ){
		//cout <<"if is flase   " << "m_if : " << sptr->m_if  << endl;
		sptr->m_if++;

		//Token p2 = sptr->nextToken();
		//int keyword = 1;
		while( sptr->m_if > 0  ){
			
			p1 = sptr->nextToken();
			if ( (p1.m_text == "IFTHEN") ){
				sptr->m_if++;
			}
			if(p1.m_text == "ELSE"){
				sptr->m_if--;
				
			}
				


			}
			

		}
		sptr->m_endif++;
		
}



void Sally::doElse(Sally *sptr){
//cout << "I am at do else " << endl;
	//if (sptr->params.size() < 1 ){
	//	throw out_of_range("Need two parameter for doIF");
	//}
	Token p1 = sptr->nextToken();
	while ( sptr-> m_endif !=  0   ){
		p1  = sptr->nextToken() ;
		if (p1.m_text == "ENDIF"){
			sptr->m_endif--; 
		}
			
}
}

void Sally::doEndif(Sally *sptr){
cout << "I am at endif "<< endl;
//sptr->m_if --; 

//while (!sptr->params.empty()){
//	sptr->params.pop();
//}
}


// doDo() pull out the stuff from nextToken and save them to a list 
// then push the stuff in the tkBufffer read by the mainloop with out deleting them. 
void Sally::doDO(Sally *sptr){
	Token p1 = sptr->nextToken();
	while (true ){
		sptr->myList.push_back(p1);
		p1 = sptr->nextToken();
		if(p1.m_text == "UNTIL"){

			sptr->myList.push_back(p1);
			break;
		}
	}

		for (list<Token>::iterator it = sptr->myList.begin() ; it != sptr->myList.end() ; ++it){

			sptr->tkBuffer.push_back(*it);
		}

       
	
}

// doUntill 
// checks the value in the params stack if true does not nothing else refill tkBuffer 
void Sally::doUntil(Sally *sptr){

	if(sptr->params.size() < 1 ){
		throw out_of_range("stack does have paramer at Until ");

	}
	Token p1; 
	p1 = sptr->params.top();
	sptr->params.pop();

	if (!p1.m_value){

		for (list<Token>::iterator it = sptr->myList.begin() ; it != sptr->myList.end() ; ++it  ){

		sptr->tkBuffer.push_back(*it);


		}

	}
	//cout << "until is alright " << endl;
}




