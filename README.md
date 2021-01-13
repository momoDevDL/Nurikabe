# Nurikabe

building an auto-solver solution for the japanese puzzle Nurikabe ( School project )



Pour lancer le jeu :

	- Ouvrir un terminal(invite de commande) dans le dossier ou se trouve le README.
	
	- Tapez "make" pour compiler les fichiers source du projet et créer l'executable.
	
	- Puis vous pouvez lancer l'execution d'une grille avec l'option "-cfg" ou "CONFIG"
	qui se trouve dans le dossier "cfg" de la maniere suivante:
	
	       "./Nurikabe -cfg cfg/facile6.cfg "
	       
	Cette façon permet de passer un fichier de configuration contenant les infos nécessaire
	pour la création de la grille.

	Vous pouvez soit utiliser les fichiers "*.cfg" existant déjà dans le dossier
	ou bien créer vos propres grilles.

	Les fichiers de config sont classés par 3 catégorie :
	
	----->facile6.cfg    ----->medium3.cfg  ---->hard15.cfg
	----->facile14.cfg   ----->medium5.cfg  ---->hard1.cfg 
	----->facile10.cfg   ----->medium8.cfg
	
	Ces grilles sont tous Résolvable .
	
	D'autres fichiers de config contiennent des grilles sans solution :

	--->hardSS.cfg  --->facileSS.cfg

	- d'autres options existe comme :
	
	  -> afficher les auteurs "-a" .
	  -> afficher la version du programme "-v" .
	  -> afficher toute les options possible "-h"
	
	
	
