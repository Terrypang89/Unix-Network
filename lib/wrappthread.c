
// thread functions do not set the standard Unix errno variable when an error occurs


// every time we call one of the pthread_ functions, 
// we must allocate a variable, save the return value in that variable, 
// and then set errno to this value before calling err_sys
void
Pthread_mutex_lock(pthread_mutex_t *mptr)
{
    int n;
    if ( (n = pthread_mutex_lock(mptr)) == 0)
        return;
    errno = n;
    err_sys("pthread_mutex_lock error");
}