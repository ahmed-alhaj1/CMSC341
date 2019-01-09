#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std ;

#include "City.h"

//
// Comparison functions for City objects
//

bool City::sameCity(const City &c1, const City &c2) {
   return (c1.m_name == c2.m_name) && (c1.m_state == c2.m_state) ;
}

bool City::smallerLatitude(const City &c1, const City &c2) {
   return c1.m_latitude < c2.m_latitude ;
}

bool City::biggerLatitude(const City &c1, const City &c2) {
   return c1.m_latitude > c2.m_latitude ;
}

bool City::smallerLongitude(const City &c1, const City &c2) {
   return c1.m_longitude < c2.m_longitude ;
}

bool City::biggerLongitude(const City &c1, const City &c2) {
   return c1.m_longitude > c2.m_longitude ;
}

bool City::smallerPopulation(const City &c1, const City &c2) {
   return c1.m_population < c2.m_population ;
}

bool City::biggerPopulation(const City &c1, const City &c2) {
   return c1.m_population > c2.m_population ;
}

bool City::smallerElevation(const City &c1, const City &c2) {
   return c1.m_elevation < c2.m_elevation ;
}

bool City::biggerElevation(const City &c1, const City &c2) {
   return c1.m_elevation > c2.m_elevation ;
}


//
// Comparison functions for City pointers
//

bool City::sameCityP(City* const &ptr1, City* const &ptr2) {
   return (ptr1->m_name == ptr2->m_name) && (ptr1->m_state == ptr2->m_state) ;
}

bool City::smallerLatitudeP(City* const &ptr1, City* const &ptr2) {
   return ptr1->m_latitude < ptr2->m_latitude ;
}

bool City::biggerLatitudeP(City* const &ptr1, City* const &ptr2) {
   return ptr1->m_latitude > ptr2->m_latitude ;
}

bool City::smallerLongitudeP(City* const &ptr1, City* const &ptr2) {
   return ptr1->m_longitude < ptr2->m_longitude ;
}

bool City::biggerLongitudeP(City* const &ptr1, City* const &ptr2) {
   return ptr1->m_longitude > ptr2->m_longitude ;
}

bool City::smallerPopulationP(City* const &ptr1, City* const &ptr2) {
   return ptr1->m_population < ptr2->m_population ;
}

bool City::biggerPopulationP(City* const &ptr1, City* const &ptr2) {
   return ptr1->m_population > ptr2->m_population ;
}

bool City::smallerElevationP(City* const &ptr1, City* const &ptr2) {
   return ptr1->m_elevation < ptr2->m_elevation ;
}

bool City::biggerElevationP(City* const &ptr1, City* const &ptr2) {
   return ptr1->m_elevation > ptr2->m_elevation ;
}


istream& operator>>(istream& is, City& c) {
   is >> c.m_name 
      >> c.m_state 
      >> c.m_latitude 
      >> c.m_longitude 
      >> c.m_population 
      >> c.m_elevation ;
   return is ;
}


istream& operator>>(istream& is, City* c) {
   return is >> *c ;
}


ostream& operator<<(ostream& os, const City& c) {
   ostringstream out ;

   out << setw(20) << left << c.m_name << right ;
   out << setw(5) << c.m_state << "   " 
       << fixed << setw(10) << setprecision(3) << right << c.m_latitude 
       << fixed << setw(10) << setprecision(3) << right << c.m_longitude
       << setw(10) << c.m_population 
       << setw(10) << c.m_elevation ;

   os << out.str() ;
   return os ;
}


ostream& operator<<(ostream& os, City* c) {
   return os << *c ;
}
