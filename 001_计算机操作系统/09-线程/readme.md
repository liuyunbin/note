
## 线程
```
* pthread_equal()
* pthread_self()
* pthread_create()
* pthread_exit()
* pthread_join() -- 等待线程终止
* pthread_cancel() -- 取消线程
* pthread_cleanup_push() -- 线程正常退出或被取消时执行
* pthread_cleanup_pop() ---
* pthread_detach() -- 线程设置为游离态
```

## 互斥锁 -- 资源的原子访问
```
* pthread_mutex_init()
* pthread_mutex_destroy()
* pthread_mutex_lock()
* pthread_mutex_trylock()
* pthread_mutex_unlock()
* pthread_mutex_timedlock()
```

## 读写锁 -- 使用于读远大于写的情况
```
* pthread_rwlock_init()
* pthread_rwlock_destroy()
* pthread_rwlock_rdlock()
* pthread_rwlock_tryrdlock()
* pthread_rwlock_wrlock()
* pthread_rwlock_trywrlock()
* pthread_rwlock_unlock()
* pthread_rwlock_timedrdlock()
* pthread_rwlock_timewrdlock()
```

## 条件变量 -- 等待某一条件满足
```
* pthread_cond_init()
* pthread_cond_destroy()
* pthread_cond_timedwait()
* pthread_cond_wait()
* pthread_cond_signal()
* pthread_cond_broadcast()
```

## 自旋锁
```
* pthread_spin_init()
* pthread_spin_destroy()
* pthread_spin_lock()
* pthread_spin_trylock()
* pthread_spin_unlock()
```

## 屏障
```
* pthread_barrierattr_init
* pthread_barrier_destroy
* pthread_barrier_wait
```

