#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Node {
	int data;
	struct Node* left;
	struct Node* right;
};

struct Node* CreateTree(struct Node* root, int data)
{
	if (root == NULL)
	{
		root = (struct Node*)malloc(sizeof(struct Node));
		if (root == NULL)
		{
			printf("Ошибка выделения памяти");
			exit(0);
		}

		root->left = NULL;
		root->right = NULL;
		root->data = data;
		return root;
	}

	if (data > root->data)
	{
		root->right = CreateTree(root->right, data);
	}
	else
	{
		root->left = CreateTree(root->left, data);
	}
	return root;
}

void print_tree(struct Node* root, int l)
{
	if (root == NULL)
	{
		return;
	}

	print_tree(root->right, l + 1);
	for (int i = 0; i < l; i++)
	{
		printf(" ");
	}

	printf("%d\n", root->data);
	print_tree(root->left, l + 1);
}

// Функция подсчета количества входов определенного числа в дерево
int CountOccurrences(struct Node* root, int target)
{
	// Если в дереве нет нужного элемента
	if (root == NULL)
	{
		return 0; // Возврат 0
	}

	if (root->data == target) // Если нужный элемент найден
	{
		// Увеличиваем счётчик и проходимся по правому и левому поддереву
		return 1 + CountOccurrences(root->left, target) + CountOccurrences(root->right, target);
	}
	else if (target < root->data) // Если искомый элемент меньше текущего 
	{
		return CountOccurrences(root->left, target); // То ищем его в левом поддереве
	}
	else // Иначе 
	{
		return CountOccurrences(root->right, target); // Ищем его в правом поддереве
	}
}

int main()
{
	setlocale(LC_ALL, "RUS");
	int D, start = 1;

	struct Node* root = NULL;
	printf("\t\t\t\tВведите -10, чтобы прекратить построение дерева: \n");
	while (start)
	{
		printf("Введите число: ");
		scanf("%d", &D);
		if (D == -10)
		{
			printf("Построение дерева окончено\n\n");
			start = 0;
		}
		else
			root = CreateTree(root, D);
	}

	print_tree(root, 0);

	printf("\nВведите значение для подсчета вхождений: ");
	scanf("%d", &D); // Ввод искомого числа 

	int count = CountOccurrences(root, D); // Счетчик

	printf("\nЗначение %d встречается %d раз(а) в дереве\n", D, count);

	return 0;
}