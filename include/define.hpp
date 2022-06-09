#ifndef GEOCOLD_INCLUDE_DEFINE_HPP
#define GEOCOLD_INCLUDE_DEFINE_HPP

#if _WIN32 || _WIN64 
  #define PLATFORM_WINDOWS
#else
#if __linux__ 
  #define PLATFORM_LINUX
#elif __APPLE__
  #define PLATFORM_APPLE
#else
#error "Unable to determine the platform you're on."
#endif
#endif

#ifdef PLATFORM_WINDOWS 
 #define FORCEINLINE __forceinline;
 #define FORCENOINLINE __declspec(noinline)
#ifdef GEOCOLD_BUILD_LIB
 #define GEOCOLD_API __declspec(dllexport)
#else 
 #define GEOCOLD_API __declspec(dllimport)
#endif
#endif

#ifdef PLATFORM_LINUX
  #define FORCEINLINE inline
#endif

#ifdef PLATFORM_APPLE
  #defnie FORCEINLINE inline
#endif

// Assertions


#define ASSERTIONS_ENABLED

#ifdef ASSERTIONS_ENABLED
  #include <iostream>
  #define debugBreak() __debugBreak();
#else 
  #define debugBreak() __asm { int 3 } //this is an inline assembly code to break the application because there is no such thing as that instruction
#endif


FORCEINLINE void reportAssertionFailure(
    const char* expression,
    const char* message,
    const char* file,
    int line
    )
{
  std::cerr << "Assertion Failure : " << expression << ", message: '" << message << "' in file: " << file << ", line : " << line << '\n';
}

#define ASSERT(expr) { \
  if (expr) { \
  } else { \
    reportAssertionFailure(#expr, "", __FILE__, __LINE__); \
    debugBreak(); \
  } \
}

#define ASSERT_MSG(expr, message) { \
  if (expr) { \
  } else { \
    reportAssertionFailure(#expr, #message __FILE__, __LINE__); \
    debugBreak(); \
  } \
}

#ifdef _DEBUG
#define ASSERT(expr) { \
  if (expr) { \
  } else { \
    reportAssertionFailure(#expr, "", __FILE__, __LINE__); \
    debugBreak(); \
  } \
}
#endif




#endif //GEOCOLD_INCLUDE_DEFINE_HPP
