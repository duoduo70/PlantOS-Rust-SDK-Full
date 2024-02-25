// min0911_'s memory alloc library, the project began on 2023/11/18
// 
// 
//  ����������Ŀû��ʵ�ü�ֵ��Ϲд��
// 
// 
// -------------------------------------------------------------------
// idea: thought on 2023 11.18
// ���һ������ĳ��ӣ���insert����������Ͷ���ڴ棬insertҪע���ж��Ƿ����ڴ���е��ڴ��������ģ�����������ģ���ϲ�
// malloc ���������ڴ�أ��ҵ����������ģ�Ȼ��ɾ�����ڴ棬����
// free��������ڴ�����insert��ȥ
#pragma once
#include <stdint.h>
// Attention: *limit���ɱ�����
typedef enum {
	MMEMORY_NO_MORE_MEMORY, // �ڴ治����
	MMEMORY_NO_MORE_FREE_BLOCK, // �ڴ���Ƭ����
	MMEMORY_NOTHING, // û�д���
	MMEMORY_INVAILD_PARAMETER // �Ƿ�����
} MMEMORY_ERROR;
// start��limit����Ϊ0����������ӻ�ûʹ��
typedef struct {
	uint32_t start;
	uint32_t limit; // ���ɱ�����/д��
} mmemory_free;
typedef struct {
	int free_block_num_max; // ����ڴ���Ƭ��
	int useable_memory_for_user_start; // �û������ڴ�Ŀ�ʼ���ɷ���/д�룩
	int useable_memory_for_user_limit; // �û������ڴ����ߵ㣨���ɱ�����/д�룩
	MMEMORY_ERROR mmemory_err; // ����
	mmemory_free* memory_pool; // �ڴ��
}mm_head; // ͷ���ڶѵĿ�ͷ����¼һЩ��Ϣ


// ----------------------------------------
// macros
// ----------------------------------------

// �ж�ĳ�������Ƿ����
// --> start��limit��Ϊ0
//   --> start��limit ������Ϊ����
//     --> start+limit��Ϊ0����start=0��limit=0 
#define MMEMORY_IS_FREE(n) (n.start + n.limit == 0)
#define MMEMORY_IS_FREE_PTR(n) (n->start + n->limit == 0)

// ����ĳ�����ӿ���
#define MMEMORY_SET_FREE(n) n.start = 0;n.limit = 0
#define MMEMORY_SET_FREE_PTR(n) n->start = 0;n->limit = 0

// ��ȡĳ�����ӵĴ�С
#define MMEMORY_GET_SIZE(n) (n.limit - n.start)
#define MMEMORY_GET_SIZE_PTR(n) (n->limit - n->start)

// ----------------------------------------
// functions
// ----------------------------------------
mm_head* mmalloc_init(uint32_t start, uint32_t limit, uint32_t free_block_number_max);
void mmemory_insert(mm_head* head, uint32_t start, uint32_t limit);
void* mmemory_alloc(mm_head* head, uint32_t size);
void mmemory_set_free(mm_head* head, void* ptr, uint32_t size);