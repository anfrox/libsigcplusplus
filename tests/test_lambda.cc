// -*- c++ -*-
/* Copyright 2002, The libsigc++ Development Team
 *  Assigned to public domain.  Use as you wish without restriction.
 */

#include <iostream>
#include <sigc++/functors/functors.h>
#include <sigc++/adaptors/lambda/lambda.h>

using namespace sigc::functor;

int foo(int i, int j)
  {std::cout << "foo(int "<<i<<", int "<<j<<")" << std::endl; return 4*i+j;}

main()
{
  // test lambda operators
  std::cout << (_1 + _2)(3,4) << std::endl;
  std::cout << (_1 + 1) (3,4) << std::endl;
  std::cout << (_2 + 1) (3,4) << std::endl;
  std::cout << (2 + _1) (3,4) << std::endl;
  std::cout << (2 + _2) (3,4) << std::endl;
  std::cout << (_1+_2*_3) (1,2,3) << std::endl;

  // test grp adaptor
  std::cout << (group(ptr_fun(&foo), _1, _2)) (1, 2) << std::endl;
  std::cout << (group(ptr_fun(&foo), _2, _1)) (1, 2) << std::endl;

  // same functionality as bind
  std::cout << (group(ptr_fun(&foo), _1, 2))  (1)    << std::endl;
  std::cout << (group(ptr_fun(&foo), 1, 2))   ()     << std::endl;

  //TODO: is there an equivalent for bind_return ?

  // same functionality as hide
  std::cout << (group(ptr_fun(&foo), _1, _2)) (1,2,3) << std::endl;

  // same functionality as compose
  std::cout << (group(ptr_fun(&foo), group(ptr_fun(&foo), _1, _2), _3)) (1,2,3) << std::endl;

  //TODO: code doesn't compile: the lambdas return std::ostream instead of std::ostream&.
  //      The reason is that withh gcc-3.2 typeof(std::ostream& << int) == std::ostream (instead of std::ostream).
  //      Probably, this is a compiler error.
//  (lambda<std::ostream&>(std::cout) << 1)();
//  (lambda<std::ostream&>(std::cout) << _1)("hello world");
}
