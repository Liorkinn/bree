//#include <bits/stdc++.h>
#include <iostream>
using namespace std;


const int N = 8;
struct node 
{
    int key[N - 1];
    // ключ из N-1 узлов  
    // Дочерний массив длины 'N'
    struct node* child[N];
    // Чтобы указать, является ли лист или нет; если узел
    // это лист, isleaf = 1, иначе isleaf = 0
    int isleaf;
    // Подсчитывает количество заполненных ключей в узле
    int n;
    // Отслеживает родительский узел
    struct node* parent;
};

// Эта функция ищет лист
// в который нужно вставить элемент 'k'

struct node* searchforleaf(struct node* root, int k,
    struct node* parent, int chindex)
{
    if (root)
    {
        // Если переданный корень является листовым узлом, то
        // k может быть вставлен в сам этот узел
        if (root->isleaf == 1)
            return root;
        // Если переданный корень не является листовым узлом,
        // подразумевается, что есть один или несколько детей
        else 
        {
           int i;
            ////Если передан root, исходный ключ сам по себе
            //    больше, чем элемент для вставки,
            //    нам нужно вставить в новый лист слева от корня* /
            if (k < root->key[0])
                root = searchforleaf(root->child[0], k, root, 0);
            else
            {
                // Находим первый ключ, значение которого больше
                // чем значение вставки
                // и вставить в дочерний элемент этого ключа
                for (i = 0; i < root->n; i++)
                    if (root->key[i] > k)
                        root = searchforleaf(root->child[i], k, root, i);
                // Если все ключи меньше, чем вставка
                // значение ключа, вставить справа от последнего ключа
                if (root->key[i - 1] < k)
                    root = searchforleaf(root->child[i], k, root, i);

            }

        }

    }

    else {



        // Если переданный корень равен NULL (такого нет

        // дочерний узел для поиска), затем создаем новый лист

        // узел в этом месте

        struct node* newleaf = new struct node;
        newleaf->isleaf = 1;
        newleaf->n = 0;
        parent->child[chindex] = newleaf;
        newleaf->parent = parent;
        return newleaf;
    }
}



struct node* insert(struct node* root, int k)

{

    if (root) {
        struct node* p = searchforleaf(root, k, NULL, 0);
        struct node* q = NULL;
        int e = k;
        // Если листовой узел пуст, просто
        // добавляем элемент и возвращаем
        for (int e = k; p; p = p->parent) {
            if (p->n == 0) {
                p->key[0] = e;
                p->n = 1;
                return root;
            }

            // Если количество заполненных ключей меньше максимального
            if (p->n < N - 1) {
                int i;
                for (i = 0; i < p->n; i++) {
                    if (p->key[i] > e) {
                        for (int j = p->n - 1; j >= i; j--)
                            p->key[j + 1] = p->key[j];
                        break;
                    }
                }

                p->key[i] = e;
                p->n = p->n + 1;
                return root;
            }



            // Если количество заполненных ключей равно максимальному

            // и это не root и в родительском месте есть место
            if (p->n == N - 1 && p->parent && p->parent->n < N) {
                int m;
                for (int i = 0; i < p->parent->n; i++)
                    if (p->parent->child[i] == p) {
                        m = i;
                        break;
                    }



                // Если правильный брат или сестра возможны

                if (m + 1 <= N - 1)
                {
                    // д правильный брат
                    q = p->parent->child[m + 1];
                    if (q) {
                        // Если правильный брат заполнен

                        if (q->n == N - 1) {

                           struct node* r = new struct node;
                            int* z = new int[((2 * N) / 3)];
                            int parent1, parent2;
                            int* marray = new int[2 * N];
                            int i;
                            for (i = 0; i < p->n; i++)
                                marray[i] = p->key[i];
                            int fege = i;
                            marray[i] = e;
                            marray[i + 1] = p->parent->key[m];
                            for (int j = i + 2; j < ((i + 2) + (q->n)); j++)
                                marray[j] = q->key[j - (i + 2)];



                            // marray = bubblesort (marray, 2 * N)

                            // более строгая реализация

                            // сортируем эти элементы



                            // Поместить первые (2 * N-2) / 3 элемента в ключи p

                            for (int i = 0; i < (2 * N - 2) / 3; i++)
                                p->key[i] = marray[i];
                            parent1 = marray[(2 * N - 2) / 3];



                            // Поместить следующие (2 * N-1) / 3 элемента в ключи q

                            for (int j = ((2 * N - 2) / 3) + 1; j < (4 * N) / 3; j++)
                                q->key[j - ((2 * N - 2) / 3 + 1)] = marray[j];
                            parent2 = marray[(4 * N) / 3];



                            // Поместить последние (2 * N) / 3 элемента в ключи

                            for (int f = ((4 * N) / 3 + 1); f < 2 * N; f++)

                                r->key[f - ((4 * N) / 3 + 1)] = marray[f];



                            // Поскольку m = 0 и m = 1 являются дочерними элементами одного и того же ключа,

                            // для них сделан особый случай

                            if (m == 0 || m == 1) {
                                p->parent->key[0] = parent1;
                                p->parent->key[1] = parent2;
                                p->parent->child[0] = p;
                                p->parent->child[1] = q;
                                p->parent->child[2] = r;
                                return root;
                            }



                            else {

                                p->parent->key[m - 1] = parent1;
                                p->parent->key[m] = parent2;
                                p->parent->child[m - 1] = p;
                                p->parent->child[m] = q;
                                p->parent->child[m + 1] = r;
                                return root;
                            }
                        }
                    }

                    else // Если правильный брат не заполнен
                    {
                        int put;
                        if (m == 0 || m == 1)
                            put = p->parent->key[0];
                        else
                            put = p->parent->key[m - 1];
                        for (int j = (q->n) - 1; j >= 1; j--)
                            q->key[j + 1] = q->key[j];
                        q->key[0] = put;
                        p->parent->key[m == 0 ? m : m - 1] = p->key[p->n - 1];
                    }
                }
            }
        }
        /*/ *Случаи расщепления корней и т.Д.Опущены
            так как эта реализация просто для демонстрации
            разделенная на две - три операции * /*/
    }

    else
    {

        // Создать новый узел, если root равен NULL
        struct node* root = new struct node;
        root->key[0] = k;
        root->isleaf = 1;
        root->n = 1;
        root->parent = NULL;
    }
}



int main()
{  
   
    int N;
    cin >> N;
 
    struct node* root = NULL;
    cout << "Сколько элементов ввести?"
    int l; cin << l;
    for(int i = 0;i < l; i++
    {
      int owo; cin << owo; 
      root = insert(root, owo);
    }
   

    cout << "Original tree: " << endl;
    for (int i = 0; i < root->n; i++)
        cout << root->key[i] << " ";
    cout << endl;

    return 0;
}
