#ifndef _TS_ATTRIBUTES_H
#define _TS_ATTRIBUTES_H

#ifndef __GNUC__
	#error "Compiler not supported"
	#define ATTR(attrs) ((void) 0)
#else
	/* Automatic attribute definition/expansion for one or more attributes */
	#define ATTR(attrs, ...) __attribute__((attrs, ##__VA_ARGS__))

	/* Indicates a function that should run before main */
	#define ATTR_CTOR ATTR(constructor)

	/* Indicates a function that should run after main */
	#define ATTR_DTOR ATTR(destructor)

	/* Forces the compiler to inline the function */
	#define ATTR_INLINE ATTR(always_inline)

	/* Informs the compiler that no paramters should be NULL */
	#define ATTR_NONNULL ATTR(nonnull)

	/* Indicates a function that never returns */
	#define ATTR_NORETURN ATTR(noreturn)
#endif

#endif
