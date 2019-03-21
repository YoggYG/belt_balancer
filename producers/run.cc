#include "producers.ih"

void Producers::run(size_t n, size_t power, size_t rows, size_t cols, size_t undergroundLength)
{
    for (size_t idx = d_producers.size(); idx--; )     // start the producer
        d_thread[idx] = thread(ref(d_producers[idx]), n, power, rows, cols, undergroundLength); // threads
}
