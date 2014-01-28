#include "ms_rational_nt.h"
#include <CGAL/Cartesian.h>
#include <CGAL/minkowski_sum_2.h>
#include <iostream>

#include "print_utils.h"

typedef CGAL::Cartesian<Number_type>                Kernel;
typedef Kernel::Point_2                             Point_2;
typedef CGAL::Polygon_2<Kernel>                     Polygon_2;


#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>


int main () {
  std::string line;
  std::ifstream myfile ("Ostacles");
  char * pch;
  float x,y;
  int i=0;
  Polygon_2 obstacles [500];
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    { //Read a polygon
	Polygon_2   P;
	pch = NULL;
	char * cstr = new char [line.length()+1];
  	strcpy (cstr, line.c_str());
	pch = strtok (cstr," ;");
  	while (pch != NULL)
  	{
	 x = atof( pch );
    	 pch = strtok (NULL, " ;");
	 y = atof( pch );
	 pch = strtok (NULL, " ;");
	 P.push_back (Point_2 (x, y));
  	} 
	obstacles[i] = P; i++;   
    }
    myfile.close();
  }

  else std::cout << "Unable to open file"; 

  return 0;
}




