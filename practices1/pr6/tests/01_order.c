#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

#define CMP_EQ(a, b) ((a) == (b))
#define CMP_LT(a, b) ((a) < (b))
#define CMP_GT(a, b) ((a) > (b))

typedef struct node
{
    int data;            // поле данных
    struct node* left;   // левый узел
    struct node* right;  // правый узел
    struct node* parent; // родительский узел
} node;

typedef struct tree
{
    struct node* _head; // Корень дерева
} tree;

// возведение в степень
int _powf(int x, int y)
{
    int tmp = x;
    while (y > 1)
    {
        y--;
        tmp = tmp * x;
    }
    return tmp;
}

// инициализация пустого дерева
void init(tree* t)
{
    t->_head = NULL;
}

// удаление элемента
node* cleanNode(node* n)
{
    if (n != NULL)
    {
        cleanNode(n->left);
        cleanNode(n->right);
        if (n->parent != NULL)
            n->parent = NULL;
        if (n->left != NULL)
            n->left = NULL;
        if (n->right != NULL)
            n->right = NULL;
        free(n);
    }
    return NULL;
}

// удалить все элементы дерева
void clean(tree* t)
{
    cleanNode(t->_head);
    t->_head = NULL;
}

// проверка дерева на пустоту
bool is_empty(tree* t)
{
    return t->_head == NULL;
}

// поиск элемента по значению. вернуть NULL если элемент не найден
node* find(tree* t, int value)
{
    if (!is_empty(t))
    {
        node* root = t->_head;
        while (root)
        {
            if (CMP_GT(root->data, value)) {
                root = root->left;
                continue;
            }
            else if (CMP_LT(root->data, value)) {
                root = root->right;
                continue;
            }
            else {
                return root;
            }
        }
        return NULL;
    }
    else return NULL;
}

node* findNode(node* root, int value)
{
    if (root)
    {
        //node *root = t->_head;
        while (root)
        {
            if (CMP_GT(root->data, value)) {
                root = root->left;
                continue;
            }
            else if (CMP_LT(root->data, value)) {
                root = root->right;
                continue;
            }
            else {
                return root;
            }
        }
        return NULL;
    }
    else return NULL;
}

// Создание нового узла
node* getFreeNode(int value, node* parent) {
    node* tmp = (node*)malloc(sizeof(node));
    tmp->left = tmp->right = NULL;
    tmp->data = value;
    tmp->parent = parent;
    return tmp;
}

/*
 0 - вставка выполнена успешно
 1 - элемент существует
 2 - не удалось выделить память для нового элемента
*/
int insert(tree* t, int value)
{
    if (is_empty(t))
    {
        t->_head = getFreeNode(value, NULL);
        return 0;
    }

    if (find(t, value) != NULL)
        return 1;

    node* tmp = t->_head;
    while (tmp != NULL)
    {
        if (CMP_GT(value, tmp->data))
        {
            if (tmp->right)
            {
                tmp = tmp->right;
                continue;
            }
            else
            {
                tmp->right = getFreeNode(value, tmp);
                return 0;
            }
        }
        else if (CMP_LT(value, tmp->data))
        {
            if (tmp->left)
            {
                tmp = tmp->left;
                continue;
            }
            else
            {
                tmp->left = getFreeNode(value, tmp);
                return 0;
            }
        }
        else
        {
            return 2;
        }
    }

    return 2;
}

// Поиск минимального узла
node* getMinNode(node* root)
{
    while (root->left) {
        root = root->left;
    }
    return root;
}

// Поиск максимального узла
node* getMaxNode(node* root)
{
    while (root->right) {
        root = root->right;
    }
    return root;
}

// Удаление узла по указателю
void removeNodeByPtr(node* target)
{
    if (target->left && target->right) {
        node* localMax = target->left->data > target->right->data ? target->left : target->right; //getMaxNode(target->left);
        target->data = localMax->data;
        removeNodeByPtr(localMax);
        return;
    }
    else if (target->left) {
        if (target == target->parent->left) {
            target->parent->left = target->left;
        }
        else {
            target->parent->right = target->left;
        }
    }
    else if (target->right) {
        if (target == target->parent->right) {
            target->parent->right = target->right;
        }
        else {
            target->parent->left = target->right;
        }
    }
    else {
        if (target == target->parent->left) {
            target->parent->left = NULL;
        }
        else {
            target->parent->right = NULL;
        }
    }
    free(target);
}

/*
 Удалить элемент из дерева:
  0 - удаление прошло успешно
  1 - нет элемента с указанным значением
*/
int remove_node(tree* t, int value)
{
    node* n = find(t, value);
    if (n != NULL)
    {
        removeNodeByPtr(n);
        return 0;
    }
    else return 1;
}

/*
 Удалить минимальный элемент из поддерева, корнем которого является n
 Вернуть значение удаленного элемента
*/
int remove_min(node* n)
{
    node* r = getMinNode(n);
    int res = r->data;
    removeNodeByPtr(r);
    return res;
}

// Поворот напрово
void l2rRotation(node* root) {
    node* C = NULL,
        * a = NULL,
        * b = NULL;

    a = root;

    b = a->right;
    if (b == NULL) {
        return;
    }
    C = b->left;
    b->parent = a->parent;

    if (a->parent != NULL) {
        if (a->parent->data > a->data)
            a->parent->left = b;
        else
            a->parent->right = b;
    }

    if (C != NULL)
        C->parent = a;

    a->right = C;
    a->parent = b;

    b->left = a;
}

// Поворот налево
void r2lRotation(node* root) {
    node* C = NULL,
        * a = NULL,
        * b = NULL;

    b = root;

    a = b->left;
    if (a == NULL) {
        return;
    }
    C = a->right;
    a->parent = b->parent;

    if (b->parent != NULL) {
        if (b->parent->data > b->data)
            b->parent->left = a;
        else
            b->parent->right = a;
    }
    if (C != NULL)
        C->parent = b;
    b->left = C;
    b->parent = a;
    a->right = b;
}

/*
 Выполнить правое вращение поддерева, корнем которого является n:
  0 - успешно выполненная операция
  1 - вращение невозможно
*/
int rotate_right(node* n)
{
    if (n != NULL)
    {
        if (n->right != NULL)
        {
            l2rRotation(n);
            //print( n->parent );
            return 0;
        }
        else return 1;
    }
    else return 1;
}

/*
 Выполнить левое вращение поддерева, корнем которого является n:
  0 - успешно выполненная операция
  1 - вращение невозможно
*/
int rotate_left(node* n)
{
    if (n != NULL)
    {
        if (n->left != NULL)
        {
            r2lRotation(n);

            return 0;
        }
        else return 1;
    }
    else return 1;
}

// Вывод значения предка и потомков
void print_node(node* n)
{
    if (n != NULL)
    {
        int p = n->parent != NULL ? n->parent->data : -1;
        int l = n->left != NULL ? n->left->data : -1;
        int r = n->right != NULL ? n->right->data : -1;
        printf((p != -1 ? "%d " : "_ "), p);
        printf((l != -1 ? "%d " : "_ "), l);
        printf((r != -1 ? "%d" : "_"), r);
        printf("\n\n");
    }
    else printf("-\n\n");
}

typedef struct struct_item {
    void* payload;
    struct struct_item* next;
} item;

typedef struct struct_queue {
    item* begin;
    item* end;
}queue;

queue* create_queue() {
    queue* res = malloc(sizeof(queue));
    res->begin = NULL;
    res->end = NULL;
    return res;
}

void queue_push(queue* q, void* payload) {
    item* i = malloc(sizeof(item));
    i->next = NULL;
    i->payload = payload;

    if (q->end == NULL) {
        q->begin = i;
        q->end = i;
    }
    else {
        q->end->next = i;
        q->end = i;
    }
}

void* queue_pop(queue* q) {
    if (q->begin == NULL) return NULL;
    item* current = q->begin;
    q->begin = q->begin->next;
    if (q->begin == NULL) q->end = NULL;
    void* payload = current->payload;
    free(current);
    return payload;
}

// Вывести все значения из поддерева, корнем которого является n
// по уровням начиная с корня.
// Каждый уровень выводится на своей строке.
// Элементы в строке разделяются пробелом. Если элемента нет, заменить на _.
// Если дерево пусто, вывести -
void print(node* root) {

    if (root == NULL)
    {
        printf("-\n\n");
        return;
    }

    queue* q_current = NULL;
    queue* q_next = create_queue();
    queue_push(q_next, (void*)root);
    int isNotLastLevel;
    do {
        free(q_current);
        q_current = q_next;
        q_next = create_queue();
        void* payload;
        isNotLastLevel = 0;
        while (q_current->begin != NULL) {
            payload = queue_pop(q_current);
            if (payload != NULL) {
                node* n = (node*)payload;
                printf("%d ", n->data);
                queue_push(q_next, n->left);
                queue_push(q_next, n->right);
                isNotLastLevel = isNotLastLevel || n->left || n->right;
            }
            else {
                printf("_ ");
                queue_push(q_next, NULL);
                queue_push(q_next, NULL);
            }
        }
        puts("");
    } while (isNotLastLevel);
    printf("\n");
}

// Вывести все значения дерева t, аналогично функции print
void print_tree(tree* t)
{
    print(t->_head);
}

// подсчет количества узлов дерева
int nodeCount(node* n)
{
    if (!n) return 0;

    if (n->left == NULL && n->right == NULL)
        return 1;

    int left, right;
    if (n->left != NULL)
        left = nodeCount(n->left);
    else
        left = 0;
    if (n->right != NULL)
        right = nodeCount(n->right);
    else
        right = 0;

    return left + right + 1;
}

// Задание 1 - обход в ширину
void print1(node* root) {

    if (root == NULL)
    {
        printf("-\n\n");
        return;
    }

    queue* q_current = NULL;
    queue* q_next = create_queue();
    queue_push(q_next, (void*)root);
    int isNotLastLevel;
    do {
        free(q_current);
        q_current = q_next;
        q_next = create_queue();
        void* payload;
        isNotLastLevel = 0;
        while (q_current->begin != NULL) {
            payload = queue_pop(q_current);
            if (payload != NULL) {
                node* n = (node*)payload;
                printf("%d ", n->data);
                queue_push(q_next, n->left);
                queue_push(q_next, n->right);
                isNotLastLevel = isNotLastLevel || n->left || n->right;
            }
        }
    } while (isNotLastLevel);
}


int main(void)
{
    int i, a;

    tree* t = malloc(sizeof(tree));
    init(t);

    for (i = 0; i < 7; i++)
    {
        scanf("%d", &a);
        insert(t, a);
    }

    print1(t->_head);

    return 0;
}
