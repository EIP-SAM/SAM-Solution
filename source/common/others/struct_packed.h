#ifndef STRUCT_PACKED_H_
# define STRUCT_PACKED_H_

//
// Here is an easy way to declare a packed structure
// wihtout paying attention to the OS and the compiler
// Usage example:
//
// STRUCT_PACKED(toto,
//     int foo;
//     char bar;
// );
// struct toto;
//
// Note: (nov 2015) Works fine with g++ 5.2.0, and MSVC 2013
// Note2: Why adding an other declaration of the structure right
//  after the first one ? To make your IDE/Editor happy; like that
//  you are sure that the type is well defined, and recocognized for
//  the syntaxic coloration; plus, the indentation may be broken
//  after the usage of the macro, so it tries to reset it
//

# if __GNUC__

#  define STRUCT_PACKED(name, declaration) \
    struct name \
    { \
        declaration \
    } \

# elif _WIN32

#  define STRUCT_PACKED(name, declaration) \
    __pragma(pack(push, 1)) \
    struct name \
    { \
        declaration \
    } \

# endif // !_WIN32 || !__GNUC__

#endif // !STRUCT_PACKED_H_
