/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmTag.h"
#include "gdcmStringStream.h"

int TestTag(int , char * [])
{
  const uint32_t dummy = 0x12345678;
  gdcm::Tag t16(0x1234, 0x5678);
  gdcm::StringStream ss;
  t16.Write( ss );
  gdcm::Tag t16_2;
  t16_2.Read( ss );

  gdcm::Tag t1;
  gdcm::Tag t2(0,0);
  if ( t1[0] != 0 )
    {
    std::cerr << "1" << std::endl;
    return 1; 
    }
  if (t1[1] != 0 )
    {std::cout << "2" << std::endl ; return 1; }
    
  if (t2[0] != 0 )
    {std::cout << "3" << std::endl ; return 1; }
  if (t2[1] != 0 )
    {std::cout << "4" << std::endl ; return 1; }
    
  if ( !(t1 == t2) )
    {std::cout << "5" << std::endl ; return 1; }
  if ( t1 != t2 )
    {std::cout << "6" << std::endl ; return 1; }
  if ( t1 < t2 )
    {std::cout << "7" << std::endl ; return 1; }

  unsigned int i;

  const uint32_t tag = dummy;
  std::cout << "Just to inform : uint32_t value=" << std::hex << tag ; 
  std::cout << " stored in RAM as :";  
  for (i=0;i<sizeof(uint32_t);i++) 
    {
    std::cout << std::hex <<"[" <<(uint32_t)((uint8_t*)&tag)[i] << "] " ;
    }
  std::cout << std::endl;

  const uint16_t group   = 0x1234;
  const uint16_t element = 0x5678;

  std::cout << "Just to inform : uint16_t values= " << group <<"," << element ; 
  std::cout << " stored in RAM as : ";  
  for (i=0;i<sizeof(uint16_t);i++) 
    {
    std::cout << std::hex <<"[" <<(uint32_t)((uint8_t*)&group)[i] << "] " ;
    }
  for (i=0;i<sizeof(uint16_t);i++) 
    {
    std::cout << std::hex <<"[" <<(uint32_t)((uint8_t*)&element)[i] << "] " ;
    }
  std::cout << std::endl;

  std::cout << "Constructor with 2 x uin16_t : " << group <<"," << element
    << std::endl;

  const gdcm::Tag t3(group, element);
  std::cout << "t3=" << t3 << std::endl;
  if( t3.GetGroup() != t3[0] )
    {std::cout << "8"  << std::endl ; return 1; }
  if( t3.GetElement() != t3[1] )
    {std::cout << "9"  << std::endl ; return 1; }
  if( !(t3 == gdcm::Tag(group, element)) )
    {std::cout << "10" << std::endl ; return 1; }
  if ( t3 != gdcm::Tag(group, element) )
    {std::cout << "11" << std::endl ; return 1; }
  if( t3[0] == t3[1] )
    {std::cout << "13" << std::endl ; return 1; }
  if( t3 < t1 )
    {std::cout << "14" << std::endl ; return 1; }


  std::cout << "Constructor with 1x uin32_t : " << std::hex <<tag <<std::endl;  
  const gdcm::Tag t4(tag);
  std::cout << "t4=" << t4 << std::endl;     
  if( t4.GetGroup() != group )
    {std::cout << "15" << std::endl ; return 1; }
  if( t4.GetElement() != element )
    {std::cout << "16" << std::endl ; return 1; }
  if ( !(t4 == gdcm::Tag(group, element)) )
    {std::cout << "17" << std::endl ; return 1; }
  if ( t4 != gdcm::Tag(group, element) )
    {std::cout << "18" << std::endl ; return 1; }
  if( t4[0] == t3[1] )
    {std::cout << "19" << std::endl ; return 1; }
  if( t4 != t3 )
    {std::cout << "20" << std::endl ; return 1; }
  if( !(t4 == t3) )
    {std::cout << "21" << std::endl ; return 1; }

  if( t4.GetElementTag() != tag )
    {std::cout << "22" << std::endl;
    std::cout << std::hex << t4.GetElementTag() << std::endl; 
    std::cout << std::hex << tag << std::endl; 
    return 1;
    }

  if( t3 < t4 )
    {std::cout << "23" << std::endl ; return 1; }

  std::cout << "T1: " << t1 << std::endl;
  std::cout << "T2: " << t2 << std::endl;
  std::cout << "T3: " << t3 << std::endl;
  std::cout << "T4: " << t4 << std::endl;

  std::cout << "Constructor with 2 x uin16_t" << std::endl;
  // Test ordering:
  gdcm::Tag o1(0x0000,0x0000);
  gdcm::Tag o2(0x0010,0x0000);
  gdcm::Tag o3(0x0000,0x0010);
  gdcm::Tag o4(0x0010,0x0010);
  std::cout << " o1:" << o1 << " o2:" << o2 << " o3:" << o3 << " o4:" << o4
    << std::endl;

  // Clearly order should be o1 < o3 < o2 < 04
  // Test o1
  if( !(o1 < o3)
    ||!(o1 < o2) 
    ||!(o1 < o4) )
    {std::cout << "24" << std::endl ; return 1; }

  // Test o2
  if( !(o2 < o4)
    ||!(o1 < o2) 
    ||!(o3 < o2) )
    {std::cout << "25" << std::endl ; return 1;}

  // Test o3
  if( !(o3 < o2)
    ||!(o3 < o4) 
    ||!(o1 < o3) )
    {std::cout << "26" << std::endl ; return 1; }

  // Test o4 (I know this duplicate some tests, but we don't need to optimize a test!)
  if( !(o1 < o4)
    ||!(o2 < o4) 
    ||!(o3 < o4) )
    {std::cout << "27" << std::endl ; return 1; }


  std::cout << "Constructor with 1 x uin32_t" << std::endl;
  gdcm::Tag O1(0x00000000);
  gdcm::Tag O2(0x00100000);
  gdcm::Tag O3(0x00000010);
  gdcm::Tag O4(0x00100010);

  std::cout << " O1:" << O1 << " O2:" << O2 << " O3:" << O3 << " O4:" << O4
    << std::endl;


  // Clearly order should be O1 < O3 < O2 < 04
  // Test O1
  if( !(O1 < O3)
    ||!(O1 < O2) 
    ||!(O1 < O4) )
    {std::cout << "28" << std::endl ; return 1; }

  // Test O2
  if( !(O2 < O4)
    ||!(O1 < O2) 
    ||!(O3 < O2) )
    {std::cout << "29" << std::endl ; return 1;}

  // Test O3
  if( !(O3 < O2)
    ||!(O3 < O4) 
    ||!(O1 < O3) )
    {std::cout << "30" << std::endl ; return 1; }

  // Test O4 (I know this duplicate some tests, but we don't need to optimize a test!)
  if( !(O1 < O4)
    ||!(O2 < O4) 
    ||!(O3 < O4) )
    {std::cout << "31" << std::endl ; return 1; }

  return 0;
}
