#ifndef SLIBC_SWIG_H
#define SLIBC_SWIG_H

#ifdef SWIG
%include "std_string.i"
%include "std_vector.i"
%include "std_pair.i"
%template(RectangleVector) std::vector<sl::Rectangle>;
%template(ObjectModelVector) std::vector<sl::ObjectModel>;
#endif

#endif //SLIBC_SWIG_H
