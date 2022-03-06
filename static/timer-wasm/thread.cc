#include <stdio.h>
#include <pthread.h>
#include <malloc.h>

#ifndef EM_PORT_API
#if defined(__EMSCRIPTEN__)
#include <emscripten.h>
#if defined(__cplusplus)
#define EM_PORT_API(rettype) extern "C" rettype EMSCRIPTEN_KEEPALIVE
#else
#define EM_PORT_API(rettype) rettype EMSCRIPTEN_KEEPALIVE
#endif
#else
#if defined(__cplusplus)
#define EM_PORT_API(rettype) extern "C" rettype
#else
#define EM_PORT_API(rettype) rettype
#endif
#endif
#endif

int *count = (int *)malloc(sizeof(int));
void *func(void *arg)
{

    while (true)
    {
        count[0]++;
        // printf("thread count %d\n", count[0]);
        // sleep(1);
    }
    return (void *)1;
}

EM_PORT_API(int*)
createThread(int argc, char *argv[])
{
    count[0] = 0;
    pthread_t tid;
    void *tret;

    //设置线程属性分离
    pthread_attr_t attr;
    pthread_attr_init(&attr);                                    //初始化属性设置
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED); //设置线程分离
    pthread_create(&tid, &attr, func, NULL);                     //创建线程，传入属性设置参数

    return count; // 返回指针
}