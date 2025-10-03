
#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN     // Exclude rarely-used stuff from Windows headers
    #include <windows.h>
#else
    #include <sys/time.h>
    #include <string.h>
    #include <stdlib.h>
#endif

#include <vector>
#include <atomic>
#include <thread>

//-----------------------------------------------
// Volatile vs. Atomic Test
//-----------------------------------------------
int num_reads = 20000000;
int num_writes = 20000000;
const int num_threads = 5;
volatile uint32_t volatile_counter = 0;
std::atomic<uint32_t> atomic_counter(0);

//-----------------------------------------------
uint64_t get_micro_time() {

#ifdef _WIN32
    LARGE_INTEGER iTime, iFrequency;
    QueryPerformanceFrequency(&iFrequency);
    QueryPerformanceCounter(&iTime);
    iTime.QuadPart *= 1000000;
    iTime.QuadPart /= iFrequency.QuadPart;
    return (uint64_t)iTime.QuadPart;
#else
    struct timeval tv;
    gettimeofday(&tv, 0);
    return ((long long)tv.tv_sec * 1000000) + tv.tv_usec;
#endif

}

//-----------------------------------------------
void write_atomic_counter() {

    uint32_t val = 0;
    for (int i=0; i<num_writes; i++) {
        val = atomic_counter.fetch_add(1, std::memory_order_relaxed);
        //val = atomic_counter++;
        //val = atomic_counter.load(std::memory_order_relaxed);
        //atomic_counter.store(val+1, std::memory_order_relaxed);
    }
    //printf("[1] Value ATOMIC WRITE = %d\n", val);
}

//-----------------------------------------------
void read_atomic_counter(int id) {

    uint32_t val = 0;
    for (int i=0; i<num_reads; i++) {
        val = atomic_counter.load(std::memory_order_relaxed);
    }
    //printf("[%d] ATOMIC READ = %d\n", id, val);
}

//-----------------------------------------------
void write_volatile_counter() {

    uint32_t val = 0;
    for (int i=0; i<num_writes; i++) {
        val = volatile_counter++;
    }
    //printf("[1] Value VOLATILE WRITE = %d\n", val);
}

//-----------------------------------------------
void read_volatile_counter(int id) {

    uint32_t val = 0;
    for (int i=0; i<num_reads; i++) {
        val = volatile_counter;
    }
    //printf("[%d] VOLATILE READ = %d\n", id, val);
}

//-----------------------------------------------
int main() {

    uint64_t time_start = 0;
    uint64_t time_elapsed = 0;

    // ATOMIC
    std::vector<std::thread> read_threads_atomic;
    atomic_counter = 0;
    std::thread write_thread_atomic(write_atomic_counter);     
    time_start = get_micro_time();
    for (int t=0; t<num_threads; t++) {
        read_threads_atomic.emplace_back(read_atomic_counter, (t+1));
    }
    for (std::thread& t : read_threads_atomic) { t.join(); }
    time_elapsed = get_micro_time() - time_start;
    write_thread_atomic.join();
    printf("time_elapsed ATOMIC   = %llu us\n", time_elapsed);

    // VOLATILE
    std::vector<std::thread> read_threads_volatile;
    volatile_counter = 0;
    std::thread write_thread_volatile(write_volatile_counter);
    time_start = get_micro_time();
    for (int t=0; t<num_threads; t++) {
        read_threads_volatile.emplace_back(read_volatile_counter, (t+1));
    }
    for (std::thread& t : read_threads_volatile) { t.join(); }
    time_elapsed = get_micro_time() - time_start;
    write_thread_volatile.join();
    printf("time_elapsed VOLATILE = %llu us\n", time_elapsed);

    return 0;
}
