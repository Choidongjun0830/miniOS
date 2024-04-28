#include "memory_management.h"

void *partitions[NUM_PARTITIONS]; // 메모리 분할 배열

void init_partitions() { //파티션 초기화
    for (int i = 0; i < NUM_PARTITIONS; i++) {
        partitions[i] = NULL; //초기에는 메모리가 비어있음.
    }
}

//메모리 채워달라고 하면 채우는거? 파라미터로 인덱스 전달해서 거기 비어있으면 채우기?
void *allocate_memory() {
    for(int i = 0; i < NUM_PARTITIONS; i++) {
        if(partitions[i] == NULL) {
            partitions[i] = malloc(PARTITION_SIZE);
            fprintf(stderr, "Try to allocate memory for partitions[%d]\n", i);
            if (partitions[i] == NULL) { //할당 실패
               fprintf(stderr, "Failed to allocate memory for partition[%d]\n", i);
               return NULL;
            }
            memset(partitions[i], 0, PARTITION_SIZE); //partition[i]에 0으로 세팅. 메모리 크기 한 조각의 크기
            return partitions[i];
        }
    }
    //여기 까지오면 에러. 잘 실행된거면 for문에서 리턴 됐어야함.
    fprintf(stderr, "No available memory partitions\n");
    return NULL;
}

void free_memory(void *memory) {
    for(int i = 0; i < NUM_PARTITIONS; i++) {
        if (partitions[i] == memory) {
            free(partitions[i]);
            partitions[i] = NULL;
            return;
        }
    }
    fprintf(stderr, "Attempted to free a non-allocated partition\n");
    return;
}

void print_partitions() {
    printf("Partitions status:\n");
    for (int i = 0; i < NUM_PARTITIONS; i++) {
        printf("Partition %d: %p\n", i, partitions[i]);
    }
}

int fixedsize_memory_management() {
    init_partitions();

    printf("----- Print partitions after init ----- \n");
    print_partitions();

    //메모리 할당 시도
    void *mem1 = allocate_memory();
    if (mem1 != NULL) {
        printf("Allocated memory at %p\n", mem1);
    }

    printf("----- Print partitions after allocation ----- \n");
    print_partitions();

    //메모리 해제
    free_memory(mem1);
    printf("Memory at %p freed\n", mem1);

    printf("----- Print partitions after free ----- \n");
    print_partitions();

    return 0;
}
