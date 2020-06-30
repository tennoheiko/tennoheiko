#include <stdio.h>
#include <stdlib.h>


// Структура для хранения узла дерева
// Необходимо хранить ссылки на потомков, предка и некоторое значение
typedef struct node {
    int value;          // значение, которое хранит узел
    struct node* left;  // ссылка на левого потомка
    struct node* right;  // ссылка на правого потомка
    struct node* parent;  // ссылка на предка
} node;


// Структура для хранения дерева.
// Хранит ссылку на корень дерева и количество элементов в дереве
typedef struct tree {
    struct node* root;  // корень
    int qt; // количество элементов
} tree;


// Инициализация дерева
void init(tree* t) {
    t->root = NULL;
    t->qt = 0;
}


//Удаление элементов с рекурсией
node* cleant(node* t)
{
    if(t!=NULL)
    {
        cleant(t->left);
        cleant(t->right);
        if(t->parent!=NULL)
            t->parent = NULL;
        if(t->left!=NULL)
            t->left = NULL;
        if(t->right!=NULL)
            t->right = NULL;
        free(t);
    }
    return NULL;
}

// Удалить все элементы из дерева
void clean(tree* t)
{
        node* root = t->root;
        cleant(root);
        t->root = NULL;
}


// Поиск элемента по значению. Вернуть NULL если элемент не найден
node* find(tree* t, int value) {
    node* temp = t->root;
	while ((temp != NULL)&&(temp->value != value))
	{
		if (temp->value > value) {
			temp = temp->left;
                         continue;
                           }
		if (temp->value < value) {
			temp = temp->right;
                         continue;
                           }
	}
	return temp;
}


// проверка поиска элемента
void check(tree *t, int value) {
node *temp = find (t, value);
if (temp == NULL)
     printf("-\n");
else {
    if (temp->parent != NULL)
       printf("%d ", temp->parent->value);
        else printf ("_ ");
  if (temp->left != NULL)
     printf("%d ", temp->left->value);
        else printf ("_ ");
  if (temp->right != NULL)
         printf("%d", temp->right->value);
            else printf ("_");
   }
}


int insert(tree* t, int value) {
    node *prev = t->root, *next = NULL;
    node *temp = malloc(sizeof(node));
    temp->value = value;
    if (t->root == NULL) {
        temp->parent = NULL;
        temp->left = NULL;
        temp->right = NULL;
        t->root = temp;
        t->qt = 1;
        return 0;
    }
    while (prev != NULL) {
        next = prev;
        if (value == prev->value) {
            return 1;
        }
        if (value < prev->value) {
            prev = prev->left;
        }
        else {
        prev = prev->right;
        }
    }
    temp->parent = next;
    temp->left = NULL;
    temp->right = NULL;
    if (value < next->value) {
        next->left = temp;
        t->qt++;
        return 0;
    }
    if (value > next->value) {
        next->right = temp;
        t->qt++;
        return 0;
    }
}

// Удалить минимальный элемент из поддерева, корнем которого является n
// Вернуть значение удаленного элемента
int remove_min(node* n) {
    node* temp = n;
    int tempValue;
    while (temp->left != NULL)
        temp = temp->left;
    tempValue = temp->value;
    if (temp->right != NULL)
    {
        if (tempValue < temp->parent->value)
        {
            temp->parent->left = temp->right;
            free(temp);
            return tempValue;
        }
        else
        {
            temp->parent->right = temp->right;
            free(temp);
            return tempValue;
        }
    }
    else {
        if (tempValue < temp->parent->value)
        {
            temp->parent->left = NULL;
            free(temp);
            return tempValue;
        }
        else
        {
            temp->parent->right = NULL;
            free(temp);
            return tempValue;
        }
    }
}



// Удалить элемент из дерева:
// 0 - удаление прошло успешно
// 1 - нет элемента с указанным значением
int remove_node(tree* t, int value) {
    node* temp = find(t, value);
    if (temp == NULL)
        return 1;
    if ((temp->left == NULL) && (temp->right == NULL))
    {
        if (temp != t->root) {
            if (temp->value < temp->parent->value)
            {
                temp->parent->left = NULL;
                    free (temp);
                    t->qt--;
                    return 0;
            }
            else {
                temp->parent->right = NULL;
                free(temp);
                t->qt--;
                return 0;
            }
        }
        else {
            free(temp);
            t->root = NULL;
            t->qt=0;
            return 0;
        }
    }
    if ((temp->left == NULL) && (temp->right != NULL))
    {
        if (temp != t->root) {
            if (temp->value < temp->parent->value)
            {
                temp->parent->left = temp->right;
                    temp->right->parent = temp->parent;
                    free(temp);
                    t->qt--;
                    return 0;
            }
            else {
                temp->parent->right = temp->right;
                temp->right->parent = temp->parent;
                free(temp);
                t->qt--;
                return 0;
            }
        }
        else {
            temp->right->parent = NULL;
            t->root = temp->right;
            free(temp);
            t->qt--;
            return 0;
        }
    }
    if ((temp->left != NULL) && (temp->right == NULL))
    {
        if (temp != t->root) {
            if (temp->value < temp->parent->value)
            {
                temp->parent->left = temp->left;
                temp->left->parent = temp->parent;
                free(temp);
                t->qt--;
                return 0;
            }
            else {
                temp->parent->right = temp->left;
                temp->left->parent = temp->parent;
                free(temp);
                t->qt--;
                return 0;
            }
        }
        else {
            temp->left->parent = NULL;
            t->root = temp->left;
            free(temp);
            t->qt--;
                return 0;
        }
    }
    if ((temp->right != NULL) && (temp->left != NULL)) {
        temp->value = remove_min(temp->right);
        t->qt--;
        return 0;
    }
}


// Выполнить правое вращение поддерева, корнем которого является n:
// 0 - успешно выполненная операция
// 1 - вращение невозможно
int rotate_right(node* n) {
    node *temp = n;
    node *leftTemp = temp->left;
    node *rightTemp = leftTemp->right;
  leftTemp->parent = temp->parent;
    if (temp->parent != NULL) {
        if (temp->parent->value > temp->value)
              temp->parent->left = leftTemp;
                    else
                         temp->parent->right = leftTemp;
    }
    if (rightTemp != NULL)
             rightTemp->parent = temp;
    temp->left = rightTemp;
    temp->parent = leftTemp;
    leftTemp->right = temp;
    return 0;
}

// Выполнить левое вращение поддерева, корнем которого является n:
// 0 - успешно выполненная операция
// 1 - вращение невозможно
int rotate_left(node* n) {
    node *temp = n;
    node *rightTemp = temp->right;
    node *leftTemp = rightTemp->left;
    rightTemp->parent = temp->parent;
    if (temp->parent != NULL) {
        if (temp->parent->value > temp->value)
                temp->parent->left = rightTemp;
                     else
                             temp->parent->right = rightTemp;
    }
    if (leftTemp != NULL)
        leftTemp->parent = temp;
    temp->right = leftTemp;
    temp->parent = rightTemp;
    rightTemp->left = temp;
    return 0;
}


int rotateRootleft(tree* t)
{
        rotate_left(t->root);
    if (t->root->parent != NULL)
        t->root = t->root->parent;
    return 0;
}

int rotateRootright(tree* t)
{
        rotate_right(t->root);
    if (t->root->parent != NULL)
            t->root = t->root->parent;
        return 0;
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
                printf("%d ", n->value);
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
}


// Вывести все значения дерева t, аналогично функции print
void print_tree(tree* t) {
    if (t->root == NULL)
       printf("-\n");
         else
    print(t->root);
}

//Функция, возвращающая указатель на корень
node* getRoot(tree* t)
{
    return t->root;
}

//Вывод количества элементов в списке
void getQt(tree* t)
{
    printf("%d", t->qt);
}

int main() {
    int n, a;
    tree t;
    init(&t);
    for (int i=0; i < 4; ++i)
    {
        (void) scanf("%d", &a);
        insert(&t, a);
    }
    print_tree(&t);
  printf("\n");

    // Вводим еще три числа
    for (int i=0; i < 3; ++i)
    {
        (void) scanf("%d", &a);
        insert(&t, a);
    }
    print_tree(&t);
    printf("\n");

    // Поиск элементов
    for (int i=0; i < 2; ++i) {
    (void) scanf("%d", &a);
    check (&t, a);
        printf("\n\n");
  }

    // Удаление элемента
     (void) scanf("%d", &a);
   remove_node (&t, a);
     print_tree(&t);
     printf("\n");

     // Левый поворот
    node* tRoot =  getRoot (&t);
     if (tRoot != NULL)
     {
         while (tRoot->right != NULL)
         {
             rotateRootleft(&t);
      tRoot = getRoot (&t);
         }
     }
     printf("\n");
  print_tree(&t);

    // Правый поворот
  tRoot = getRoot (&t);
    if(tRoot != NULL)
    {
     while (tRoot->left != NULL)
     {
         rotateRootright(&t);
       tRoot = getRoot (&t);
     }
  }
  printf("\n");
  print_tree(&t);
    printf("\n");

 // Количество элементов
  getQt(&t);
  printf("\n\n");

 //Удаление дерева
  clean(&t);
  print_tree(&t);

  return 0;


};




