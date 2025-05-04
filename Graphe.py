import matplotlib.pyplot as plt

# Données mesurées (extraites de ton tableau)
disques = [5, 8, 10, 16, 20]
temps_iteratif = [1, 20, 74, 4874, 85456]
temps_recursif = [0, 20, 73, 5033, 87133]

# Création du graphe
plt.figure(figsize=(10, 6))
plt.plot(disques, temps_iteratif, marker='o', label='Itératif', color='blue')
plt.plot(disques, temps_recursif, marker='s', label='Récursif', color='orange')

# Personnalisation
plt.title("Temps d'exécution des algorithmes des tours de Hanoï")
plt.xlabel("Nombre de disques")
plt.ylabel("Temps (ms)")
plt.grid(True)
plt.legend()
plt.tight_layout()

# Affichage
plt.show()
