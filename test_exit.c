#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Include ta fonction
int	ft_exit(int argc, char **argv, int last_status);

int	main(void)
{
	char	*argv1[] = {"exit", "1", "2", NULL};
	int		result1;
	char	*argv2[] = {"exit", "abc", NULL};

	printf("=== Test de la fonction ft_exit ===\n\n");
	// Test 1: exit avec trop d'arguments (ne doit PAS quitter)
	printf("Test 1: exit avec trop d'arguments\n");
	result1 = ft_exit(3, argv1, 42);
	printf("Code de retour: %d (fonction n'a pas quitté)\n\n", result1);
	// Test 2: exit avec argument invalide (va quitter avec 2)
	printf("Test 2: exit avec argument invalide - va quitter!\n");
	ft_exit(2, argv2, 42);
	// Cette ligne ne sera jamais exécutée
	printf("Cette ligne ne devrait pas s'afficher\n");
	return (0);
}
