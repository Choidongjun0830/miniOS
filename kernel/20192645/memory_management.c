#include "memory_management.h"
//memory block 1칸에 1024로
MemoryBlock memory_blocks[MAX_MEM_BLOCKS]; // 메모리 분할 배열
int next_id = 1; //random으로?

void init_partitions() {
    for (int i = 0; i < MAX_MEM_BLOCKS; i++) {
        memory_blocks[i].addr = NULL;
        memory_blocks[i].id = 0;
        memory_blocks[i].in_use_flag = 0;
    }
}


int fixedsize_memory_management() {
    init_partitions();

    printf("----- Print partitions after init ----- \n");
    print_memory_blocks();

    //메모리 할당 시도
    void *mem1 = fixed_allocate_memory();
    if (mem1 != NULL) {
        printf("Allocated memory at %p\n", mem1);
    }

    printf("----- Print partitions after allocation ----- \n");
    print_memory_blocks();

    //메모리 해제
    fixed_free_memory(mem1);
    printf("Memory at %p freed\n", mem1);

    printf("----- Print partitions after free ----- \n");
    print_memory_blocks();

    return 0;
}

void* fixed_allocate_memory() {
    for(int i = 0; i < MAX_MEM_BLOCKS; i++) {
        if(!memory_blocks[i].in_use_flag) {
            memory_blocks[i].addr = malloc(PARTITION_SIZE);
            fprintf(stderr, "Try to allocate memory for partitions[%d]\n", i);
            if (!memory_blocks[i].addr) { //할당 실패
               fprintf(stderr, "Failed to allocate memory for partition[%d]\n", i);
               return NULL;
            }
            memset(memory_blocks[i].addr, 0, PARTITION_SIZE); //memory_blocks[i]에 0으로 세팅. 메모리 크기 한 조각의 크기
            return memory_blocks[i].addr;
        }
    }
    //여기 까지오면 에러. 잘 실행된거면 for문에서 리턴 됐어야함.
    fprintf(stderr, "No available memory partitions\n");
    return NULL;
}

void fixed_free_memory(void *memory) {
    for(int i = 0; i < MAX_MEM_BLOCKS; i++) {
        if (memory_blocks[i].addr == memory) {
            free(memory_blocks[i].addr);
            memory_blocks[i].addr = NULL;
            return;
        }
    }
    fprintf(stderr, "Attempted to free a non-allocated partition\n");
    return;
}

//사이즈를 받고 할당하고 id 리턴
int dyna_alloc_ret_id(size_t size) {

    for(int i = 0; i < MAX_MEM_BLOCKS; i++) {
        if(!memory_blocks[i].in_use_flag) { //사용 중이 아니면
            memory_blocks[i].addr = malloc(size);
            if(!memory_blocks[i].addr) {
                return -1;
            }
            memory_blocks[i].id = next_id++;
            memory_blocks[i].in_use_flag = 1;
            memory_blocks[i].size = size;
            memset(memory_blocks[i].addr, 0, size);
            return memory_blocks[i].id;
        }
    }
    return -1; //할당 공간없음.
}

//id받아서 할당
void dyna_free(int free_id) {
    for(int i = 0; i < MAX_MEM_BLOCKS; i++) {
        if(memory_blocks[i].in_use_flag && memory_blocks[i].id == free_id) {
            free(memory_blocks[i].addr);
            memory_blocks[i].addr = NULL;
            memory_blocks[i].id = 0;
            memory_blocks[i].in_use_flag = 0;
            memory_blocks[i].size = 0;
            return;
        }
    }
    fprintf(stderr, "Attempted to free a non-allocated partition\n");
    return;
}

void print_memory_blocks() {
    printf("Memory Blocks Status:\n");
    for (int i = 0; i < MAX_MEM_BLOCKS; i++) {
        if (memory_blocks[i].in_use_flag) {  // 메모리 블록이 사용 중인지 확인
            printf("Block %d: ID=%d, Size=%zu, Address=%p\n", i, memory_blocks[i].id, memory_blocks[i].size, memory_blocks[i].addr);
        } else {
            printf("Block %d: UNUSED\n", i);  // 사용되지 않는 블록 표시
        }
    }
}
