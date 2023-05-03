#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int key;
	struct Node* llink;  // 이전 노드를 가리키는 포인터
	struct Node* rlink;  // 다음 노드를 가리키는 포인터
} listNode;

typedef struct Head {
	struct Node* first;  // 리스트의 첫 번째 노드를 가리키는 포인터
}headNode;

int initialize(headNode** h);  // 연결 리스트 초기화
int freeList(headNode* h);  // 연결 리스트 메모리 해제
int insertNode(headNode* h, int key);  // 주어진 키를 가진 노드 삽입
int insertLast(headNode* h, int key);  // 마지막에 노드 삽입
int insertFirst(headNode* h, int key);  // 첫 번째에 노드 삽입
int deleteNode(headNode* h, int key);  // 주어진 키를 가진 노드 삭제
int deleteLast(headNode* h);  // 마지막 노드 삭제
int deleteFirst(headNode* h);  // 첫 번째 노드 삭제
int invertList(headNode* h);  // 연결 리스트 역순으로 뒤집기

void printList(headNode* h);  // 연결 리스트 출력

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);  // 연결 리스트 초기화
			break;
		case 'p': case 'P':
			printList(headnode);  // 연결 리스트 출력
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);  // 주어진 키를 가진 노드 삽입
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);  // 주어진 키를 가진 노드 삭제
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);  // 마지막에 노드 삽입
			break;
		case 'e': case 'E':
			deleteLast(headnode);  // 마지막 노드 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key); //맨 앞으로 노드 삽입
			break;
		case 't': case 'T':
			deleteFirst(headnode);		//앞 노드 삭제
			break;
		case 'r': case 'R':
			invertList(headnode);		//순서 바꾸기
			break;
		case 'q': case 'Q':		
			freeList(headnode);			//끝내기
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(headNode** h) {
    if (*h != NULL)
        freeList(*h); // 기존 리스트가 있다면 메모리 해제

    *h = (headNode*)malloc(sizeof(headNode)); // 헤드 노드 동적 할당
    (*h)->first = NULL; // 헤드 노드의 첫 번째 노드를 NULL로 초기화
    return 1; // 성공적으로 초기화되었음을 나타내는 값 반환
}

int freeList(headNode* h) {
    listNode* p = h->first; // 첫 번째 노드를 가리키는 포인터

    listNode* prev = NULL; // 이전 노드를 가리키는 포인터
    while (p != NULL) {
        prev = p; // 현재 노드를 prev에 저장
        p = p->rlink; // 다음 노드로 이동
        free(prev); // prev가 가리키는 노드를 메모리에서 해제
    }
    free(h); // 헤드 노드를 메모리에서 해제
    return 0; // 성공적으로 해제되었음을 나타내는 값 반환
}

void printList(headNode* h) {
    int i = 0; // 노드의 인덱스
    listNode* p;

    printf("\n---PRINT\n");

    if (h == NULL) {
        printf("Nothing to print....\n"); // 리스트가 비어있을 경우 출력
        return;
    }

    p = h->first; // 첫 번째 노드를 가리키는 포인터

    while (p != NULL) {
        printf("[ [%d]=%d ] ", i, p->key); // 현재 노드의 인덱스와 키 값을 출력
        p = p->rlink; // 다음 노드로 이동
        i++; // 인덱스 증가
    }

    printf("  items = %d\n", i); // 총 아이템 개수 출력
}

int insertLast(headNode* h, int key) {
    listNode* node = (listNode*)malloc(sizeof(listNode)); // 새로운 노드 동적 할당
    node->key = key; // 노드의 키 값을 설정
    node->rlink = NULL; // 노드의 다음 노드를 NULL로 초기화
    node->llink = NULL; // 노드의 이전 노드를 NULL로 초기화

    if (h->first == NULL) {
        h->first = node; // 리스트가 비어있을 경우 첫 번째 노드로 설정
        return 0; // 성공적으로 삽입되었음을 나타내는 값 반환
    }

    listNode* n = h->first; // 첫 번째 노드를 가리키는 포인터
    while (n->rlink != NULL) {
        n = n->rlink; // 마지막 노드
	}
	n->rlink = node;
	node->llink = n;
	return 0;
}

// 리스트의 마지막 노드를 삭제하는 함수
int deleteLast(headNode* h) {

	if (h->first == NULL) // 리스트가 비어있는 경우
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first; // 첫 번째 노드를 가리키는 포인터
	listNode* trail = NULL;

	if(n->rlink == NULL) { // 리스트에 노드가 하나만 있는 경우
		h->first = NULL;
		free(n);
		return 0;
	}

	// 리스트의 마지막 노드를 찾음
	while(n->rlink != NULL) {
		trail = n;
		n = n->rlink;
	}

	trail->rlink = NULL; // 마지막 노드의 이전 노드의 포인터를 NULL로 설정
	free(n); // 마지막 노드 삭제

	return 0;
}


// 리스트의 첫 번째에 노드를 추가하는 함수
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = node->llink = NULL;

	if(h->first == NULL) // 리스트가 비어있는 경우
	{
		h->first = node; // 첫 번째 노드로 추가
		return 1;
	}

	node->rlink = h->first; // 새로운 노드를 첫 번째 노드 앞에 추가
	node->llink = NULL;

	listNode *p = h->first;
	p->llink = node;
	h->first = node; // 첫 번째 노드로 설정

	return 0;
}
// 리스트의 첫 번째 노드를 삭제하는 함수
int deleteFirst(headNode* h) {

	if (h->first == NULL) // 리스트가 비어있는 경우
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first; // 첫 번째 노드를 가리키는 포인터
	h->first = n->rlink; // 첫 번째 노드의 다음 노드를 첫 번째 노드로 설정

	free(n); // 첫 번째 노드 삭제

	return 0;
}


// 리스트를 역순으로 변환하는 함수
int invertList(headNode* h) {

	if(h->first == NULL) // 리스트가 비어있는 경우
	{
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first; // 첫 번째 노드를 가리키는 포인터
	listNode *trail = NULL; // 이전 노드를 가리키는 포인터
	listNode *middle = NULL; // 현재 노드를 가리키는 포인터

	while(n != NULL){
		trail = middle; // middle을 trail로 이동
		middle = n; // n을 middle로 이동
		n = n->rlink; // 다음 노드로 이동
		middle->rlink = trail; // middle의 오른쪽 링크를 trail로 설정
		middle->llink = n; // middle의 왼쪽 링크를 n으로 설정
	}

	h->first = middle; // 마지막으로 middle을 첫 번째 노드로 설정

	return 0;
}


int insertNode(headNode* h, int key) {

// 먼저 새로운 노드를 동적할당한다.
listNode* node = (listNode*)malloc(sizeof(listNode));
node->key = key;
node->llink = node->rlink = NULL;

// 만약 이중연결리스트가 비어있다면 첫번째 노드로 삽입하고 종료한다.
if (h->first == NULL)
{
	h->first = node;
	return 0;
}

// 노드를 삽입할 위치를 찾기 위해 이중연결리스트를 탐색한다.
listNode* n = h->first;

while(n != NULL) {
	// 새로운 노드를 삽입할 위치를 찾았다면
	if(n->key >= key) {
		// 만약 찾은 위치가 첫번째 노드라면 insertFirst 함수를 호출하여 첫번째 노드로 삽입한다.
		if(n == h->first) {
			insertFirst(h, key);
		} else { 
			// 만약 찾은 위치가 첫번째 노드가 아니라면, 이전 노드와 다음 노드를 연결하고 새로운 노드를 삽입한다.
			node->rlink = n;
			node->llink = n->llink;
			n->llink->rlink = node;
		}
		return 0;
	}
	// 다음 노드를 탐색한다.
	n = n->rlink;
}

// 만약 삽입할 위치가 리스트의 맨 뒤라면 insertLast 함수를 호출하여 맨 뒤에 삽입한다.
insertLast(h, key);
return 0;
}

// 주어진 키 값을 가진 노드를 이중 연결 리스트에서 삭제하는 함수입니다.
// 노드 삭제가 성공하면 1을 반환하고, 그렇지 않으면 0을 반환합니다.
int deleteNode(headNode* h, int key) {

    // 리스트가 비어있는 경우, 메시지를 출력하고 1을 반환합니다. (삭제 실패)
    if (h->first == NULL)
    {
        printf("삭제할 노드가 없습니다.\n");
        return 1;
    }

    // 현재 노드를 가리키는 포인터를 헤드 노드로 초기화합니다.
    listNode* n = h->first;

    // 리스트를 순회하면서 삭제할 노드를 찾습니다.
    while(n != NULL) {
        // 삭제할 노드를 찾은 경우
        if(n->key == key) {
            // 만약 삭제할 노드가 첫번째 노드라면 deleteFirst 함수를 호출하여 첫번째 노드를 삭제합니다.
            if(n == h->first) { 
                deleteFirst(h);
            } 
            // 만약 삭제할 노드가 마지막 노드라면 deleteLast 함수를 호출하여 마지막 노드를 삭제합니다.
            else if (n->rlink == NULL){ 
                deleteLast(h);
            } 
            // 그 외의 경우, 삭제할 노드의 이전 노드와 다음 노드를 연결하고 메모리를 해제합니다.
            else { 
                n->llink->rlink = n->rlink;
                n->rlink->llink = n->llink;
                free(n);
            }
            return 1;
        }

        // 다음 노드로 이동합니다.
        n = n->rlink;
    }

    // 삭제할 노드를 찾지 못한 경우, 해당 키값을 가진 노드를 찾을 수 없다는 메시지를 출력합니다.
    printf("키값 %d에 해당하는 노드를 찾을 수 없습니다.\n", key);
    return 1;
}

