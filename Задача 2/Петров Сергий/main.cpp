//
//  main.cpp
//  buddy_allocator
//
//  Created by Сергий Петров on 19/04/2019.
//  Copyright © 2019 Сергий Петров. All rights reserved.
//

#include <iostream>
#include <cmath>

class Chunk
{
public:
    Chunk* next;
    Chunk* prev;
    int* ptr;
    int startIdx;
    bool isFree;
    int size;
    
    Chunk(int size1) {
        ptr = (int*)malloc(size1);
        size = size1;
        isFree = true;
    }
    
    ~Chunk()
    {
        free(ptr);
    }
    
};


class BuddyAllocator
{
private:
    Chunk *pointer;
    int size;
    int chunks_amount;
    
    Chunk* findMinChunk(int needed_chunk) {
        auto chunk = pointer;
        Chunk* suitable_chunk = NULL;
        int min_suitable_chunk_size = size + 1;
        for (int i = 0; i < chunks_amount; i++) {
            chunk = chunk->next;
            int chunk_size = chunk->size;
            if (chunk->isFree) {
                if (needed_chunk <= chunk_size && chunk_size < min_suitable_chunk_size) {
                    min_suitable_chunk_size = chunk_size;
                    suitable_chunk = chunk;
                }
            }
        };
        return suitable_chunk;
    }
    
    Chunk* SplitChunk(Chunk* chunk) {
        int buddy_sizes = chunk->size / 2;
        auto prev_chunk = chunk->prev;
        auto next_chunk = chunk->next;
        auto left_chunk = new Chunk(buddy_sizes);
        auto right_chunk = new Chunk(buddy_sizes);
        splitChunksUsing(left_chunk, chunk, right_chunk, prev_chunk, next_chunk);
        delete chunk;
        this->chunks_amount += 1;
        return left_chunk;
    }
    
    void splitChunksUsing(Chunk* left, Chunk* chunk, Chunk* right, Chunk* prev, Chunk* next) {
        prev->next = left;
        next->prev = right;
        left->next = right;
        left->prev = prev;
        right->next = next;
        right->prev = left;
        left->startIdx = chunk->startIdx;
        right->startIdx = chunk->startIdx + (chunk->size / 2);
    }
    
    Chunk* MergeChunks(Chunk* chunk, Chunk* buddy) {
        int new_size = chunk->size * 2;
        auto prev_chunk = chunk->prev;
        auto next_chunk = buddy->next;
        auto new_chunk = getNewChunk(next_chunk, prev_chunk, new_size, chunk->startIdx);
        delete buddy;
        delete chunk;
        this->chunks_amount -= 1;
        return new_chunk;
    }
    
    void mergeChunksIfNeeded(Chunk* chunk) {
        int size = chunk->size;
        int offset = chunk->startIdx / size;
        auto maybe_buddy = (offset % 2 == 0) ? chunk->next : chunk->prev;
        auto delta = (offset % 2 == 0) ? -1 : 1;
        if (maybe_buddy->isFree && maybe_buddy->size == size &&
            maybe_buddy->startIdx / size + delta == offset) {
            chunk = MergeChunks(chunk, maybe_buddy);
            mergeChunksIfNeeded(chunk);
        }
    }
    
    int getRequiredSizeFor(int size) {
        int default_size = this->size;
        int required_size = this->size + 1;
        while (size <= default_size) {
            required_size = default_size;
            default_size /= 2;
        }
        return required_size;
    }
    
    Chunk* getNewChunk(Chunk* next, Chunk* prev, int size, int index) {
        Chunk* new_chunk = new Chunk(size);
        prev->next = new_chunk;
        next->prev = new_chunk;
        new_chunk->next = next;
        new_chunk->prev = prev;
        new_chunk->startIdx = index;
        return new_chunk;
    }
    
    
public:
    BuddyAllocator(int size_t) {
        this->size = (int)pow(2, ceil(log2(size_t)));
        this->pointer = new Chunk(1);
        auto chunk = new Chunk(this->size);
        this->pointer->prev = pointer;
        this->pointer->next = chunk;
        chunk->prev = pointer;
        chunk->next = chunk;
        this->chunks_amount = 1;
    }
    
    void* alloc(int size) {
        auto required_size = getRequiredSizeFor(size);
        auto required_chunk = findMinChunk(required_size);
        if (required_chunk == NULL) {
            std::cerr << "No free chunk available\n";
            exit(1);
        }
        
        int chunk_size = required_chunk->size;
        while (chunk_size != required_size) {
            required_chunk = SplitChunk(required_chunk);
            chunk_size = required_chunk->size;
        }
        required_chunk->isFree = false;
        return required_chunk->ptr;
    }
    
    void free(void *ptr) {
        Chunk* chunk = pointer;
        for (int i = 0; i < chunks_amount; i++) {
            chunk = chunk->next;
            if (chunk->ptr == ptr) {
                chunk->isFree = true;
                break;
            }
        }
        
        mergeChunksIfNeeded(chunk);
    }
    
    void dump() {
        auto chunk = pointer;
        for (int i = 0; i < chunks_amount; i++) {
            chunk = chunk->next;
            if (chunk->isFree) {
                std::cout << "free: ";
            } else {
                std::cout << "captured: ";
            }
            std::cout << chunk->startIdx << ", " << chunk->startIdx + chunk->size-1 << "\n";
        };
        std::cout << "\n";
    }
    
    ~BuddyAllocator()
    {
        free(pointer);
    }
    
};



int main(int argc, const char * argv[]) {

    auto allocator = BuddyAllocator((int)pow(2, 10));
    auto ptr1 = allocator.alloc(6);
    for (auto i = 2; i < 10; i++) {
        allocator.alloc(6*i);
        std::cout << "Operation: " << i-1 << "\n";
        allocator.dump();
    }
    allocator.free(ptr1);
    std::cout << "After free:\n";
    allocator.dump();
    return 0;
}
