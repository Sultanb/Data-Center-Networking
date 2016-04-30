

typedef struct List list_t;
struct List {
  void * head;
  list_t * tail;
};

list_t * makelist (void * x, list_t * xs) {
  list_t * ans = (list_t *)malloc(sizeof(list_t));
  ans->head = x;
  ans->tail = xs;
  return ans;
}


// clients of our list implementation:
// [the clients that cast from void* to intptr_t are technically not legal C, 
//  as explained in detail below if curious]

// awful type casts to match what map expects
void* doubleInt(void* ignore, void* i) {
  return (void*)(((intptr_t)i)*2);
}

// assumes list holds intptr_t fields
list_t * doubleAll(list_t * xs) {
  return map(doubleInt, NULL, xs);
}

// awful type casts to match what filter expects
bool isN(void* n, void* i) {
  return ((intptr_t)n)==((intptr_t)i);
}

// assumes list hold intptr_t fields
int countNs(list_t * xs, intptr_t n) {
  return length(filter(isN, (void*)n, xs));
}

/*
  The promised explanation: Some of the client code above tries to use
  a number for the environment by using a number (intptr_t) where a
  pointer (void *) is expected.  This is technically not allowed: any
  pointer (including void*) can be cast to intptr_t (always) and the
  result can be cast back to the pointer type, but that is different
  than starting with an intptr_t and casting it to void* and then back
  to intptr_t.

  It appears there is no legal, portable way to create a number that
  can be cast to void* and back.  People do this sort of thing often,
  but the resulting code is not strictly portable.  So what should we
  do for our closures example besides ignore this and write
  non-portable code using int or intptr_t?
  
  Option 1 is to use an int* for the environment, passing a pointer to the
  value we need.  That is the most common approach and what we need to do for
  environments with more than one value in them anyway.  For the examples above,
  it would work to pass the address of a stack-allocated int, but that works
  only because the higher-order functions we are calling will not store those
  pointers in places where they might be used later after the stack variable
  is deallocated.  So it works fine for examples like map and filter, but would
  not work for callback idioms.  For those, the pointer should refer to memory
  returned by malloc or a similar library function.

  Option 2 is to change our approach to have the higher-order functions use
  intptr_t for the type of the environment instead of void*.  This works in
  general since other code can portably cast from any pointer type to
  intptr_t.  It is a less standard approach -- one commonly sees void* used
  as we have in the code above.
*/
