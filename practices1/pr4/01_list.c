#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
  int field;         // поле данных
  struct node *next; // указатель на следующий элемент
  struct node *prev; // указатель на предыдущий элемент
} node;

typedef struct list
{ 
    struct node *_head; // Голова списка
    struct node *_tail; // Конец списка
} list;

// инициализация пустого списка
void init(list *l)
{
    l->_head = NULL;
    l->_tail = NULL;
}

// удалить все элементы из списка
void clean(list *l)
{
    l->_head = NULL;
    l->_tail = NULL;
}

// проверка на пустоту списка
bool is_empty(list *l)
{
    return l->_head == NULL;
}

// поиск элемента по значению. вернуть NULL если элемент не найден
node *find(list *l, int value)
{
    if( !is_empty( l ) )
    {
        node *_n = l->_head;
        while( _n != NULL )
        {
            if( _n->field == value )
            {
                return _n;
            }
            _n = _n->next;
        }
        return NULL;
    } else return NULL;
}

// вставка значения в конец списка, вернуть 0 если успешно
int push_back(list *l, int value)
{
    node *_n = malloc( sizeof( node ));
    _n->field = value;
    _n->next = NULL;
    _n->prev = NULL;
    if( !is_empty( l ) )
    {
        node *_node = l->_head;
        while( _node != NULL )
        {
            if( _node->next != NULL )
                _node = _node->next;
            else
            {
                _n->prev = _node;
                _node->next = _n;
                l->_tail = _n;
                return 0;
            }
        }
        return -1;
    } 
    else
    {
        l->_head = _n;
        l->_tail = _n;
        return 0;
    }
}

// вставка значения в начало списка, вернуть 0 если успешно
int push_front(list *l, int value)
{
    node *_n = l->_head;
    node *_node = malloc( sizeof( node ));
    _node->field = value;
    _node->next = _n;
    _node->prev = NULL;
    if( is_empty( l ) ) 
        l->_tail = _node;
    l->_head = _node;
    return 0;
}

// вставка значения после указанного узла, вернуть 0 если успешно
int insert_after(list *l, int x, int j)
{
    if( !is_empty( l ))
    {
        int _c = 1;
        if( x < _c ) return -1;
        list *_l = malloc( sizeof( list ));
        node *_n = l->_head;
        int res = -1;
        while( _n != NULL )
        {
            push_back( _l , _n->field );
            if( _c == x )
            {
                push_back( _l , j );
                res = 0;
            }
            _n = _n->next;
            _c++;
        }
        l->_head = _l->_head;
        l->_tail = _l->_tail;
        return res;
    } else return -1;
}

// вставка значения до указанного узла, вернуть 0 если успешно
int insert_before(list *l, int x, int j)
{
    if( !is_empty( l ))
    {
        int _c = 1;
        if( x < _c ) return -1;
        list *_l = malloc( sizeof( list ));
        node *_n = l->_head;
        int res = -1;
        while( _n != NULL )
        {
            if( _c == x )
            {
                push_back( _l , j );
                res = 0;
            }
            push_back( _l , _n->field );
            _n = _n->next;
            _c++;
        }
        l->_head = _l->_head;
        l->_tail = _l->_tail;
        return res;
    } else return -1;
}

// удалить первый элемент из списка с указанным значением, вернуть 0 если успешно
int remove_first(list *l, int value)
{
    if( !is_empty( l ))
    {
        list *_l = malloc( sizeof( list ));
        node *_n = l->_head;
        int res = -1;
        bool f = false;
        while( _n != NULL )
        {
            if( _n->field == value && !f )
            {
                res = 0;
                f = true;
            } else
            {
                push_back( _l , _n->field );
            }
            _n = _n->next;
        }
        l->_head = _l->_head;
        l->_tail = _l->_tail;
        return res;
    } else return -1;
}

// удалить последний элемент из списка с указанным значением, вернуть 0 если успешно
int remove_last(list *l, int value)
{
    if( !is_empty( l ))
    {
        list *_l = malloc( sizeof( list ));
        node *_n = l->_tail;
        int res = -1;
        bool f = false;
        while( _n != NULL )
        {
            if( _n->field == value && !f )
            {
                res = 0;
                f = true;
            } else
            {
                push_front( _l , _n->field );
            }
            _n = _n->prev;
        }
        l->_head = _l->_head;
        l->_tail = _l->_tail;
        return res;
    } else return -1;
}

// вывести все значения из списка в прямом порядке через пробел, после окончания вывода перейти на новую строку
void print(list *l)
{
    if( !is_empty( l ))
    {
        node *_n = l->_head;
        while( _n != NULL )
        {
            printf( ( _n->next != NULL ) ? "%d " : "%d\n" , _n->field );
            _n = _n->next;
        }
    }
}

void print_invers(list *l)
{
    if( !is_empty( l ))
    {
        node *_n = l->_tail;
        while( _n != NULL )
        {
            printf( ( _n->prev != NULL ) ? "%d " : "%d\n" , _n->field );
            _n = _n->prev;
        }
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    list *l = malloc( sizeof( list ));
    init( l );
    for (int i = 0; i < n; i++)
    {
        int t;
        scanf("%d", &t);
        push_back( l , t );
    }
    print( l );
    int k1,k2,k3;
    scanf("%d", &k1);
    scanf("%d", &k2);
    scanf("%d", &k3);
    k1 = ( find( l , k1 ) != NULL ) ? 1 : 0;
    k2 = ( find( l , k2 ) != NULL ) ? 1 : 0;
    k3 = ( find( l , k3 ) != NULL ) ? 1 : 0;
    printf( "%d %d %d\n" , k1 , k2 , k3 );
    int m;
    scanf("%d", &m);
    push_back( l , m );
    print_invers( l );
    int t;
    scanf("%d", &t);
    push_front( l , t );
    print( l );
    int j,x;
    scanf("%d", &j);
    scanf("%d", &x);
    insert_after( l , j , x );
    print_invers( l );
    scanf("%d", &j);
    scanf("%d", &x);
    insert_before( l , j , x );
    print( l );
    int z;
    scanf("%d", &z);
    remove_first( l , z );
    print_invers( l );
    scanf("%d", &z);
    remove_last( l , z );
    print( l );
    clean( l );
    return 0;
}
