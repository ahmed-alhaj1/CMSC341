#ifndef _CITY_H_
#define _CITY_H_

#include <string>

using namespace std ;

class City {
   public:
      string m_name ;
      string m_state ;
      float m_latitude ;
      float m_longitude ;
      int m_population ;
      int m_elevation ;
      int m_index;
      int m_status;

      //
      // Comparison functions for City objects
      //
      static bool sameCity(const City& c1, const City& c2) ;
      static bool smallerLatitude(const City& c1, const City& c2) ;
      static bool biggerLatitude(const City& c1, const City& c2) ;
      static bool smallerLongitude(const City& c1, const City& c2) ;
      static bool biggerLongitude(const City& c1, const City& c2) ;
      static bool smallerPopulation(const City& c1, const City& c2) ;
      static bool biggerPopulation(const City& c1, const City& c2) ;
      static bool smallerElevation(const City& c1, const City& c2) ;
      static bool biggerElevation(const City& c1, const City& c2) ;

      //
      // Comparison functions for City pointers
      //
      static bool sameCityP(City* const &ptr1, City* const &ptr2) ;
      static bool smallerLatitudeP(City* const &ptr1, City* const &ptr2) ;
      static bool biggerLatitudeP(City* const &ptr1, City* const &ptr2) ;
      static bool smallerLongitudeP(City* const &ptr1, City* const &ptr2) ;
      static bool biggerLongitudeP(City* const &ptr1, City* const &ptr2) ;
      static bool smallerPopulationP(City* const &ptr1, City* const &ptr2) ;
      static bool biggerPopulationP(City* const &ptr1, City* const &ptr2) ;
      static bool smallerElevationP(City* const &ptr1, City* const &ptr2) ;
      static bool biggerElevationP(City* const &ptr1, City* const &ptr2) ;

} ;


// prototypes for using City with iostream

istream& operator>>(istream& is, City& c) ;
istream& operator>>(istream& is, City* c) ;

ostream& operator<<(ostream& os, const City& c) ;
ostream& operator<<(ostream& os, City* c) ;

#endif
