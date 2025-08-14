 # 🍜 PHILOSOPHERS 🍜

### THREADS
Thread synchronization is defined as a mechanism which ensures that two or more concurrent processes or threads do not simultaneously execute some particular program segment known as a critical section. Processes' access to critical section is controlled by using synchronization techniques. When one thread starts executing the critical section (a serialized segment of the program) the other thread should wait until the first thread finishes. If proper synchronization techniques are not applied, it may cause a race condition where the values of variables may be unpredictable and vary depending on the timings of context switches of the processes or threads. 

To compile a multithreaded program using gcc, we need to link it with the pthreads library.

#### CREATE A THREAD

> **int pthread_create** (pthread_t *restrict thread,
const pthread_attr_t *restrict attr,
void *(*start_routine)(void *),
void *restrict arg)
- **thread:** a pointer towards a pthread_t type variable, to store the ID of the thread we will be creating.
- **attr:** an argument that allows us to change the default attributes of the new thread. This is beyond the scope of this article, and in general, passing NULL here suffices.
- **start_routine:** the function where the thread will start its execution. This function will have as its prototype: void *function_name(void *arg);. When the thread reaches the end of this function, it will be done with its tasks.
- **arg:** a pointer towards an argument to pass to the thread’s start_routine function. If we’d like to pass several parameters to this function, we will need to give it a pointer to a data structure.
#### JOIN A THREAD
>**int pthread_join** (pthread_t thread, void **retval);
- thread: the ID of the thread that this thread should wait for. The specified thread must be joinable (meaning not detached - see below).
- retval: a pointer towards a variable that can contain the return value of the thread’s routine function (the start_routine function we supplied at its creation). Here, we will not need this value: a simple NULL will suffice.

#### DETACHE A THREAD
>**int pthread_detach** (pthread_t thread);
- thread: the ID of the thread that this thread should wait for. The specified thread must be joinable (meaning not detached - see below).

Tells the system to automatically reclaim resources once the thread terminates.

The pthread_join function returns 0 for success, or an error code for failure.
### RACE CONDITION
It occurs when 2 or more threads can access to data and try to modify it at the same time.

### MUTEX

So this ensures that once a thread has locked a piece of code then no other thread can execute the same region until it is unlocked by the thread who locked it.

> **int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr)**

Creates a mutex, referenced by mutex, with attributes specified by attr. If attr is NULL, the default mutex attribute (NONRECURSIVE) is used. Returned value If successful, pthread_mutex_init() returns 0, and the state of the mutex becomes initialized and unlocked. If unsuccessful, pthread_mutex_init() returns -1.

> **int pthread_mutex_lock(pthread_mutex_t *mutex)**

Locks a mutex object, which identifies a mutex. If the mutex is already locked by another thread, the thread waits for the mutex to become available. The thread that has locked a mutex becomes its current owner and remains the owner until the same thread has unlocked it. 
Returned value If successful, pthread_mutex_lock() returns 0. If unsuccessful, pthread_mutex_lock() returns -1.

> **int pthread_mutex_unlock(pthread_mutex_t *mutex)**

Releases a mutex object.
Returned value If successful, pthread_mutex_unlock() returns 0. If unsuccessful, pthread_mutex_unlock() returns -1

> **int pthread_mutex_destroy(pthread_mutex_t *mutex)**

Deletes a mutex object, which identifies a mutex.
Returned value If successful, pthread_mutex_destroy() returns 0. If unsuccessful, pthread_mutex_destroy() returns -1.

## SUBJECT
- No global variable allowed
- Tu programa debe aceptar los siguientes argumentos (5 or 6)
	- number_of_philosophers
	- time_to_die
	- time_to_eat
	- time_to_sleep
	- [number_of_times_each_philosopher_must_eat]
- Cada filósofo tendrá asignado un número del 1 al number_of_philosophers.

## FUNCTIONS

**gettimeofday()** int gettimeofday(struct timeval *tv, struct timezone *tz)

- Sets the current wall-clock time and/or timezone for the system.
- timeval tv: A pointer to a struct timeval where the current time will be stored.

 **memset** --> fills the first n bytes of the memory area
      pointed to by s with the constant byte c.
 **printf** \
 **malloc** \
 **free** \
 **write** \
 **usleep** \
 **pthread_create** \
 **pthread_detach** \
 **pthread_join** \
 **pthread_mutex_init** \
 **pthread_mutex_destroy** \
 **pthread_mutex_lock** \
 **pthread_mutex_unlock**

## OUTPUT
> Cualquier cambio de estado de un filósofo debe tener el siguiente formato:
>- timestamp_in_ms X has taken a fork
>- timestamp_in_ms X is eating 
>- timestamp_in_ms X is sleeping
>- timestamp_in_ms X is thinking
>- timestamp_in_ms X died

*Reemplaza timestamp_in_ms con la marca de tiempo actual en milisegundos
y X con el numero del filósofo.*

